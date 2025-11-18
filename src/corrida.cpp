#include "../include/corrida.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

void Corrida::construirRota(Demanda demandas[], int num, float velocidadeVeiculo) {
    if (num <= 0 || num > MAX_DEMANDAS_POR_CORRIDA) {
        std::cerr << "ERROR: Tentativa de construir rota com " << num 
              << " demandas. Operação ignorada." << std::endl;
        return;
    }

    this->numDemandas = num;
    this->numTrechos = 0;

    // Ordem: Embarque 0, 1...N, Desembarque 0, 1...N 
    Parada paradasDaRota[MAX_PARADAS_POR_CORRIDA];
    for (int i = 0; i < num; i++) {
        this->idsDemandas[i] = demandas[i].getId();
        
        // Parada de Embarque
        paradasDaRota[i] = Parada(demandas[i].getOrigem(),
                                  TipoParada::EMBARQUE,
                                  demandas[i].getId());
        
        // Parada de Desembarque
        paradasDaRota[i + num] = Parada(demandas[i].getDestino(),
                                        TipoParada::DESEMBARQUE,
                                        demandas[i].getId());
    }

    int totalDeParadas = num * 2;
    for (int i = 0; i < totalDeParadas - 1; i++) {
        this->trechos[i] = Trecho(paradasDaRota[i],
                                  paradasDaRota[i + 1],
                                  velocidadeVeiculo);
        this->numTrechos++;
    }

    calcularTotais(); // Atualiza this->distanciaTotal e this->duracaoTotal

    // calcular a Eficiência
    // Eficiência = (Soma das distâncias retas) / (Distância total da rota)
    // Exemplo do PDF: 8km (útil) / 10km (rota) = 80% 
    
    float distanciaUtilTotal = 0.0;
    for (int i = 0; i < num; i++) {
        distanciaUtilTotal += calcularDistanciaReta(demandas[i].getOrigem(),
                                                    demandas[i].getDestino());
    }

    if (this->distanciaTotal > 0) {
        this->eficiencia = distanciaUtilTotal / this->distanciaTotal;
    } else {
        // Se a distância total for 0 (ex: origem = destino),
        // a eficiência é 100%
        this->eficiencia = 1.0;
    }
}

void Corrida::calcularTotais() {
    this->distanciaTotal = 0.0;
    this->duracaoTotal = 0.0;
    for (int i = 0; i < this->numTrechos; i++) {
        this->distanciaTotal += this->trechos[i].getDistancia();
        this->duracaoTotal += this->trechos[i].getTempoGasto();
    }
}

float Corrida::calcularDistanciaReta(Ponto p1, Ponto p2) {
    // Dist = sqrt( (x2-x1)^2 + (y2-y1)^2 )
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}