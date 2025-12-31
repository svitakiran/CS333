{- Memory management in Haskell

Svita Kiran
CS333
11/13/2025
-}

module Main where

makeLargeList :: Int -> Int
makeLargeList n =
    let bigList = [1..n]
    in length bigList

stressMemory :: Int -> IO ()
stressMemory 0 = putStrLn "done"
stressMemory n = do
    let val = makeLargeList 500000
    val `seq` return ()
    stressMemory (n - 1)

main :: IO ()
main = do
    putStrLn "memory stress test"
    stressMemory 5
