//cat.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void print_help() {
    printf("cat [OPÇÕES] [ARQUIVO]\n");
    printf("Lista o conteúdo do(s) diretório(s)\n");
    printf("    OPÇÕES\n");
    printf("        -h Lista os comandos permitidos e utilização\n");
    printf("    ARQUIVO\n");
    printf("        <CAMINHO DO ARQUIVO>\n");
}

int main(int argc, char *argv[]) {
    FILE *file;
    int opt;
    char ch;

    if (argc < 2) {
        print_help();
        return 1;
    }

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
        }
    }

    
    if ((file = fopen(argv[1], "r")) == NULL) {
        perror("cat");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}
