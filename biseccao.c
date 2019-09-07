#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "omp.h"

// gcc -fopenmp -g biseccao.c -o biseccao -lm
// ./biseccao

void obter_argumentos();
void mostrar_argumento();
void calcular();
float funcao(float intervalo);
void resposta_formatada();

float intervalo_inicial = 0;
float intervalo_final = 0;
float toleracia = 0;
int numero_threads = 1;

float raiz = 0;
float erro = 0;
int iteracoes = 0;

int main ()
{
  obter_argumentos();
  mostrar_argumento();
  calcular();
  resposta_formatada();
  return 0;
}

void obter_argumentos() 
{
  puts("ARGUMENTOS");
  
  puts("NUMERO_THREADS");
  scanf("%d", &numero_threads);
  
  puts("INTERVALO_INICIAL");
  scanf("%f", &intervalo_inicial);
  
  puts("INTERVALO_FINAL");
  scanf("%f", &intervalo_final);

  puts("TOLERACIA");
  scanf("%f", &toleracia);
}

void mostrar_argumento()
{
  system("cls | clear");
  puts("ARGUMENTOS:\n");
  printf("NUMERO_THREADS: %i\t", numero_threads);
  printf("INTERVALO_INICIAL: %.4f\t", intervalo_inicial);
  printf("INTERVALO_FINAL: %.4f\t", intervalo_final);
  printf("TOLERACIA: %.1e\t", toleracia);
  puts("");
}

void calcular ()
{
  float pontoMedio = 0;
  float resultadoFuncaoParaintervalo_inicial = 0;
  float resultadoFuncaoParaIntervaloMedio = 0;

  erro = fabs(intervalo_inicial - intervalo_final);

  #pragma omp parallel num_threads(numero_threads)
  while (erro > toleracia)
  {
    iteracoes++;
    pontoMedio = (intervalo_inicial + intervalo_final) / 2;
    resultadoFuncaoParaintervalo_inicial = funcao(intervalo_inicial);
    resultadoFuncaoParaIntervaloMedio = funcao(pontoMedio);

    if (resultadoFuncaoParaintervalo_inicial * resultadoFuncaoParaIntervaloMedio < 0)
      intervalo_final = pontoMedio;
    else
      intervalo_inicial = pontoMedio;
    
    erro = fabs(intervalo_inicial - intervalo_final);
  }

  raiz = pontoMedio;
}

float funcao(float intervalo) 
{
  return (pow(intervalo, 3) - 9 * intervalo + 5);
}

void resposta_formatada()
{
  puts("");
  printf(
    " Raiz aproximada: %.4f\n Erro: %.4f\n Numero de Iterações: %i\n",
    raiz,
    erro,
    iteracoes
  );
  puts("");
}