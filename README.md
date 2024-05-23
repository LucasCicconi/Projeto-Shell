# Projeto-Shell
Este é um interpretador de comandos Shell desenvolvido em C, com o objetivo de fornecer funcionalidades básicas de um terminal.

## Desenvolvedores
- Heitor Scheidt
- Lucas Cicconi
- Vinicius Hardy
- Rafael Waiti

## Funcionalidades Básicas
O Shell é capaz de:

- Receber comandos:
    - Via terminal (Interativamente)
    - Por um batch de comandos em arquivo 
        - Exemplo de uso: 
            ```shell
            # 1.
            user@computer:~$ ./program input_example.txt # argumento
            # 2.
            user@computer:~$ ./program < input_example.txt # input override
            ```
        - Obs. Para evitar comportamento não esperado o arquivo precisa possuir uma linha em branco no final, use como base o input_example.txt
- Interpretar cada comando e decidir se é um comando interno (built-in) ou um programa externo.
- Executar cada comando em um novo processo filho.

- Comandos Internos (Built-in)
``` shell
exit
Finaliza o Shell.

ls [OPÇÕES]... [DIRETÓRIO]...
Lista o conteúdo do(s) diretório(s)
    OPÇÕES
        -a Lista todos os diretórios
        -l Lista os diretórios com mais informações
    DIRETÓRIO
        <CAMINHO DO DIRETÓRIO>

cd [CAMINHO]
Muda o diretório de trabalho.
    CAMINHO
        <CAMINHO DO DIRETÓRIO>

path [CAMINHO]...
Define caminhos para busca de executáveis.
    CAMINHO
        <CAMINHO DO DIRETÓRIO>
```
## Condições de Erro
O Shell trata condições de erro e imprime mensagens ao usuário.

## Argumentos
Os argumentos dos comandos são separados por espaços. Não é necessário se preocupar com caracteres de escape ou argumentos com espaços entre aspas.

## Funcionalidades Extras
- Clone do cat: O binário cat <arquivo> lê o conteúdo do arquivo no argumento e o escreve na saída padrão ou com a extensão > para criar um novo arquivo com o conteúdo.
- Clone do ls: O binário ls lista o conteúdo do diretório atual, suportando os parâmetros -l e -a.
- Redirecionamento de Saída: A saída dos comandos pode ser redirecionada para um arquivo.
- Comandos em Paralelo: Vários comandos separados por & são executados de forma concorrente, em processos separados.

## Compilação
Para compilar o projeto, execute o Makefile fornecido.
``` shell
make ./program [OPÇÕES]
OPÇÕES
    all Builda com as libs personalizadas (ls, cat)
    clean Deleta arquivos
```
