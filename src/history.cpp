#include "history.hpp"

namespace brsh_lib {
    std::string HistoryTracker::get_prev_cmd(size_t ind) {
        if (ind == 0) {
            return stack.back();
        } else if (ind >= stack.size()) {
            return "";
        } else {
            return stack[stack.size() - ind];
        }
    }

    std::deque<std::string> HistoryTracker::get_history() {
        return stack;
    }

    void HistoryTracker::queue_command(std::string cmd) {
        queued_command = cmd;
    }

    void HistoryTracker::commit_queued_command() {
        if (queued_command == "" || (stack.size() > 0 && stack.back() == queued_command)) {
            return;
        }

        if (stack.size() == maxSize) {
           stack.pop_front(); 
        } 

        stack.push_back(queued_command);
        queued_command = "";
    }
}