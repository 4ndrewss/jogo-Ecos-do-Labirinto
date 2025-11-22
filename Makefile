# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -I include -Wall -Wextra

# --- MUDANÇA 1: Definir a pasta de saída ---
BUILD_DIR = build

# Arquivos fonte
SRCS = src/main.c \
       src/jogo.c \
       src/mapa.c \
       src/screen.c \
       src/keyboard.c \
       src/ranking.c \
       src/timer.c

# --- MUDANÇA 2: O executável agora tem o caminho da pasta build ---
TARGET = $(BUILD_DIR)/jogo

# Regra principal
$(TARGET): $(SRCS)
	mkdir -p $(BUILD_DIR)  # Cria a pasta 'build' se ela não existir
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Regra para limpar (Apaga a pasta build inteira para garantir limpeza total)
clean:
	rm -rf $(BUILD_DIR)
	rm -f jogo  # Remove o antigo da raiz caso tenha sobrado

# Regra para rodar o jogo
run: $(TARGET)
	./$(TARGET)

# Regra para compilar e rodar
all: $(TARGET) run

.PHONY: clean run all