#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace brsh_lib {
    class Parser {
        private:
            std::string infile;
            std::string outfile;
            std::vector<std::vector<std::string>> commands;

            std::string read_one_line();
            std::string trim(const std::string& str);
            void tokenize_line(std::string line); 

        public:
            std::string get_infile();
            std::string get_outfile();
            std::vector<std::vector<std::string>> get_commands();

            void parse_next_line(); 

            void debug(); // debug purposes only.
    };
}

#endif