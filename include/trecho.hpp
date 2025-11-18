/*
3.4 Trecho
O TAD trecho registra as informações de deslocamento de um veículo entre duas paradas.
Isso inclui a referência para as duas paradas que o delimitam, o tempo, a
 distância percorrida e a natureza do trecho:
  coleta (caracterizado por duas paradas de embarque), entrega
(caracterizado por duas paradas de desembarque), ou deslocamento (caracterizado por um
embarque e um desembarque)
*/

#ifndef TRECHO_HPP
#define TRECHO_HPP

#include "parada.hpp" 
#include <cmath>       // para calcular sqrt e pow

enum class TipoTrecho {
    COLETA,      
    ENTREGA,     
    DESLOCAMENTO 
};

class Trecho {
private:
    Parada parada1;
    Parada parada2;
    float distancia;
    float tempoGasto;
    TipoTrecho tipo;

    TipoTrecho definirTipoTrecho(Parada p1, Parada p2);
    float calcularDistancia(Ponto p1, Ponto p2);

public:
    Trecho(Parada p1, Parada p2, float velocidadeVeiculo);

    Trecho() : distancia(0.0), tempoGasto(0.0), tipo(TipoTrecho::DESLOCAMENTO) {}

    // getters
    Parada getParada1() const { return parada1; }
    Parada getParada2() const { return parada2; }
    float getDistancia() const { return distancia; }
    float getTempoGasto() const { return tempoGasto; }
    TipoTrecho getTipo() const { return tipo; }
};

#endif