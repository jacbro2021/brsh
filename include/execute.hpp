#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <deque>

#include "config.hpp"
#include "history.hpp"

namespace brsh_lib {
    enum ExecutorErrorType {
        INVALID_COMMAND = -256,
        BUILTIN_NOT_FOUND = -257, 
        CD_EXTRA_ARGUMENTS = -258,
        R_INCORRECT_ARGUMENTS = -259,
    };

    class Executor {
        private:
            static constexpr std::array<std::string_view, 5> builtins = {"cd", "exit", "brsh", "history", "r"};
            brsh_lib::HistoryTracker* tracker;
            std::string queued_cmd = "";
            bool executing_r_flag = false;

            int execute_builtin(std::vector<std::string>& args);
            int is_builtin(std::string& command);
            std::string get_current_working_directory();
            int execute_builtin_cd(std::vector<std::string>& args);
            int execute_builtin_exit();
            int execute_builtin_history();
            int execute_builtin_r(std::vector<std::string>& args);

            int execute_external(std::vector<std::string>& args, int in, int out);

        public:
            Executor(brsh_lib::HistoryTracker* _tracker) : tracker(_tracker) {}
            int execute_command(std::vector<std::string>& command, int in, int out);
            int execute_builtin_brsh();

            std::string get_queued_cmd();
            void reset_queued_cmd();

            bool is_executing_r();
            void reset_is_executing_r();
    };
}

#endif