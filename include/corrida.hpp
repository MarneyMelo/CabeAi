#ifndef CORRIDA_HPP
#define CORRIDA_HPP

#include "demanda.hpp"
#include "trecho.hpp"
#include "parada.hpp" 

// Define a capacidade máxima de demandas. Deve ser >= 'eta' (capacidade do veículo).
const int MAX_DEMANDAS_POR_CORRIDA = 50; 

// O número máximo de paradas é o dobro das demandas, considerando 1 embarque e 1 desembarque por solicitação.
const int MAX_PARADAS_POR_CORRIDA = MAX_DEMANDAS_POR_CORRIDA * 2; 

// Um trecho conecta duas paradas consecutivas.
// Exemplo: Paradas A e B formam o trecho A->B.
const int MAX_TRECHOS_POR_CORRIDA = MAX_PARADAS_POR_CORRIDA - 1; 

class Corrida {
private:
    int idsDemandas[MAX_DEMANDAS_POR_CORRIDA];
    Trecho trechos[MAX_TRECHOS_POR_CORRIDA];

    int numDemandas;
    int numTrechos;

    double duracaoTotal;
    double distanciaTotal;
    double eficiencia;

    // Atualiza a distância e a duração total somando os valores de todos os trechos da rota.
    void calcularTotais();

    // Calcula a distância euclidiana (reta) entre dois pontos.
    double calcularDistanciaReta(Ponto p1, Ponto p2);

public:
    // Construtor padrão.
    Corrida()
    : numDemandas(0),
      numTrechos(0),
      duracaoTotal(0.0),
      distanciaTotal(0.0),
      eficiencia(1.0) // Inicializa com eficiência máxima (100%) por padrão.
    {
    }

    void construirRota(Demanda demandas[], int num, double velocidadeVeiculo);

    // Métodos de acesso (Getters)
    double getDistanciaTotal() const { return distanciaTotal; }
    double getDuracaoTotal() const { return duracaoTotal; }
    double getEficiencia() const { return eficiencia; }
    int getNumDemandas() const { return numDemandas; }

    // Auxiliar para a formatação da saída de dados (número total de paradas).
    int getNumParadas() const { return numTrechos + 1; }

    // Retorna o array de trechos (usado para gerar o output das coordenadas).
    const Trecho* getTrechos() const { return trechos; }
};

#endif