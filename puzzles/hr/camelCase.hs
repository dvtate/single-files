{-# LANGUAGE DuplicateRecordFields, FlexibleInstances, UndecidableInstances #-}

module Main where

import Control.Monad
import Data.Array
import Data.Bits
import Data.List
import Data.List.Split
import Data.Set
import Data.Text
import Debug.Trace
import Data.Char (ord)
import System.Environment
import System.IO
import System.IO.Unsafe

--
-- Complete the 'camelcase' function below.
--
-- The function is expected to return an INTEGER.
-- The function accepts STRING s as parameter.
--

isUpperCase :: Char -> Bool
isUpperCase c = let oc = ord c 
    in (oc >= (ord 'A')) && (oc <= (ord 'Z'))
    
camelcase s = Data.List.foldl (\a lc -> if lc then a + 1 else a) 1 (Data.List.map isUpperCase s)
    
main :: IO()
main = do
    stdout <- getEnv "OUTPUT_PATH"
    fptr <- openFile stdout WriteMode

    s <- getLine

    let result = camelcase s

    hPutStrLn fptr $ show result

    hFlush fptr
    hClose fptr
