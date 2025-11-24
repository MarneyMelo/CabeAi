#ifndef DEMANDA_HPP
#define DEMANDA_HPP

#include "ponto.hpp"
#include "estado.hpp"

class Demanda {
private:
    int id;
    float tempo;
    Ponto origem;
    Ponto destino;
    EstadoCorrida estado;

public: 
Demanda() 
        : id(-1),
          tempo(-1),
          origem(Ponto(0,0)),
           destino(Ponto(0,0)),
          estado(EstadoCorrida::DEMANDADA) 
          {}

    Demanda(int id, float tempo, Ponto origem, Ponto destino)
        : id(id),
          tempo(tempo),
          origem(origem),
          destino(destino),
          estado(EstadoCorrida::DEMANDADA) // toda nova demanda começa como "DEMANDADA"
    {
        //
    }

    //getters    
    int getId() const { return id; }
    float getTempo() const { return tempo; }
    Ponto getOrigem() const { return origem; }
    Ponto getDestino() const { return destino; }
    EstadoCorrida getEstado() const { return estado; }

    //setters    
    void setEstado(EstadoCorrida novoEstado) {
        this->estado = novoEstado;
    }
};

#endif