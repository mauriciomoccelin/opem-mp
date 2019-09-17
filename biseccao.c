#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "omp.h"

// gcc -fopenmp -g biseccao.c -o biseccao -lm
// ./biseccao

void mostrar_argumento();
void calcular();
float funcao(float intervalo);
void resposta_formatada();
void mostrar_tempo_processamento(clock_t begin, clock_t end);

void calcular_com_32threads();
void calcular_com_16threads();
void calcular_com_8threads();
void calcular_com_4threads();
void calcular_com_2threads();
void calcular_com_1threads();
void calcular_com_nthreads();

float intervalo_inicial = 0;
float intervalo_final = 2;
float toleracia = 0.00000000000001;
int numero_threads = 1;

float raiz = 0;
float erro = 0;
int iteracoes = 0;

int main ()
{
  // calcular_com_32threads();
  // calcular_com_16threads();
  // calcular_com_8threads();
  // calcular_com_4threads();
  // calcular_com_2threads();
  calcular_com_1threads();
  return 0;
}

void calcular_com_32threads()
{
  calcular_com_nthreads(32);
}

void calcular_com_16threads()
{
  calcular_com_nthreads(16);
}

void calcular_com_8threads()
{
  calcular_com_nthreads(8);
}

void calcular_com_4threads()
{
  calcular_com_nthreads(4);
}

void calcular_com_2threads()
{
  calcular_com_nthreads(2);
}

void calcular_com_1threads()
{
  calcular_com_nthreads(1);
}

void calcular_com_nthreads(int threads)
{
  numero_threads = threads;
  clock_t begin = clock();
  mostrar_argumento();
  calcular();
  resposta_formatada();
  clock_t end = clock();
  mostrar_tempo_processamento(begin, end);
}

void mostrar_tempo_processamento (clock_t begin, clock_t end) 
{
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Número Threads: %d Tempo de processamento: %f\n", numero_threads, time_spent);
}

void mostrar_argumento()
{
  puts("******************************************************");
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
    if (iteracoes == 1000) break;
  }

  raiz = pontoMedio;
}

float funcao(float intervalo) 
{
  return (
    pow(intervalo, 5) -
    pow(intervalo, 4) -
    pow(intervalo, 3) -
    pow(intervalo, 2)
  );
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