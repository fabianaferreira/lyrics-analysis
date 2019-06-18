CC=g++
CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts -e ldopts)
LD=g++
LDFLAGS=$(shell perl -MExtUtils::Embed -e ccopts -e ldopts)

OBJS= main.o functions.o perlWrapper.o 

EXEC= main

.cpp.o:
	$(CC) -c $< $(CCFLAGS)

all: $(EXEC)

main: $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC)
