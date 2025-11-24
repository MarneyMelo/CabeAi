#include "../include/trecho.hpp"
#include <cmath>


Trecho::Trecho(Parada p1, Parada p2, double velocidadeVeiculo)
    : parada1(p1),
      parada2(p2)
{
    this->distancia = calcularDistancia(p1.getCoordenadas(), p2.getCoordenadas());

    if (velocidadeVeiculo > 0) { //verificacao para robustez
        this->tempoGasto = this->distancia / velocidadeVeiculo;
    } else {
        this->tempoGasto = 0;
    }

    this->tipo = definirTipoTrecho(p1, p2);
}


double Trecho::calcularDistancia(Ponto p1, Ponto p2) {
    // Dist = sqrt( (x2-x1)^2 + (y2-y1)^2 )
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

TipoTrecho Trecho::definirTipoTrecho(Parada p1, Parada p2) { //definicao de tipos de trechos conforme o enunciado
    if (p1.getTipo() == TipoParada::EMBARQUE && p2.getTipo() == TipoParada::EMBARQUE) {
        return TipoTrecho::COLETA;
    } else if (p1.getTipo() == TipoParada::DESEMBARQUE && p2.getTipo() == TipoParada::DESEMBARQUE) {
        return TipoTrecho::ENTREGA;
    } else {
        return TipoTrecho::DESLOCAMENTO;
    }
}