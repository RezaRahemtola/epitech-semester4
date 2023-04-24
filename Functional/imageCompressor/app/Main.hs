{-
-- EPITECH PROJECT, 2023
-- app
-- File description:
-- $DESCRIPTION
-}
module Main (main) where

import           Parsing (getOpts, Conf(confFile))
import           System.Exit (exitWith, ExitCode(ExitFailure), exitSuccess)
import           System.IO (hPutStrLn, stderr)
import           System.Environment (getArgs)
import           FileParsing (parseImage)
import           KMeans (runKMeans, sortPixelsIntoCentroids, Pixel, Color)
import           Control.Exception.Base (IOException, catch)

exitError :: String -> IO ()
exitError msg = hPutStrLn stderr ("Error: " ++ msg)
  >> exitWith (ExitFailure 84)

openImage :: String -> IO String
openImage file = catch (readFile file) handler
  where
    handler :: IOException -> IO String
    handler _ = return ""

main :: IO ()
main = do
  cliArgs <- getArgs
  case getOpts cliArgs of
    Nothing   -> exitError "Invalid configuration"
    Just conf -> do
      content <- openImage $ confFile conf
      let pixels = parseImage content
      if content /= "" && not (null pixels)
        then runKMeans pixels conf >>= displayClusters pixels >> exitSuccess
        else exitError "Invalid file"

displayClusters :: [Pixel] -> [Color] -> IO ()
displayClusters pixels centroids = mapM_
  (\(cluster, centroid) -> putStrLn ("--\n" ++ show centroid ++ "\n-")
   >> mapM_ print cluster)
  (zip (sortPixelsIntoCentroids pixels centroids) centroids)
