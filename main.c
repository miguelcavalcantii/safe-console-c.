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
// etapa 1 fgets tirando linha
void ler_string(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);

    int i = (int) strlen(texto) - 1;
    if (i >= 0 && texto[i] == '\n') {
        texto[i] = '\0';
    }
}
void limpar_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        //descarta caracteres restantes
    }
}
/* Substitui todos os caracteres por '*', exceto os 4 ultimos.
 * A troca e feita direto na propria string. */
void mascarar_dados(char texto[]) {
    int tamanho = (int) strlen(texto);
    int i;

    /* se a string tiver 4 caracteres ou menos, nada e mascarado */
    for (i = 0; i < tamanho - 4; i++) {
        texto[i] = '*';
    }
}

// etapa 1 - verifica se a senha contem todos os requisitos
int validar_senha(char senha[]) {
    int tamanho = (int) strlen(senha);
    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_numero = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        char c = senha[i];

        if (c >= 'A' && c <= 'Z') {
            tem_maiuscula = 1;
        } else if (c >= 'a' && c <= 'z') {
            tem_minuscula = 1;
        } else if (c >= '0' && c <= '9') {
            tem_numero = 1;
        }
    }

    if (tamanho < 8) {
        printf("Senha invalida: precisa ter no minimo 8 caracteres.\n");
        return 0;
    }
    if (tem_maiuscula == 0) {
        printf("Senha invalida: falta pelo menos 1 letra maiuscula.\n");
        return 0;
    }
    if (tem_minuscula == 0) {
        printf("Senha invalida: falta pelo menos 1 letra minuscula.\n");
        return 0;
    }
    if (tem_numero == 0) {
        printf("Senha invalida: falta pelo menos 1 numero.\n");
        return 0;
    }

    printf("Senha valida! Atende a todos os requisitos.\n");
    return 1;
}
void cifrar_cesar(char texto[], int deslocamento, char saida[]) {
    int tamanho = (int) strlen(texto);
    int i;
    int c;

    /* transforma qualquer deslocamento (negativo ou grande) em um
     * valor equivalente entre 0 e 25 */
    while (deslocamento < 0) {
        deslocamento = deslocamento + 26;
    }
    deslocamento = deslocamento % 26;

    for (i = 0; i < tamanho; i++) {
        c = texto[i]; /* usamos "int" para a conta nao estourar o char */

        if (c >= 'A' && c <= 'Z') {
            c = c + deslocamento;
            if (c > 'Z') {
                c = c - 26;
            }
        } else if (c >= 'a' && c <= 'z') {
            c = c + deslocamento;
            if (c > 'z') {
                c = c - 26;
            }
        }

        saida[i] = (char) c;
    }
    saida[tamanho] = '\0';
}

// só cifra com o deslocamento invertido
void descifrar_cesar(char texto[], int deslocamento, char saida[]) {
    cifrar_cesar(texto, -deslocamento, saida);
}

//mostrado em hexadecimal
void cifrar_xor(char texto[], char chave) {
    int tamanho = (int) strlen(texto);
    int i;
    char hex_log[TAM_BUFFER] = ""; 
    char par[3];                  

    printf("Texto cifrado (em hexadecimal): ");
    for (i = 0; i < tamanho; i++) {
        xor_cifrado[i] = (unsigned char) texto[i] ^ (unsigned char) chave;
        printf("%02X", xor_cifrado[i]);

        sprintf(par, "%02X", xor_cifrado[i]);
        strcat(hex_log, par); //cola o par de caracteres no final de hex_log
    }
    printf("\n");

    xor_tamanho = tamanho;
    registrar_log(hex_log, "XOR");
}

/* O XOR e simetrico: aplicar a mesma operacao com a mesma chave
 * devolve o texto original. Por isso usamos o vetor ja cifrado
 * (xor_cifrado) em vez de pedir o hexadecimal de novo. */
void decifrar_xor(char chave, char saida[]) {
    int i;
    for (i = 0; i < xor_tamanho; i++) {
        saida[i] = (char) (xor_cifrado[i] ^ (unsigned char) chave);
    }
    saida[xor_tamanho] = '\0';
}
