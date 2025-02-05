#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "parse.hpp"
#include "execute.hpp"

int main() {
    brsh_lib::Executor executor;

    while (true) {
        brsh_lib::Parser parser;
        std::cout << config::prompt;
        parser.parse_next_line(); 
        executor.execute_command(parser.get_commands()[0], 0, 1);
    }

    return 0;
}