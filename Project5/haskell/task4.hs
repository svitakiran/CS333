{- How to read from and write to a file in Haskell

Svita Kiran
CS333
11/13/2025
-}

import System.IO

main :: IO ()
main = do
    writeFile "hstask4.txt" "This is a file I/O for task 4 with haskell"

    contents <- readFile "hstask4.txt"
    putStrLn "reading file:"
    putStrLn contents
