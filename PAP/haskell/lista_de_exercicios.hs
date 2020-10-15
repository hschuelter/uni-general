-- Lista de Exercícios de Haskell disponível em: >https://github.com/takanuva/pap<

-- 1. Escreva uma função que retorne a concatenação entre duas listas
concatena :: Eq x => [x] ->  [x] -> [x]
concatena [] l2 = l2
concatena (l1_h:l1_t) l2 = 
    l1_h : concatena l1_t l2

-- ou usando o operador > ++ <
concatena' :: Eq x => [x] -> [x] -> [x]
concatena' a b =
    a ++ b

-- 2. Escreva uma função que retorne se um elemento pertence a lista
pertence :: Eq x => x -> [x] -> Bool
pertence a [] = False
pertence a (b:c) =
    if a == b then
        True
    else
        pertence a c


-- 3. Escreva uma função que retorna a interseção de duas listas
intersecao :: Eq x => [x] -> [x] -> [x]
intersecao [] b = []
intersecao (a:as) b =
    if (pertence a b) then
        a : intersecao as b
    else
        intersecao as b
        
-- 4. Escreva uma função que retorna o inverso de uma lista
inverso :: Eq x => [x] -> [x]
inverso [] = []
inverso (a:as) = concatena (inverso as) [a]


-- 5. Escreva uma função que retorne os n primeiros elementos de uma lista
primeiros :: Int -> [x] -> [x]
primeiros 0 a = []
primeiros n [] = []
primeiros n (a:as) = 
    a : primeiros (n-1) as

-- 6. Escreva uma função que retorne os n últimos elementos de uma lista
ultimos :: Eq x => Int -> [x] -> [x]
ultimos 0 a = []
ultimos n [] = []
ultimos n (a:as) = 
    inverso ( primeiros n (inverso (a:as)) )

-- ou usando a função > remover (similar a drop) < 
-- que remove os n primeiros elementos de uma lista
ultimos' :: Int -> [x] -> [x]
ultimos' 0 lista  = []
ultimos' num [] = []
ultimos' num lista = 
    -- drop (  length lista - num ) lista
    remover ( tamanho lista - num ) lista

-- 7. Escreva uma função que converta um número binário,
--    representado como uma string, em um número inteiro:
binParaInt :: String -> Int
binParaInt ('0':[]) = 0
binParaInt ('1':[]) = 1
binParaInt ('0':cs) = binParaInt cs
binParaInt ('1':cs) = 2 ^ (tamanho cs) + binParaInt cs

-- 8. Escreva uma função que converta um número inteiro
--    para um número binário, representado como uma string
intParaBin :: Int -> String
intParaBin x =
    inverso (auxiliar x)
    where
        auxiliar 0 = "0"
        auxiliar 1 = "1"
        auxiliar x =
            if x `mod` 2 == 0 then
                '0' : auxiliar (x `div` 2)
            else
                '1' : auxiliar (x `div` 2)

-- 9. Escreva uma função que retorna o menor valor de uma 
--    lista
menorValor :: Ord a => [a] -> a
menorValor (x:[]) = x
menorValor (x:xs) = 
    if x < (menorValor xs) then
        x
    else
        menorValor xs


-- 10. Escreva uma função que receba uma lista e um 
--     elemento e retorne a lista sem a primeira ocorrência 
--     desse elemento:
removerPrimeiro :: Eq a => [a] -> a -> [a]
removerPrimeiro [] y = []
removerPrimeiro (x:xs) y = 
    if x == y then
        xs
    else
        x : removerPrimeiro xs y

-- 11. Escreva uma função, utilizando os exercícios 
--     anteriores, que ordele os elementos de uma lista:
ordenar :: Ord a => [a] -> [a]
ordenar [] = []
ordenar lista = 
    menorValor lista : ordenar ( removerPrimeiro lista (menorValor lista))

-- 12. Escreva uma função que dobre uma lista pela direita,
-- lembrando que: 
-- dobrar_dir f x [a, b, c] = f a (f b (f c x))
dobrar_dir :: (a -> b -> b) -> b -> [a] -> b
dobrar_dir f y [] = y
dobrar_dir f y (x:xs) = 
    f x (dobrar_dir f y xs)

-- 13. Escreva uma função que dobre uma lista pela esquerda,
-- lembrando que: 
-- dobrar_esq f x [a, b, c] = f (f (f x a) b) c
dobrar_esq :: (b -> a -> b) -> b -> [a] -> b
dobrar_esq f y [] = y
dobrar_esq f y (x:xs) = 
    dobrar_esq f (f y x) xs

-- 14. Escreva uma função que filtre uma lista, retornando os
-- elementos que satisfazem um predicado:
filtrar :: (a -> Bool) -> [a] -> [a]
filtrar f [] = []
filtrar f (x:xs) = 
    if (f x) then
        x : (filtrar f xs)
    else
        filtrar f xs


--  15. Usando a função anterior, escreva uma função que receba
--  uma lista e retorne seus elementos ímpares:
impares :: [Int] -> [Int]
impares list =
    filtrar (is_impar) list


