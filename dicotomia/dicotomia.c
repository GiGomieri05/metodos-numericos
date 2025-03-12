#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// protótipos

void aloca_multi(float **m, int tam);

int main(void)
{
	float *multi = NULL;
	
	int grau, i, pos;
	
	// recebe o grau da funcao entre 2 a 6
	printf("Informe o grau da funcao (2 a 6): ");
	scanf("%i", &grau);
	
	aloca_multi(&multi, grau + 1);
	
	// recebe os multiplicadores.
	// aX^0 + bX^1 + cX^2 ... ---> Indice do vetor igual ao expoente
	for(i = grau; i >= 0; i--) 
	{
		pos = grau-i;
		printf("Informe o fator multiplicador de x^%i(%c): ", i, 65+(pos));
		scanf("%f", (multi + pos));
	}
	
	// exibindo a funcao recebida
	printf("A funcao recebida foi: ");
	for(i = grau; i >= 0; i--)
	{
		pos = grau - i;
		if (i == 0)
			printf("%.2f = 0", *(multi + pos), i);
		else
			printf("%.2fx^%i + ", *(multi + pos), i);
	}
	
	printf("\n\n");
	system("pause");
	printf("\n\n");
	
	return 0;
	
} // main

void aloca_multi(float **m, int tam) {
	if((*m = (float*)realloc(*m, tam*sizeof(float))) == NULL)
		exit(1);
} // aloca_multi
