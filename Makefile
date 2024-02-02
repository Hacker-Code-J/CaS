CC=gcc
CFLAGS=-Wall -std=c99 -g -O3 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./include

# Object files
OBJS=$(OBJDIR)/utils.o \
	 $(OBJDIR)/toycipher2.o \
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

# Rule for compiling main source files to main object files
$(OBJDIR)/main.o: main.c $(INCDIR)/config.h
	$(CC) $(CFLAGS) -c main.c -o $@

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include automatically generated dependencies
-include $(OBJS:.o=.d)

# Dependencies
$(OBJDIR)/utils.o: $(SRCDIR)/utils.c $(INCDIR)/utils.h
$(OBJDIR)/toycipher2.o: $(SRCDIR)/toycipher2.c $(INCDIR)/toycipher2.h

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d
	rm -f ./view/*.txt

# Create necessary directories
dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

lat:
	(cd bin && ./a.out > SBOX_LAT.txt)
	(cd bin && mv SBOX_LAT.txt ../view/)
	(cd view && python3 lat.py)
	