module DeBruijn where


-------------------------

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
    | x == y    = x : merge xs ys
    | x <= y    = x : merge xs (y:ys)
    | otherwise = y : merge (x:xs) ys

msort :: Ord a => [a] -> [a]
msort []  = []
msort [x] = [x]
msort xs  = merge (msort (take n xs)) (msort (drop n xs))
  where
    n = div (length xs) 2


-------------------------

type Var = String

data Term =
    Variable Var
  | Lambda   Var  Term
  | Apply    Term Term

instance Show Term where
  show = f 0
    where
      f i (Variable x) = x
      f i (Lambda x m) = if i /= 0 then "(" ++ s ++ ")" else s where s = "\\" ++ x ++ ". " ++ f 0 m 
      f i (Apply  n m) = if i == 2 then "(" ++ s ++ ")" else s where s = f 1 n ++ " " ++ f 2 m

example1 :: Term
example1 = Lambda "a" (Lambda "x" (Apply (Apply (Lambda "y" (Apply (Variable "a") (Variable "c"))) (Variable "x")) (Variable "b")))

numeral :: Int -> Term
numeral i = Lambda "f" (Lambda "x" (numeral' i))
  where
    numeral' i
      | i <= 0    = Variable "x"
      | otherwise = Apply (Variable "f") (numeral' (i-1))

variables :: [String]
variables = map (:[]) ['a'..'z'] ++ [ x : show i | i <- [1..] , x <- ['a'..'z'] ]

free :: Term -> [Var]
free (Variable x) = [x]
free (Lambda x n) = filter (/=x) (free n)
free (Apply  n m) = merge (free n) (free m)

------------------------- Assignment 1

data TermDB = 
    VariableDB Int
  | LambdaDB TermDB
  | ApplyDB TermDB TermDB
--  deriving Show
--  deriving Eq
  
instance Show TermDB where
  show = f 0
    where
      f i (VariableDB x) = show x
      f i (LambdaDB m)   = if i /= 0 then "(" ++ s ++ ")" else s where s = "\\. " ++ f 0 m 
      f i (ApplyDB n m)  = if i == 2 then "(" ++ s ++ ")" else s where s = f 1 n ++ " " ++ f 2 m
    {-
      f i (VariableDB x) = "$" ++ show x
      f i (LambdaDB body) = "{ " ++ (f i body) ++ " }"
      f i (ApplyDB n m) = (f i n) ++ "(" ++ (f i m) ++ ")"
    -}
example2 :: TermDB
example2 = LambdaDB (ApplyDB (LambdaDB (LambdaDB (ApplyDB (VariableDB 1) (ApplyDB (LambdaDB (VariableDB 0)) (VariableDB 5))))) (ApplyDB (LambdaDB (VariableDB 1)) (VariableDB 1)))

depth :: TermDB -> Int
depth = depth' 0
  where -- tail-recursive helper
    depth' ret (LambdaDB body) = depth' (ret + 1) body
    depth' ret (VariableDB _) = ret
    depth' ret (ApplyDB a b) = if depthA > depthB then depthA else depthB
      where 
        depthA = depth' ret a
        depthB = depth' ret b

------------------------- Assignment 2

-- bound ids -> free ids -> db term -> named term
giveNames :: [Var] -> [Var] -> TermDB -> Term
giveNames a b (VariableDB i) = Variable (b !! i)
giveNames (x : a) b (LambdaDB body) = Lambda x (giveNames a (x : b) body)
giveNames a b (ApplyDB n m) = Apply (giveNames a b n) (giveNames a b m)

named :: TermDB -> Term
named term = giveNames (take termDepth variables) (drop termDepth variables) term
  where termDepth = depth term

------------------------- Assignment 3

indexOf :: Eq a => a -> [a] -> Int
indexOf needle haystack = indexOf' 0 haystack
  where
    indexOf' i (e : l) = if e == needle then i else indexOf' (i + 1) l
    indexOf' i [] = error "item not in list"

deBruijnList :: [Var] -> Term -> TermDB
deBruijnList vars (Variable s) = VariableDB (indexOf s vars)
deBruijnList vars (Lambda s body) = LambdaDB (deBruijnList (s : vars) body)
deBruijnList vars (Apply a b) = ApplyDB (deBruijnList vars a) (deBruijnList vars b)

deBruijn :: Term -> TermDB
deBruijn term = deBruijnList (freeVars [] term) term
  where
    -- Generate a list of free vars
    freeVars vars (Lambda s body) = freeVars (s : vars) body
    freeVars vars (Apply a b) = (freeVars vars b) ++ (freeVars vars a)
    freeVars vars (Variable s) = if s `elem` vars then [] else [s]

------------------------- Assignment 4

lift :: Int -> TermDB -> TermDB
lift n term = lift' 0 term
  where
    lift' depth (VariableDB id) = if id >= depth 
      then VariableDB (id + n) 
      else VariableDB id
    lift' depth (LambdaDB body) = LambdaDB (lift' (depth + 1) body)
    lift' depth (ApplyDB a b) = ApplyDB (lift' depth a) (lift' depth b)

-- substitute id n in term with replacement
substitute :: Int -> TermDB -> TermDB -> TermDB
substitute id replacement (VariableDB var)
  | var  < id = VariableDB var        -- keep free variable
  | var == id = replacement           -- replace
  | var >  id = VariableDB (var - 1)  -- decrease bound variable
substitute id repl (ApplyDB a b) = ApplyDB (substitute id repl a) (substitute id repl b)
substitute id repl (LambdaDB body) = LambdaDB (substitute (id + 1) (lift 1 repl) body)


beta :: TermDB -> [TermDB]
beta term = [red term, red $ red $ term, red $ red $ red $ term]
  where 
    red (VariableDB a) = VariableDB a
    red (LambdaDB a) = LambdaDB (red a)
    red (ApplyDB (LambdaDB body) value) = red (substitute 0 value body)
    red (ApplyDB a b) = ApplyDB (red a) (red b)

normalize :: TermDB -> IO ()
normalize term = case beta term of
  [] -> return ()
  (h:t) -> putStrLn $ show $ h

------------------------- Assignment 5

-- Note: in examples it's negated
isalpha :: Term -> Term -> Bool
isalpha terma termb = isalpha' (deBruijn terma) (deBruijn termb)
  where
    isalpha' (LambdaDB a) (LambdaDB b) = isalpha' a b
    isalpha' (ApplyDB a1 b1) (ApplyDB a2 b2) = (isalpha' a1 a2) && (isalpha' b1 b2)
    isalpha' (VariableDB a) (VariableDB b) = a /= b
    isalpha' a b = True
