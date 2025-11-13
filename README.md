# Sistema Escolar - Relatórios

**Sistema de Gestão de Notas e Relatórios Acadêmicos**

## 📝 Descrição

Este é um sistema desenvolvido em C para gerenciamento de dados escolares, permitindo a visualização de relatórios de notas por disciplina, listagem de alunos e consulta por turmas específicas.

## ⚡ Funcionalidades

- 📊 **Relatórios por Disciplina**: Visualização de notas e médias em Geografia, História, Matemática e Português
- 👥 **Lista Completa de Alunos**: Exibição de todos os alunos cadastrados no sistema
- 🏫 **Consulta por Turma**: Filtro de alunos por turma específica (9A, 9B, 9C)
- 📈 **Cálculo de Médias**: Cálculo automático da média de cada disciplina
- 🔤 **Ordenação Alfabética**: Listagem de alunos ordenada por nome

## 🗂️ Estrutura do Projeto

```
pim_final/
├── codpimc.c                 # Código principal do sistema
├── README.md                 # Este arquivo
├── dados_escolares/          # Pasta com os dados dos alunos
│   ├── alunos.txt           # Lista completa dos alunos
│   ├── geografia.txt        # Notas de Geografia
│   ├── historia.txt         # Notas de História
│   ├── matematica.txt       # Notas de Matemática
│   └── portugues.txt        # Notas de Português
├── output/                  # Pasta para arquivos de saída
└── turmas/                  # Pasta com dados por turma
    ├── 9A.txt
    ├── 9B.txt
    └── 9C.txt
```

## 🚀 Como Compilar e Executar

### Pré-requisitos
- Compilador GCC ou similar
- Sistema Windows (configurado para Windows no código)

### Compilação
```bash
gcc -o sistema_escolar codpimc.c
```

### Execução
```bash
./sistema_escolar
```

## 🎯 Como Usar

Ao executar o programa, você verá o menu principal com as seguintes opções:

```
=== SISTEMA ESCOLAR - RELATÓRIOS ===
1 - Geografia
2 - História
3 - Matemática
4 - Português
5 - Lista de Alunos Completa
6 - Alunos por Turma
7 - Sair
```

### Opções do Menu:

1. **Geografia (1)**: Exibe relatório de notas da disciplina de Geografia
2. **História (2)**: Exibe relatório de notas da disciplina de História
3. **Matemática (3)**: Exibe relatório de notas da disciplina de Matemática
4. **Português (4)**: Exibe relatório de notas da disciplina de Português
5. **Lista Completa (5)**: Mostra todos os alunos cadastrados
6. **Por Turma (6)**: Permite consultar alunos de uma turma específica
7. **Sair (7)**: Encerra o programa

## 📋 Formato dos Dados

### Arquivo de Alunos (`alunos.txt`)
```
===== TURMA 9A =====
Aluno: Nome do Aluno | RA: CODIGO | Turma: 9A
```

### Arquivos de Disciplinas
```
Aluno: Nome do Aluno | RA: CODIGO | Turma: 9A | Nota: 8.5
```

## 🔧 Configuração

### Caminho dos Arquivos
Por padrão, o sistema procura os arquivos na pasta:
```c
#define PASTA "C:/Users/LEONETTI/Desktop/pim_final/dados_escolares"
```

**⚠️ IMPORTANTE**: Ajuste este caminho conforme a localização dos seus arquivos.

### Personalização
- **Limite de Alunos**: O sistema suporta até 150 alunos por disciplina
- **Tamanho do Nome**: Nomes podem ter até 100 caracteres
- **Código RA**: Códigos podem ter até 20 caracteres
- **Código da Turma**: Códigos podem ter até 10 caracteres

## 🏗️ Estrutura do Código

### Principais Funções:

- `exibir_relatorio()`: Processa e exibe relatórios por disciplina
- `exibir_alunos()`: Mostra a lista completa de alunos
- `exibir_turma()`: Filtra e exibe alunos por turma
- `compararAlunos()`: Função de comparação para ordenação
- `remover_espacos()`: Remove espaços desnecessários das strings

### Estrutura de Dados:
```c
typedef struct {
    char nome[100];    // Nome do aluno
    char ra[20];       // RA do aluno
    char turma[10];    // Turma do aluno
    float nota;        // Nota do aluno
} AlunoInfo;
```

## 🎨 Características Técnicas

- **Linguagem**: C (C99+)
- **Platform**: Windows
- **Encoding**: UTF-8
- **Locale**: pt_BR
- **Ordenação**: Alfabética por nome
- **Formato de Notas**: Decimal com 2 casas

## 📞 Funcionalidades Especiais

- ✅ **Auto-limpeza de tela**: Interface limpa a cada navegação
- ✅ **Validação de entrada**: Tratamento de erros de arquivo
- ✅ **Formatação de texto**: Remove espaços e caracteres indesejados
- ✅ **Cálculo automático**: Médias calculadas em tempo real
- ✅ **Suporte a acentos**: Configuração completa para português brasileiro

## 🚨 Possíveis Problemas

### Arquivo não encontrado
```
[ERRO] Arquivo não encontrado!
```
**Solução**: Verifique se o caminho da pasta `PASTA` está correto e se os arquivos existem.

### Problemas de encoding
**Solução**: Certifique-se de que os arquivos estão salvos em UTF-8.

### Compilação
**Solução**: Use um compilador compatível com as bibliotecas Windows incluídas.

## 📄 Licença

© Todos os direitos reservados TecMais LTDA - 2025

---

**Desenvolvido em C para gestão acadêmica eficiente** 🎓
