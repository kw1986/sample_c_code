# Declaration of variables
# -g: default debug information, run gdb
# -Wall: Enable warning messages 
CC = g++ -I../inc
CC_FLAGS = -g -Wall

# File names
EXEC = test
SOURCES = linked_list.cpp test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
