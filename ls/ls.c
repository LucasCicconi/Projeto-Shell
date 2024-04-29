#include <stdio.h>
#include <dirent.h>
#include "error_handling.h"

int main(int argc, char *argv[]) {

    // Se um argumento não foi passado, usa o diretório atual
    if (argc < 2) {
        argv[1] = ".";
    }

    // Abre o diretório
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        print_error(DIRECTORY_FAILED);
        return 1;
    }


    // Lê o diretório
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\t", entry->d_name);
    }

    // Fecha o diretório
    closedir(dir);

    return 0;
}