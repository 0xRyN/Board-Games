# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I. -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE = BoardGames

# Dossiers
SRC_DIR = Board-Games
OBJ_DIR = obj

# Trouver tous les fichiers .cpp dans SRC_DIR et ses sous-dossiers
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
# Convertir les chemins des fichiers sources en chemins de fichiers objets
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Règle principale
all: $(EXECUTABLE)
	./$(EXECUTABLE)

# Règle pour créer l'exécutable with all errors and warnings
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFMLFLAGS)  

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
