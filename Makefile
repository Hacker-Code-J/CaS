CC=gcc
CFLAGS=-Wall -std=c99 -g -O3 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./include

# Object files
OBJS=$(OBJDIR)/utils.o $(OBJDIR)/lat.o\
	 $(OBJDIR)/toy_cipher3.o \
	 $(OBJDIR)/main.o

# Executable
TARGET=$(BINDIR)/a.out

# Phony Targets
.PHONY: all clean dir rebuild

# Default target
all: dir $(TARGET)

# Rule for building the final target
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include automatically generated dependencies
-include $(OBJS:.o=.d)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d
	rm -f ./view/*.txt

# Create necessary directories
dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

run:
	(cd bin && ./a.out)

lat:
	(cd bin && ./a.out > SBOX_LAT.txt)
	(cd bin && mv SBOX_LAT.txt ../view/)
	(cd view && python3 lat.py)
	