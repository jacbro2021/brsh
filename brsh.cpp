#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "parse.hpp"

int main() {
    parser::Parser p;

    while (true) {
        std::cout << config::prompt;
        std::vector<std::string> tokens = p.parse_next_line();

        for (auto tok : tokens) {
            std::cout << tok << std::endl;
        }
    }

    return 0;
}