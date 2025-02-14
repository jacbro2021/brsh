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
            std::string append_outfile;
            std::string overwrite_outfile;
            std::vector<std::vector<std::string>> commands;
            std::string raw_line;

            std::string read_one_line();
            std::string trim(const std::string& str);
            void tokenize_line(std::string line); 

        public:
            std::string get_infile();
            std::string get_append_outfile();
            std::string get_overwrite_outfile();
            std::vector<std::vector<std::string>> get_commands();
            std::string get_raw_line();

            void parse_next_line(); 

            void debug(); // debug purposes only.
    };
}

#endif