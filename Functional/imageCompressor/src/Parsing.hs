{-
-- EPITECH PROJECT, 2023
-- app
-- File description:
-- Parsing
-}
module Parsing (getOpts, Conf(..)) where

import           Text.Read (readMaybe)

data Conf =
  Conf { confColors :: Int, confConvergence :: Float, confFile :: String }

defaultConf :: Conf
defaultConf = Conf { confColors = 0, confConvergence = -1, confFile = "" }

setColors :: Conf -> Int -> Maybe Conf
setColors conf val
  | val <= 0 = Nothing
  | otherwise = Just (conf { confColors = val })

setConvergence :: Conf -> Float -> Maybe Conf
setConvergence conf val
  | val < 0 = Nothing
  | otherwise = Just (conf { confConvergence = val })

setFile :: Conf -> String -> Maybe Conf
setFile conf val = Just (conf { confFile = val })

isError :: [String] -> Bool
isError args
  | "-n" `notElem` args = True
  | "-l" `notElem` args = True
  | "-f" `notElem` args = True
  | otherwise = False

getOpts :: [String] -> Maybe Conf
getOpts args
  | isError args = Nothing
  | otherwise = parse args (Just defaultConf)

parse :: [String] -> Maybe Conf -> Maybe Conf
parse (opt:val:rest) (Just conf) = parse rest (parseArg opt val conf)
parse [] (Just conf) = Just conf
parse _ _ = Nothing

parseArg :: String -> String -> Conf -> Maybe Conf
parseArg "-n" val conf = case (readMaybe val :: Maybe Int) of
  Nothing    -> Nothing
  Just color -> setColors conf color
parseArg "-l" val conf = case (readMaybe val :: Maybe Float) of
  Nothing          -> Nothing
  Just convergence -> setConvergence conf convergence
parseArg "-f" val conf = setFile conf val
parseArg _ _ _ = Nothing
