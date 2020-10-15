import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Char
-- import DataKinds

data Term = Atom String
          | Var Name
          | Predicate Predicate
          deriving (Show, Eq)


type Name = (Int, String)
type Predicate = (String, [Term])
type Rule = (Predicate, [Predicate])
type Substitution = [(Name, Term)]

build :: IO()
build = do
    content <- (readFile "banco.pl")
    let clean_content = (whitespace content)
    print (content)
    print (parse term "<stdin>" clean_content )

repl :: IO()
repl = do
    putStr "?- "
    line <- getLine
    print ( parse term "<stdin>" line)
    -- print (result)
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


unify :: Term -> Term -> Substitution

-- Regra (REFL)
unify (Var a) (Var b) | a == b =
    []

-- Regra (LEFT)
unify (Var a) t | not (occursCheck t a) =
    [(a, t)]

-- Regra (RIGHT)
unify t (Var a) | not (occursCheck t a) =
    [(a, t)]

-- Regra (INT)
unify (Atom a) (Atom b) =
    []

-- Regra (ARROW)
-- unify (TypeArrow t1 r1) (TypeArrow t2 r2) = do
--     theta1 <- unify t1 t2
--     theta2 <- unify (subst theta1 r1) (subst theta1 r2)
--     --
--     Just (compose theta2 theta1)

-- Caso geral (não dá pra unificar)
unify a b =
    error
    []

-- =========== Parser ===========
whitespace :: [Char] -> [Char]
whitespace [] = []
whitespace (x:xs) = 
    if x == ' ' then
        whitespace xs
    else 
        x : whitespace xs

name :: Parser String
name = do
        head <- lower
        tail <- many alphaNum
        return (head : tail)

atom :: Parser Term
atom = do
    a <- name <|> many1 digit
    return (Atom a)

variable :: Parser Term
variable = do
    head <- upper
    tail <- many alphaNum
    return (Var (0, head : tail))

predicate :: Parser Term
predicate = do
    n <- name
    args <- arguments
    return (Predicate (n, args))

arguments :: Parser [Term]
arguments = do
    char '('
    body <- sepBy term (char ',')
    char ')'
    return body

term :: Parser Term
term = do
  try predicate <|> atom <|> variable

rule :: Parser Term
rule = do
    try predicate

parse_from_file :: Parser [Term]
parse_from_file = do
    body <-  predicate `sepBy` spaces
    return body


----------------------------------------------
db1 :: [Rule]
db1 = [ (("likes", [ (Atom "ana"), (Atom "banana") ]), []),
        (("likes", [ (Atom "ana"), (Atom "potato") ]), []),
        (("likes", [ (Atom "bob"), (Atom "potato") ]), []) ]

db2 :: [Rule]
db2 = [ (("likes", [ (Atom "ana"), (Predicate( "yellow", [] ))  ]), []),
        (("likes", [ (Atom "ana"), (Atom "potato") ]), []),
        (("dislikes", [ (Atom "bob"), (Atom "potato") ]), []) ]

my_goal :: Predicate
my_goal = ("likes", [ (Atom "ana") , (Var (1, "X")) ])

my_goal_potato :: Predicate
my_goal_potato = ("likes", [ (Var (1, "Z")), (Atom "potato") ])


resolve :: Predicate -> [Rule] -> [Substitution]
-- resolve :: Predicate -> [Rule] -> Substitution
resolve goal [] = [] 
resolve goal ( (pred, body) : rules) = 
    if (verify goal pred) then
        (unifyPred goal pred) ++ (resolve goal rules)
    else
        (resolve goal rules)


verify :: Predicate -> Predicate -> Bool
verify (str_a, [] ) (str_b, []) = True

verify (goal_str, ( (Atom goal_t) : goal_ts)) (pred_str, ( (Atom pred_t) : pred_ts)) = 
    if (goal_t == pred_t && goal_str == pred_str) then
        True && (verify (goal_str, (goal_ts)) (pred_str, (pred_ts)))
    else
        False
    
verify (goal_str, (goal_t : goal_ts)) (pred_str, (pred_t : pred_ts)) = 
    True && (verify (goal_str, (goal_ts)) (pred_str, (pred_ts)))

-- unifyPred :: Predicate -> Predicate -> Maybe Substitution
-- unifyPred :: Predicate -> Predicate -> Substitution
unifyPred :: Predicate -> Predicate -> [Substitution]
unifyPred (str_a, [] ) (str_b, []) = []

unifyPred (goal_str, ( (Atom goal_t) : goal_ts)) (pred_str, ( (Atom pred_t) : pred_ts)) = 
    if goal_t == pred_t then
        (unifyPred (goal_str, (goal_ts)) (pred_str, (pred_ts)))
    else
        []    

unifyPred (goal_str, (goal_t : goal_ts)) (pred_str, (pred_t : pred_ts)) = 
    (unify goal_t pred_t ) : (unifyPred (goal_str, (goal_ts)) (pred_str, (pred_ts)))
