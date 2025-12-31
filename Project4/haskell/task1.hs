{- Implementing a bubble sort algorithm in Go that can be used for any type and to obtain
any desired order

Svita Kiran
CS333
10/30/2025
-}

quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    let smallerSorted = quicksort [a | a <- xs, a <= x]
        biggerSorted  = quicksort [a | a <- xs, a > x]
    in smallerSorted ++ [x] ++ biggerSorted

main :: IO ()
main = do
    -- Sorting integers
    let nums = [5, 2, 9, 1, 6]
    print $ quicksort nums
    
    -- Sorting strings
    let wordsList = ["car", "bike", "train"]
    print $ quicksort wordsList