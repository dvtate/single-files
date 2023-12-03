'use strict';

import { WriteStream, createWriteStream } from "fs";
process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString: string = '';
let inputLines: string[] = [];
let currentLine: number = 0;

process.stdin.on('data', function(inputStdin: string): void {
    inputString += inputStdin;
});

process.stdin.on('end', function(): void {
    inputLines = inputString.split('\n');
    inputString = '';

    main();
});

function readLine(): string {
    return inputLines[currentLine++];
}

// Should do this in C++ so that perf is better
function setCharAt(str: string,index: number, chr: string): string {
    if (index > str.length - 1) return str;
    return str.substring(0, index) 
        + chr 
        + str.substring(index + 1);
}


/*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */
function bomberMan(n: number, grid: string[]): string[] {
    // naive implementation
    
    // after one second bm does nothing
    n--;
    if (n <= 0)
        return grid;
    
    // releat 3 and 4 indefinitely 
    // this means that only the first set of bombs explode after 3 seconds
    //  the others explode after 2 seconds
    //  the guide is wrong and overly verbose 
    for (;;) {
        
        // another second and he places all the bombs
        n--;
        const oldGrid = grid.slice();
        grid = grid.map(r => 'O'.repeat(r.length));
        if (n <= 0)
            return grid;
        
        // simulate bomb explosions destroying neighbors
        function kaboom(oldGrid: string[], newGrid: string[]) {
            const maxY = oldGrid.length - 1;
            const maxX = oldGrid[0].length - 1;
            oldGrid.forEach((row, y) => {
                for (let x = 0; x < row.length; x++) {
                    if (row[x] === 'O') {
                        newGrid[y] = setCharAt(newGrid[y], x, '.');
                        if (x !== 0)
                            newGrid[y] = setCharAt(newGrid[y], x - 1, '.');
                        if (x < maxX)
                            newGrid[y] = setCharAt(newGrid[y], x + 1, '.');
                        if (y !== 0)                            
                            newGrid[y - 1] = setCharAt(newGrid[y - 1], x, '.');
                        if (y < maxY)                            
                            newGrid[y + 1] = setCharAt(newGrid[y + 1], x, '.');
                    }
                }
            });
        }
        
        // another second and the old bombs explode
        n--;
        kaboom(oldGrid, grid);
        if (n <= 0)
            return grid;
    }
}

function main() {
    const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

    const firstMultipleInput: string[] = readLine().replace(/\s+$/g, '').split(' ');

    const r: number = parseInt(firstMultipleInput[0], 10);

    const c: number = parseInt(firstMultipleInput[1], 10);

    const n: number = parseInt(firstMultipleInput[2], 10);

    let grid: string[] = [];

    for (let i: number = 0; i < r; i++) {
        const gridItem: string = readLine();
        grid.push(gridItem);
    }

    const result: string[] = bomberMan(n, grid);

    ws.write(result.join('\n') + '\n');

    ws.end();
}
