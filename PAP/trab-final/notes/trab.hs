import Text.ParserCombinators.Parsec
-- import DataKinds

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


db :: [Rule]
db = [  (Predicate ("likes", ["ana", "banana"])) ]

main :: IO()
main = do
    repl

repl :: IO()
repl = do
    putStr "?- "
    line <- getLine
    putStrLn ("Você digitou '" ++ (whitespace line) ++ "'")
    repl


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


unify :: Term -> Term -> Maybe Substitution

-- Regra (REFL)
unify (Var a) (Var b) | a == b =
    Just []

-- Regra (LEFT)
unify (Var a) t | not (occursCheck t a) =
    Just [(a, t)]

-- Regra (RIGHT)
-- unify (Term t) (Var a) | not (occursCheck a t) =
--     Just [(a, t)]

-- Regra (INT)
unify (Atom a) (Atom b) =
    Just []

-- Regra (ARROW)
-- unify (TypeArrow t1 r1) (TypeArrow t2 r2) = do
--     theta1 <- unify t1 t2
--     theta2 <- unify (subst theta1 r1) (subst theta1 r2)
--     --
--     Just (compose theta2 theta1)

-- Caso geral (não dá pra unificar)
unify a b =
    Nothing

-- =========== Parser ===========
whitespace :: [Char] -> [Char]
whitespace [] = []
whitespace (x:xs) = 
    if x == ' ' then
        whitespace xs
    else 
        x : whitespace xs

atom :: Parser Term
atom = do
    name <- many1 lower
    return (Atom name)

variable :: Parser Term
variable = do
    name <- many1 upper
    return (Var (1, name))

parse_type :: Parser Term
parse_type =
  try atom <|> variable

-- parse_rule :: Parser Type
-- parse_rule = do
--     left <- atomic
--     char ':'
--     char '-'
--     right <- parse_type
--     return (Rule left right)


-- Em ordem (?):

-- Adicionar e testar as regras de unificação. Falta a Arrow
-- O profeossor tem a dele mas precisa de alterações para funcionar corretamente

-- Fazer resolve e resolveBody -- Ver o do professor, que está no final do arquivo sala11e13
-- Aparentemente o do profeossr é funcional, juntar com os composes e testar
-- Adicionar o compose e seus métodos (inclusive o subst). Testar se estão corretores 
--  O compose está nos arquivos trabUnificado.hs etc

-- Fazer e verificar os parser types - tem os do profesosr pra base - pode deixar pro final/não fazer

-- Aplicar mapeamento dentro do substTerm que será aplicado no unifyBody

-- Verificar no arquivo sala11e13.hs a explicação para a lista de predicados
-- Tentar implementar e testar essa

