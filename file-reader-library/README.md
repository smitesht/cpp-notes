# This code contains the demonstration of library creation and usage of the library in C++.

### Lib
This folder contains the library code. 

The files file_reader.h declare a function called file_2_user() that reads the file.
The file_reader.cpp implement file_2_user() the function defined by file_reader.h. 
The function reads the file based on given handler and return the total bytes of the first line of the file.

**How to build library:** 

Run the below command on your command prompt to create a shared library.

**command_prompt> make all**

```cpp
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
```
Makefile
```cpp
CXX = g++

CXXFLAGS = -Wall -fpic

DFLAGS = -g

LIBNAME = mylib
LIBSRC = file_reader.cpp
LIBOBJ = $(LIBSRC:.cpp=.o)
LIBSO = lib$(LIBNAME).so

all:$(LIBSO)


$(LIBSO): $(LIBOBJ)
	@echo --------------------------------------------
	@echo Buliding shared library $@
	$(CXX) -shared -o $@ $^
	@echo Shared library $@ built!	
	@echo --------------------------------------------
	
clean:
	@echo ----------------------------------------------
	@echo Cleaning
	-rm -f *.o $(LIBSO)
	-rm -f *~
	@echo Project cleaned!
	@echo ----------------------------------------------
```

### client

This folder use the library created in Lib folder.

The main function open the file that needs to be read, and calls the file_2_user() library function to read the file. The main also print the number of bytes read and content of the file.

How to build main:

- Copy libmylib.so and file_reader.h in client folder.

- Run the below command on your command prompt to create a binary.

  **command_prompt> make all**

- Add the library location to the **LD_LIBRARY_PATH** environment variable
**export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH**

- Display Output: 
  **command_prompt> ./main**

Code:
```cpp
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

```

Makefile

```cpp
CXX = g++

CXXFLAGS = -Wall

DFLAGS = -g

TARGET = main
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

LIBNAME = mylib
LIBSO = lib$(LIBNAME).so

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo ---------------------------------------------
	@echo Building client program $@
	$(CXX) $(CXXFLAGS) $(DFLAGS) -o $@ $^ -L. -l$(LIBNAME)
	@echo Client program $@ built!
	@echo ----------------------------------------------
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@
	
clean:
	@echo ----------------------------------------------
	@echo Cleaning
	-rm -f *.o $(TARGET)
	-rm -f *~
	@echo Project cleaned!
	@echo ----------------------------------------------

```
  
