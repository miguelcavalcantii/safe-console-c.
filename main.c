#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_BUFFER 256   /* tamanho maximo de uma string digitada pelo usuario */
#define MAX_LOGS   20    /* quantidade maxima de logs guardados em memoria    */
#define TAM_ALGO   25    /* tamanho maximo do nome do algoritmo no log        */

//guarda ultimo texto cifrado
unsigned char xor_cifrado[TAM_BUFFER];
int xor_tamanho = 0;

char historico[MAX_LOGS][TAM_BUFFER];
char algoritmos[MAX_LOGS][TAM_ALGO];
int  tamanhos[MAX_LOGS];
int  total_logs = 0;
//prototipos
void ler_string(char texto[], int tamanho);
void limpar_entrada(void);

//1
void mascarar_dados(char texto[]);
int  validar_senha(char senha[]);

//2
void cifrar_cesar(char texto[], int deslocamento, char saida[]);
void descifrar_cesar(char texto[], int deslocamento, char saida[]);
void cifrar_xor(char texto[], char chave);
void decifrar_xor(char chave, char saida[]);

//3
void registrar_log(char mensagem[], char algoritmo[]);
void listar_logs(void);
void buscar_logs(char termo[]);

//funcao extra 1 
void gerar_senha_segura(int tamanho, char saida[]);
