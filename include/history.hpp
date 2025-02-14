#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept> 

#define HISTORY_LENGTH 1000

namespace brsh_lib {
    class HistoryTracker {
        private:
            std::deque<std::string> stack;
            std::string queued_command = "";
            size_t maxSize;

        public:
            HistoryTracker(size_t maxSize) : maxSize(maxSize) {}
            std::string get_prev_cmd(size_t ind);
            std::deque<std::string> get_history();

            void queue_command(std::string cmd);
            void commit_queued_command();
    };
}

#endif