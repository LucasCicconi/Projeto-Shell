//error_handling.h
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

typedef enum {
    NO_ERROR,
    INVALID_COMMAND, // Comando inválido
    READ_ERROR, // Erro de leitura ou EOF
    CD_FAILED, // Erro no comando "CD"
    EXEC_FAILED, // Erro no fork "LS"
    BATCH_FAILED, // Erro ao abrir arquivo batch
    PATH_FAILED, // Erro no caminho atual ao prompt
    DIRECTORY_FAILED, // Erro ao abrir o diretório
    MAX_PATHS_LIMIT, // Limite máximo de caminhos atingido
    MALLOC_FAILED, // Erro no Malloc
    FORK_FAILED, // Erro na cração do Fork
    OPEN_FAILED, //Erro ao abrir o arquivo de saída

} ErrorCode;

void print_error(ErrorCode error_code);

#endif
