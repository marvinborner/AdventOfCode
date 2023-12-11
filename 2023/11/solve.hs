type Pos = (Int, Int)
data Part = Empty | Galaxy
  deriving Eq
type Universe = [(Pos, Part)]

imageToUniverse :: String -> Universe
imageToUniverse = conv (0, 0)
 where
  conv pos@(x, y) ('.'  : rst) = (pos, Empty) : conv (x + 1, y) rst
  conv pos@(x, y) ('#'  : rst) = (pos, Galaxy) : conv (x + 1, y) rst
  conv pos@(x, y) ('\n' : rst) = conv (0, y + 1) rst
  conv _          _            = []

expandableRows :: Universe -> [Int]
expandableRows universe = filter (\y -> all (\(_, part) -> part == Empty) (filter (\((_, y'), _) -> y == y') universe)) [0 .. fst $ fst $ last universe]

expandableCols :: Universe -> [Int]
expandableCols universe = filter (\x -> all (\(_, part) -> part == Empty) (filter (\((x', _), _) -> x == x') universe)) [0 .. snd $ fst $ last universe]

solve :: Int -> Universe -> Int
solve expansion universe = horizontalCount + verticalCount
 where
  rows = expandableRows universe
  horizontalExpansion row | row `elem` rows = expansion
  horizontalExpansion _                     = 1
  horizontalCount = sum $ concat [ horizontalExpansion <$> [a .. b - 1] | ((_, a), Galaxy) <- universe, ((_, b), Galaxy) <- universe, a < b ]

  cols = expandableCols universe
  verticalExpansion col | col `elem` cols = expansion
  verticalExpansion _                     = 1
  verticalCount = sum $ concat [ verticalExpansion <$> [a .. b - 1] | ((a, _), Galaxy) <- universe, ((b, _), Galaxy) <- universe, a < b ]

main :: IO ()
main = do
  input <- readFile "input"
  let universe = imageToUniverse input
  print $ solve 2 universe
  print $ solve 1000000 universe
