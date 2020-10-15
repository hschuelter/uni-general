import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Char

-- Vai postar no Github

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
-- f a função e a,b e c os predicados, transformando em [fa, gb, fc].
-- irá fazer fa || (fb || (fc || False))
-- A ideia é escrever o f (occursCheck com o Name que a gente quer), para verificar se um nome aparece naquele termo
-- Detalhe, um name nunca aparece em um Atom, aparece em um Var se Name = Var, porém para predicado esse forma acima é a "mais fáciL"


data Type = TypeInt
        | TypeVar Name
        | TypeArrow Type Type
        deriving Show

type Name = String

type Unifier = [(Name, Type)]

int_prim :: Parser Type
int_prim = do
    char ‘i’
    char ‘n’
    char ‘t’
    return TypeInt

variable :: Parser Type
variable =
    many1 lower
    type Var

function :: Parser Type
function = do
    left <- try int_prim <|> variable
    char ‘-’
    char ‘>’
    right <- parse_type
    return (TypeArrow left right)

atomic :: Parser Type
atomic =
    try int_prim <|> variable <|> parentheses

parentheses :: Parser Type
parentheses = do
    char ‘(‘
    t <- parse_type
    char ‘)’
    return t



parse_type :: Parser Type
parse_type =
    try function <|> int_prim <|> variable
        --retorno ou ver um tipo primitivo int ou retorno uma variável

main = do
    putStrLn “Digite o tipo A: “
    a <- getLine
    putStrLn “Digte o tipo B:”
    b <- getLIne

    case(parse parse_type “<stdin>” a, parse parse_type
    (Right ta, Right tb) ->
        let mgu = unify ta tb in
        putStrLen ("Unificação A ~ B = " ++ show mgu) 
        -> do
        putStrLn "Erro. Tente novamente!"

-- Regra (REFL)
unify :: Type -> Type -> Maybe Unifier --para trabalho final
unify (TypeVar a) (TypeVar b) | a == b =
    Just []

-- Regra (LEFT)
unify (TypeVar a) t | not (occusCheck a t) =
  Just [(a, t)]

-- Regra (RIGHT)
unify t (TypeVar a) | not (occusCheck a t) =
  Just [(a, t)]

-- REGRA (INT)
unify (TypeInt) (TypeInt) =
  Just []

-- Regra (ARROW)
unify (TypeArrow t1 r1) (TypeArrow t2 r2) = do
    -- usango monada Maybe!
    theta1 <- unify t1 t2
    -- se retornar just a unificação é atribuida a theta1
    -- se retornar nothing, vai parar toda a função e retornar nothing pra ela, parando por aí
    theta2 <- unify (subst theta1 r1) (...)
    -- ...
    Just (compose theta2 theta1)

-- caso geral (n dá para unificar)
  unify a b =
    Nothing- Verificar no arquivo sala11e13.hs a explicação para a lista de predicados
    -- Tentar implementar e testar essaybe b
subst u (TypeArrow t1 t2) =
    (subst u t1) (subst u t2)
    -- Substituo variáveis dentro de uma seta, porém continua sendo seta

-- occursCheck aqui.

mapear :: (a->b) -> [a] -> [b]
mapear = fmap

-- Essa compose e a subst_in_unifier pode copiar para o trabalho final, vai ficar idêntico lá
compose :: Unifier -> Unifier -> Unifier
compose xs ys =
    ++ xs (mapear subst_in_unifier xs) ys

subst_in_unifier :: Unifier -> (Name, Type) -> (Name, Type)
subst_in_unifier u (name, t) =
    (name, subst u t)



-- Aula 18/11 - funçõa resolve

--Estar com types declarados- Verificar no arquivo sala11e13.hs a explicação para a lista de predicados
-- Tentar implementar e testar essa
freshenTerm (Predicate (name, body)) = 
    Predicate (name, fmap freshenTerm body)

    main :: IO()
    main = do   
        -- let db' = fmap (freshen . freshen) db  
        -- print db'
        -- o "." faz uma composição (ali chamada freshen duas vezes)
        let result = resolve my_goal db
        print result

-- resolução do Resolve()

-- Predicado exemplo
my_goal :: Predicate
my_goal = ("likes", [Atom "bob", Var(0, "X")])

unifyPred :: Predicate -> Predicate -> Maybe Substitution
unifyPred a b = Nothing

resolve :: Predicate -> [Rule] -> [Substitution]
resolve goal rules = 
    let rules' = fmap freshen rules in 
    do
        (pred, body) <- rules' 
        case unifyPred goal pred of 
            Just u->
               resolveBody rules' u body
            Nothing ->
                -- zero respostas
                []

-- Ou:
resolve goal ((pred, body) : rules) = 
    let rules' = fmap freshen rules in 
    case unifyPred goal (freshenPred pred) of  
        Just u ->
            resolveBody rules' u (fmap freshenPred body) ++ resolve goal rules
        Nothing -> resolve goal rules
    
subsPred :: Substitution -> Predicate -> Predicate
substPred s e = e -- só retornou isso para não dar erro, não está correto
-- acredito que o substUnifier já é o correto deste

resolveBody :: Substitution -> [Rule] -> [Predicate] -> [Substitution]
-- Rules é meu banco de dados e o Predicate o que to tentando provar que cada um seja verdadeiro
resolveBody t1 rules [] =
    return t1
resolveBody t1 rules (p:ps) = 
    let rules' = fmap freshen rules in
    do 
        t2 <- resolve (substPred t1 p) rules' -- regras atualizadas
        resolveBody (compose t2 t1) rules' ps
        

        -- 
