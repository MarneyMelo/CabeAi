#include <iostream>
#include "../include/demanda.hpp"
#include "../include/corrida.hpp"
#include "../include/escalonador.hpp"

const int MAX_DEMANDAS_SISTEMA = 10000;

int main() {

    int eta;        // Capacidade do veículo
    float gama;     // Velocidade do veículo
    float delta;    // Intervalo temporal máx. entre corridas combinadas
    float alfa;     // Distância máx. entre origens
    float beta;     // Distância máx. entre destinos
    float lambda;   // Eficiência mínima da corrida combinada
    int numDemandas; // Número total de demandas

    std::cin >> eta;
    std::cin >> gama;
    std::cin >> delta;
    std::cin >> alfa;
    std::cin >> beta;
    std::cin >> lambda;
    std::cin >> numDemandas;

    // Validacao basica, se der erro basta alterar MAX_DEMANDAS_SISTEMA
    if (numDemandas > MAX_DEMANDAS_SISTEMA) {
        std::cerr << "ERRO: Numero de demandas (" << numDemandas 
                  << ") excede o limite maximo suportado (" 
                  << MAX_DEMANDAS_SISTEMA << ")." << std::endl;
        return 1;
    }

    static Demanda listaDemandas[MAX_DEMANDAS_SISTEMA];

    for (int i = 0; i < numDemandas; i++) {
        int id;
        float tempo;
        float xOrig, yOrig, xDest, yDest;

        // Format: <id> <tempo> <origem> <destino>
        std::cin >> id >> tempo >> xOrig >> yOrig >> xDest >> yDest;

        Ponto pOrigem(xOrig, yOrig);
        Ponto pDestino(xDest, yDest);

        // Cria o objeto e guarda no array
        listaDemandas[i] = Demanda(id, tempo, pOrigem, pDestino);
    }

    //Debug: Confirmação de Leitura
    std::cout << "--- Leitura Concluida ---" << std::endl;
    std::cout << "Capacidade (eta): " << eta << std::endl;
    std::cout << "Velocidade (gama): " << gama << std::endl;
    std::cout << "Total de Demandas lidas: " << numDemandas << std::endl;

    // despacho......

    return 0;
}