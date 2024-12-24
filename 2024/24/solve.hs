{-# LANGUAGE DeriveGeneric #-}

import           Data.Bits                      ( (.&.)
                                                , (.|.)
                                                , xor
                                                )
import           Data.Functor                   ( ($>) )
import qualified Data.HashMap.Strict           as M
import           Data.HashMap.Strict            ( HashMap )
import           Data.Hashable
import           Data.List                      ( sort )
import           Data.Void
import           GHC.Generics                   ( Generic )
import           Text.Megaparsec         hiding ( Pos
                                                , single
                                                )
import           Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer    as L

type Parser = Parsec Void String

data Term = Term Reg Operator Reg
  deriving (Show, Generic, Eq)
data Operator = AND | OR | XOR
  deriving (Show, Generic, Eq)

instance Hashable Operator
instance Hashable Term

type Reg = String
type Regs = HashMap Reg Int
type Wires = HashMap Reg Term

reg :: Parser Reg
reg = some alphaNumChar

regs :: Parser Regs
regs = M.fromList <$> many
  (do
    r <- reg
    string ": "
    val <- L.decimal
    char '\n'
    return (r, val)
  )

operator :: Parser Operator
operator =
  (string "AND" $> AND) <|> (string "OR" $> OR) <|> (string "XOR" $> XOR)

wires :: Parser Wires
wires = M.fromList <$> many
  (do
    a <- reg
    char ' '
    op <- operator
    char ' '
    b <- reg
    string " -> "
    out <- reg
    char '\n'
    return (out, Term a op b)
  )

eval :: Int -> Operator -> Int -> Int
eval a AND b = a .&. b
eval a OR  b = a .|. b
eval a XOR b = a `xor` b

solve1 :: (Regs, Wires) -> Reg -> Int
solve1 (rs, _) r | r `M.member` rs = rs M.! r
solve1 s@(_, ws) r                 = eval (solve1 s a) op (solve1 s b)
  where Term a op b = ws M.! r

toDec :: [Char] -> Int
toDec []       = 0
toDec (x : xs) = (read [x] :: Int) + 2 * toDec xs

outRegs :: [Reg] -> [Reg]
outRegs []                 = []
outRegs (r@('z' : _) : rs) = r : outRegs rs
outRegs (_           : rs) = outRegs rs

part1 :: Parser Int
part1 = do
  rs <- regs
  char '\n'
  ws <- wires
  return $ toDec $ concat $ show . solve1 (rs, ws) <$> sort
    (outRegs $ M.keys rs ++ M.keys ws)


main :: IO ()
main = do
  f <- readFile "input"
  case runParser (part1 <* eof) "" f of
    Right res -> print res
    Left  err -> putStrLn $ errorBundlePretty err
