{-
-- EPITECH PROJECT, 2023
-- app
-- File description:
-- FileParsing
-}
module FileParsing (parseImage) where

import           Data.Char (isDigit)
import           KMeans (Pixel(position, color, Pixel), Color(Color)
                       , Position(Position))

data WrongPixel = WrongPixel
  deriving Show

type FilePixel = Either WrongPixel Pixel

removeSpaces :: String -> String
removeSpaces xs = [x | x <- xs, x `notElem` " "]

clearNonNum :: String -> String
clearNonNum [] = []
clearNonNum (x:xs)
  | not (isDigit x) = ' ':clearNonNum xs
  | otherwise = x:clearNonNum xs

dataToPixel :: [String] -> FilePixel
dataToPixel (x:y:r:g:b:_)
  | not $ all (\e -> e >= 0 && e <= 255) [sr, sg, sb] = Left WrongPixel
  | otherwise = Right
    Pixel { position = Position (read x :: Int, read y :: Int)
          , color = Color col
          }
  where
    col = (read r :: Int, read g :: Int, read b :: Int)

    (sr, sb, sg) = col
dataToPixel _ = Left WrongPixel

lineToData :: String -> FilePixel
lineToData x
  | length (words x) /= 5 = Left WrongPixel
  | otherwise = dataToPixel (words x)

containsWrongPixel :: [FilePixel] -> Bool
containsWrongPixel [] = False
containsWrongPixel (x:xs) = case x of
  Left WrongPixel -> True
  Right _         -> containsWrongPixel xs

convertToPixel :: [FilePixel] -> [Pixel]
convertToPixel [] = []
convertToPixel (e:xs) = case e of
  Left WrongPixel -> []
  Right Pixel { position = Position (x, y), color = Color (r, g, b) }
    -> Pixel { position = Position (x, y), color = Color (r, g, b) }
    :convertToPixel xs

parseLines :: [String] -> [Pixel]
parseLines line
  | containsWrongPixel content = []
  | otherwise = convertToPixel content
  where
    content = map lineToData line

parseImage :: String -> [Pixel]
parseImage content =
  parseLines $ map clearNonNum $ words (removeSpaces content)
