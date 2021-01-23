# paths
MODULES = ./modules
INCLUDE = ./include

all:	quic \
		directories \
		files \
		List \

clean: 
	rm -f 	quic \
		directories.o \
		files.o \
		List.o \

List: $(MODULES)/List.c
	gcc -Wall -g -I$(INCLUDE) $(MODULES)/List.c -c 

files: $(MODULES)/files.c $(MODULES)/List.c
	gcc -Wall -g -I$(INCLUDE) $(MODULES)/files.c $(MODULES)/List.c -c 

directories: $(MODULES)/directories.c $(MODULES)/files.c
	gcc -Wall -g -I$(INCLUDE) $(MODULES)/directories.c $(MODULES)/files.c -c 

quic: $(MODULES)/quic.c $(MODULES)/directories.c $(MODULES)/files.c $(MODULES)/List.c
	gcc -Wall -g -I$(INCLUDE) $(MODULES)/quic.c $(MODULES)/directories.c $(MODULES)/files.c $(MODULES)/List.c -c



