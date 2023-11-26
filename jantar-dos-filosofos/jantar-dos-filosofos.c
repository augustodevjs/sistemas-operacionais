#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define PHILOS 5
#define DELAY 5000
#define COMIDA 50

void *filosofo(void *num);
void pegar_garfos(int);
void liberar_garfos(int);
int comida_na_mesa();

pthread_mutex_t garfos[PHILOS];
pthread_t filo[PHILOS];
pthread_mutex_t lock_comida;
int segundos_para_dormir = 0;

int main(int argc, char **argv)
{
  int i;
  int *philosopher_id;

  if (argc == 2)
    segundos_para_dormir = atoi(argv[1]);

  pthread_mutex_init(&lock_comida, NULL);
  for (i = 0; i < PHILOS; i++)
    pthread_mutex_init(&garfos[i], NULL);

  for (i = 0; i < PHILOS; i++)
  {
    philosopher_id = (int *)malloc(sizeof(int));
    *philosopher_id = i;
    pthread_create(&filo[i], NULL, filosofo, philosopher_id);
  }

  for (i = 0; i < PHILOS; i++)
    pthread_join(filo[i], NULL);
  return 0;
}

void *filosofo(void *num)
{
  int *id = (int *)num;
  int i, f;

  printf("Filósofo %d terminou de pensar e está pronto para comer.\n", *id);

  while (f = comida_na_mesa())
  {
    if (*id == 1)
      sleep(segundos_para_dormir);

    pegar_garfos(*id);

    printf("Filósofo %d: comendo.\n", *id);
    usleep(DELAY * (COMIDA - f + 1));
    liberar_garfos(*id);
  }

  printf("Filósofo %d terminou de comer.\n", *id);
  free(id); // Liberar memória alocada para o número do filósofo
  return NULL;
}

int comida_na_mesa()
{
  static int comida = COMIDA;
  int minha_comida;

  pthread_mutex_lock(&lock_comida);
  if (comida > 0)
  {
    comida--;
  }
  minha_comida = comida;
  pthread_mutex_unlock(&lock_comida);
  return minha_comida;
}

void pegar_garfos(int filosofo)
{
  int garfo_esquerdo = filosofo;
  int garfo_direito = (filosofo + 1) % PHILOS;

  pthread_mutex_lock(&garfos[garfo_esquerdo]);
  pthread_mutex_lock(&garfos[garfo_direito]);

  printf("Filósofo %d: pegou os garfos %d e %d\n", filosofo, garfo_esquerdo, garfo_direito);
}

void liberar_garfos(int filosofo)
{
  int garfo_esquerdo = filosofo;
  int garfo_direito = (filosofo + 1) % PHILOS;

  printf("Filósofo %d: liberou os garfos %d e %d\n", filosofo, garfo_esquerdo, garfo_direito);

  pthread_mutex_unlock(&garfos[garfo_esquerdo]);
  pthread_mutex_unlock(&garfos[garfo_direito]);
}