-- Soma básica
soma :: Int -> Int -> Int
soma a b = a + b

-- Soma que retorna uma String
maior_que_dez :: Int -> String
maior_que_dez num =
    if num > 10 then
        "eh maior que 10"
    else
        "eh menor que 10"

-- Funções booleanas 
maior :: Int -> Int -> Bool
maior a b =
    a > b

menor :: Int -> Int -> Bool
menor a b =
    a < b

fibonacci :: Int -> Int
fibonacci num =
    if num < 2 then
        num
    else
        fibonacci (num - 1) + fibonacci (num - 2)

-- Somar 1 + 2 + 3 + ... + n
soma_recursiva :: Int -> Int
soma_recursiva n =
    if n == 1 then
        1
    else
        n + soma_recursiva (n-1)

hipotenusa :: Float -> Float -> Float
hipotenusa x y = 
    let a = x * x in
    let b = y * y in
    let c = a + b in
    sqrt c
