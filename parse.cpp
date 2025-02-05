#include "parse.hpp"

namespace brsh_lib {
    std::string Parser::get_infile() {
        return infile;
    }

    std::string Parser::get_outfile() {
        return outfile;
    }

    std::vector<std::vector<std::string>> Parser::get_commands() {
        return commands;
    }

    void Parser::parse_next_line() {
        tokenize_line(read_one_line());
    }

    std::string Parser::read_one_line() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    void Parser::tokenize_line(std::string line) {
        std::stringstream ss(line);
        std::string pipeline;

        // split the line into pipelines
        while (std::getline(ss >> std::ws, pipeline, '|')) {
            std::vector<std::string> args;
            std::stringstream ps(trim(pipeline));
            std::string arg;

            while (std::getline(ps >> std::ws, arg, ' ')) {
                args.push_back(trim(arg));
            }

            commands.push_back(args);
        }

        // check if the first command has an input redirection
        if (commands.size() >= 1) {
            const std::string target = "<";
            auto it = std::find(commands[0].begin(), commands[0].end(), target);
            if (it != commands[0].end()) {
                infile = *(it + 1);
                commands[0].erase(it, commands[0].end());
            } 
        }

        // check if the last command has an output redirection
        if (commands.size() >= 1) {
            const std::string target = ">";
            auto it = std::find(commands[commands.size() - 1].begin(), commands[commands.size() - 1].end(), target);
            if (it != commands[commands.size() - 1].end()) {
                outfile = *(it + 1);
                commands[commands.size() - 1].erase(it, commands[commands.size() - 1].end());
            } 
        }
    }

    std::string Parser::trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");

        if (first == std::string::npos) return ""; // Entire string is whitespace
        return str.substr(first, last - first + 1);
    }

    void Parser::debug() {
        for (auto cmd : commands) {
            std::cout << "[ ";
            for (auto arg : cmd) {
                std::cout << arg << ", ";
            }
            std::cout << "]" << std::endl;
        }
    }
}