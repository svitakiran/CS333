{- Error handling in Haskell

Svita Kiran
CS333
11/13/2025
-}

import System.IO
import System.IO.Error (catchIOError)
import Control.Exception (catch, SomeException)
import Text.Read (readMaybe)

fileDemo :: IO ()
fileDemo = do
    putStrLn "file I/O error"
    content <- catchIOError (readFile "dne.txt")
                            (\e -> do
                                putStrLn ("error opening file: " ++ show e)
                                return "")
    if null content
        then putStrLn "file read failed\n"
        else putStrLn ("file contents:\n" ++ content)


safeDivide :: Int -> Int -> Maybe Int
safeDivide _ 0 = Nothing
safeDivide a b = Just (a `div` b)

divideDemo :: IO ()
divideDemo = do
    putStrLn "division error"
    case safeDivide 10 0 of
        Nothing -> putStrLn "error: divide by zero\n"
        Just r  -> putStrLn ("result: " ++ show r)


main :: IO ()
main = do
    fileDemo
    divideDemo
