{- Program that automatically detects garbage collections from the timing information
 in Haskell (Haskell has automatic memory management)

Svita Kiran
CS333
11/13/2025
-}

import Control.DeepSeq (deepseq, NFData)
import System.CPUTime
import Text.Printf

-- allocate memory
allocateMemory :: Int -> [Int]
allocateMemory n = [1..n]

-- time function call
timeAction :: NFData a => IO a -> IO (a, Double)
timeAction action = do
    start <- getCPUTime
    result <- action
    result `deepseq` return ()  -- force evaluation
    end <- getCPUTime
    let diff = fromIntegral (end - start) / 1e12 :: Double  -- seconds
    return (result, diff)

-- iterations
iterations :: Int
iterations = 100

main :: IO ()
main = do
    let size = 1000000
    times <- mapM (\_ -> snd <$> timeAction (return $ allocateMemory size)) [1..iterations]
    let avgTime = sum times / fromIntegral iterations
    putStrLn $ "average time: " ++ show avgTime ++ " s"

    mapM_ (\(i :: Int, t :: Double) ->
               if t > 2 * avgTime
               then printf "iteration %d: %.6f s\n" i t
               else return ()) (zip [1..] times)