soma2 :: Int -> Int
soma2 x = x + 2 


mapear :: (a -> b) -> [a] -> [b]
mapear (a) [] = []
mapear (a) (y:ys) = 
    a y : mapear a ys