#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Aqui, MAX_ARGS define o número máximo de argumentos que o programa pode aceitar, e TRUE é uma constante representando o valor lógico "verdadeiro". A matriz argumentos armazena os argumentos do comando, e temporario é uma matriz temporária para armazenar a entrada do usuário.
*/
#define MAX_ARGS 64
#define TRUE 1

char entrada_usuario[64];
char *args[MAX_ARGS];

/*
    Esta função imprime #Inserir comando: na tela, servindo como um indicador para o usuário inserir um comando.
*/
void mostrar_prompt()
{
    printf("#Inserir comando: ");
}

/*
    ler_comando() lê a entrada do usuário usando fgets(), remove a quebra de linha final e, em seguida, divide a entrada em argumentos usando strtok().
*/
void ler_entrada(char *args[])
{
    int n = 0;

    fgets(entrada_usuario, sizeof(entrada_usuario), stdin);
    entrada_usuario[strcspn(entrada_usuario, "\n")] = '\0';

    args[0] = strtok(entrada_usuario, " ");
    while (n < MAX_ARGS - 1 && args[n] != NULL)
    {
        n++;
        args[n] = strtok(NULL, " ");
    }
    args[n] = NULL;
}

/*
    Um loop infinito (while(TRUE)) mantém o programa em execução, aceitando comandos continuamente. Exibir_prompt() mostra o prompt, e ler_comando() obtém o comando do usuário. Fork() cria um novo processo. O processo pai espera pelo filho usando wait(NULL). No processo filho, execvp() executa o comando inserido pelo usuário. Se houver algum erro, perror() exibe uma mensagem de erro.
*/
int main()
{
    while (TRUE)
    {
        mostrar_prompt();
        ler_entrada(args);

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Erro ao criar processo");
            exit(EXIT_FAILURE);
        }
        else if (pid != 0)
        {
            wait(NULL);
        }
        else
        {
            if (execvp(args[0], args) == -1)
            {
                perror("Erro ao executar comando");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}