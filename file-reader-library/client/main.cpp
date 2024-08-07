#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include "file_reader.h"

int main()
{

    std::cout << "Starting main....."<<std::endl;

    char* file = "001sample_c.c";

    int fd = open(file, 2);

    if (fd == -1)
    {
        std::cout << "Error while opening file" << std::endl;
    }

    char buffer[5000];

    ssize_t bytesRead = file_2_user(fd, buffer, sizeof(buffer));

    std::cout <<"Total bytes read: "<<bytesRead << std::endl;
    std::cout <<"Buffer Content: "<< buffer << std::endl;
    
    return 0;

}
