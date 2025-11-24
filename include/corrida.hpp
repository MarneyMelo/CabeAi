#ifndef CORRIDA_HPP
#define CORRIDA_HPP

#include "demanda.hpp"
#include "trecho.hpp"
#include "parada.hpp" 

const int MAX_DEMANDAS_POR_CORRIDA = 50; // >= 'eta' = capacidade do veiculo
const int MAX_PARADAS_POR_CORRIDA = MAX_DEMANDAS_POR_CORRIDA * 2;
const int MAX_TRECHOS_POR_CORRIDA = MAX_PARADAS_POR_CORRIDA - 1;

class Corrida {
private:
    int idsDemandas[MAX_DEMANDAS_POR_CORRIDA];
    Trecho trechos[MAX_TRECHOS_POR_CORRIDA];

    int numDemandas;
    int numTrechos;

    float duracaoTotal;
    float distanciaTotal;
    float eficiencia;


    // soma a dist e duração de todos os trechos
    void calcularTotais();

    // calcula a distância euclidiana (reta)
    float calcularDistanciaReta(Ponto p1, Ponto p2);

public:
    Corrida::Corrida()
    : numDemandas(0),
      numTrechos(0),
      duracaoTotal(0.0),
      distanciaTotal(0.0),
      eficiencia(1.0) // Uma corrida (mesmo vazia) tem 100% por padrão
    {
    }

    void construirRota(Demanda demandas[], int num, float velocidadeVeiculo);

    //getters
    float getDistanciaTotal() const { return distanciaTotal; }
    float getDuracaoTotal() const { return duracaoTotal; }
    float getEficiencia() const { return eficiencia; }
    int getNumDemandas() const { return numDemandas; }

    // Usado para a saida
    int getNumParadas() const { return numTrechos + 1; }

    // Usado para a saida
    const Trecho* getTrechos() const { return trechos; }

};

#endif