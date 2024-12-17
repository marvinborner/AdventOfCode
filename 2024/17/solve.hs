{-# LANGUAGE LambdaCase #-}

import           Control.Monad.State            ( State
                                                , evalState
                                                , gets
                                                , modify
                                                )
import           Data.Bits                      ( (.&.)
                                                , shiftL
                                                , xor
                                                )
import           Data.Functor                   ( (<&>) )
import           Data.Void
import           Prelude                 hiding ( (||) )
import           Text.Megaparsec         hiding ( Pos
                                                , State
                                                , single
                                                )
import           Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer    as L

data Registers = Registers
  { a   :: Int
  , b   :: Int
  , c   :: Int
  , pc  :: Int
  , out :: Maybe Int -- eh :)
  }
  deriving Show

type Program = [Int]
type Out = [Int]

type Parser = Parsec Void String
type ST = State Registers

register :: Parser Int
register =
  string "Register " *> oneOf "ABC" *> string ": " *> L.decimal <* char '\n'

program :: Parser Program
program = string "Program: " *> L.decimal `sepBy` char ','

input :: Parser (Registers, Program)
input = do
  regs <- Registers <$> register <*> register <*> register
  char '\n'
  prog <- program <* many (char '\n')
  return (regs 0 Nothing, prog)

combo :: Int -> ST Int
combo x | x <= 3 = return x
combo 4          = gets a
combo 5          = gets b
combo 6          = gets c
combo 7          = error "RESERVED COMBO OPERAND"

evalInstruction :: Int -> Int -> ST ()
evalInstruction 0 x = do
  numerator   <- gets a
  denominator <- (2 ^) <$> combo x
  modify $ \s -> s { a = numerator `div` denominator }
evalInstruction 1 x = do
  y <- gets b
  modify $ \s -> s { b = x `xor` y }
evalInstruction 2 x = do
  x <- combo x
  modify $ \s -> s { b = x .&. 7 }
evalInstruction 3 x = do
  gets a >>= \case
    0 -> return ()
    _ -> modify $ \s -> s { pc = x }
evalInstruction 4 x = do
  x <- gets b
  y <- gets c
  modify $ \s -> s { b = x `xor` y }
evalInstruction 5 x = do
  x <- combo x
  modify $ \s -> s { out = Just $ x .&. 7 }
evalInstruction 6 x = do
  numerator   <- gets a
  denominator <- (2 ^) <$> combo x
  modify $ \s -> s { b = numerator `div` denominator }
evalInstruction 7 x = do
  numerator   <- gets a
  denominator <- (2 ^) <$> combo x
  modify $ \s -> s { c = numerator `div` denominator }

eval :: Program -> ST Out
eval is = gets pc >>= \case
  ip | ip + 1 > length is -> return []
  ip                      -> do
    evalInstruction (is !! ip) (is !! (ip + 1))
    ip' <- gets pc -- jumped?
    mx  <- gets out
    modify $ \s -> s { out = Nothing, pc = if ip == ip' then ip + 2 else ip' }
    next <- eval is
    return $ case mx of
      Just x  -> x : next
      Nothing -> next

rev :: Registers -> Program -> [Int]
rev regs prog = go [0] prog
 where
  go z []       = z
  go z (x : xs) = do
    val <- go z xs
    off <- [0 .. 7]
    let try = val `shiftL` 3 + off
    case evalState (eval prog) (regs { a = try }) of
      h : _ | h == x -> return try
      _              -> empty

main :: IO ()
main = do
  f <- readFile "input"
  case runParser (input <* eof) "" f of
    Right (regs, prog) -> do
      print $ evalState (eval prog) regs
      print $ rev regs prog
    Left err -> putStrLn $ errorBundlePretty err
