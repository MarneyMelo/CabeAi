#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "evento.hpp"

const int MAX_EVENTOS = 5000; 

class Escalonador {
private:
    Evento heap[MAX_EVENTOS];
    int tamanho;              

    void refazerDescendo(int indice);
    void refazerSubindo(int indice);

public:
    Escalonador() : tamanho(0) {}
    bool temEventos() const {return tamanho > 0;}
    int getTamanho() const {return tamanho;}

    void inserirEvento(Evento e);
    Evento retirarProximoEvento();
};

#endif