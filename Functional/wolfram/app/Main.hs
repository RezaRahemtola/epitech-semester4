{-
-- EPITECH PROJECT, 2023
-- app
-- File description:
-- $DESCRIPTION
-}
module Main (main) where

import           System.Environment (getArgs)
import           System.Exit (exitWith, ExitCode(ExitFailure))
import           Parsing (getOpts)
import           System.IO (hPutStrLn, stderr)
import           Automaton (automaton)

exitError :: String -> IO ()
exitError msg = hPutStrLn stderr ("Error: " ++ msg)
  >> exitWith (ExitFailure 84)

main :: IO ()
main = do
  cliArgs <- getArgs
  case getOpts cliArgs of
    Nothing   -> exitError "Invalid configuration"
    Just conf -> automaton conf
