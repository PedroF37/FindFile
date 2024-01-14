#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <fnmatch.h>
#include <dirent.h>
#include <sys/stat.h>

#include <dirutils.h>
#include <fileutils.h>


void find_item(char *dirname, char *pattern)
{
    DIR *dhandle = opendir(dirname);
    if (dhandle == NULL)
    {
        fprintf(stderr, "Erro ao abrir diretório %s\n", dirname);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dhandle)) != NULL)
    {
        if (is_dot_directory(entry->d_name) == false)
        {
            char *fullpath;
            if ((fullpath = create_pathname(dirname, entry->d_name)) == NULL)
            {
                fprintf(stderr, "Erro ao construir caminho para %s/%s\n",
                    dirname, entry->d_name);
                closedir(dhandle);
                exit(EXIT_FAILURE);
            }

            struct stat itemstat;

            /* Usa lstat para não ir atrás de link simbólico.
             * Dá erro se for a tras */
            if (lstat(fullpath, &itemstat) == -1)
            {
                //fprintf(stderr, "Erro ao obter informções sobre o item %s\n",
                    //fullpath);
                free(fullpath);
                continue;
            }

            /* Se for diretório, faz chamada recursiva */
            if (S_ISDIR(itemstat.st_mode))
            {
                find_item(fullpath, pattern);
            }
            else
            {
                /* Se for arquivo, vê se corresponde ao padrão */
                if (fnmatch(pattern, entry->d_name, 0) == 0 ||
                    strcasecmp(pattern, entry->d_name) == 0)
                {
                    printf("%s\n", fullpath);
                }
            }

            free(fullpath);
        }
    }

    closedir(dhandle);
}


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <diretório> <arquivo-ou-padrão>\n",
            *argv);
        return(1);
    }

    argv++;
    char *dirname = *argv;
    char *pattern = *(argv + 1);

    /* Verifica se diretorio é válido */
    if (is_valid_directory(dirname) == false)
    {
        fprintf(stderr, "Diretório especificado é inválido"
            " ou não tem permissão de acesso\n");
        return(1);
    }

    /* Remove a última barra do diretório se tiver */
    remove_last_char(dirname, '/');
    find_item(dirname, pattern);
    return(0);
}
