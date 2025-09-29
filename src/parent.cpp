#include "os.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <string>

int main() {
    int pipe_to_child[2];
    int pipe_from_child[2];
    PipeCreate(pipe_to_child);
    PipeCreate(pipe_from_child);

    pid_t pid = ProcessCreate();
    if (pid == 0) {
        PipeClose(pipe_to_child[1]);
        dup2(pipe_to_child[0], 0);
        PipeClose(pipe_to_child[0]);
        PipeClose(pipe_from_child[0]);
        dup2(pipe_from_child[1], 1);
        PipeClose(pipe_from_child[1]);
        execl("./child", "child", NULL);
        std::cerr << "Ошибка execl" << std::endl;
        exit(-1);
    }
    if (pid > 0) {
        PipeClose(pipe_to_child[0]);
        PipeClose(pipe_from_child[1]);

        std::string file_name;
        std::cin >> file_name;
        std::string data = file_name + "\n";
        PipeWrite(pipe_to_child[1], data.c_str(), data.size());

        int number;
        int message;
        while (true) {
            if (!(std::cin >> number)) {
                break;
            }
            PipeWrite(pipe_to_child[1], &number, sizeof(number));
            PipeRead(pipe_from_child[0], &message, sizeof(message));
            if (message == 1) {
                break;
            }
        }

        PipeClose(pipe_to_child[1]);
        PipeClose(pipe_from_child[0]);
    }
    return 0;
}