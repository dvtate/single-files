/// Planning for DAGGIR - a DAG-based Generic IR

////////////////////////////////////////////////////////////
// Convert IR to WASM
////////////////////////////////////////////////////////////

// This can be useful for generating errors and/or debugging
interface CodeLocation {
    name?: string;
    description?: string;
    file?: string;
    charIndex?: number;
    lineNumber?: number;
    linePosition?: number;
    end?: CodeLocation;
}

abstract class Target {
    abstract basicTypes(): string;
    abstract addExport(fn: Expr, name?: string): void;
}

type TargetDataType = string;

abstract class TargetInstruction {
    /**
     * @constructor 
     * @param name mnemonic
     * @param args list of immediates and/or nested instructions that
     *      the target determines the best way to combine instructions
     * @param source optional debug info
     */
    constructor(
        public name: string,
        public args: Array<string | TargetInstruction> = [],
        public datatype: string[],
        public source?: Expr[]
    ) {}
}

abstract class TargetFunctionLocal {
    expr: Expr;
    fun: TargetFunction;
    abstract get(): TargetInstruction[];
    abstract set(input: TargetInstruction): TargetInstruction[];
    tee(input: TargetInstruction): TargetInstruction[] {
        return [...this.set(input), ...this.get() ];
    }
    abstract free(): TargetInstruction[];
}

abstract class TargetFunction {
    params: TargetFunctionLocal[];
    body: Expr;
    abstract addLocal(type: TargetDataType, expr: Expr): TargetFunctionLocal;
    addLocals(types: TargetDataType[], expr: Expr): TargetFunctionLocal[] {
        return types.map(t => this.addLocal(t, expr));
    }

    isTailRecursive(): boolean {
        // TODO
    }
}

////////////////////////////////////////////////////////////
// DAG IR Definition
//
////////////////////////////////////////////////////////////

enum ExprConnectionType {
    /// Expressions that must be compiled before this one in order for it to be valid
    Depends,
    
    /// Expressions used as data I/O
    Input,
    Output,
}

/**
 * The compiler can extend this class and do operations on it.
 */
class ExprConnection {
    constructor(
        public type: ExprConnectionType,
        public origin: Expr,
        public index = 0,
        public dataType?: TargetDataType,
    ) {}
}

class CachedResult {
    /**
     * @param locals Locals that store the result, also contain reference to parent expr
     * @param scope Scope within which this cached result is valid
     */
    constructor(
        public locals: TargetFunctionLocal[],
        public scope: Expr,
    ) {}

    get(): TargetInstruction[] {
        return [].concat(...this.locals.map(l => l.get()));
    }
}

class ExprScope {
    locals: TargetFunctionLocal[][] = [[]];
    scopes: Expr[] = [null];
    
    push(e: Expr) {
        this.scopes.push(e);
        this.locals.push([]);
    }

    current(): Expr {
        return this.scopes[this.scopes.length - 1];
    }

    pop(): TargetInstruction[] {
        if (this.scopes.pop() === null)
            throw new Error("Cannot pop top level scope");
        return [].concat(...this.locals.pop().map(l => l.free()));
    }

    findCache(crs: CachedResult[]): CachedResult {
        return crs.find(cr => this.scopes.includes(cr.scope));
    }
}

abstract class Expr {
    /**
     * Ordered depends, inputs, outputs
     */
    depends: ExprConnection[];
    inputs: ExprConnection[];
    outputs: ExprConnection[];

    /// Optional debugging info
    codeLocation?: CodeLocation[];

    /// Result caching
    cache: CachedResult[] = [];
    alwaysCache: boolean;
    // Problem: if we're allowing mutation of locals/params that could result in different values?

    /// Have we already compiled the depends exprs?
    dependsCompiled = false;

    constructor(
        depends: Expr[] = [],
        inputs: ExprConnection[] = [],
        outputs: number = 1,
        alwaysCache = false
    ) {
        this.depends = depends.map((e, i) =>
            new ExprConnection( ExprConnectionType.Depends, e, i ));
        this.inputs = inputs.map((c, i) =>
            new ExprConnection( ExprConnectionType.Input, c.origin, i, c.dataType ));

        this.outputs = [];
        for (let i = 0; i < outputs; i++)
            this.outputs.push(new ExprConnection( ExprConnectionType.Output, this, i));

        this.alwaysCache = alwaysCache || outputs > 1 || inputs.length > 1;
    }

    abstract outBody(fun: TargetFunction, scope: ExprScope): TargetInstruction[];

    out(fun: TargetFunction, scope: ExprScope): TargetInstruction[] {
        const ret: TargetInstruction[] = [];

        // Compile depends if needed
        if (!this.dependsCompiled)
            ret.push(...[].concat(...this.depends.map(e => e.origin.out(fun, scope))));
        
        // Use cache if available
        const cachedResult = scope.findCache(this.cache);
        if (cachedResult) {
            ret.push(...cachedResult.get());
            return ret;
        }

        // Compile body
        const outInstrs = this.outBody(fun, scope);

        // Set cache if necessary
        if (this.alwaysCache) {
            // If cache, tee body into locals
            const cr = new CachedResult(
                [].concat(...outInstrs.map(instr =>
                    fun.addLocals(instr.datatype, this))),
                scope.current(),
            );
            this.cache.push(cr);
            cr.locals.map((l, i) => l.tee(outInstrs[i]))
                .forEach(instrs => ret.push(...instrs));
            // problem: leaving them on stack like this would require careful planning?
            // instead: outputs should have this as dependant
        } else {
            ret.push(...outInstrs);
        }

        return ret;
    }
}


// Branch expr should find expressions used by all branches and compute those in parent scope
// 
