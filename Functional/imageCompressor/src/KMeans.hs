{-
-- EPITECH PROJECT, 2023
-- src
-- File description:
-- KMeans
-}
module KMeans
    ( getColorDistance
    , generateNRandomColors
    , getAverageColor
    , getClosestCentroidIndexForColor
    , sortPixelsIntoCentroids
    , runKMeans
    , Position(..)
    , Color(..)
    , Pixel(..)) where

import           System.Random (randomRIO)
import           Data.List (elemIndex)
import           Parsing (Conf(..))
import           GHC.Float (int2Float)

newtype Position = Position (Int, Int)

newtype Color = Color (Int, Int, Int)

data Pixel = Pixel { position :: Position, color :: Color }

instance Show Pixel where
  show pixel = show (position pixel) ++ " " ++ show (color pixel)

instance Show Color where
  show (Color (r, g, b)) =
    "(" ++ show r ++ "," ++ show g ++ "," ++ show b ++ ")"

instance Show Position where
  show (Position (x, y)) = "(" ++ show x ++ "," ++ show y ++ ")"

runKMeans :: [Pixel] -> Conf -> IO [Color]
runKMeans pixels conf = generateNRandomColors (confColors conf)
  >>= \centroids -> return $ runKMeans' pixels (confConvergence conf) centroids

runKMeans' :: [Pixel] -> Float -> [Color] -> [Color]
runKMeans' pixels convergence centroids
  | maxMove < convergence = newCentroids
  | otherwise = runKMeans' pixels convergence newCentroids
  where
    newCentroids = map
      (getAverageColor . map color)
      (sortPixelsIntoCentroids pixels centroids)

    maxMove = maximum (zipWith getColorDistance centroids newCentroids)

createPixelListsForCentroids :: [Color] -> [[Pixel]]
createPixelListsForCentroids = map (const [])

sortPixelsIntoCentroids :: [Pixel] -> [Color] -> [[Pixel]]
sortPixelsIntoCentroids pixels centroids = foldl
  (\acc pixel -> sortPixelIntoCentroid pixel centroids acc)
  (createPixelListsForCentroids centroids)
  pixels

sortPixelIntoCentroid :: Pixel -> [Color] -> [[Pixel]] -> [[Pixel]]
sortPixelIntoCentroid pixel centroids pixels =
  case getClosestCentroidIndexForColor (color pixel) centroids of
    Nothing    -> pixels
    Just index -> let (before, after) = splitAt index pixels
                  in before ++ [pixel:head after] ++ tail after

getClosestCentroidIndexForColor :: Color -> [Color] -> Maybe Int
getClosestCentroidIndexForColor _ [] = Nothing
getClosestCentroidIndexForColor col centroids =
  let distances = getCentroidsDistanceForColor col centroids
  in elemIndex (minimum distances) distances

getCentroidsDistanceForColor :: Color -> [Color] -> [Float]
getCentroidsDistanceForColor col = map (getColorDistance col)

getColorDistance :: Color -> Color -> Float
getColorDistance (Color (rA, gA, bA)) (Color (rB, gB, bB)) = sqrt
  $ int2Float
    (((rA - rB) ^ (2 :: Integer))
     + ((gA - gB) ^ (2 :: Integer))
     + ((bA - bB) ^ (2 :: Integer)))

generateRandomColor :: IO Color
generateRandomColor = do
  r <- randomRIO (0, 255) :: IO Int
  g <- randomRIO (0, 255) :: IO Int
  b <- randomRIO (0, 255) :: IO Int
  return (Color (r, g, b))

generateNRandomColors :: Int -> IO [Color]
generateNRandomColors n = generateNRandomColors' n []

generateNRandomColors' :: Int -> [Color] -> IO [Color]
generateNRandomColors' n colors
  | n <= 0 = return colors
  | otherwise = do
    col <- generateRandomColor
    previous <- generateNRandomColors' (n - 1) colors
    return (col:previous)

getAverageColor :: [Color] -> Color
getAverageColor colors = divideColorBy (getSumColorOfColors colors)
  $ length colors

getSumColorOfColors :: [Color] -> Color
getSumColorOfColors [] = Color (0, 0, 0)
getSumColorOfColors [lastColor] = lastColor
getSumColorOfColors (currentColor:rest) = addColors currentColor nextColor
  where
    nextColor = getSumColorOfColors rest

addColors :: Color -> Color -> Color
addColors (Color (rA, gA, bA)) (Color (rB, gB, bB)) =
  Color (rA + rB, gA + gB, bA + bB)

divideColorBy :: Color -> Int -> Color
divideColorBy col 0 = col
divideColorBy (Color (r, g, b)) denominator =
  Color (r `div` denominator, g `div` denominator, b `div` denominator)
