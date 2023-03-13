{-
-- EPITECH PROJECT, 2023
-- automaton
-- File description:
-- $DESCRIPTION
-}
module Automaton (automaton) where

import           Parsing (Conf(confWidth, confHeight, confStart, confRule, confMove))
import           System.Exit (exitSuccess)
import           Data.Bits (shiftR, Bits((.&.)))

patternToInt :: String -> Int
patternToInt [] = 0
patternToInt (c:rest) = (if c == '*'
                         then 1
                         else 0)
  + 2 * patternToInt rest

generateChar :: Int -> Int -> String
generateChar rule intPattern
  | (shiftR rule intPattern .&. 1) == 1 = "*"
  | otherwise = " "

generateLine :: String -> Int -> String
generateLine [] _ = ""
generateLine [_] _ = ""
generateLine [_, _] _ = ""
generateLine previousLine rule = generateChar rule (patternToInt line)
  ++ generateLine (tail previousLine) rule
  where
    line = take 3 previousLine

mainLoop :: Int -> String -> Conf -> IO ()
mainLoop 0 _ _ = exitSuccess
mainLoop nbLeft previousLine conf =
  displayLine previousLine (confStart conf) (confWidth conf) (confMove conf)
  >> mainLoop
    (if confStart conf > 0
     then nbLeft
     else nbLeft - 1)
    line
    conf { confStart = confStart conf - 1 }
  where
    line = generateLine ("  " ++ previousLine ++ "  ") (confRule conf)

getLeftSpace :: Int -> Int -> String
getLeftSpace lineLength width
  | lineLength >= width = ""
  | otherwise = replicate
    ((width - lineLength) `div` 2 + ((width - lineLength) `mod` 2))
    ' '

getRightSpace :: Int -> Int -> String
getRightSpace lineLength width
  | lineLength >= width = ""
  | otherwise = replicate ((width - lineLength) `div` 2) ' '

moveLine :: String -> Int -> String
moveLine line move
  | move >= 0 = replicate move ' ' ++ take (length line - move) line
  | otherwise = drop (abs move) line ++ replicate (abs move) ' '

formatLine :: String -> Int -> String
formatLine line width =
  getLeftSpace lineLength width ++ line ++ getRightSpace lineLength width
  where
    lineLength = length line

displayLine :: String -> Int -> Int -> Int -> IO ()
displayLine line leftToSkip width move
  | leftToSkip > 0 = return ()
  | otherwise = putStrLn
    $ moveLine (take width (drop ((length fline - width) `div` 2) fline)) move
  where
    fline = formatLine (reverse line) width

getHeight :: Maybe Int -> Int
getHeight Nothing = -1
getHeight (Just height) = height

automaton :: Conf -> IO ()
automaton conf = mainLoop (getHeight (confHeight conf)) "*" conf
