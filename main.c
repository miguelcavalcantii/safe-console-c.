#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_BUFFER 256   /* tamanho maximo de uma string digitada pelo usuario */
#define MAX_LOGS   20    /* quantidade maxima de logs guardados em memoria    */
#define TAM_ALGO   25    /* tamanho maximo do nome do algoritmo no log        */

/* Guarda o ultimo texto cifrado com XOR, para podermos decifrar
 * depois sem precisar digitar o texto em hexadecimal de novo. */
unsigned char xor_cifrado[TAM_BUFFER];
int xor_tamanho = 0;

char historico[MAX_LOGS][TAM_BUFFER];
char algoritmos[MAX_LOGS][TAM_ALGO];
int  tamanhos[MAX_LOGS];
int  total_logs = 0;
