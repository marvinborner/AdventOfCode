import           Data.Void
import           Prelude                 hiding ( (||) )
import           Text.Megaparsec
import           Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer    as L

type Parser = Parsec Void String

data Equation = Equation Int [Int]

equation :: Parser Equation
equation = do
  test <- L.decimal
  string ": "
  nums <- L.decimal `sepBy` char ' '
  pure $ Equation test nums

input :: Parser [Equation]
input = equation `sepEndBy` char '\n'

-- good enough
(||) :: Int -> Int -> Int
(||) b a = read $ show a ++ show b

prune :: Int -> [Int] -> [Int]
prune t = filter (<= t)

combos :: Int -> [Int] -> [Int]
combos t (n : ns) =
  foldl (\s v -> prune t $ ((v +) <$> s) ++ ((v *) <$> s)) [n] ns

combos2 :: Int -> [Int] -> [Int]
combos2 t (n : ns) = foldl
  (\s v -> prune t $ ((v +) <$> s) ++ ((v *) <$> s) ++ ((v ||) <$> s))
  [n]
  ns

solve :: (Int -> [Int] -> [Int]) -> [Equation] -> Int
solve f es = sum [ test | (Equation test _, m) <- zip es matches, m ]
  where matches = (\(Equation test nums) -> test `elem` f test nums) <$> es

main :: IO ()
main = do
  f <- readFile "input"
  case runParser (input <* eof) "" f of
    Right p -> do
      print $ solve combos p
      print $ solve combos2 p
    Left err -> print $ errorBundlePretty err
