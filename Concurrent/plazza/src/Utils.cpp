/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** utils.cpp
*/

#include <vector>
#include <string>
#include <regex>

namespace plazza::utils {
    std::vector<std::string> split(const std::string &str, const std::regex &separator)
    {
        std::vector<std::string> result;
        std::copy(std::sregex_token_iterator(str.begin(), str.end(), separator, -1),
                  std::sregex_token_iterator(),
                  std::back_inserter(result));
        return result;
    }
}
