/*
Criação de threads POSIX em UNIX.

gcc -o thread-create thread-create.c -lpthread

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 16

void *threadBody (void *id)
{
  long tid = (long) id ; // ID da thread

  printf ("t%02ld: Olá!\n", tid) ;
  sleep (3) ;   
  printf ("t%02ld: Tchau!\n", tid) ;  
  pthread_exit (NULL) ;
}

int main (int argc, char *argv[])
{
  pthread_t thread [NUM_THREADS] ;
  long i, status ;
   
  for (i=0; i<NUM_THREADS; i++)
  {
    printf ("Main: criando thread %02ld\n", i) ;
    status = pthread_create (&thread[i], NULL, threadBody, (void *) i) ;
    if (status)
    {
      perror ("pthread_create") ;
      exit (1) ;
    }
  }
  printf ("Main: fim\n") ;
  pthread_exit (NULL) ;
}
