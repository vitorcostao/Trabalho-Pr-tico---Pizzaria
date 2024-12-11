CC = gcc
CFLAGS = -Wall -g

# Definindo os diretórios de inclusão
INCLUDE_DIRS = -IIngredientes -IPizzas

# Definindo os arquivos fontes
SRC = Pizzaria.c Pizzas/Pizzas.c Ingredientes/Ing.c

# Nome do executável
EXEC = pizzaria

# Regras
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC) -o $(EXEC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC)
