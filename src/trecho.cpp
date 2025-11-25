#include "../include/trecho.hpp"
#include <cmath>

Trecho::Trecho(Parada p1, Parada p2, double velocidadeVeiculo)
    : parada1(p1),
      parada2(p2)
{
    // Calcula a distância espacial entre as paradas.
    this->distancia = calcularDistancia(p1.getCoordenadas(), p2.getCoordenadas());

    // Calcula o custo temporal do trecho.
    // Inclui verificação de segurança para evitar inconsistências (divisão por zero).
    if (velocidadeVeiculo > 0) {
        this->tempoGasto = this->distancia / velocidadeVeiculo;
    } else {
        this->tempoGasto = 0;
    }

    // Classifica automaticamente o tipo de trecho no momento da instanciação.
    this->tipo = definirTipoTrecho(p1, p2);
}

double Trecho::calcularDistancia(Ponto p1, Ponto p2) {
    // Implementação da Distância Euclidiana: sqrt((Δx)² + (Δy)²) = sqrt( (x2-x1)^2 + (y2-y1)^2 )
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

TipoTrecho Trecho::definirTipoTrecho(Parada p1, Parada p2) {
    // Regra de negócio: Classifica a natureza do deslocamento com base nos tipos das paradas adjacentes.
    if (p1.getTipo() == TipoParada::EMBARQUE && p2.getTipo() == TipoParada::EMBARQUE) {
        return TipoTrecho::COLETA;      // Dois embarques
    } else if (p1.getTipo() == TipoParada::DESEMBARQUE && p2.getTipo() == TipoParada::DESEMBARQUE) {
        return TipoTrecho::ENTREGA;     // Dois desembarques
    } else {
        return TipoTrecho::DESLOCAMENTO; // Transição mista (Embarque -> Desembarque).
    }
}