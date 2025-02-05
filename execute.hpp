#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <limits.h>

#include "config.hpp"

namespace brsh_lib {
    enum ExecutorErrorType {
        INVALID_COMMAND = -256,
        BUILTIN_NOT_FOUND = -257, 
        CD_EXTRA_ARGUMENTS = -258,
    };

    class Executor {
        private:
            std::vector<std::string> paths;
            const std::string builtins[3] = {"cd", "exit", "brsh"};

            int is_builtin(std::string command);
            std::string get_current_working_directory();
            int execute_builtin(std::vector<std::string> args);
            int execute_builtin_cd(std::vector<std::string> args);
            int execute_builtin_exit(std::vector<std::string> args);
            int execute_builtin_brsh(std::vector<std::string> args);

        public:
            int execute_command(std::vector<std::string> command, int in, int out);
    };
}

#endif