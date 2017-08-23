CC = g++
DEBUG = -g
CFLAGS = 
LFLAGS = -lstdc++
SOURCE = Cpu6507.h Cpu6507.cpp common.cpp common.h main.cpp rom.h rom.cpp
OBJECT = atari2600.o


$(OBJECT) : $(SOURCE) 
	$(CC) $(SOURCE) $(CFLAGS) $(LFLAGS) -o $(OBJECT) 

all: $(OBJECT)

clean: 
	rm $(OBJECT)
