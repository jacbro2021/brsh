#include "pipeline.hpp"

namespace brsh_lib {
    Pipeline::Pipeline(int start_in, int final_out) {
        in_fd = start_in;
        out_fd = final_out;
    }

    void Pipeline::setup_current_descriptors(int& in, int& out, bool first, bool last) {
        if (first) {
            in = in_fd;
        } else {
            close(in_pipe[1]);
            in = in_pipe[0];
        }

        if (last) {
            out = out_fd;
        } else {
            pipe(out_pipe.data());
            out = out_pipe[1];
        }

        return;
    }

    void Pipeline::transition_pipes(bool first) {
        if (!first) {
            close(in_pipe[0]);
        }

        in_pipe[0] = out_pipe[0];
        in_pipe[1] = out_pipe[1];
    }
}