{-# LANGUAGE TupleSections #-}

import           Control.Monad
import qualified Data.HashMap                  as Map
import           Data.HashMap                   ( Map )
import           Data.List
import           Data.MemoTrie
import           Text.Regex.TDFA

m !!! k = Map.findWithDefault 9999999 k m

parse input = (valves, Map.fromList rates, Map.fromList dists)
 where
  match :: String -> [String]
  match s = getAllTextMatches $ s =~ "([A-Z]{2}|[0-9]+)"
  matches = map match input
  valves  = map head matches
  rates = [ (valve, read rate :: Int) | (valve : rate : _) <- matches, rate /= "0" ]
  dists = [ ((valve, pipe), 1) | (valve : _ : pipes) <- matches, pipe <- pipes ]

precompute valves distances = updated distances prod
 where
  prod = sequence $ replicate 3 valves
  dist (x : y : z : _) m = min (m !!! (y, z)) ((m !!! (y, x)) + (m !!! (x, z)))
  updated = foldr (\c@(_ : y : z : _) m -> Map.insert (y, z) (dist c m) m)

solve' :: Int -> Int -> String -> [String] -> Map String Int -> Map (String, String) Int -> Int
solve' p time current valves rates dists = maximum $ single ++ case p of
  1 -> [0]
  2 -> [solve 1 26 "AA" valves rates dists]
 where
  single = [ each valve | valve <- valves, (dists !!! (current, valve)) < time ]
  new_rate = (rates Map.!)
  new_time = (+ (-1)) . (-) time . (dists !!!) . (current, ) -- troll
  next valve = solve p (new_time valve) valve (delete valve valves) rates dists
  each = ap ((+) . liftM2 (*) new_rate new_time) next -- lol

solve = memo solve'

main :: IO ()
main = do
  input <- lines <$> readFile "input"
  let (valves, rates, dists) = parse input
      dists'                 = precompute valves dists
  putStrLn $ show $ solve 1 30 "AA" (Map.keys rates) rates dists'
  putStrLn $ show $ solve 2 26 "AA" (Map.keys rates) rates dists'