--  16. Escreva uma função que mapeie todos os elementos de uma
--  lista de acordo com uma função:
mapear :: (a -> b) -> [a] -> [b]
mapear f [] =
    []
mapear (f) (x:xs) =
    (f x) : (mapear (f) xs)

--  17. Usando a função anterior, escreva uma função que receba
--  uma lista de duplas, e retorne uma lista com os primeiros itens:
primeiros_dupla :: [(a, b)] -> [a]
primeiros_dupla [] = []
primeiros_dupla ( (a,b):xs ) =
    [a] ++ primeiros_dupla xs

--  18. Escreva uma função que receba uma lista de booleanos e
--  retorne se todos são verdadeiros, utilizando uma das funções
--  de dobra anteriores:
todos :: [Bool] -> Bool
todos [] = False
todos (x:xs) =
    dobrar_esq (funcao_and) x xs


--  19. Considere o tipo de dados abaixo:
data Tree a = Leaf a
            | Branch (Tree a) (Tree a)
--  Escreva uma função que encontra o maior item de uma árvore:
--         maior :: Ord a => Tree a → a

maior_item_tree :: Ord a => Tree a -> a
maior_item_tree (Leaf x) = x
maior_item_tree (Branch x y) =
    if (maior_item_tree x) > (maior_item_tree y ) then
        maior_item_tree x
    else
        maior_item_tree y

--  20. Considere o tipo acima; escreva uma função que retorna a altura de uma árvore:
altura_tree :: Tree a -> Int
altura_tree (Leaf a) = 0
altura_tree (Branch a b) =
    if (altura_tree a) > (altura_tree b) then
        1 + altura_tree a
    else
        1 + altura_tree b

tree_ex0 = Branch (Leaf 10) (Leaf 20)
tree_ex1 = Branch (Leaf 10) (Branch (Leaf 20) (Leaf 30))
tree_ex2 = Branch (Branch (Leaf 5) (Leaf 15)) (Branch (Leaf 20) (Branch (Leaf 5) (Leaf 15)))

----------------------------------------------------------
--      ======== Funções auxiliares ========

-- Tamanho da lista
tamanho :: [x] -> Int
tamanho [] = 0
tamanho (a:as) = 
    1 + tamanho(as)

-- Remove elementos
remover :: Int -> [x] -> [x]
remover 0 list = list
remover n (a:as) = 
    remover (n-1) as

-- Resto da divisão
modulo :: Int -> Int -> Int
modulo a b = 
    if( a >= b ) then
        modulo (a-b) b
    else
        a

-- Retorna se um número é maior que dois
maior_que_dois :: Int -> Bool
maior_que_dois x = 
    x > 2


-- dobrar (\a \b a + b) [1, 2, 3, 4] =
--   1 + 2 + 3 + 4
dobrar :: (a -> a -> a) -> [a] -> a
dobrar f (x:[]) = x
dobrar f (x1:x2:[]) = f x1 x2
dobrar f (x:xs) =
    f x (dobrar f xs)

-- Verifica que o numero é ímpar:
is_impar :: Int -> Bool
is_impar x =
    (modulo x  2 /= 0)

-- Função AND:
funcao_and :: Bool -> Bool -> Bool
funcao_and a b =
    a && b
            
----------------------------------------------------------

-- 09/16
data Arvore a = Folha a
              | Galho (Arvore a) (Arvore a)
              deriving Show

-- Folha :: a -> Arvore a
-- Galho :: Arvore a -> Arvore a -> Arvore a

exemplo0 = Galho (Folha 10) (Folha 20)
exemplo1 = Galho (Folha 10) (Galho (Folha 20) (Folha 30))
exemplo2 = Galho (Galho (Folha 5) (Folha 15)) (Galho (Folha 20) (Galho (Folha 5) (Folha 15)))

altura :: Arvore a -> Int
altura (Folha a) = 0
altura (Galho a b) = 
    if (altura a) > (altura b) then
        1 + altura a
    else
        1 + altura b

maior_item :: Ord a => Arvore a -> a
maior_item (Folha x) = x
maior_item (Galho x y) = 
    if (maior_item x) > (maior_item y ) then
        maior_item x
    else
        maior_item y


tamanho_arvore :: Arvore a -> Int
tamanho_arvore (Folha a) = 1
tamanho_arvore (Galho a b) = 
    (tamanho_arvore a) + (tamanho_arvore b)

converte :: Ord a => [a] -> Arvore a
converte (x:[]) = Folha x
converte lista =
    let menor_item = menorValor lista in
    Galho (Folha menor_item) (converte (removerPrimeiro lista menor_item))

instance Functor Arvore where
    -- fmap :: (a -> b) -> Arvore a -> Arvore b
    fmap f (Folha a) = Folha (f a)
    fmap f (Galho a b) = 
        Galho (fmap f a) (fmap f b)

exemplo3 = fmap (* 2) exemplo2


----------------------------------------------------------

quicksort :: [Int] -> [Int]
quicksort [] = []
quicksort (x:xs) = 
    quicksort (filtrar (<x) xs ) ++ [x] ++ quicksort (filtrar (>=x) xs )

