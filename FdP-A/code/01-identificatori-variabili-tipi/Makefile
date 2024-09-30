# Variabili
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
SRC_FILES = area-rettangolo.cpp chilometri-metri.cpp differenza-quadrati.cpp interesse-composto.cpp minuti-secondi.cpp pari-dispari.cpp perimetro-quadrato.cpp prodotto-tre-numeri.cpp velocita-media.cpp
BIN_DIR = bin
TARGETS = $(SRC_FILES:%.cpp=$(BIN_DIR)/%)

# Regola per creare tutti gli eseguibili
all: $(TARGETS)

# Regola per compilare i singoli file .cpp
$(BIN_DIR)/%: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Creare la directory bin se non esiste
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Pulizia dei file oggetto e degli eseguibili
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
