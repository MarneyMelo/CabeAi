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
    // Construtor padrão: inicializa a demanda com valores inválidos ou neutros.
    Demanda() 
        : id(-1),
          tempo(-1),
          origem(Ponto(0,0)),
          destino(Ponto(0,0)),
          estado(EstadoCorrida::DEMANDADA) 
          {}

    // Construtor parametrizado: instancia uma nova demanda com os dados fornecidos.
    // O estado inicial é sempre definido como 'DEMANDADA'.
    Demanda(int id, float tempo, Ponto origem, Ponto destino)
        : id(id),
          tempo(tempo),
          origem(origem),
          destino(destino),
          estado(EstadoCorrida::DEMANDADA)
    {
    }

    // Métodos de acesso (Getters)    
    int getId() const { return id; }
    float getTempo() const { return tempo; }
    Ponto getOrigem() const { return origem; }
    Ponto getDestino() const { return destino; }
    EstadoCorrida getEstado() const { return estado; }

    // Métodos de modificação (Setters)    
    void setEstado(EstadoCorrida novoEstado) {
        this->estado = novoEstado;
    }
};

#endif