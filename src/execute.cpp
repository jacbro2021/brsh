#include "execute.hpp"

namespace brsh_lib {
    int Executor::execute_command(std::vector<std::string>& cmd, int in, int out) {
        if (cmd.empty()) {
            return 0;
        }

        if (is_builtin(cmd[0]) == ExecutorErrorType::BUILTIN_NOT_FOUND) {
            return execute_external(cmd, in, out);
        }

        return execute_builtin(cmd);
    }

    int Executor::execute_builtin(std::vector<std::string>& args) {
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
            case 3:
                return execute_builtin_history();
            case 4:
                return execute_builtin_r(args);
            default:
                break;
        }

        return ExecutorErrorType::BUILTIN_NOT_FOUND;
    }

    int Executor::is_builtin(std::string& command) {
        for (size_t i = 0; i < builtins.size(); i++) {
            if (command == builtins[i]) {
                return (int)i;
            }
        }

        return ExecutorErrorType::BUILTIN_NOT_FOUND;
    }

    // TODO: Fix this.
    int Executor::execute_builtin_cd(std::vector<std::string>& args) {
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
       std::cout << config::ascii << std::endl;
       std::cout << "brsh v" << config::version << std::endl;
       std::cout << "author(s): " << config::author << std::endl << std::endl;
       return 0;
    }

    int Executor::execute_builtin_history() {
        tracker->commit_queued_command();
        int size = tracker->get_history().size();
        int offset = 0;

        for (auto cmd : tracker->get_history()) {
            std::cout << size - (offset++) << " " << cmd << std::endl;
        } 

        return 0;
    }

    int Executor::execute_builtin_r(std::vector<std::string>& args) {
        (void) args; // DELETE ME
        int ind;
        executing_r_flag = true;

        if (args.size() > 2) {
            return R_INCORRECT_ARGUMENTS;
        }
        
        if (args.size() == 2) {
            try {
                ind = std::stoi(args[1]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
                return R_INCORRECT_ARGUMENTS;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << std::endl;
                return R_INCORRECT_ARGUMENTS;
            }
        } else {
            ind = 1;
        }

        queued_cmd = tracker->get_prev_cmd(ind);
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

    int Executor::execute_external(std::vector<std::string>& cmd, int in, int out) {
        if (cmd.empty()) { 
            return 0;
        }

        std::array<int, 2> parent_to_child;
        std::array<int, 2> child_to_parent;
        pipe(parent_to_child.data());
        pipe(child_to_parent.data());
        dup2(in, parent_to_child[0]);
        dup2(out, child_to_parent[1]);

        pid_t pid = fork();
        if (pid == -1) {
            // Should add better error handling here.
            return -1;
        } else if (pid == 0) {
            close(parent_to_child[1]);
            dup2(parent_to_child[0], 0);

            close(child_to_parent[0]);
            dup2(child_to_parent[1], 1);

            std::vector<char*> argv;
            for (auto& arg : cmd)
                argv.push_back(&arg[0]);
            argv.push_back(nullptr); 

            execvp(argv[0], argv.data());

            // If child fails then exit with error.
            // could use some better error handling here.
            exit(-1); 
        } else {
            close(parent_to_child[0]);
            close(child_to_parent[1]);

            int status;
            wait(&status); // Wait for child to finish
        }

        return 0;
    }

    std::string Executor::get_queued_cmd() {
        return queued_cmd;
    }

    void Executor::reset_queued_cmd() {
        queued_cmd = "";
    }

    bool Executor::is_executing_r() {
        return executing_r_flag;
    }

    void Executor::reset_is_executing_r() {
        executing_r_flag = false;
    }
}