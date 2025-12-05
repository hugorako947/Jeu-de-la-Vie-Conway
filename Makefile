CXX = g++
TARGET = Jeu

SRCS = main.cpp Jeu.cpp Tests.cpp Grille.cpp Fichier.cpp Regles.cpp Cellule.cpp EtatMort.cpp EtatVivant.cpp Graphique.cpp

OBJS = $(SRCS:.cpp=.o)

SFML_VERSION = $(shell pkg-config --modversion sfml-graphics 2>/dev/null | cut -d. -f1-2)
ifeq ($(SFML_VERSION),)
    SFML_VERSION = 2.5
endif

ifeq ($(SFML_VERSION), 2.6)
    CXXFLAGS = -g -Wall -std=c++17 -DSFML_2_6
    SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
else
    CXXFLAGS = -g -Wall -std=c++14 -DSFML_2_5
    SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
endif

PKG_CONFIG_FLAGS = $(shell pkg-config --cflags --libs sfml-all 2>/dev/null)
ifneq ($(PKG_CONFIG_FLAGS),)
    SFML_FLAGS = $(PKG_CONFIG_FLAGS)
endif

LDFLAGS = $(SFML_FLAGS)

$(TARGET): $(OBJS)
	$(INFO)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install-deps:
	sudo apt update
	sudo apt install -y build-essential g++ libsfml-dev

clean:
	rm -f $(TARGET) $(OBJS) *.gch

rebuild: clean all

help:
	@echo "Commandes disponibles:"
	@echo "  make          : Compile le projet"
	@echo "  make run      : Compile et exécute"
	@echo "  make clean    : Nettoie les fichiers compilés"
	@echo "  make rebuild  : Recompile depuis le début"
	@echo "  make install-deps : Installe les dépendances"
	@echo "  make help     : Affiche cette aide"

.PHONY: all info run install-deps clean rebuild help check
