CC = g++
DEBUG = -g
CFLAGS = 
LFLAGS = -lstdc++
SOURCE = ./src/Cpu6507.h ./src/Cpu6507.cpp ./src/common.cpp ./src/common.h ./src/main.cpp ./src/rom.h ./src/rom.cpp ./src/MemoryController.h ./src/MemoryController.cpp
OBJECT = atari2600.o


$(OBJECT) : $(SOURCE) 
	$(CC) $(SOURCE) $(CFLAGS) $(LFLAGS) -o $(OBJECT) 

all: $(OBJECT)

clean: 
	rm -f $(OBJECT)
