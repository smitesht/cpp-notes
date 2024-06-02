# Variables
CXX = g++

CXXFLAGS = -Wall -std=c++17

DFLAGS = -g

TARGET = async.exe

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@echo ---------------------------------------------
	@echo building $@ ...
	$(CXX) $(CXXFLAGS) $(DFLAGS) -o $@ $^
	@echo $@ built !
	@echo ----------------------------------------------

clean:
	@echo ----------------------------------------------
	@echo cleaning
	-rm -rf *.o
	-rm $(TARGET)
	-rm -f *~
	@echo project cleaned!
	@echo ----------------------------------------------
