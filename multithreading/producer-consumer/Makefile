CC = g++

CFLAGS = -Wall

DFLAGS = -g

TARGET = pc.exe

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

all: $(TARGET)

$(TARGET):	$(OBJS)
	@echo ------------------------------------------
	@echo building $@ ...
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $^
	@echo $@ built !
	@echo ------------------------------------------

clean:
	@echo ------------------------------------------
	@echo cleaning
	-rm -r *.o
	-rm $(TARGET)
	-rm -f *~
	@echo project cleaned!
	@echo ------------------------------------------