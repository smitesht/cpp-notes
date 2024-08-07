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