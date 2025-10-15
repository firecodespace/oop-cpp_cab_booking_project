# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++11

# Directories
INCDIR = include
SRCDIR = src
OBJDIR = obj

# Target executable
TARGET = ride_booking

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp) main.cpp

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter $(SRCDIR)/%.cpp,$(SRCS))) $(OBJDIR)/main.o

# Default target
all: $(OBJDIR) $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "✓ Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c main.cpp -o $(OBJDIR)/main.o

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "✓ Clean successful!"

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
