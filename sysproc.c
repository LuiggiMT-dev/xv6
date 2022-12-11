#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#define INITIAL    0
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  // Extraemos el estado de la pila de usuario
  if(argint(0, &status) < 0) return -1;
  
  exit(status << 8);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int* status;
  // Extraemos el estado de la pila de usuario
  if (argptr(INITIAL, (void**)&status, sizeof(int)) < 0)
    return -1;
    
  return wait(status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;
  
  // Extraemos de la pila el valor de n
  if(argint(0, &n) < 0)
    return -1;
  // Guardamos el tamaño actual del proceso
  addr = myproc()->sz;
  // Si n es negativa desallocamos los bytes correspondientes a su valor
  if (n<0)
  {
    if(growproc(n) < 0)
      return -1;
  }
  // En otro caso aumentamos el tamaño del proceso
  else
    myproc()->sz += n; 
  // Devolvemos el tamaño antiguo del proceso
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int 
sys_date(void)
{
  struct rtcdate *r; 
  // Comprobación de parámetros de entrada
  if ((argptr(INITIAL, (void**)&r, sizeof(struct rtcdate)))<0)
	 return -1; 
  // Llamada
  cmostime(r);
  return 0;
}
int 
sys_getprio(void)
{
  int pid; 
  if (argint(INITIAL, &pid) < 0)
    return -1; 
  return getprio(pid);
}
int 
sys_setprio(void)
{
  int pid; 
  int prio;
  
  if (argint(INITIAL, &pid) < 0)
    return -1;
  if (argint(1, &prio) < 0)
    return -1; 
  setprio(pid, prio); 
  return 0; 
}