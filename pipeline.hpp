#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <unistd.h>

#include <array>

/*

stdin of first command is either 0 or input redirect
next command stdin is stdout of first command 
...
pattern: 
    create a pipeline class that can be called to get the proper IO descriptor. 
    the logic for creating the pipes can be completely abstracted out of the main loop this way. 

    first cmd will set in fd to starting input fd, create a pipe for the out pipe, and set the out fd to the read end of the out pipe
    run cmd...
    set the in_pipe write end to the out pipe write end 
    set the in_pipe read end to the out pipe read end 
    second command will close the read end of the in_pipe and set the input_fd to the write end of the in pipe
    if this is the last stage then out fd gets set to proper final out, otherwise init out_pipe and set out fd to the pipes write end 
    run cmd...
    close in_pipe write end
    move both output pipe fd's into in_pipe indicies
    repeat until done. 
...
stdout of last command is either 1 or output redirect

*/

namespace brsh_lib {
    class Pipeline {
        private:
            int in_fd;              // line start stdin
            int out_fd;             // line end stdout

            std::array<int, 2> in_pipe;
            std::array<int, 2> out_pipe;


        public:
            Pipeline(int start_in, int final_out);
            void setup_current_descriptors(int& in, int& out, bool first, bool last);
            void transition_pipes(bool first);
    };
}

#endif 