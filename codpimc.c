#include <stdio.h> // Para entrada e saída padrão
#include <stdlib.h> // Para funções de alocação de memória
#include <string.h> // Para manipulação de strings
#include <locale.h> // Para configuração de locale
#include <windows.h> // Para funções específicas do Windows
#include <ctype.h> // Para funções de manipulação de caracteres 

// Pasta onde ficam os arquivos de dados
#define PASTA "C:/Users/LEONETTI/Desktop/pim_final/dados_escolares"    // Ajustar conforme necessário para cada computador para apontar para a pasta correta 

// Estrutura para armazenar os dados de um aluno
typedef struct { // Estrutura para armazenar os dados de um aluno
    char nome[100]; // Nome do aluno
    char ra[20]; // RA do aluno
    char turma[10]; // Turma do aluno
    float nota; // Nota do aluno
} AlunoInfo; // Estrutura para armazenar os dados de um aluno

// Função de comparação para o qsort, para ordenar por nome
int compararAlunos(const void *a, const void *b) { // Função de comparação para o qsort, para ordenar por nome
    AlunoInfo *alunoA = (AlunoInfo *)a; // Ponteiro para o primeiro aluno
    AlunoInfo *alunoB = (AlunoInfo *)b; // Ponteiro para o segundo aluno
    return strcmp(alunoA->nome, alunoB->nome); // Comparação dos nomes dos alunos
}

// Função para remover espaços e quebras de linha no início e final da string
void remover_espacos(char *str) { // Função para remover espaços e quebras de linha no início e final da string
    char *start = str; // Ponteiro para o início da string
    char *end; // Ponteiro para o final da string
 
    while (*start && isspace((unsigned char)*start)) { // Remove espaços no início
        start++; // Incrementa o ponteiro
    } 

    if (*start == 0) { // String vazia após remover espaços
        *str = 0; // Define a string como vazia
        return; // Retorna
    }

    if (str != start) { // Move a string para o início se necessário
        memmove(str, start, strlen(start) + 1); // Move a string
    }
 
    end = str + strlen(str) - 1; // Ponteiro para o final da string
    while (end > str && (isspace((unsigned char)*end) || *end == '\r' || *end == '\n')) { // Remove espaços no final
        *end = '\0'; // Define o caractere como nulo
        end--; // Decrementa o ponteiro
    }
}

// Função para limpar a tela
void limpar_tela() { // Função para limpar a tela
    #ifdef _WIN32 // Se estiver no Windows
        system("cls");  // Comando para limpar a tela no Windows
    #endif // Fim do ifdef
}

// Função para pausar o programa e esperar o usuário pressionar ENTER
void pausar() { // Função para pausar o programa e esperar o usuário pressionar ENTER
    printf("\nPressione ENTER para continuar..."); // Mensagem para o usuário
    while (getchar() != '\n'); // Limpa o buffer de entrada
    getchar(); // Espera o ENTER
} 

