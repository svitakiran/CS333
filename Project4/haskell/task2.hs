{- implementing a linked list in go making use of some polymorphism to implement the
data structure 

Svita Kiran
CS333
10/30/2025
-}

data LinkedList a = Empty | Node a (LinkedList a)
    deriving Show

llCreate :: LinkedList a
llCreate = Empty

llPush :: a -> LinkedList a -> LinkedList a
llPush x xs = Node x xs

llPop :: LinkedList a -> (Maybe a, LinkedList a)
llPop Empty = (Nothing, Empty)
llPop (Node x xs) = (Just x, xs)

llAppend :: a -> LinkedList a -> LinkedList a
llAppend x Empty = Node x Empty
llAppend x (Node y ys) = Node y (llAppend x ys)

llFind :: (a -> Bool) -> LinkedList a -> Maybe a
llFind _ Empty = Nothing
llFind pred (Node x xs)
    | pred x    = Just x
    | otherwise = llFind pred xs

llRemove :: (a -> Bool) -> LinkedList a -> (Maybe a, LinkedList a)
llRemove _ Empty = (Nothing, Empty)
llRemove pred (Node x xs)
    | pred x    = (Just x, xs)
    | otherwise = let (res, rest) = llRemove pred xs
                  in (res, Node x rest)

llSize :: LinkedList a -> Int
llSize Empty = 0
llSize (Node _ xs) = 1 + llSize xs

llMap :: (a -> b) -> LinkedList a -> LinkedList b
llMap _ Empty = Empty
llMap f (Node x xs) = Node (f x) (llMap f xs)

llClear :: LinkedList a -> LinkedList a
llClear _ = Empty


-- test program
main :: IO ()
main = do
    let list1 = llPush 1 $ llPush 2 $ llPush 3 llCreate
    print list1
    print $ llSize list1
    print $ llFind (==2) list1

    let list2 = llPush "car" $ llPush "bike" llCreate
    print list2
    print $ llFind (=="car") list2

    let list2Appended = llAppend "train" list2
    print $ llMap (++"!") list2Appended