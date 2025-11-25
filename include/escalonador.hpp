#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "evento.hpp"

// Define a capacidade máxima de eventos que o sistema pode enfileirar simultaneamente.
const int MAX_EVENTOS = 5000; 

// Classe responsável pelo gerenciamento temporal da simulação.
// Implementa uma Fila de Prioridade (Priority Queue) baseada em Min-Heap,
// garantindo que o evento com o menor tempo (mais próximo) esteja sempre na raiz.
class Escalonador {
private:
    Evento heap[MAX_EVENTOS]; // Estrutura de armazenamento da árvore binária (Heap).
    int tamanho;              // Contador do número atual de eventos na fila.

    // Restaura a propriedade de Min-Heap movendo um elemento para baixo (Heapify Down).
    // Utilizado após a remoção da raiz para reorganizar a estrutura.
    void refazerDescendo(int indice);

    // Restaura a propriedade de Min-Heap movendo um elemento para cima (Heapify Up).
    // Utilizado após a inserção de um novo evento.
    void refazerSubindo(int indice);

public:
    // Construtor: inicializa o escalonador com tamanho zero.
    Escalonador() : tamanho(0) {}

    // Verifica se há eventos pendentes para processamento.
    bool temEventos() const { return tamanho > 0; }

    // Retorna a quantidade total de eventos agendados no momento.
    int getTamanho() const { return tamanho; }

    // Insere um novo evento na fila e rebalanceia o heap automaticamente.
    void inserirEvento(Evento e);

    // Extrai e retorna o próximo evento da cronologia (o de menor tempo).
    Evento retirarProximoEvento();
};

#endif