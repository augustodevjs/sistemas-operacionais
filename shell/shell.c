#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    As constantes MAX_ARGS e TRUE são definidas. MAX_ARGS é o número máximo de argumentos que o programa pode aceitar. TRUE é uma constante representando o valor lógico "verdadeiro".
*/
#define MAX_ARGS 64
#define TRUE 1

/*
    entrada_usuario é uma string que armazena a entrada do usuário. args é um array de ponteiros para strings, que armazena os argumentos do comando.
*/
char entrada_usuario[64];
char *args[MAX_ARGS];

/*
    A função mostrar_prompt() imprime um prompt na tela para o usuário inserir um comando.
*/
void mostrar_prompt()
{
    printf("#Inserir comando: ");
}

/*
    A função ler_entrada() lê a entrada do usuário usando fgets(), remove a quebra de linha final e divide a entrada em argumentos usando strtok(). Os argumentos são armazenados no array args.
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
    A função main() contém um loop infinito que mantém o programa em execução. Dentro do loop, o prompt é exibido, a entrada é lida e um novo processo é criado usando fork().

    Se fork() retorna -1, um erro ocorreu e o programa termina com uma mensagem de erro. Se fork() retorna um valor diferente de zero, estamos no processo pai e esperamos o processo filho terminar usando wait(NULL).

    Se fork() retorna zero, estamos no processo filho. O comando do usuário é executado usando execvp(). Se execvp() retorna -1, um erro ocorreu e o programa termina com uma mensagem de erro.
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