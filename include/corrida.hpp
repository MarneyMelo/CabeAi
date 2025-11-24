#ifndef CORRIDA_HPP
#define CORRIDA_HPP

#include "demanda.hpp"
#include "trecho.hpp"
#include "parada.hpp" 

const int MAX_DEMANDAS_POR_CORRIDA = 50; // >= 'eta' = capacidade do veic
const int MAX_PARADAS_POR_CORRIDA = MAX_DEMANDAS_POR_CORRIDA * 2; // cada demanda tem no max 1 embarque e 1 desembarque 
const int MAX_TRECHOS_POR_CORRIDA = MAX_PARADAS_POR_CORRIDA - 1; // um trecho liga duas paradas
                                                                // (ex: Paradas: A, B. Trecho: A->B)

class Corrida {
private:
    int idsDemandas[MAX_DEMANDAS_POR_CORRIDA];
    Trecho trechos[MAX_TRECHOS_POR_CORRIDA];

    int numDemandas;
    int numTrechos;

    double duracaoTotal;
    double distanciaTotal;
    double eficiencia;


    // soma a dist e duração de todos os trechos
    void calcularTotais();

    // calcula a dist euclidiana
    double calcularDistanciaReta(Ponto p1, Ponto p2);

public:
    //construtor default
    Corrida()
    : numDemandas(0),
      numTrechos(0),
      duracaoTotal(0.0),
      distanciaTotal(0.0),
      eficiencia(1.0) // corrida tem 100% de eficiencia por padrao
    {
    }

    void construirRota(Demanda demandas[], int num, double velocidadeVeiculo);

    //getters
    double getDistanciaTotal() const { return distanciaTotal; }
    double getDuracaoTotal() const { return duracaoTotal; }
    double getEficiencia() const { return eficiencia; }
    int getNumDemandas() const { return numDemandas; }

    // Usado para a saida
    int getNumParadas() const { return numTrechos + 1; }

    // Usado para a saida
    const Trecho* getTrechos() const { return trechos; }

};

#endif