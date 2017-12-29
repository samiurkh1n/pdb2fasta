# PDB2FASTA Converter Makefile

CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -o3
DBGFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -g

EXECUTABLE = pdb2fasta
PROJECTFILE = pdb2fasta.cpp

main: $(PROJECTFILE) protein.o
	g++ $(CXXFLAGS) $(PROJECTFILE) protein.cpp -o pdb2fasta

debug: $(PROJECTFILE) protein.o
	g++ $(DBGFLAGS) $(PROJECTFILE) protein.cpp -o pdb2fasta_debug

clean:
	rm -rf $(EXECUTABLE) $(EXECUTABLE)_debug $(EXECUTABLE)_debug.dSYM *.o

.PHONY: main debug clean
