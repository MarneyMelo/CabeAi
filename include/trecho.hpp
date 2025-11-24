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
    //cada trecho tem duas paradas
    Parada parada1;
    Parada parada2;
    double distancia;
    double tempoGasto;
    TipoTrecho tipo;

    TipoTrecho definirTipoTrecho(Parada p1, Parada p2);
    double calcularDistancia(Ponto p1, Ponto p2);

public:
    Trecho(Parada p1, Parada p2, double velocidadeVeiculo);

    Trecho() : distancia(0.0), tempoGasto(0.0), tipo(TipoTrecho::DESLOCAMENTO) {}

    // getters
    Parada getParada1() const { return parada1; } 
    Parada getParada2() const { return parada2; }
    double getDistancia() const { return distancia; }
    double getTempoGasto() const { return tempoGasto; }
    TipoTrecho getTipo() const { return tipo; }
};

#endif