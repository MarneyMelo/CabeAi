/*
3.2.1 Demanda
A demanda por uma corrida, cujas informações são lidas do arquivo de entrada, representa
a origem e destino de uma corrida, assim como um identificador e quando ela foi solicitada.
Para fins da simulação, a demanda por uma corrida pode estar em 4 estados:
1. Corrida demandada
2. Corrida individual
3. Corrida combinada
4. Corrida concluída
O TAD demanda, além de manter os dados da demanda e a corrida associada, deve
armazenar o estado atual, e as estatísticas de execução da corrida. Essas informações
serão fundamentais para o cálculo das estatísticas gerais do sistema.
*/
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