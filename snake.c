#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 21
#define H 65
#define N 100

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct
{
	int x, y;
	int ModX, ModY;
	char imagen;
}snk;

typedef  struct
{
	int x,y;
}frt;

snk snake[N];
frt fruta;

void inicio(int *tam, char campo[V][H]);
void Intro_Campo(char campo [V][H]);
void Intro_Datos(char campo[V][H], int tam);
void draw(char campo[V][H]);
void loop(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int*muerto);
void update(char campo[V][H], int tam);
void Intro_Datos2(char campo[V][H], int tam);

int main(int argc, char *argv[]) {
	
	int tam;
	char campo[V][H];
	
	inicio(&tam, campo);//iniciar todos los elementos	
	loop(campo, tam);
	
	return 0;
}

void inicio(int *tam, char campo[V][H])
{
	int i;
	
	//la cabeza de la serpiente
	snake[0].x =32;
	snake[0].y = 10;
	
	//tamaño de la serpiente
	*tam = 4;
	
	//coordenadas fruta
	srand(time(NULL));
	
	fruta.x = rand()% (H-1);
	fruta.y = rand()% (V-1);
	
	while(fruta.x == 0)
	{
		fruta.x = rand() % (H-1);
	}
	
	while(fruta.y == 0)
	{
		fruta.y = rand() % (V-1);
	}
	
	for(i=0; i<*tam; i++)
	{
		snake[i].ModX = 1;
		snake[i].ModY = 0;
	}
	
	Intro_Campo(campo);
	Intro_Datos(campo, *tam);
}

//Creacion del campo de juego
void Intro_Campo(char campo [V][H])
{
	int i, j;
	
	for(i = 0; i<V; i++)
	{
		for(j = 0; j< H; j++)
		{
			if(i == 0 || i == V-1)
			{
				campo[i][j] = '-';
			}
			
			else if(j == 0 || j == H -1)
			{
				campo[i][j] = '|';
			}
			
			else
			{
				campo[i][j] = ' ';
			}
		}
	}
}

//Metera todos los datos en la matriz campo
void Intro_Datos(char campo[V][H], int tam)
{
	int i;
	
	for(i = 1; i<tam; i++)
	{
		snake[i].x = snake[i - 1].x-1;
		snake[i].y = snake[i - 1].y;
		
		snake[i].imagen = 'X';		
	}
	
	snake[0].imagen = 'O';
	
	for(i = 0; i< tam; i++)
	{
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}

void draw(char campo[V][H])
{
	int i, j;
	
	for(i = 0; i<V; i++)
	{
		for(j = 0; j< H; j++)
		{
			printf("%c", campo[i][j]);
		}
		printf("\n");
	}
}

void loop(char campo[V][H], int tam)
{
	int muerto; 
	
	muerto = 0;
	
	do
	{
		system("cls");
		draw(campo);
		input(campo, &tam, &muerto);
		update(campo, tam);		
		
	}while(muerto == 0);
}

void input(char campo[V][H], int *tam, int*muerto)
{
	int i;
	char key;
	
	//comprobamos si hemos muerto
	if(snake[0].x == 0 || snake[0].x == H-1 || snake[0].y == 0 || snake[0].y == V-1)
	{
		*muerto = 1;
	}
	
	for(i = 1; i< *tam && *muerto == 0; i++)
	{
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			*muerto = 1;
		}
	}
	
	//comprobar si nos hemos comido la fruta
	
	if(snake[0]. x == fruta.x && snake[0].y == fruta.y)
	{
		*tam+=1;		
		snake[*tam - 1].imagen = 'X';
		
		fruta.x = rand()% (H-1);
		fruta.y = rand()% (V-1);
	
		while(fruta.x == 0)
		{
			fruta.x = rand() % (H-1);
		}
		
		while(fruta.y == 0)
		{
			fruta.y = rand() % (V-1);
		}
	}
	
	if(*muerto == 0)
	{
		if(kbhit() == 1)
		{
			key = getch();
			
			if(key == '2' && snake[0].ModY != -1)
			{
				snake[0].ModX = 0;
				snake[0].ModY = 1;
			}
			
			if(key == '8' && snake[0].ModY != 1)
			{
				snake[0].ModX = 0;
				snake[0].ModY = -1;
			}
			
			if(key == '4'&& snake[0].ModX != 1)
			{
				snake[0].ModX= -1;
				snake[0].ModY = 0;
			}
			
			if(key == '6'&& snake[0].ModX != -1)
			{
				snake[0].ModX= 1;
				snake[0].ModY = 0;
			}
		}
	}
}

void update(char campo[V][H], int tam)
{
	//borrar todos los datos de la matriz
	Intro_Campo(campo);
	
	//introducir los nuevos datos
	Intro_Datos2(campo, tam);
}

void Intro_Datos2(char campo[V][H], int tam)
{
	int i;
	//crear la persecucion de los elementos del cuerpo
	
	for(i = tam-1; i>0; i--)
	{
		snake[i].x = snake [i-1].x;
		snake[i].y = snake [i-1].y;
	}
	
	snake[0].x += snake[0].ModX;
	snake[0].y += snake[0].ModY;
	
	for(i = 0; i<tam; i++)
	{
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}

