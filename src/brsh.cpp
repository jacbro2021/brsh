#include <fcntl.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "config.hpp"
#include "parse.hpp"
#include "execute.hpp"
#include "pipeline.hpp"
#include "history.hpp"

int main() {
    constexpr int outfile_mode = S_IRWXU | S_IRWXG | S_IRWXO;
    brsh_lib::HistoryTracker* tracker = new brsh_lib::HistoryTracker(HISTORY_LENGTH);
    brsh_lib::Executor executor = brsh_lib::Executor(tracker);
    executor.execute_builtin_brsh();

    while (true) {
        int in = 0;
        int out = 1;
        brsh_lib::Parser parser;

        std::string queued_cmd;
        if ((queued_cmd = executor.get_queued_cmd()).empty()) {
            std::cout << config::red << config::prompt << config::reset;
            parser.parse_next_line(); 
            tracker->queue_command(parser.get_raw_line());
        } else {
            parser.tokenize_line(queued_cmd);
        }

        std::vector<std::vector<std::string>> cmds = parser.get_commands();
        if (cmds.empty()) 
            continue;

        if (!parser.get_infile().empty()) {
            int redirect_in = open(parser.get_infile().c_str(), O_RDONLY);
            if (redirect_in != -1)
                in = redirect_in;
        }

        if (!parser.get_append_outfile().empty())  {
            int redirect_append_out = open(parser.get_append_outfile().c_str(), O_WRONLY | O_CREAT | O_APPEND, outfile_mode);
            if (redirect_append_out != -1)
                out = redirect_append_out;
        } else if (!parser.get_overwrite_outfile().empty()) {
            int redirect_overwrite_out = open(parser.get_overwrite_outfile().c_str(), O_WRONLY | O_CREAT | O_TRUNC, outfile_mode);
            if (redirect_overwrite_out != -1)
                out = redirect_overwrite_out;
        }

        brsh_lib::Pipeline pipeline = brsh_lib::Pipeline(in, out);

        for (std::vector<std::string> cmd : cmds) {
            int cur_in, cur_out;
            bool first = (cmd == cmds.front());
            bool last = (cmd == cmds.back());

            pipeline.setup_current_descriptors(cur_in, cur_out, first, last);
            executor.execute_command(cmd, cur_in, cur_out);
            pipeline.transition_pipes(first);
        } 

        if (!queued_cmd.empty()) {
            executor.reset_queued_cmd();
        } else if (!executor.is_executing_r()) {
            tracker->commit_queued_command();
        } else {
            executor.reset_is_executing_r();
        }
    } // while(true)

    delete tracker;
    return 0;
}

