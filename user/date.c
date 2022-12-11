#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[])
{
	char *month[12] = {"ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
	char *day[7] = {"dom", "lun", "mar", "mier", "jue", "vie", "sab"};
	// CONNTANTES PARA AÑOS NORMALES 
	int r_m[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
	//CONTANTES PARA AÑOS BISIESTOS 
	int b_m[12] = {6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
	//CONSTANTES DE SIGLO 
	int siglo[4] = {6, 4, 2, 0}; 
	struct rtcdate r;
       	
	int ks; //INDICE DE LA CONSTANTE DE SIGLO 
	int d, m,a; 	// VARIABLES PARA CALCULAR EL INDICE DEL ARRAY DAY: dia, constante de mes y los dos ultimos digitos del año 
	int calculate_day; 
	if (date(&r))
	{
		printf(2,"date failed\n");
		exit(0); 
	}

	ks = r.year%400;
	if (ks<100) ks = 0;
       	else if (ks < 200) ks = 1; 
	else if (ks<300) ks = 2; 
	else ks = 3; 	
	d = r.day; 
	if ((r.year % 4) == 0) m = b_m[r.month -1]; 
	else m = r_m[r.month -1]; 
	a = r.year % 100;
	calculate_day = (d + m + a + (a/4) + siglo[ks]) % 7; 
	printf(1,"%s %d %s %d %d:%d:%d\n",day[calculate_day],r.day,month[r.month-1], r.year, r.hour, r.minute, r.second); 
	exit(0); 
}

