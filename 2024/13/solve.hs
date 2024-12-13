import           Data.Void
import           Prelude                 hiding ( (||) )
import           Text.Megaparsec         hiding ( Pos
                                                , single
                                                )
import           Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer    as L

type Parser = Parsec Void String

data Pos = Pos
  { x :: Int
  , y :: Int
  }
  deriving Show

data Machine = Machine
  { a :: Button
  , b :: Button
  , p :: Prize
  }
  deriving Show

type Button = Pos
type Prize = Pos

signed :: Parser Int
signed = L.signed (pure ()) L.decimal

delim :: Parser ()
delim = many (oneOf " \n\r") *> pure ()

button :: String -> Parser Button
button n = do
  string $ "Button " <> n <> ": X"
  x <- signed
  string ", Y"
  y <- signed
  return $ Pos x y

prize :: Parser Prize
prize = do
  string "Prize: X="
  x <- L.decimal
  string ", Y="
  y <- L.decimal
  return $ Pos x y

machine :: Parser Machine
machine = do
  a <- button "A"
  delim
  b <- button "B"
  delim
  p <- prize
  delim
  return $ Machine a b p

machines :: Parser [Machine]
machines = many machine

single :: Machine -> Int
single m@(Machine { a = Pos ax ay, b = Pos bx by, p = Pos px py }) =
  let d   = ax * by - ay * bx
      aD  = (by * px - bx * py) `div` d
      bD  = (ax * py - ay * px) `div` d
      hit = ax * aD + bx * bD == px && ay * aD + by * bD == py
  in  if hit then aD * 3 + bD else 0

part1 :: [Machine] -> Int
part1 = sum . map single

part2 :: [Machine] -> Int
part2 = part1 . map
  (\(Machine { a, b, p = Pos px py }) ->
    Machine a b (Pos (px + 10000000000000) (py + 10000000000000))
  )

main :: IO ()
main = do
  f <- readFile "input"
  case runParser (machines <* eof) "" f of
    Right ms -> do
      print $ part1 ms
      print $ part2 ms
    Left err -> print $ errorBundlePretty err
