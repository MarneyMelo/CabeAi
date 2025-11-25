#ifndef TRECHO_HPP
#define TRECHO_HPP

#include "parada.hpp" 
#include <cmath>

// Classificação do tipo de movimento realizado pelo veículo entre dois pontos.
enum class TipoTrecho {
    COLETA,      // Movimento entre duas paradas de embarque (coletando passageiros).
    ENTREGA,     // Movimento entre duas paradas de desembarque (entregando passageiros).
    DESLOCAMENTO // Caracterizado por um embarque e um desembarque
};

// Representa um segmento (aresta) da rota, conectando duas paradas consecutivas (nós).
// Armazena as métricas de custo (distância e tempo) associadas a esse deslocamento.
class Trecho {
private:
    Parada parada1; // Ponto de partida do trecho.
    Parada parada2; // Ponto de chegada do trecho.
    double distancia;
    double tempoGasto;
    TipoTrecho tipo;

    // Determina a natureza do trecho com base nos tipos das paradas de origem e destino.
    TipoTrecho definirTipoTrecho(Parada p1, Parada p2);

    // Calcula a distância euclidiana entre as coordenadas das duas paradas.
    double calcularDistancia(Ponto p1, Ponto p2);

public:
    // Construtor principal: inicializa o trecho e calcula automaticamente a distância,
    // o tempo gasto (baseado na velocidade) e o tipo do trecho.
    Trecho(Parada p1, Parada p2, double velocidadeVeiculo);

    // Construtor padrão: inicializa com valores nulos/neutros para instanciar arrays.
    Trecho() : distancia(0.0), tempoGasto(0.0), tipo(TipoTrecho::DESLOCAMENTO) {}

    // Métodos de acesso (Getters)
    Parada getParada1() const { return parada1; } 
    Parada getParada2() const { return parada2; }
    double getDistancia() const { return distancia; }
    double getTempoGasto() const { return tempoGasto; }
    TipoTrecho getTipo() const { return tipo; }
};

#endif