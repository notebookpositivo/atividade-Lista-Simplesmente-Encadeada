# Sistema de Gestão de Funcionários

Programa em C para cadastro de funcionários usando **lista simplesmente encadeada**, feito para a disciplina de **Estrutura de Dados** (UNICIVE), com o Prof. Rodney Carneiro.

**Autor:** Gabriel de Brito Abreu

## Funcionalidades

O programa roda no console, com um menu de 9 opções:

| Opção | Ação |
|-------|------|
| 1 | Cadastrar funcionário no final da lista |
| 2 | Cadastrar funcionário no início da lista |
| 3 | Cadastrar funcionário em uma posição da lista |
| 4 | Remover funcionário do final da lista |
| 5 | Remover funcionário do início da lista |
| 6 | Remover funcionário de uma posição da lista |
| 7 | Alterar o cadastro de um funcionário (pelo código) |
| 8 | Consultar funcionários |
| 9 | Sair do programa (grava os dados em disco) |

Outros recursos:

- **Confirmação** antes de salvar ou remover (1 para salvar, 2 para cancelar, 0 para voltar).
- **Código único:** não deixa cadastrar dois funcionários com o mesmo código.
- **Consulta com ordenação:** na ordem de cadastro, em ordem alfabética (nome), por código ou por salário (do menor para o maior). A ordenação é feita em um vetor de ponteiros, então a lista original não é alterada.
- **Persistência:** os dados são salvos em `Funcionario.dat` ao sair (opção 9) e carregados automaticamente quando o programa abre.

## Dados de cada funcionário

| Campo | Tipo |
|-------|------|
| Código | `int` |
| Nome | `char[50]` |
| Endereço | `char[50]` |
| Data de nascimento | `char[10]` |
| Telefone | `char[15]` |
| CPF | `char[15]` |
| Cargo | `char[40]` |
| Departamento | `char[30]` |
| Salário | `float` |

## Como compilar e executar

O programa usa `windows.h` e `conio.h`, então **só funciona no Windows**.

Com o GCC (MinGW) instalado:

```bash
gcc funcionariosB.c -o funcionarios.exe
funcionarios.exe
```

## Arquivo de dados

O `Funcionario.dat` é um arquivo **binário** (gravado com `fwrite`, um registro da struct por funcionário, 220 bytes cada). Este repositório traz um exemplo com 10 funcionários cadastrados. Para usar, deixe o arquivo **na mesma pasta do executável**. Se ele não existir, o programa começa com a lista vazia e cria o arquivo ao sair.

> Não abra o `.dat` em editor de texto e salve, porque isso corrompe os registros.

## Estrutura do projeto

```
├── funcionariosB.c    # código-fonte
├── Funcionario.dat    # arquivo de dados de exemplo (10 registros)
└── README.md
```
