{-# LANGUAGE DuplicateRecordFields, FlexibleInstances, UndecidableInstances #-}
-- https://www.hackerrank.com/challenges/migratory-birds
module Main where

import Control.Monad
import Data.Array
import Data.Bits
import Data.List
import Data.List.Split
import Data.Set
import Data.Text
import Data.Map
import Debug.Trace
import System.Environment
import System.IO
import System.IO.Unsafe


--
-- Complete the 'migratoryBirds' function below.
--
-- The function is expected to return an INTEGER.
-- The function accepts INTEGER_ARRAY arr as parameter.
--



migratoryBirds arr = let
    -- add bird to map
    recordBird m species =
        let count = Data.Map.findWithDefault 0 species m
        in Data.Map.insert species (count + 1) m
    
    -- convert map into list of (species, count) pairs
    fm = Prelude.foldl recordBird (Data.Map.empty :: Map Int Int) arr
    fml = Data.List.zip (Data.Map.keys fm) (Data.Map.elems fm)
    
    -- comparison function between two pairs
    pickMax (sa, ca) (sb, cb) = 
        if ca > cb || (ca == cb && sa < sb) then (sa, ca) 
        else (sb, cb)
        
    in
        fst (Prelude.foldl pickMax (Data.List.head fml) (Data.List.tail fml))
        

lstrip = Data.Text.unpack . Data.Text.stripStart . Data.Text.pack
rstrip = Data.Text.unpack . Data.Text.stripEnd . Data.Text.pack

main :: IO()
main = do
    stdout <- getEnv "OUTPUT_PATH"
    fptr <- openFile stdout WriteMode

    arrCountTemp <- getLine
    let arrCount = read $ lstrip $ rstrip arrCountTemp :: Int

    arrTemp <- getLine

    let arr = Data.List.map (read :: String -> Int) . Data.List.words $ rstrip arrTemp

    let result = migratoryBirds arr

    hPutStrLn fptr $ show result

    hFlush fptr
    hClose fptr
