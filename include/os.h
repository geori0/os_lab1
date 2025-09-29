#pragma once

#include <cstddef>

int ProcessCreate();
int PipeCreate(int fd[2]);
int PipeRead(int fd, void * buf, size_t count);
int PipeWrite(int fd, const void * buf, size_t count);
void PipeClose(int fd);