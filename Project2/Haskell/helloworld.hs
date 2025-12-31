main :: IO()
main = printhello 5

printhello :: Int -> IO ()
printhello 0 = return ()
printhello n = do
    putStrLn "hello world!"
    printhello (n - 1)