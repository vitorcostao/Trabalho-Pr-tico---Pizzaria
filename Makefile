# Nome do executável final
TARGET = pizzaria

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Arquivos-fonte
SRCS = pizzaria.c pizzas.c ing.c

# Arquivos-objeto
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(TARGET)

# Criação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos arquivos .c para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: all
	./$(TARGET)
