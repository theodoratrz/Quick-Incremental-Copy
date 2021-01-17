# paths
MODULES = ./modules
INCLUDE = ./include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -g -I$(INCLUDE)

# Αρχεία .o
OBJS_S = $(MODULES)/is_dir.o
OBJS =  $(MODULES)/quic.o $(MODULES)/search_and_compare.o 

# Το εκτελέσιμο πρόγραμμα
EXEC = quic

$(EXEC): $(OBJS) $(OBJS_S)
	$(CC) $(OBJS) $(OBJS_S) -o $(EXEC) 
