# Projeto Pizzaria

Este trabalho prático de Algoritmos e estruturas de dados I é uma implementação de um sistema gestão de uma pizzaria. Neste repositório contém todas as estruturas utilizadas para registrar e manipular informações sobre as pizzas e os ingredientes.

## Makefile

O **Makefile** é uma ferramenta importante para a compilação do projeto, além de ser um dos requisitos para o trabalho prático. Ele permite a vinculação de todos os arquivos de código-fonte do programa de maneira eficiente.

### Funcionalidade do Makefile

O Makefile foi configurado para compilar e gerar o executável a partir dos arquivos:

- `Pizzaria.c`
- `Pizzas/Pizzas.c`
- `Ingredientes/Ing.c`

Ele usa o compilador **gcc** e inclui as instruções necessárias para encontrar os arquivos de cabeçalho nos diretórios específicos, neste caso **Pizzas** e **Ingredientes**.
Com o **Makefile** no projeto, basta utilizar o comando:

```bash
make 
```

Feito isso, será gerado um arquivo executável pizzaria.exe, agora basta executá-lo para que possa testar as funcionalidades do projeto.
