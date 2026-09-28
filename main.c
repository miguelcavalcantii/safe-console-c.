#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_BUFFER 256
#define MAX_LOGS   20
#define TAM_ALGO   25

unsigned char xor_cifrado[TAM_BUFFER];
int xor_tamanho = 0;

char historico[MAX_LOGS][TAM_BUFFER];
char algoritmos[MAX_LOGS][TAM_ALGO];
int  tamanhos[MAX_LOGS];
int  total_logs = 0;

void ler_string(char texto[], int tamanho);
void limpar_entrada(void);

void mascarar_dados(char texto[]);
int  validar_senha(char senha[]);

void cifrar_cesar(char texto[], int deslocamento, char saida[]);
void descifrar_cesar(char texto[], int deslocamento, char saida[]);
void cifrar_xor(char texto[], char chave);
void decifrar_xor(char chave, char saida[]);

void registrar_log(char mensagem[], char algoritmo[]);
void listar_logs(void);

void gerar_senha_segura(int tamanho, char saida[]);
void mostrar_forca_visual(char senha[]);
int  senha_tem_sequencia(char senha[]);

int main(void) {
    int opcao;
    char texto[TAM_BUFFER];
    char saida[TAM_BUFFER];
    int deslocamento;
    int tamanho_senha;
    char chave;

    srand((unsigned int) time(NULL));
    // começo do menu
    printf("      SAFECONSOLE C - Seguranca\n");
    printf("      Aluno: Miguel B. Cavalcanti\n");

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
                mostrar_forca_visual(texto);
                if (senha_tem_sequencia(texto)) {
                    printf("Atencao: a senha contem uma sequencia previsivel (ex: 123, abc, aaa).\n");
                }
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
                validar_senha(saida);
                mostrar_forca_visual(saida);
                registrar_log(saida, "Gerador de Senha");
                break;

            case 8:
                listar_logs();
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
    }
}

void mascarar_dados(char texto[]) {
    int tamanho = (int) strlen(texto);
    int i;

    for (i = 0; i < tamanho - 4; i++) {
        texto[i] = '*';
    }
}

int validar_senha(char senha[]) {
    int tamanho = (int) strlen(senha);
    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_numero = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        int codigo = senha[i];

        if (codigo >= 65 && codigo <= 90) {
            tem_maiuscula = 1;
        } else if (codigo >= 97 && codigo <= 122) {
            tem_minuscula = 1;
        } else if (codigo >= 48 && codigo <= 57) {
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

    while (deslocamento < 0) {
        deslocamento = deslocamento + 26;
    }
    deslocamento = deslocamento % 26;

    for (i = 0; i < tamanho; i++) {
        c = texto[i];

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

void descifrar_cesar(char texto[], int deslocamento, char saida[]) {
    cifrar_cesar(texto, -deslocamento, saida);
}

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
        strcat(hex_log, par);
    }
    printf("\n");

    xor_tamanho = tamanho;
    registrar_log(hex_log, "XOR");
}

void decifrar_xor(char chave, char saida[]) {
    int i;
    for (i = 0; i < xor_tamanho; i++) {
        saida[i] = (char) (xor_cifrado[i] ^ (unsigned char) chave);
    }
    saida[xor_tamanho] = '\0';
}

void registrar_log(char mensagem[], char algoritmo[]) {
    if (total_logs >= MAX_LOGS) {
        printf("Aviso: limite de %d logs atingido.\n", MAX_LOGS);
        return;
    }

    strcpy(historico[total_logs], mensagem);
    strcpy(algoritmos[total_logs], algoritmo);
    tamanhos[total_logs] = (int) strlen(mensagem);

    total_logs++;
}

void listar_logs(void) {
    int i;

    if (total_logs == 0) {
        printf("Nenhum log registrado ainda.\n");
        return;
    }

    printf("\n%-4s %-16s %-6s %s\n", "ID", "Algoritmo", "Tam.", "Payload");
    printf("--------------------------------------------------\n");
    for (i = 0; i < total_logs; i++) {
        printf("%-4d %-16s %-6d %s\n", i + 1, algoritmos[i], tamanhos[i], historico[i]);
    }
}

void gerar_senha_segura(int tamanho, char saida[]) {
    char banco[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%&*";
    int tamanho_banco = (int) strlen(banco);
    int i;
    int indice;

    for (i = 0; i < tamanho; i++) {
        indice = rand() % tamanho_banco;
        saida[i] = banco[indice];
    }
    saida[tamanho] = '\0';
}

void mostrar_forca_visual(char senha[]) {
    int tamanho = (int) strlen(senha);
    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_numero = 0;
    int tem_simbolo = 0;
    int pontos = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        int codigo = senha[i];

        if (codigo >= 65 && codigo <= 90) {
            tem_maiuscula = 1;
        } else if (codigo >= 97 && codigo <= 122) {
            tem_minuscula = 1;
        } else if (codigo >= 48 && codigo <= 57) {
            tem_numero = 1;
        } else {
            tem_simbolo = 1;
        }
    }

    if (tamanho >= 8)  pontos++;
    if (tem_maiuscula) pontos++;
    if (tem_minuscula) pontos++;
    if (tem_numero)    pontos++;
    if (tem_simbolo)   pontos++;

    printf("Forca da senha: [");
    for (i = 0; i < 5; i++) {
        if (i < pontos) {
            printf("#");
        } else {
            printf("-");
        }
    }
    printf("] (%d de 5)\n", pontos);
}

int senha_tem_sequencia(char senha[]) {
    int tamanho = (int) strlen(senha);
    int i;

    for (i = 0; i < tamanho - 2; i++) {
        char a = senha[i];
        char b = senha[i + 1];
        char c = senha[i + 2];

        if ((b == a + 1 && c == a + 2) || (b == a && c == a)) {
            return 1;
        }
    }
    return 0;
}
