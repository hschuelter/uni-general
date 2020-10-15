data Tree a = Leaf a
            | Node (Tree a) (Tree a)
            deriving Show

main :: IO()
main = do
    putStrLn "Hello, World"
    putStrLn "Diga o seu nome:"
    nome <- getLine
    putStrLn ( "Olá, " ++ nome )



teste1 :: [Int]
teste1 = [1,2,3] >>=
    (\x -> [4,5,6] >>=
        \y -> return (x+y))
    
teste2 :: [Int]
teste2 = do
    x <- [1,2,3]
    y <- [4,5,6]
    return (x+y)

teste3 :: [Int]
teste3 = do
    x <- [1,2,3]
    y <- [4,5,6]
    return (x*y)

find_min :: [Int] -> Int
find_min (x:[]) = x
find_min (x:xs) = 
    if (x < find_min xs) then
        x
    else
        find_min xs

find_max :: [Int] -> Int
find_max (x:[]) = x
find_max (x:xs) = 
    if (x > find_max xs) then
        x
    else
        find_max xs
    
lista_para_arvore :: [Int] -> Tree Int
lista_para_arvore (x:[]) = Leaf x
lista_para_arvore (x:xs) = 
    Node ( Leaf x ) ( lista_para_arvore xs )

remove_elemento :: Int -> [Int] -> [Int]
remove_elemento x [] = []
remove_elemento x (y:ys) = 
    if x == y then
        ys
    else 
        y : (remove_elemento x ys)

lista_para_arvore_ordenada ::  [Int] -> Tree Int
lista_para_arvore_ordenada (x:[]) = Leaf x
lista_para_arvore_ordenada x =
    Node ( Leaf (find_min x) ) ( lista_para_arvore_ordenada (remove_elemento (find_min x) x) )
