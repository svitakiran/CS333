{-
simple parallel PPM colorize in Haskell
Svita Kiran
CS333
12/5/25
-}


import System.Environment
import Data.Word
import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as BC
import Control.Concurrent
import Control.Monad
import System.CPUTime

type Pixel = (Word8, Word8, Word8)

-- Pixel-wise operator
colorize :: Pixel -> Pixel
colorize (r,g,b) = (f r, f g, f b)
  where
    f x = if x > 128 then fromIntegral ((220 + fromIntegral x) `div` 2)
                      else fromIntegral ((30 + fromIntegral x) `div` 2)

-- Split list into chunks
chunksOf :: Int -> [a] -> [[a]]
chunksOf _ [] = []
chunksOf n xs = let (h,t) = splitAt n xs in h : chunksOf n t

main :: IO ()
main = do
    args <- getArgs
    case args of
      [filename, threadsStr] -> do
        let numThreads = read threadsStr :: Int

        -- Read PPM file (P6)
        content <- B.readFile filename
        let ls = BC.lines content
        let header = take 3 ls
        let w = read (BC.unpack ((BC.words (ls !! 1)) !! 0)) :: Int
        let h = read (BC.unpack ((BC.words (ls !! 1)) !! 1)) :: Int
        let pixelsData = B.drop (B.length (B.concat header) + 1) content
        let pixels = [(pixelsData `B.index` i,
                       pixelsData `B.index` (i+1),
                       pixelsData `B.index` (i+2)) | i <- [0,3..B.length pixelsData -3]]

        let chunkSize = (length pixels + numThreads -1) `div` numThreads
        let chunks = chunksOf chunkSize pixels

        -- Create MVar to collect results
        resultVar <- newEmptyMVar

        -- Start timing
        start <- getCPUTime

        -- Spawn threads
        forM_ chunks $ \chunk -> forkIO $ do
            let processed = map colorize chunk
            putMVar resultVar processed

        -- Collect results
        results <- replicateM (length chunks) (takeMVar resultVar)
        let finalPixels = concat results

        end <- getCPUTime
        let elapsed = fromIntegral (end - start) / 1e12
        putStrLn $ "threads: " ++ show numThreads ++ ", time: " ++ show elapsed ++ " secs"

        -- Write output
        let headerOut = BC.unlines header
        let pixelsOut = B.pack $ concat [[r,g,b] | (r,g,b) <- finalPixels]
        B.writeFile "hsmod.ppm" (B.append headerOut pixelsOut)

      _ -> putStrLn "Usage: runhaskell hscolorize.hs <image.ppm> <threads>"
