CC = gcc
CFLAGS = -std=gnu99
TARGET = reverse
OBJS = main.o stack.o 
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c
stack.o: stack.c 
	$(CC) $(CFLAGS) -c stack.c 
clean:
	/bin/rm -f *.o 
clean_all:
	/bin/rm -f *.o $(TARGET)
