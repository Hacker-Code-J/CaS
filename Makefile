CC=gcc
CFLAGS=-Wall -g -O3 -I./include  # Include directory for header files
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./include

# Object files
OBJS=$(OBJDIR)/SBOX_LAT.o $(OBJDIR)/main.o

# Executable
TARGET=$(BINDIR)/SBOX_LAT

# Phony Targets
.PHONY: all clean dir rebuild

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Pattern rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include automatically generated dependencies
-include $(OBJS:.o=.d)

# Dependencies
$(OBJDIR)/SBOX_LAT.o: $(SRCDIR)/SBOX_LAT.c $(INCDIR)/linear_analysis.h
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/config.h

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d
	rm -f ./view/*.txt

# Create necessary directories
dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

lat:
	(cd bin && ./SBOX_LAT > SBOX_LAT.txt)
	(cd bin && mv SBOX_LAT.txt ../view/)
	(cd view && python3 SBOX_LAT.py)
	