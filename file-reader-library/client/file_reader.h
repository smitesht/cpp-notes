#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>

extern "C" {

    ssize_t file_2_user(int fd, void *buffer, size_t n);
}



#endif