// --- FUNÇÃO ATUALIZADA COM DIAGNÓSTICO ---
void exibir_relatorio(const char *arquivo, const char *disciplina) { // Função para exibir o relatório de uma disciplina
    char caminho[256]; // Caminho completo do arquivo
    snprintf(caminho, sizeof(caminho), "%s/%s", PASTA, arquivo); // Monta o caminho completo do arquivo

    FILE *fp = fopen(caminho, "r"); // Abre o arquivo para leitura
    if (!fp) { // Se não conseguiu abrir o arquivo
        printf("\n[ERRO] Arquivo %s não encontrado!\n", caminho); // Mensagem de erro
        return; 
    }

    AlunoInfo alunos[150]; // Array para armazenar os dados dos alunos
    int qtd = 0; // Quantidade de alunos lidos
    float soma = 0; // Soma das notas dos alunos
    char linha[512]; // Linha para leitura do arquivo

    printf("\n[DEBUG] Lendo o arquivo: %s\n\n", caminho); // DEBUG INICIAL

    while (fgets(linha, sizeof(linha), fp) && qtd < 150) { // Lê cada linha do arquivo
        linha[strcspn(linha, "\r\n")] = 0; // Remove quebras de linha

        if (strstr(linha, "Aluno") && strstr(linha, "Nota:")) { // Verifica se a linha contém os dados do aluno
            char *aluno_str, *ra_str, *turma_str, *nota_str; // Strings temporárias para os dados
            char copia[512]; // Cópia da linha para manipulação
            strcpy(copia, linha); // Copia a linha para a variável temporária

            aluno_str = strtok(copia, "|"); // Extrai os dados usando strtok
            ra_str = strtok(NULL, "|"); // Continua extraindo
            turma_str = strtok(NULL, "|"); // Continua extraindo
            nota_str = strtok(NULL, "|"); // Continua extraindo

            if (aluno_str && ra_str && turma_str && nota_str) { // Verifica se todos os dados foram extraídos corretamente
                remover_espacos(aluno_str); // Remove espaços desnecessários
                remover_espacos(ra_str); // Remove espaços desnecessários
                remover_espacos(turma_str); // Remove espaços desnecessários
                remover_espacos(nota_str); // Remove espaços desnecessários


                // Zera os campos da struct antes de preencher, para evitar lixo de memória
            // ...

                // Tenta extrair os dados
                int res_aluno = sscanf(aluno_str, "Aluno : %[^|]", alunos[qtd].nome); // IMPORTANTE: Veja se a extração funciona
                int res_ra = sscanf(ra_str, "RA : %[^|]", alunos[qtd].ra); // IMPORTANTE: Veja se a extração funciona
                int res_turma = sscanf(turma_str, "Turma : %[^|]", alunos[qtd].turma); // IMPORTANTE: Veja se a extração funciona

               
                // DEBUG DAS EXTRAÇÕES
                setlocale(LC_NUMERIC, "C"); // Define locale para C para garantir o ponto decimal
                sscanf(nota_str, "Nota : %f", &alunos[qtd].nota); // IMPORTANTE: Veja se a extração funciona
                setlocale(LC_NUMERIC, "pt_BR.UTF-8"); // Restaura o locale para pt_BR

                soma += alunos[qtd].nota; // Acumula a nota para cálculo da média
                qtd++; // Incrementa a quantidade de alunos lidos
            }
        }
    }
    fclose(fp); // Fecha o arquivo

    printf("\n=== RELATÓRIO DE %s ===\n", disciplina); // Título do relatório

    if (qtd > 0) { // Se encontrou alunos no arquivo
        qsort(alunos, qtd, sizeof(AlunoInfo), compararAlunos); // Ordena os alunos por nome

        for (int i = 0; i < qtd; i++) { // Exibe os dados de cada aluno
            printf("Aluno: %-20s | RA: %-10s | Turma: %-5s | Nota: %.2f\n", // Formato de exibição
                   alunos[i].nome, alunos[i].ra, alunos[i].turma, alunos[i].nota); //   Dados do aluno
        }
        printf("Média da turma: %.2f\n", soma / qtd); // Exibe a média da turma
    } else { // Se não encontrou alunos no arquivo
        printf("Nenhum dado encontrado no formato esperado.\n"); // Mensagem de aviso
    }
}

// Função para exibir a lista de todos os alunos
void exibir_alunos() { // Função para exibir a lista de todos os alunos
    char caminho[256]; // Caminho completo do arquivo
    snprintf(caminho, sizeof(caminho), "%s/alunos.txt", PASTA); // Monta o caminho completo do arquivo

    FILE *fp = fopen(caminho, "r"); // Abre o arquivo para leitura
    if (!fp) { // Se não conseguiu abrir o arquivo
        printf("\n[ERRO] Arquivo de alunos não encontrado!\n"); // Mensagem de erro
        return;
    }

    char linha[256]; // Linha para leitura do arquivo
    printf("\n=== LISTA DE ALUNOS ===\n"); // Título da lista

    while (fgets(linha, sizeof(linha), fp)) { // Lê cada linha do arquivo
        printf("%s", linha); // Exibe a linha lida
    }
    
    fclose(fp); // Fecha o arquivo
}

