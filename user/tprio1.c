#include "types.h"
#include "user.h"
enum proc_prio {HI_PRIO, NORM_PRIO}; 
int
main(int argc, char *argv[])
{
  // El padre sale, el hijo establece la máxima prioridad
  if (fork() != 0)
    exit(0);
  
  // Establecer máxima prioridad. Debe hacer que el shell ni aparezca hasta
  // que termine
  setprio(getpid(), HI_PRIO); 

  /*enum proc_prio prio = getprio(getpid());
  if(prio == NORM_PRIO)
    printf(1, "Prioridad baja");
  else printf(1, "Prioridad alta");*/
  
  int r = 0;
  
  for (int i = 0; i < 2000; ++i)
    for (int j = 0; j < 1000000; ++j)
      r += i + j;
  // Imprime el resultado
  printf (1, "Resultado: %d\n", r);
  
  exit(0);
}
