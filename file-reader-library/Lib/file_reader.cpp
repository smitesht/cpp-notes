#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include "file_reader.h"

extern "C" {

    /*

    The function read the first line of file. 
    The function returns number of bytes it read of a given file descriptor

    Parameters:
    fd: file descriptor. [input]
    buffer: contains content of the file [output]
    n: size of buffer [input]

    */
    ssize_t file_2_user(int fd, void* buffer, size_t n)
    {
        ssize_t numRead; size_t totRead; char* buf; char ch;

        // return error or -1 if the size of the buffer is not given or NULL or < 0 
        if (n <= 0 || buffer == NULL) {
            errno = EINVAL;
            return -1;
        }
        buf = (char*)buffer;
        totRead = 0;

        // Read file character by character
        for (;;) {

            // read system call
            numRead = read(fd, &ch, 1);

            // if received interrupt signal continue reading o.w. return error with code -1
            if (numRead == -1) {
                if (errno == EINTR)
                    continue;
                else
                    return -1;
            }

            // file empty, reaturn 0
            else if (numRead == 0) {
                if (totRead == 0)
                    return 0;
                else
                    break;
            }

            // read the file untill '\n' and return number of bytes and exit the loop.
            else {
                if (totRead < n - 1) {
                    totRead++;
                    *buf++ = ch;
                }
                if (ch == '\n')
                    break;
            }
        }
        *buf = '\0';
        return totRead;
    }

}