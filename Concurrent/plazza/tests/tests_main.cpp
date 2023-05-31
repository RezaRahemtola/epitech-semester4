#define CATCH_CONFIG_MAIN
#include "../src/configuration/Configuration.hpp"
#include <regex>
#define private public
#include "../src/reception/Shell.hpp"
#include "../src/reception/Shell.hpp"
#undef private

#include <catch2/catch.hpp>

TEST_CASE("Configuration", "[configuration]")
{
    SECTION("Valid arguments")
    {
        std::vector<std::string> arguments = {"path/to/file.txt", "1.5", "4", "10"};
        plazza::configuration::Configuration configuration(arguments);

        REQUIRE(configuration.getPath() == "path/to/file.txt");
        REQUIRE(configuration.getCookingTimeMultiplier() == 1.5);
        REQUIRE(configuration.getCooksNumber() == 4);
        REQUIRE(configuration.getRefillTime() == 10);
    }
    SECTION("Invalid number of arguments")
    {
        std::vector<std::string> arguments = { "path/to/file.txt", "1.5", "4" };
        REQUIRE_THROWS_AS(plazza::configuration::Configuration(arguments),
                          plazza::configuration::InvalidArgumentException);
    }
    SECTION("Invalid argument format")
    {
        std::vector<std::string> arguments = { "path/to/file.txt", "1.5", "4", "invalid" };
        REQUIRE_THROWS_AS(plazza::configuration::Configuration(arguments),
                          plazza::configuration::InvalidArgumentException);
    }
    SECTION("Invalid argument range")
    {
        std::vector<std::string> arguments = { "path/to/file.txt", "-1.5", "0", "10" };
        REQUIRE_THROWS_AS(plazza::configuration::Configuration(arguments),
                          plazza::configuration::InvalidArgumentException);
    }
}

TEST_CASE("parse and execute commands", "[commands]")
{
    SECTION("no arguments")
    {
        plazza::reception::ordering::Shell shell;
        std::string command = "";

        REQUIRE(shell.parseAndExecuteCommand(command) == false);
    }
    SECTION("wrong command")
    {
        plazza::reception::ordering::Shell shell;
        std::string command = "wrong command";

        REQUIRE(shell.parseAndExecuteCommand(command) == false);
    }
    SECTION("valid command")
    {
        plazza::reception::ordering::Shell shell;
        std::string command = "exit";

        REQUIRE(shell.parseAndExecuteCommand(command) == true);
    }
}

TEST_CASE("parse and send order", "[commands]")
{
    SECTION("bad arguments")
    {
        plazza::reception::ordering::Shell shell;
        std::string command = "order wrong arguments";

        REQUIRE(shell.parseAndSendOrder(command) == false);
    }
    SECTION("good arguments")
    {
        plazza::reception::ordering::Shell shell;
        std::string command = "regina XXL x2";

        REQUIRE(shell.parseAndSendOrder(command) == true);
    }
}

