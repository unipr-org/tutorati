# compilatore e flag
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -I./header -I./header/interface

ifeq ($(DEBUG),1)
    CXXFLAGS += -g -DDEBUG
endif

# directory presenti
SRCDIR = source
HEADERDIR = header
OBJDIR = obj

# sorgenti e oggetti
SOURCES = $(wildcard $(SRCDIR)/*.cc) main.cc
OBJECTS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cc)) $(OBJDIR)/main.o

# nome dell'eseguibile
TARGET = scheduler

# regola di compilazione
all: directories $(TARGET)

# creazione della directory per i file oggetto
directories:
	mkdir -p $(OBJDIR)

# compilazione
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# compilazione dei file sorgenti
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# compilazione del main.cc
$(OBJDIR)/main.o: main.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# rimozione dei file compilati
clean:
	rm -rf $(OBJDIR) $(TARGET)

# ricomiplazione tutto
rebuild: clean all

# Target non-file
.PHONY: all clean rebuild directories
