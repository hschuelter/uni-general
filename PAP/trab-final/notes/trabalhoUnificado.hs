import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Char
-- import DataKinds

-- OBS PARA FAZER DEPOIS NO NAME EXISTIR EM UM PREDICADO:
-- data Term = Atom String
-- | Var Name
-- | Pred (String, [Term])
-- segundo ele, usar foldr no Pred, pq:
-- foldr (+) a [b, ..., z]
-- então vai retornar b + (... + (z + a))
-- Ele quer olhar casa predicado, caso encontre um retorna verdadeiro da lista de booleanos, logo
-- foldr (||) False
-- Mas para isso precisamos mapear cada um deles para fazer a comparação se um predicado retorna V ou F caso esteja lá, então:
-- foldr (||) False (fmap [a, b, c])
-- Com isso consigo em uma única linha verificar se um nome existe lá dentro da lsita de predicados
-- f a função e a,b e c os predicados, transformando em [fa, fb, fc].
-- irá fazer fa || (fb || (fc || False))
-- A ideia é escrever o f (occursCheck com o Name que a gente quer), para verificar se um nome aparece naquele termo
-- Detalhe, um name nunca aparece em um Atom, aparece em um Var se Name = Var, porém para predicado esse forma acima é a "mais fáciL"
-- main = do
--     putStrLn "Works!"

-- teste :: Name -> [String]
-- teste (i, s) = 
--     [show i, s]


data Term = Atom String
          | Var Name
          | Predicate Predicate
          deriving (Show, Eq)


type Name = (Int, String)
type Predicate = (String, [Term])
type Rule = (Predicate, [Predicate])
type Substitution = [(Name, Term)]

repl :: IO()
repl = do
    putStr "?- "
    line <- getLine
    putStrLn ("Você digitou '" ++ line ++ "'")
    repl

-- ooccursCheck ok
occursCheck :: Term -> Name -> Bool
occursCheck (Atom a) n = 
    False

occursCheck (Var v) n = 
    v == n

occursCheck (Predicate (s, [])) n = 
    False

occursCheck (Predicate (s, (t:ts))) n = 
    if (occursCheck t n) then
        True
    else
        occursCheck (Predicate (s, ts)) n


-- Adicionar os métodos para executar a compose e testar
mapear :: (a->b) -> [a] -> [b]
mapear = fmap

compose :: Unifier -> Unifier -> Unifier
compose xs ys =
    ++ xs (mapear subst_in_unifier xs) ys

subst_in_unifier :: Unifier -> (Name, Type) -> (Name, Type)
subst_in_unifier u (name, t) =
    (name, subst u t)

-- Adicionar 