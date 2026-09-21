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

int main(void) {
    int opcao;
    char texto[TAM_BUFFER];
    char saida[TAM_BUFFER];
    char termo[TAM_BUFFER];
    int deslocamento;
    int tamanho_senha;
    char chave;

    srand((unsigned int) time(NULL)); // embaralha o gerador aleatorio uma unica vez 

    printf("========================================\n");
    printf("      SAFECONSOLE C - Seguranca\n");
    printf("========================================\n");

    do {
        printf("\n--------- MENU ---------\n");
        printf("1. Mascarar dado sensivel\n");
        printf("2. Validar senha\n");
        printf("3. Cifrar com Cesar\n");
        printf("4. Decifrar com Cesar\n");
        printf("5. Cifrar com XOR\n");
        printf("6. Decifrar com XOR\n");
        printf("7. Gerar senha segura (extra)\n");
        printf("8. Ver logs de auditoria\n");
        printf("9. Buscar termo nos logs\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_entrada();

        switch (opcao) {

            case 1:
                printf("Digite o dado sensivel (ex: CPF, cartao): ");
                ler_string(texto, TAM_BUFFER);
                mascarar_dados(texto);
                printf("Dado mascarado: %s\n", texto);
                registrar_log(texto, "Mascaramento");
                break;

            case 2:
                printf("Digite a senha: ");
                ler_string(texto, TAM_BUFFER);
                validar_senha(texto);
                registrar_log("Verificacao de senha realizada", "Validacao");
                break;

            case 3:
                printf("Digite o texto: ");
                ler_string(texto, TAM_BUFFER);
                printf("Digite o deslocamento (ex: 3): ");
                scanf("%d", &deslocamento);
                limpar_entrada();
                cifrar_cesar(texto, deslocamento, saida);
                printf("Texto cifrado: %s\n", saida);
                registrar_log(saida, "Cesar");
                break;

            case 4:
                printf("Digite o texto cifrado: ");
                ler_string(texto, TAM_BUFFER);
                printf("Digite o deslocamento usado: ");
                scanf("%d", &deslocamento);
                limpar_entrada();
                descifrar_cesar(texto, deslocamento, saida);
                printf("Texto decifrado: %s\n", saida);
                break;

            case 5:
                printf("Digite o texto: ");
                ler_string(texto, TAM_BUFFER);
                printf("Digite a chave (1 caractere): ");
                scanf(" %c", &chave);
                limpar_entrada();
                cifrar_xor(texto, chave);
                break;

            case 6:
                if (xor_tamanho == 0) {
                    printf("Nenhum texto foi cifrado com XOR ainda. Use a opcao 5 primeiro.\n");
                    break;
                }
                printf("Digite a chave usada para cifrar: ");
                scanf(" %c", &chave);
                limpar_entrada();
                decifrar_xor(chave, saida);
                printf("Texto decifrado: %s\n", saida);
                break;

            case 7:
                printf("Quantos caracteres a senha deve ter (minimo 8)? ");
                scanf("%d", &tamanho_senha);
                limpar_entrada();

                if (tamanho_senha < 8) {
                    printf("Escolha pelo menos 8 caracteres para uma senha segura.\n");
                    break;
                }
                if (tamanho_senha > TAM_BUFFER - 1) {
                    tamanho_senha = TAM_BUFFER - 1;
                }

                gerar_senha_segura(tamanho_senha, saida);
                printf("Senha gerada: %s\n", saida);
                validar_senha(saida); // confere senha
                registrar_log(saida, "Gerador de Senha");
                break;

            case 8:
                listar_logs();
                break;

            case 9:
                printf("Digite o termo a buscar: ");
                ler_string(termo, TAM_BUFFER);
                buscar_logs(termo);
                break;

            case 0:
                printf("Encerrando o SafeConsole. Ate mais!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
