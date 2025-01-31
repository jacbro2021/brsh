#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace parser {
    class Parser {
        private:
            std::string line;
            std::string read_one_line();
            std::vector<std::string> tokenize_line(); 

        public:
           std::vector<std::string> parse_next_line(); 
    };
}

#endif