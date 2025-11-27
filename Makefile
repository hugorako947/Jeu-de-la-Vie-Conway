CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = Jeu

SOURCES = main.cpp Fichiers.cpp
HEADERS = Jeu.hpp Grille.hpp Cellule.hpp Etat_cellule.hpp Etat_vivant.hpp Etat_morte.hpp Regles.hpp Fichiers.hpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp Fichiers.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Fichiers.o: Fichiers.cpp Fichiers.hpp
	$(CXX) $(CXXFLAGS) -c Fichiers.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

re: clean all

help:
	@echo ----------Makefile pour le Jeu de la Vie----------
	@echo Commandes disponibles:
	@echo make all   - Compile le projet
	@echo make clean - Supprime les fichiers objets et l'executable
	@echo make re    - Recompile completement
	@echo make help  - Affiche cette aide

.PHONY: all clean re help