// Função para exibir alunos de uma turma específica
void exibir_turma() { // Função para exibir alunos de uma turma específica
    char turma_desejada[10]; // Turma que o usuário deseja exibir
    char caminho[256]; // Caminho completo do arquivo
    
    printf("\nDigite a turma que deseja exibir (ex: 9A, 9B, 9C): "); // Solicita a turma ao usuário
    scanf("%9s", turma_desejada);  // Lê a turma desejada

     // Limpa o buffer de entrada
    
    int c; // Variável para leitura de caracteres
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    
    for (int i = 0; turma_desejada[i]; i++) { // Converte a turma para maiúsculas
        turma_desejada[i] = toupper((unsigned char)turma_desejada[i]); // Converte para maiúscula
    }
    
    snprintf(caminho, sizeof(caminho), "%s/alunos.txt", PASTA); // Monta o caminho completo do arquivo

    FILE *fp = fopen(caminho, "r"); // Abre o arquivo para leitura
    if (!fp) { // Se não conseguiu abrir o arquivo
        printf("\n[ERRO] Arquivo de alunos não encontrado!\n"); // Mensagem de erro
        return;
    }

    char linha[256]; // Linha para leitura do arquivo
    int turma_encontrada = 0; // Flag para indicar se a turma foi encontrada

    printf("\n=== ALUNOS DA TURMA %s ===\n", turma_desejada); // Título da lista

    while (fgets(linha, sizeof(linha), fp)) {// Lê cada linha do arquivo
        remover_espacos(linha); // Remove espaços desnecessários

        if (strstr(linha, "TURMA") && strstr(linha, turma_desejada)) { // Verifica se a linha contém a turma desejada
            turma_encontrada = 1; // Marca que a turma foi encontrada
            break; 
        }
    }

    if (!turma_encontrada) { // Se a turma não foi encontrada
        printf("Turma '%s' não encontrada.\n", turma_desejada); // Mensagem de aviso
        fclose(fp); // Fecha o arquivo
        return;
    }

    while (fgets(linha, sizeof(linha), fp)) { // Continua lendo as linhas do arquivo
        if (strstr(linha, "===") && strstr(linha, "TURMA")) { // Verifica se chegou ao fim da turma
            break;
        }
        printf("%s", linha); // Exibe a linha lida
    }
    
    fclose(fp); // Fecha o arquivo
}

// Menu principal
int main() { // Menu principal
    setlocale(LC_ALL, "pt_BR.UTF-8");  // Configura o locale para português do Brasil
    #ifdef _WIN32 // Se estiver no Windows
        SetConsoleOutputCP(CP_UTF8); // Configura o console para UTF-8
    #endif  // Fim do ifdef

    int opcao; // Opção escolhida pelo usuário

    do { // Loop do menu
        limpar_tela(); // Limpa a tela
        printf("\n=== SISTEMA ESCOLAR - RELATÓRIOS ===\n"); // Título do menu
        printf("1 - Geografia\n"); // Opção de Geografia
        printf("2 - História\n"); // Opção de História
        printf("3 - Matemática\n"); // Opção de Matemática
        printf("4 - Português\n"); // Opção de Português
        printf("5 - Lista de Alunos Completa\n"); // Opção de Lista de Alunos Completa
        printf("6 - Alunos por Turma\n"); // Opção de Alunos por Turma
        printf("7 - Sair\n"); // Opção de Sair
        printf("Escolha uma opção: "); // Solicita a opção ao usuário
        scanf("%d", &opcao); // 

        limpar_tela(); // Limpa a tela
        

        switch (opcao) { // Switch para tratar a opção escolhida
            case 1: exibir_relatorio("geografia.txt", "Geografia"); break; // Opção de Geografia
            case 2: exibir_relatorio("historia.txt", "História"); break; // Opção de História
            case 3: exibir_relatorio("matematica.txt", "Matemática"); break; // Opção de Matemática
            case 4: exibir_relatorio("portugues.txt", "Português"); break; //   Opção de Português
            case 5: exibir_alunos(); break; // Opção de Lista de Alunos Completa
            case 6: exibir_turma(); break; // Opção de Alunos por Turma
            case 7: printf("Saindo...\n"); break; // Opção de Sair
            default: printf("Opção inválida!\n"); // Opção inválida
        }

        if (opcao != 7) { // Se não for sair
            pausar(); // Pausa o programa
        } 
    } while (opcao != 7); // Enquanto não for sair

    return 0;      // Retorna 0 para indicar sucesso
}