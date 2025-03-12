#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// protótipos

void aloca_multi(float **m, int tam);
void aloca_intervalo(float **i, int tam);

float funcaoX(float ponto);

void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);

// globais
float *multi = NULL;
float *intervalo = NULL;
int grau;

int main(void)
{	
	int i, pos;
	float pontoM;
	
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
	
	printf("Intervalo [A;B]\n");
	aloca_intervalo(&intervalo, 2);
	
	printf("Informe o primeiro numero do intervalo (A): ");
	scanf("%f", intervalo);
	printf("Informe o segundo numero do intervalo (B): ");
	scanf("%f", intervalo+1);
	
	pontoM = (*(intervalo) + *(intervalo+1)) / 2;
	
	printf("Resultado: %f %f %f\n", funcaoX(*intervalo), funcaoX(pontoM), funcaoX(*(intervalo+1)));
	system("pause");
	
	ImprimirCabecalhoTabela();
	ImprimirTabela(1, 2, 3, 4, 5, 6, 7, '+', '-');
	
	system("pause");
	
	return 0;
	
} // main

void aloca_multi(float **m, int tam) 
{
	if((*m = (float*)realloc(*m, tam*sizeof(float))) == NULL)
		exit(1);
} // aloca_multi

void aloca_intervalo(float **i, int tam)
{
	if((*i = (float*)realloc(*i, tam*sizeof(float))) == NULL)
		exit(1);
} // aloca_intervalo

// funcao que realiza o calculo em determinado ponto
float funcaoX(float ponto)
{
	int i;
	float resultado;
	
	resultado = 0;
	
	for(i = 0; i <= grau; i++)
	{
		resultado = resultado + *(multi+i)*pow(ponto, i);
	}
	
	return resultado;
} // funcaoX

// imprimindo o cabecalho
void ImprimirCabecalhoTabela()
{
	/*
    // Impressao do cabecalho
    printf("I |  a\t|  b\t|  m\t|  f(a)\t|  f(b)\t|  f(m)\t| fa*fm\t| fm*fb\t|\n");
    printf("--+-----+-------+-------+-------+-------+-------+-------+-------+\n");
	*/
	// Impressao do cabecalho
    printf("I |\ta\t|\tb\t|\tm\t|\tf(a)\t|\tf(b)\t|\tf(m)\t|fa*fm\t|fm*fb\t|\n");
    printf("--+-------------+---------------+---------------+---------------+---------------+---------------+-------+-------+\n");

}

// imprimindo a tabela com os valores
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB)
{
    // printf("%i |%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
	printf("%i |%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}
