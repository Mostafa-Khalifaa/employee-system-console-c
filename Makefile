# Compiler and options
CC = gcc
CFLAGS = -Wall -g

# All .c files in project folder (added employee.c)
SRCS = main.c color.c cursor.c draw.c screen.c input.c menu.c employee.c
OBJS = $(SRCS:.c=.o)
TARGET = task11

# Main rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule for each .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean temporary files
clean:
	rm -f *.o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
