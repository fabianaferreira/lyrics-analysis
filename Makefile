# Universidade Federal do Rio de Janeiro - UFRJ
# Departamento de Engenharia Eletrônica e de Computação - DEL 
# Disciplina de Linguagens de Programação 2019.1
# Trabalho: Gerenciador de Busca de Cifras
# Alunas: Fabiana Ferreira e Tamine Alves

CC=g++
CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts -e ldopts)
LD=g++
LDFLAGS=$(shell perl -MExtUtils::Embed -e ccopts -e ldopts)

OBJS= main.o functions.o perlWrapper.o lyricsAnalysis.o

EXEC= main

.cpp.o:
	$(CC) -c $< $(CCFLAGS)

all: $(EXEC)

main: $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC)
