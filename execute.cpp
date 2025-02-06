#include "execute.hpp"

namespace brsh_lib {
    Executor::Executor() {
        const char* env_var = "PATH";

        if (std::getenv(env_var) == nullptr) {
            std::ostringstream oss;
            oss << "$" << env_var << " environment variable not found." << std::endl;
            std::string result = oss.str();
            throw std::runtime_error(result);
        }

        std::stringstream ss(std::getenv(env_var));
        std::string path;

        while (std::getline(ss, path, ':')) {
            paths.push_back(path);
        }
    }

    int Executor::execute_command(std::vector<std::string> command, int in, int out) {
        (void) in;
        (void) out;
        return execute_builtin(command);
    }

    int Executor::execute_builtin(std::vector<std::string> args) {
        if (args.size() == 0) {
            return ExecutorErrorType::INVALID_COMMAND;
        }

        std::string command = args[0];
        int builtin = is_builtin(command);

        switch (builtin) {
            case 0:
                return execute_builtin_cd(args);
            case 1:
                return execute_builtin_exit();
            case 2:
                return execute_builtin_brsh();
            default:
                break;
        }

        return ExecutorErrorType::BUILTIN_NOT_FOUND;
    }

    int Executor::is_builtin(std::string command) {
        for (int i = 0; i < 3; i++) {
            if (command == builtins[i]) {
                return i;
            }
        }

        return ExecutorErrorType::BUILTIN_NOT_FOUND;
    }

    // TODO: Fix this.
    int Executor::execute_builtin_cd(std::vector<std::string> args) {
        int res;

        if (args.size() == 1) {
            if ((res = chdir(getenv("HOME"))) != 0) {
                return -errno;
            }
        } else if (args.size() == 2) {
            if ((res = chdir(args[1].c_str())) != 0) {
                return -errno;
            }
        } else {
            return ExecutorErrorType::CD_EXTRA_ARGUMENTS;
        }

        return 0;
    }

    int Executor::execute_builtin_exit() {
        exit(0);
    }

    int Executor::execute_builtin_brsh() {
       std::cout << R"(
 __                       __      
[  |                     [  |     
 | |.--.   _ .--.  .--.   | |--.  
 | '/'`\ \[ `/'`\]( (`\]  | .-. | 
 |  \__/ | | |     `'.'.  | | | | 
[__;.__.' [___]   [\__) )[___]|__]
       )" << std::endl;
       std::cout << "brsh v" << config::version << std::endl;
       std::cout << "author(s): " << config::author << std::endl << std::endl;

       return 0;
    }

    std::string Executor::get_current_working_directory() {
        char buffer[PATH_MAX]; // Maximum path length
        if (getcwd(buffer, sizeof(buffer)) != nullptr) {
            return std::string(buffer);
        } else {
            perror("getcwd failed"); // Print error message
            return "";
        }
    }
}