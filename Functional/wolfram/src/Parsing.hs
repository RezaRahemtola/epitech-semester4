{-
-- EPITECH PROJECT, 2023
-- src
-- File description:
-- $DESCRIPTION
-}
module Parsing
    ( getOpts
    , Conf(confRule, confStart, confHeight, confWidth, confMove)) where

import           Text.Read (readMaybe)

data Conf = Conf { confRule :: Int
                 , confStart :: Int
                 , confHeight :: Maybe Int
                 , confWidth :: Int
                 , confMove :: Int
                 }

defaultConf :: Conf
defaultConf = Conf { confRule = 0
                   , confStart = 0
                   , confHeight = Nothing
                   , confWidth = 80
                   , confMove = 0
                   }

setRule :: Conf -> Int -> Maybe Conf
setRule conf val
  | val < 0 = Nothing
  | val > 255 = Nothing
  | otherwise = Just (conf { confRule = val })

setStart :: Conf -> Int -> Maybe Conf
setStart conf val
  | val < 0 = Nothing
  | otherwise = Just (conf { confStart = val })

setHeight :: Conf -> Int -> Maybe Conf
setHeight conf val
  | val < 0 = Nothing
  | otherwise = Just (conf { confHeight = Just val })

setWidth :: Conf -> Int -> Maybe Conf
setWidth conf val
  | val < 0 = Nothing
  | otherwise = Just (conf { confWidth = val })

setMove :: Conf -> Int -> Maybe Conf
setMove conf val = Just (conf { confMove = val })

isError :: [String] -> Bool
isError args
  | "--rule" `notElem` args = True
  | otherwise = False

getOpts :: [String] -> Maybe Conf
getOpts args
  | isError args = Nothing
  | otherwise = parse args (Just defaultConf)

parse :: [String] -> Maybe Conf -> Maybe Conf
parse (opt:val:rest) (Just conf) =
  parse rest (parseArg opt (readMaybe val) conf)
parse [] (Just conf) = Just conf
parse _ _ = Nothing

parseArg :: String -> Maybe Int -> Conf -> Maybe Conf
parseArg "--rule" (Just val) conf = setRule conf val
parseArg "--start" (Just val) conf = setStart conf val
parseArg "--lines" (Just val) conf = setHeight conf val
parseArg "--window" (Just val) conf = setWidth conf val
parseArg "--move" (Just val) conf = setMove conf val
parseArg _ _ _ = Nothing
