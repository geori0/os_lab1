#pragma once

#include <cstddef>

enum ProcessRole {
    IS_PARENT,
    IS_CHILD
};

ProcessRole ProcessCreate();

int PipeCreate(int fd[2]);
int PipeRead(int fd, void * buf, size_t count);
int PipeWrite(int fd, const void * buf, size_t count);
void PipeClose(int fd);
int RedirectFd(int old_fd, int new_fd);