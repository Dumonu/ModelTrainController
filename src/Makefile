EXEC=program
CXX=gcc
CC=gcc
CXXFLAGS=-Wall
CPPFLAGS=-Wall
FILES=ui.c main.c command.c

all: $(EXEC)

clean:
	rm -rf *~ *.o \#* $(EXEC)

$(EXEC): $(FILES)
	$(CXX) $(CXXFLAGS) $(OBJS) $(FILES) -o $(EXEC) -lncurses
