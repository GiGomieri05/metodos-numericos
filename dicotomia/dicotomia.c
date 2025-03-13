#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// protótipos

void aloca_multi(float **m, int tam);
void aloca_intervalo(float **i, int tam);

void define_funcao();
void define_intervalo();

int verifica_intervalo(float fa, float fb);

float funcaoX(float ponto);

float calculaValorK(float a, float b, float erro);

float implementa_dicotomia(float *a, float *b, float erro, int k);

void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);

// globais
float *multi = NULL;
float *intervalo = NULL;
float epsilon; // erro (e)

int grau;

int main(void)
{	
	
	define_funcao();
	define_intervalo();
	
	//implementando dicotomia
	
	if (verifica_intervalo(funcaoX(*(intervalo)), funcaoX(*(intervalo + 1))))
	{
		printf("Impossivel dizer se no intervalo tem raiz, pq f(a) e f(b) tem mesmo sinal.\n");
	} 
	else
	{
		printf("Raiz esta no intervalo, pq f(a) e f(b) tem sinais opostos.\n");
		
		printf("\n\n");
		system("pause");
		printf("\n\n");
		
		// calcular valor de k
		float k = calculaValorK((*intervalo), (*(intervalo+1)), epsilon);
		// printf("Serao realizadas %.0f iteracoes (k)\n", k);
		
		ImprimirCabecalhoTabela();
		
		float x = implementa_dicotomia(intervalo, intervalo + 1, epsilon, (int)k);
		
		printf("\nA raiz da funcao eh: %f", x);
	}
	
	printf("\n\n");
	system("pause");
	printf("\n\n");
	
	return 0;
	
} // main

void aloca_multi(float **m, int tam) 
{
	if ((*m = (float*)realloc(*m, tam*sizeof(float))) == NULL)
		exit(1);
} // aloca_multi

void aloca_intervalo(float **i, int tam)
{
	if ((*i = (float*)realloc(*i, tam*sizeof(float))) == NULL)
		exit(1);
} // aloca_intervalo

// funcao que realiza o calculo em determinado ponto
float funcaoX(float ponto)
{
	int i;
	float resultado;
	
	resultado = 0;
	
	for (i = 0; i <= grau; i++)
	{
		resultado += *(multi+i) * pow(ponto, grau-i);
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

} //ImprimirCabecalhoTabela

// imprimindo a tabela com os valores
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB)
{
    // printf("%i |%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
	printf("%i |%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
} //imprimirTabela

void define_funcao()
{
	int i, pos;
	// recebe o grau da funcao entre 2 a 6
	do
	{
		printf("Informe o grau da funcao (2 a 6): ");
		scanf("%i", &grau);
	} while (grau < 2 || grau > 6);
	
	aloca_multi(&multi, grau + 1);
	
	// recebe os multiplicadores.
	// aX^0 + bX^1 + cX^2 ... ---> Indice do vetor igual ao expoente
	for (i = grau; i >= 0; i--) 
	{
		pos = grau-i;
		printf("Informe o fator multiplicador de x^%i(%c): ", i, 65+(pos));
		scanf("%f", (multi + pos));
	}
	
	// exibindo a funcao recebida
	printf("A funcao recebida foi: ");
	for (i = grau; i >= 0; i--)
	{
		pos = grau - i;
		if (i == 0)
			printf("%.2f = 0", *(multi + pos));
		else
			printf("%.2fx^%i + ", *(multi + pos), i);
	}
	
	printf("\n\n");
	system("pause");
	printf("\n\n");
} //define_funcao

void define_intervalo()
{
	printf("Intervalo [A;B] e erro\n");
	aloca_intervalo(&intervalo, 2);
	
	printf("Informe o primeiro numero do intervalo (A): ");
	scanf("%f", intervalo);
	printf("Informe o segundo numero do intervalo (B): ");
	scanf("%f", intervalo + 1);
	printf("Informe o erro 'epsilon': ");
	scanf("%f", &epsilon);
	
	// m = (*(intervalo) + *(intervalo + 1)) / 2; // Calculando ponto médio
	
	// printf("Resultado: f(A)=%f, f(M)=%f, f(B)=%f\n", funcaoX(*intervalo), funcaoX(m), funcaoX(*(intervalo+1)));
	
	printf("\n\n");
} // define_intervalo

int verifica_intervalo(float fa, float fb)
{
	if (fa * fb <= 0)
		return 0;
	
	return 1;
} // verifica_intervalo

//Realiza o calculo do K (numero de passo)
float calculaValorK(float a, float b, float erro)
{
    float fValorK;

    //Realizar o calculo do valor do K
    fValorK = (log10(b-a) - log10(erro))/(log10(2));


    return ceil(fValorK);
} // calculaValorK

float implementa_dicotomia(float *a, float *b, float erro, int k)
{
	float m, fa, fb, fm;
	char fafm, fmfb;
	int i = 1;
	
	while (k >= i || *b - *a >= erro || funcaoX(m) >= erro)
	{
		m = (*a + *b) / 2;
		
		fa = funcaoX(*a);
		fb = funcaoX(*b);
		fm = funcaoX(m);
		
		if(fa * fm < 0) 
			fafm = '-'; 
		else
			fafm = '+';
		
		if(fm * fb < 0)
			fmfb = '-';
		else
			fmfb = '+';
			
		ImprimirTabela(i, *a, *b, m, fa, fb, fm, fafm, fmfb);
		
		if(fafm == '-')
			*b = m;
		else if(fmfb == '-')
			*a = m;
		
		i++;
	}
	
	return m;
	
} // implementa_dicotomia
