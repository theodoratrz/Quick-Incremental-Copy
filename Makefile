# paths
MODULES = ./modules
INCLUDE = ./include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -g -I$(INCLUDE)

# Αρχεία .o
OBJS =  $(MODULES)/quic.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quic

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) 
