{-# LANGUAGE OverloadedStrings #-}

import Data.Monoid
import Data.Text (Text)
import qualified Data.Text as T
import Data.Unique

--- Basically just this guide with better variable names and comments
-- https://jtobin.io/transforming-to-cps



-- create a unique, random variable name starting with $v
gensym :: IO Text
gensym = fmap render newUnique where
  render u =
    let hu = hashUnique u
    in  T.pack ("$v" <> show hu)


-- AST for lambda Calc (source)
data Expr =
    Lam Text Expr
  | Var Text
  | App Expr Expr
    deriving (Read, Show, Eq)

-- atomic expressions:
--  always produce a value and never have side effects
data AExpr =
    AVar Text                   -- variable name
  | ALam [Text] CExpr           -- [args] body
    deriving (Read, Show, Eq)


-- complex expressions:
--  function applications
data CExpr =
    CApp AExpr [AExpr]          -- invokee args
    deriving (Read, Show, Eq)

-- m: converts atomic expressions from source to atomic expressions in the target
-- t: actually CPS's the input

-- atomic translations
nm :: Expr -> IO AExpr
nm expr = case expr of
  -- if it's a lambda do cps of it
  Lam var cexpr0 -> do
    k      <- gensym                -- create a rng symbol for new continuation var?
    cexpr1 <- nt cexpr0 (AVar k)    -- cps transform body using t 
    return (ALam [var, k] cexpr1)   -- wrap into target
  
  -- Vars have direct translations
  Var var -> return (AVar var)
  
  -- Cannot handle applications
  App {} -> error "non-atomic expression"

-- transform expr into a CPS value, 
--  and then construct a call site that applies the term cont to that value
nt :: Expr -> AExpr -> IO CExpr
nt expr cont = case expr of
  -- use m to translate
  Lam {} -> do
    aexpr <- nm expr
    return (CApp cont [aexpr])   
  Var _  -> do
    aexpr <- nm expr
    return (CApp cont [aexpr])
  
  App f a -> do
    -- input: f e -- f invokes e
    -- output: (\v1 -> (\v2 -> v1 v2 cont)) f e
    
    -- symbols for function and body
    funSym <- gensym
    argSym <- gensym
    
    -- Create a lambda that takes binds the argument 
    --   and invokes bound-function with it 
    let centerBody = ALam [argSym] (CApp (AVar funSym) [AVar argSym, cont])
    putStrLn ("centerBody: " ++ show centerBody)

    -- Wrap centerBody lambda with application of argument real value
    argBody <- nt a centerBody
    putStrLn ("argBody: " ++ show argBody)

    -- Create a lambda that binds the function with body of argBody
    let funBody = ALam [funSym] argBody
    putStrLn ("funBody: " ++ show funBody)
    
    -- Wrap funBody lambda with application of function real value
    nt f funBody


main :: IO ()
main = do
  naive <- nt test (AVar "halt")
  putStrLn ("Naive: " ++ show naive)
  
  where 
    test = App (Var "g") (Var "a")
  
  
{-
-- centerBody: 
ALam ["$v2"] 
	(CApp (AVar "$v1") [AVar "$v2",AVar "halt"])
	
-- argBody:
CApp 
	(ALam ["$v2"] 
		(CApp (AVar "$v1") [AVar "$v2",AVar "halt"]))
	[AVar "a"]
	
-- funBody:
ALam ["$v1"] 
	(CApp 
		(ALam ["$v2"] 
			(CApp (AVar "$v1") [AVar "$v2",AVar "halt"])) 
		[AVar "a"])
		
-- Naive:
CApp 
	(ALam ["$v1"] 
		(CApp 
			(ALam ["$v2"] 
				(CApp 
					(AVar "$v1") 
					[AVar "$v2", AVar "halt"]))
			[AVar "a"])) 
	[AVar "g"]
-}
