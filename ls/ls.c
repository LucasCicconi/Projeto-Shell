// ls.c
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

void print_name(const char *name) {
    if (strchr(name, ' ') != NULL)
        printf("'%s'", name);
    else
        printf("%s", name);
}

void print_file_info(const char *path, const char *name) {
    struct stat file_stat;

    char *whole_path = (char *)malloc(strlen(path) + 1 + strlen(name) + 1);

    strcpy(whole_path, path);
    strcat(whole_path, "/");
    strcat(whole_path, name);

    if (stat(whole_path, &file_stat) < 0) {
        printf("ls -l: %s: %s\n", name, strerror(errno));
        free(whole_path);
        return;
    }
    free(whole_path);

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %ld", file_stat.st_nlink);

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    printf(" %5ld", file_stat.st_size);

    char timebuf[80];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
    printf(" %s", timebuf);

    printf(" ");
    print_name(name);
    printf("\n");
}

void print_help() {
    printf("ls [OPÇÕES]... [DIRETÓRIO]...\n");
    printf("Lista o conteúdo do(s) diretório(s)\n");
    printf("    OPÇÕES\n");
    printf("        -a Lista todos os diretórios\n");
    printf("        -l Lista os diretórios com mais informações\n");
    printf("        -h, --help Exibe esta mensagem de ajuda\n");
    printf("    DIRETÓRIO\n");
    printf("        <CAMINHO DO DIRETÓRIO>\n");
}

int main(int argc, char *argv[]) {
    int show_all = 0, show_long = 0;
    int opt;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "lah", long_options, NULL)) != -1) {
        switch (opt) {
            case 'l':
                show_long = 1;
                break;
            case 'a':
                show_all = 1;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                fprintf(stderr, "Usage: ls [-l] [-a] [-h]\n");
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        argv[argc] = ".";
        argc++;
    }

    struct stat path_stat;

    for (int i = optind; i < argc; i++) {
        if (stat(argv[i], &path_stat) != 0) {
            printf("ls: %s: %s\n", argv[i], strerror(errno));
            continue;
        }

        if (S_ISDIR(path_stat.st_mode)) {
            printf("%s:\n", argv[i]);
            DIR *dir;
            struct dirent *entry;

            if ((dir = opendir(argv[i])) == NULL) {
                printf("ls: %s: %s\n", argv[i], strerror(errno));
                continue;
            }

            while ((entry = readdir(dir)) != NULL) {
                if (!show_all && entry->d_name[0] == '.') {
                    continue;
                }
                if (show_long) {
                    print_file_info(argv[i], entry->d_name);
                } else {
                    print_name(entry->d_name);
                    printf(" ");
                }
            }

            if (show_long != 1) {
                printf("\n");
            }

            closedir(dir);
        } else {
            if (show_long) {
                print_file_info(".", argv[i]);
            } else {
                print_name(argv[i]);
                printf("\n");
            }
        }
    }

    return 0;
}
