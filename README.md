# CabeAí Sistema de Despacho de Transporte por Aplicativo

### Documentação Completa
A documentação técnica detalhada (10 páginas), incluindo
análise formal, metodologia experimental e resultados,
está disponível em: `DOC/Documentacao-Cabeai.pdf`

## Sobre o Projeto

Este repositório contém a minha implementação para um trabalho prático da disciplina de Estruturas de Dados. O desafio era criar, do zero e em C++, um sistema de *Sistema de Transporte por Aplicativo*.

Essa implementação tem como objetivo implementar um algoritmo que processe entradas com os dados de solicitações de corridas e, com base nas geolocalizações, as corridas são alocadas conjuntamente em um mesmo veículo, de acordo com um limiar de distância, tempo e capacidade do veículo.

## Análises

O trabalho, além da implementação, conta com uma documentação completa, onde é descrita a análise de complexidade e análise experimental do algoritmo, a fim de medir matematicamente e experimentalmente o custo de execução e desemepenho da implementação. 

Os scripts da análise experimental não foram anexados a esse repositório, que tem como objetivo focar na implementação do sistema, mas o resultado desta análise pode ser acessada na documentação presente na árvore do projeto.

## Tecnologias Utilizadas

* **C++ (padrão C++11)**
* **Makefile** para automação da compilação
* **G++**

## Estrutura do Projeto

```
.
├── bin/                      # Contém o executável final (tp2.out)
├── docs/                     # Contém a documentação formal do projeto
│   └── Documentacao-CabeAi.pdf
├── include/                  # Arquivos de cabeçalho (.hpp)
├── obj/                      # Arquivos de objeto intermediários (.o)
├── src/                      # Arquivos de implementação (.cpp)
├── testes/                   # Contém arquivos de entrada e saída para teste
│   ├── inputs_1.txt
│   ├── inputs_2.txt
│   ├── outputs_1.txt
│   └── outputs_2.txt
├── .gitignore                # Especifica arquivos a serem ignorados pelo Git
├── Makefile                  # Arquivo de compilação
└── README.md                 # Resumo do repositório (este arquivo)
```

## Como Compilar e Executar

### Pré-requisitos

* `g++` (compilador C++)
* `make`

### Compilação

Na pasta raiz do projeto, execute o comando:
```bash
make all
```
O executável `tp2.out` será criado na pasta `bin/`.

### Execução

O programa lê os dados via arquivos ou entrada padrão caso seja feita modificação. Para executar com um arquivo de teste, use:
```bash
./bin/tp2.out caminho/para/seu_arquivo_de_teste.txt (por exemplo testes/inputs_1.txt que ja está na raiz do projeto)
```

### Documentação Completa
A documentação técnica detalhada (10 páginas), incluindo
análise formal, metodologia experimental e resultados,
está disponível em: `DOC/Documentacao-Cabeai.pdf`

## Autor

**Marney Santos de Melo**

## Licença

Este projeto está sob a licença MIT.
