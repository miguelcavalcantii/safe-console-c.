# SafeConsole C

Ferramenta de linha de comando em C para **sanitização de dados**, **cifragem simétrica** e **registro de logs de auditoria**, desenvolvida como projeto prático da AV1.

| | |
|---|---|
| **Instituição** | CESAR School |
| **Curso** | Segurança da Informação |
| **Disciplina** | Algoritmos e Estrutura de Dados |
| **Linguagem** | C (padrão GCC) |

## Integrante

- Miguel Barros Cavalcanti

## Como compilar e executar

```bash
gcc main.c -o safe_console
./safe_console
```

## Menu do programa

```
--------- MENU ---------
1. Mascarar dado sensivel
2. Validar senha
3. Cifrar com Cesar
4. Decifrar com Cesar
5. Cifrar com XOR
6. Decifrar com XOR
7. Gerar senha segura (extra)
8. Ver logs de auditoria
0. Sair
```

## Funcionalidades por etapa

### Etapa 1: Sanitização e validação de entrada

| Função | O que faz |
|---|---|
| `ler_string()` | Lê texto com `fgets()` respeitando o tamanho do buffer e remove o `\n` final. Não usa `gets()`, evitando buffer overflow. |
| `mascarar_dados()` | Troca por `*` todos os caracteres de um dado sensível (CPF, cartão, token), deixando visíveis só os 4 últimos. |
| `validar_senha()` | Exige no mínimo 8 caracteres, uma maiúscula, uma minúscula e um número, consultando os códigos da tabela ASCII (65-90, 97-122 e 48-57). |

### Etapa 2: Cifragem simétrica e decifragem

| Função | O que faz |
|---|---|
| `cifrar_cesar()` / `descifrar_cesar()` | Desloca as letras no alfabeto de acordo com o valor escolhido pelo usuário. Números e símbolos não mudam. |
| `cifrar_xor()` | Aplica o operador bit-a-bit `^` com uma chave do tipo `char` e mostra o resultado em hexadecimal (`%02X`). |
| `decifrar_xor()` | Reaplica o XOR com a mesma chave para recuperar o texto original. |
| Menu interativo | `switch/case` dentro de um laço `do-while`. |

### Etapa 3: Logs e auditoria

| Recurso | O que faz |
|---|---|
| Matriz de histórico | `char historico[MAX_LOGS][TAM_BUFFER]` guarda as mensagens processadas em memória. |
| `registrar_log()` | Grava a mensagem, o algoritmo usado e o tamanho (`strlen`) a cada mascaramento, validação de senha, geração de senha e cifragem (César e XOR). |
| `listar_logs()` | Exibe o relatório com ID, algoritmo, tamanho e payload. |

## Recursos extras

| Função | O que faz |
|---|---|
| `gerar_senha_segura()` | Sorteia com `rand()` uma senha aleatória de tamanho escolhido, misturando letras, números e símbolos. |
| `mostrar_forca_visual()` | Desenha uma barra de força da senha, como `[###--]`, com base em cinco critérios. |
| `senha_tem_sequencia()` | Avisa quando a senha tem sequências previsíveis, como `123`, `abc` ou `aaa`. |

## Exemplo de uso

```
Digite o dado sensivel (ex: CPF, cartao): 12345678901234
Dado mascarado: **********1234

Digite o texto: Hello
Digite o deslocamento (ex: 3): 3
Texto cifrado: Khoor

Digite o texto: Segredo123
Digite a chave (1 caractere): K
Texto cifrado (em hexadecimal): 182E2C392E2F247A7978

Digite a senha: Senha@Forte9
Senha valida! Atende a todos os requisitos.
Forca da senha: [#####] (5 de 5)
```

## Conceitos de C aplicados

- Leitura segura de strings e prevenção de buffer overflow
- Vetores e matriz 2D de caracteres
- Tabela ASCII e operadores bit-a-bit (`^`)
- Formatação com `printf` (`%02X`, `%-16s`)
- Modularização em funções com protótipos
- Estruturas `switch/case`, `do-while`, `for` e `if/else`
- Números aleatórios com `rand()` e `srand()`

## Estrutura do repositório

```
safe-console-c/
├── main.c
└── README.md
```
