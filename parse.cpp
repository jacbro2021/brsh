#include "parse.hpp"

namespace parser {
    std::string Parser::read_one_line() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    std::vector<std::string> Parser::tokenize_line() {
        std::vector<std::string> tokens;
        std::string token;

        for (char c : line) {
            if (c == ' ') {
                tokens.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }

        return tokens;
    }

    std::vector<std::string> Parser::parse_next_line() {
        line = read_one_line();
        return tokenize_line();
    }
}