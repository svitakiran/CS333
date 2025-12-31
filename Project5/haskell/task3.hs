{- Impelementing a word counter that can count the number of occurences of every word
in a text file in Haskell

Svita Kiran
CS333
11/13/2025
-}

import System.Environment (getArgs)
import Data.Char (isAlpha, toLower)
import Data.List (sortOn)
import qualified Data.Map.Strict as Map

-- make all characters lowercase
normalize :: String -> String
normalize = map toLower . filter isAlpha

-- count words using Map
countWords :: [String] -> Map.Map String Int
countWords = foldr (\w -> Map.insertWith (+) w 1) Map.empty

-- print top frequency words
printTop :: Int -> Map.Map String Int -> IO ()
printTop n m = mapM_ printWord $ take n sorted
  where
    sorted = reverse $ sortOn snd $ Map.toList m
    printWord (w, c) = putStrLn $ w ++ "\t" ++ show c

main :: IO ()
main = do
    args <- getArgs
    case args of
        [filename] -> do
            content <- readFile filename
            let wordsList = map normalize $ words content
            let freqMap = countWords wordsList
            printTop 20 freqMap
        _ -> putStrLn "Usage: runhaskell WordCount.hs <filename>"