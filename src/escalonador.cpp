#include "../include/escalonador.hpp"
#include <iostream>

void Escalonador::inserirEvento(Evento e) {
    if (tamanho >= MAX_EVENTOS) {
        std::cerr << "ERRO CRITICO: Escalonador cheio (" 
                  << MAX_EVENTOS << " eventos). O evento foi descartado." << std::endl;
        return; 
    }

    heap[tamanho] = e;
    tamanho++;
    refazerSubindo(tamanho - 1);
}

Evento Escalonador::retirarProximoEvento() {
    if (tamanho == 0) {
        std::cerr << "AVISO: Tentativa de retirar de escalonador vazio." << std::endl;
        return Evento(); // Retorna um evento default (vazio/invalid)
    }

    Evento minEvento = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;

    if (tamanho > 0) {
        refazerDescendo(0);
    }

    return minEvento;
}

void Escalonador::refazerSubindo(int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        // MinHeap:::::: O pai deve ser menor que o filho. Se não for, troca
        if (heap[indice].getTempo() < heap[pai].getTempo()) {
            Evento temp = heap[indice];
            heap[indice] = heap[pai];
            heap[pai] = temp;
            indice = pai; // Continua verificando subindo a tree
        } else {
            break; // esta na posicao certa
        }
    }
}

void Escalonador::refazerDescendo(int indice) {
    int menor = indice;
    int filhoEsq = 2 * indice + 1;
    int filhoDir = 2 * indice + 2;

    // Verifica se o filho da esquerda é menor que o atual
    if (filhoEsq < tamanho && heap[filhoEsq].getTempo() < heap[menor].getTempo()) {
        menor = filhoEsq;
    }
    
    // verifica se o filho da direita e ainda menor
    if (filhoDir < tamanho && heap[filhoDir].getTempo() < heap[menor].getTempo()) {
        menor = filhoDir;
    }

    // se encontrou um filho menor, troca e continua descendo
    if (menor != indice) {
        Evento temp = heap[indice];
        heap[indice] = heap[menor];
        heap[menor] = temp;

        refazerDescendo(menor); // recursao para arrumar o resto de baixo
    }
}