//ls.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *name) {
    struct stat file_stat;
    if (stat(name, &file_stat) < 0) {
        perror("ls");
        return;
    }

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

    printf(" %s\n", name);
}

int main(int argc, char *argv[]) {
    int show_all = 0, show_long = 0;
    int opt;

    while ((opt = getopt(argc, argv, "la")) != -1) {
        switch (opt) {
        case 'l':
            show_long = 1;
            break;
        case 'a':
            show_all = 1;
            break;
        default:
            fprintf(stderr, "Usage: ls [-l] [-a]\n");
            exit(EXIT_FAILURE);
        }
    }

    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(".")) == NULL) {
        perror("ls");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }
        if (show_long) {
            print_file_info(entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
