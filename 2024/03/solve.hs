-- I had expected a more complex syntax in p2 :)

import           Data.Functor
import           Data.Void
import           Text.Megaparsec
import           Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer    as L

type Parser = Parsec Void String
type Enabled = Bool

data Instr = Mul Int Int | Do | Dont | Garbage
  deriving Show

multiplication :: Parser Instr
multiplication = do
  string "mul("
  a <- L.decimal
  string ","
  b <- L.decimal
  string ")"
  pure $ Mul a b

program :: Parser [Instr]
program =
  many
    $   try multiplication
    <|> (string "don't()" $> Dont)
    <|> (string "do()" $> Do)
    <|> (satisfy (const True) $> Garbage)


part1 :: [Instr] -> Int
part1 = sum . map eval
 where
  eval (Mul a b) = a * b
  eval _         = 0

part2 :: Enabled -> [Instr] -> Int
part2 True  (Mul a b : is) = a * b + part2 True is
part2 True  (Dont    : is) = part2 False is
part2 False (Do      : is) = part2 True is
part2 e     (_       : is) = part2 e is
part2 _     []             = 0

main :: IO ()
main = do
  f <- readFile "input"
  case runParser (program <* eof) "" f of
    Right p -> do
      print $ part1 p
      print $ part2 True p
    Left err -> print $ errorBundlePretty err
