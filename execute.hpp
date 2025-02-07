#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <sys/stat.h>
#include <sys/wait.h>

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdexcept>
#include <sstream>

#include "config.hpp"

namespace brsh_lib {
    enum ExecutorErrorType {
        INVALID_COMMAND = -256,
        BUILTIN_NOT_FOUND = -257, 
        CD_EXTRA_ARGUMENTS = -258,
    };

    class Executor {
        private:
            static constexpr std::array<std::string_view, 3> builtins = {"cd", "exit", "brsh"};

            int execute_builtin(std::vector<std::string>& args);
            int is_builtin(std::string& command);
            std::string get_current_working_directory();
            int execute_builtin_cd(std::vector<std::string>& args);
            int execute_builtin_exit();
            int execute_builtin_brsh();

            int execute_external(std::vector<std::string>& args, int in, int out);

        public:
            int execute_command(std::vector<std::string>& command, int in, int out);
    };
}

#endif