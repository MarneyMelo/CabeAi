/*
3.3 Parada
O TAD parada mantém as informações sobre cada parada feita por um veículo durante
uma corrida. Isso inclui, além das coordenadas da parada, se ela foi de embarque ou
desembarque, e qual o passageiro (de qual demanda) que embarcou ou desembarcou, 
respectivamente.
*/
#ifndef PARADA_HPP
#define PARADA_HPP

#include "ponto.hpp"

enum class TipoParada {
    EMBARQUE,
    DESEMBARQUE
};

class Parada{
    private:
    Ponto coordenadas;
    TipoParada tipo;
    int idDemanda;

    public:
    Parada()
        : coordenadas(Ponto(0,0)),
          tipo(TipoParada::EMBARQUE),
          idDemanda(-1)
    {

    }

    Parada(Ponto coords, TipoParada tipo, int demandaId)
        : coordenadas(coords),
          tipo(tipo),
          idDemanda(demandaId)
    {

    }

    //getters
    Ponto getCoordenadas() const { return coordenadas; }
    TipoParada getTipo() const {return tipo;}
    int getIdDemanda() const {return idDemanda;}

};
#endif