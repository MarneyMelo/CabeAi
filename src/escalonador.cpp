#include "../include/escalonador.hpp"
#include <iostream>

void Escalonador::inserirEvento(Evento e) {
    // Verifica overflow antes da inserção para garantir integridade da memória.
    if (tamanho >= MAX_EVENTOS) {
        std::cerr << "ERRO CRITICO: Escalonador cheio (" 
                  << MAX_EVENTOS << " eventos). O evento foi descartado." << std::endl;
        return; 
    }

    // Insere o novo evento na primeira posição livre (final do array)
    heap[tamanho] = e;
    tamanho++;

    // Reorganiza a árvore de baixo para cima para manter a propriedade do Heap.
    refazerSubindo(tamanho - 1);
}

Evento Escalonador::retirarProximoEvento() {
    // Verifica underflow.
    if (tamanho == 0) {
        std::cerr << "AVISO: Tentativa de retirar de escalonador vazio." << std::endl;
        return Evento(); // Retorna um evento inválido/neutro.
    }

    // A raiz (índice 0) sempre contém o evento com o menor tempo (Min-Heap).
    Evento minEvento = heap[0];

    // Move o último elemento para a raiz e decrementa o tamanho.
    heap[0] = heap[tamanho - 1];
    tamanho--;

    // Reorganiza a árvore de cima para baixo, se ainda houver elementos.
    if (tamanho > 0) {
        refazerDescendo(0);
    }

    return minEvento;
}

void Escalonador::refazerSubindo(int indice) { // Heapify Up
    while (indice > 0) {
        int pai = (indice - 1) / 2;

        // Propriedade de Min-Heap: O pai deve ser menor ou igual ao filho.
        // Se o filho for menor (evento ocorre antes), realizamos a troca (swap).
        if (heap[indice].getTempo() < heap[pai].getTempo()) { 
            Evento temp = heap[indice];
            heap[indice] = heap[pai];
            heap[pai] = temp;
            
            indice = pai; // Atualiza o índice para continuar a verificação ascendente.
        } else {
            break; // A propriedade do heap foi satisfeita.
        }
    }
}

void Escalonador::refazerDescendo(int indice) { // Heapify Down
    int menor = indice;
    int filhoEsq = 2 * indice + 1;
    int filhoDir = 2 * indice + 2;

    // Verifica se o filho da esquerda existe e se é menor que o nó atual.
    if (filhoEsq < tamanho && heap[filhoEsq].getTempo() < heap[menor].getTempo()) {
        menor = filhoEsq;
    }
    
    // Verifica se o filho da direita existe e se é ainda menor que o atual "menor".
    if (filhoDir < tamanho && heap[filhoDir].getTempo() < heap[menor].getTempo()) {
        menor = filhoDir;
    }

    // Se o nó atual não for o menor, troca com o menor filho e continua descendo.
    if (menor != indice) {
        Evento temp = heap[indice];
        heap[indice] = heap[menor];
        heap[menor] = temp;

        refazerDescendo(menor); // Chamada recursiva para ajustar a subárvore afetada.
    }
}