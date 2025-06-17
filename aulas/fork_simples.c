/*
Criação de processos em UNIX.

gcc -o fork fork.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
  int retval ;
   
  printf ("Ola, sou o processo %5d\n", getpid()) ;
  retval = fork () ;
  printf ("[retval: %5d] sou %5d, filho de %5d\n", retval, getpid(), getppid()) ;

  if ( retval < 0 )    // erro no fork()
  {
    perror ("Erro") ;
    exit (1) ;
  }
  else
    if ( retval > 0 )  // sou o processo pai
      wait (0) ;
    else               // sou o processo filho
      sleep (5) ;

  printf ("Tchau de %5d!\n", getpid()) ;
  exit (0) ;
}
