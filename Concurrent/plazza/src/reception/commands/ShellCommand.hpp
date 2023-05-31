/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ShellCommand.hpp
*/

#ifndef SHELLCOMMAND_HPP_
#define SHELLCOMMAND_HPP_

#include <string>
#include <vector>

namespace plazza::reception::ordering {
    class Shell;
    namespace commands {
        class ShellCommand {
        public:
            virtual ~ShellCommand() = default;

            virtual void
            execute(Shell &shell, const std::vector<std::string> &arguments) = 0;

            [[nodiscard]] const std::string &getLabel() const;
            [[nodiscard]] const std::vector<std::string> &getAliases() const;
        protected:
            explicit ShellCommand(std::string label,
                                  const std::vector<std::string> &aliases = {})
            noexcept;

            std::string _label;
            std::vector<std::string> _aliases;
        };
    }
}

#endif //SHELLCOMMAND_HPP_
