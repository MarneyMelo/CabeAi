#include "../include/corrida.hpp"
#include <cmath>
#include <iostream>

void Corrida::construirRota(Demanda demandas[], int num, double velocidadeVeiculo) {
    if (num <= 0 || num > MAX_DEMANDAS_POR_CORRIDA) {
        std::cerr << "ERROR: Tentativa de construir rota com " << num 
              << " demandas. Operação ignorada." << std::endl;
        return;
    }

    this->numDemandas = num;
    this->numTrechos = 0;

    //ordem FIFO:: embarque 0, 1...N ---> desembarque 0, 1...N 
    Parada paradasDaRota[MAX_PARADAS_POR_CORRIDA];
    for (int i = 0; i < num; i++) {
        this->idsDemandas[i] = demandas[i].getId();
        
        // parada de embarque
        paradasDaRota[i] = Parada(demandas[i].getOrigem(),
                                  TipoParada::EMBARQUE,
                                  demandas[i].getId());
        
        // parada de desembarque
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

    calcularTotais(); // atualiza this->distanciaTotal e this->duracaoTotal

    // calcular a eficiencia
    // Eficiência = (Soma das distâncias retas) / (Distância total da rota)
    // ex do enunciado: 8km (util) / 10km (rota) = 80% 
    
    double distanciaUtilTotal = 0.0;
    for (int i = 0; i < num; i++) {
        distanciaUtilTotal += calcularDistanciaReta(demandas[i].getOrigem(),
                                                    demandas[i].getDestino());
    }

    if (this->distanciaTotal > 0) {
        this->eficiencia = distanciaUtilTotal / this->distanciaTotal;
    } else {
        // se a distância total for 0 (ex: origem = destino),
        // a eficiência é 100%
        this->eficiencia = 1.0;
    }
}

void Corrida::calcularTotais() {
    this->distanciaTotal = 0.0;
    this->duracaoTotal = 0.0;
    for (int i = 0; i < this->numTrechos; i++) {
        this->distanciaTotal += this->trechos[i].getDistancia(); //pega a distancia de cada trecho e soma ao total
        this->duracaoTotal += this->trechos[i].getTempoGasto(); //pega o tempo de cada trecho e soma ao total
    }
}

double Corrida::calcularDistanciaReta(Ponto p1, Ponto p2) {
    // Dist = sqrt( (x2-x1)^2 + (y2-y1)^2 )
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}