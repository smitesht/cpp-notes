# This code contains the demonstration of library creation and usage of the library in C++.

### Lib
This folder contains the library code. 

The files file_reader.h declare a function called file_2_user() that reads the file.
The file_reader.cpp implement file_2_user() the function defined by file_reader.h. 
The function reads the file based on given handler and return the total bytes of the first line of the file.

How to build library: 
Run the below command on your command prompt to create a shared library.

command_prompt> make all


### client

This folder use the library created in Lib folder.

The main function open the file that needs to be read, and calls the file_2_user() library function to read the file. The main also print the number of bytes read and content of the file.

How to build main:

1) Copy libmylib.so and file_reader.h in client folder.

2) Run the below command on your command prompt to create a binary.

command_prompt> make all

3) Display Output: 
command_prompt> ./main