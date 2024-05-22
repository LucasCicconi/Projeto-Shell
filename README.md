# Projeto-Shell
Este é um interpretador de comandos Shell desenvolvido em C, com o objetivo de fornecer funcionalidades básicas de um terminal.

## Desenvolvedores
- Heitor Scheidt
- Lucas Ciccone
- Vinicius Hardy

## Funcionalidades Básicas
O Shell é capaz de:

- Receber comandos via terminal ou de um arquivo batch.
- Interpretar cada comando e decidir se é um comando interno (built-in) ou um programa externo.
- Executar cada comando em um novo processo filho.
- Comandos Internos (Built-in)
- exit: Finaliza o Shell.
- cd <caminho>: Muda o diretório de trabalho.
- path <caminho> [<caminho> <caminho> ...]: Define caminhos para busca de executáveis.

## Programas Externos
O Shell procura por executáveis nos caminhos definidos com o comando interno path. Após encontrar o executável, o Shell o executa em um novo processo com os argumentos solicitados pelo usuário. Ao final da execução, imprime na tela o valor retornado pelo programa.
Se o executável não for encontrado, uma mensagem de erro é emitida.

## Condições de Erro
O Shell trata condições de erro e imprime mensagens ao usuário.

## Argumentos
Os argumentos dos comandos são separados por espaços. Não é necessário se preocupar com caracteres de escape ou argumentos com espaços entre aspas.

## Funcionalidades Extras
- Clone do cat: O binário cat <arquivo> lê o conteúdo do arquivo no argumento e o escreve na saída padrão.
- Clone do ls: O binário ls lista o conteúdo do diretório atual, suportando os parâmetros -l e -a.
- Redirecionamento de Saída: A saída dos comandos pode ser redirecionada para um arquivo.
- Comandos em Paralelo: Vários comandos separados por & são executados de forma concorrente, em processos separados.

## Compilação
Para compilar o projeto, execute o Makefile fornecido.
        ```bash
        make
        ./program
        ```
