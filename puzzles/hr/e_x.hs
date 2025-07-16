{-# LANGUAGE FlexibleInstances, UndecidableInstances, DuplicateRecordFields #-}

module Main where

import Control.Monad
import Data.Array
import Data.Bits
import Data.List
import Data.List.Split
import Debug.Trace
import System.Environment
import System.IO
import System.IO.Unsafe

fac 0 = 1
fac n = n * fac (n - 1)
term x n = (x ** n) / (fac n)
series x = foldl (+) 0 (map (term x) [0..9])

main :: IO()
main = do
    n <- readLn :: IO Int

    forM_ [1..n] $ \n_itr -> do
        x <- readLn :: IO Double
        (putStrLn . show . series) x 
