-- Pegar o primeiro item de uma lista
primeiro_da_lista :: Eq x => [x] -> x
primeiro_da_lista (a:b) = a

-- Pegar todos menos o primeiro item da lista
list_tail :: [Int] -> [Int]
list_tail (x:y) = y

-- Pegar o último item de uma lista
ultimo_da_lista :: Eq x => [x] -> x
ultimo_da_lista [] = error "Nao pode"
ultimo_da_lista (a:[]) = a
ultimo_da_lista (a:b) =
    ultimo_da_lista b

-- Concatena duas listas
concatena :: Eq x => [x] ->  [x] -> [x]
concatena (l1_h:l1_t) l2 = 
    if l1_t == [] then
        l1_h : l2
    else
        l1_h : concatena l1_t l2

-- Pegar o último item de uma lista
existe_na_lista :: Eq x => x -> [x] -> Bool
existe_na_lista a [] = False
existe_na_lista a (b:c) =
    if a == b then
        True
    else
        existe_na_lista a c


-- Maior elemento de uma lista
maior_elemento :: [Int] -> Int
maior_elemento (a:[]) = a
maior_elemento (a:b) = 
    if a >= maior_elemento b then
        a
    else
        maior_elemento b

-- ou usando uma "função worker"
maior_elemento_worker :: [Int] -> Int 
maior_elemento_worker (x:xs) = 
    worker (x:xs) x
    where
        worker [] y = y
        worker (x:xs) y = 
            let maior = if x > y then x
                        else y in
            worker xs maior


-- Tamanho da lista
tamanho :: [x] -> Int
tamanho [] = 0
tamanho (a:as) = 
    1 + tamanho(as)