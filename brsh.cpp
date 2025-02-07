#include <fcntl.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "config.hpp"
#include "parse.hpp"
#include "execute.hpp"

int main() {
    brsh_lib::Executor executor;

    while (true) {
        brsh_lib::Parser parser;
        std::cout << config::prompt;
        parser.parse_next_line(); 

        std::vector<std::vector<std::string>> cmds = parser.get_commands();
        if (cmds.empty()) 
            continue;

        for (std::vector<std::string> cmd : cmds) {
            int in = 0;
            int out = 1;

            if (cmd == cmds[0] && !parser.get_infile().empty()) {
                int redirect_in = open(parser.get_infile().c_str(), O_RDONLY);
                if (redirect_in != -1)
                    in = redirect_in;
            }

            if (cmd == cmds[cmds.size()-1]) {
                int mode = S_IRWXU | S_IRWXG | S_IRWXO;

                if (!parser.get_append_outfile().empty())  {
                    int redirect_append_out = open(parser.get_append_outfile().c_str(), O_CREAT | O_WRONLY | O_APPEND, mode);
                    if (redirect_append_out != -1)
                        out = redirect_append_out;
                } else if (!parser.get_overwrite_outfile().empty()) {
                    // TODO: Find a way to clear the contents of the file first.
                    int redirect_overwrite_out = open(parser.get_overwrite_outfile().c_str(), O_CREAT | O_WRONLY, mode);
                    if (redirect_overwrite_out != -1)
                        out = redirect_overwrite_out;
               }
            }

            executor.execute_command(cmd, in, out);
        } 
    }

    return 0;
}