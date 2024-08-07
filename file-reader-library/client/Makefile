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