#include "os.h"

#include <iostream>
#include <unistd.h>
#include <cstdlib>

int ProcessCreate() {
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Ошибка создания process" << std::endl;
        exit(-1);
    }
    return pid;
}

int PipeCreate(int fd[2]) {
    int err = pipe(fd);
    if (err == -1) {
        std::cerr << "Ошибка создания pipe" << std::endl;
        exit(-1);
    }
    return err;
}

int PipeRead(int fd, void * buf, size_t count) {
    int bytes = read(fd, buf, count);
    if (bytes == -1) {
        std::cerr << "Ошибка чтения из pipe" << std::endl;
        exit(-1);
    }
    return bytes;
}

int PipeWrite(int fd, const void * buf, size_t count) {
    int bytes = write(fd, buf, count);
    if (bytes == -1) {
        std::cerr << "Ошибка записи в pipe" << std::endl;
        exit(-1);
    }
    return bytes;
}

void PipeClose(int fd) {
    close(fd);
}