# Makefile para o projeto TP

# Definição de compilador e opções de compilação
CC = g++
CFLAGS = -Wall -std=c++11
INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte (código)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Gera o nome dos objetos a partir dos fontes
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nome do executável final
EXEC = $(BIN_DIR)/tp2.out

# Regra default para o comando 'make all submetido'
all submetido: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

# Regra para compilar os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Cria diretório de objetos se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Cria diretório do executável se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpar arquivos objeto e executável
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Fazer o make sem especificar "all submetido" não faz nada
.PHONY: all submetido clean
