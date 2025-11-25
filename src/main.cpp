#include <iostream>
#include <cmath> // Necessário para sqrt e pow (cálculo de distâncias).
#include <iomanip>
#include "../include/demanda.hpp"
#include "../include/corrida.hpp"
#include "../include/escalonador.hpp"

const int MAX_DEMANDAS_SISTEMA = 10000;

int main() {
    // ---------------------------------------------------------
    // 1. Leitura dos parâmetros de configuração do sistema
    // ---------------------------------------------------------
    int eta;         // Capacidade máxima de passageiros por veículo.
    double gama;     // Velocidade média do veículo (km/h ou m/s).
    double delta;    // Janela de tempo máxima permitida para agrupamento (ride-pooling).
    double alfa;     // Desvio máximo permitido entre as origens das demandas.
    double beta;     // Desvio máximo permitido entre os destinos das demandas.
    double lambda;   // Eficiência mínima exigida para validar uma rota compartilhada.
    int numDemandas; // Quantidade total de solicitações a processar.

    if (!(std::cin >> eta >> gama >> delta >> alfa >> beta >> lambda >> numDemandas)) {
        return 0; // Encerra a execução caso a entrada esteja incompleta.
    }

    // Validação de segurança para evitar estouro de buffer nos arrays estáticos.
    if (numDemandas > MAX_DEMANDAS_SISTEMA) {
        std::cerr << "ERRO: Numero de demandas (" << numDemandas 
                  << ") excede o limite maximo suportado (" 
                  << MAX_DEMANDAS_SISTEMA << ")." << std::endl;
        return 1;
    }

    // ---------------------------------------------------------
    // 2. Carregamento das Demandas
    // ---------------------------------------------------------
    
    static Demanda listaDemandas[MAX_DEMANDAS_SISTEMA];

    for (int i = 0; i < numDemandas; i++) {
        int id;
        double tempo;
        double xOrig, yOrig, xDest, yDest;

        std::cin >> id >> tempo >> xOrig >> yOrig >> xDest >> yDest;

        Ponto pOrigem(xOrig, yOrig);
        Ponto pDestino(xDest, yDest);

        listaDemandas[i] = Demanda(id, tempo, pOrigem, pDestino);
    }

    // ---------------------------------------------------------
    // 3. Lógica de Despacho (Heurística Gulosa)
    // ---------------------------------------------------------
    
    static Corrida listaCorridas[MAX_DEMANDAS_SISTEMA];
    int totalCorridas = 0;
    
    Escalonador escalonador;

    // Buffer auxiliar para simular a construção de rotas antes de confirmá-las.
    static Demanda buffer[50]; 

    for (int i = 0; i < numDemandas; i++) {
        // Se a demanda já foi atendida (alocada em uma rota anterior), passa para a próxima.
        if (listaDemandas[i].getEstado() != EstadoCorrida::DEMANDADA) {
            continue;
        }

        // Início de uma nova rota candidata.
        int qtdAtual = 0;
        
        // Adiciona a demanda atual como pivô da nova corrida.
        buffer[qtdAtual] = listaDemandas[i];
        qtdAtual++;
        
        // Marcação temporária de estado.
        listaDemandas[i].setEstado(EstadoCorrida::INDIVIDUAL);

        // Tenta agrupar demandas subsequentes na mesma rota.
        for (int j = i + 1; j < numDemandas; j++) {
            
            // 1. Restrição Temporal (Delta): Demandas muito distantes no tempo não são compatíveis.
            // Como a lista está ordenada cronologicamente, podemos interromper o loop.
            if (listaDemandas[j].getTempo() - listaDemandas[i].getTempo() >= delta) {
                break; 
            }

            // Ignora demandas que já foram alocadas.
            if (listaDemandas[j].getEstado() != EstadoCorrida::DEMANDADA) {
                continue;
            }

            // 2. Restrição de Capacidade (Eta).
            if (qtdAtual >= eta) {
                break;
            }

            // 3. Restrições Espaciais (Alfa e Beta):
            // Verifica a viabilidade geométrica em relação a todas as demandas já inseridas no buffer.
            bool distanciasOk = true;
            for (int k = 0; k < qtdAtual; k++) {
                // Distância entre origens
                double dOrig = std::sqrt(std::pow(listaDemandas[j].getOrigem().x - buffer[k].getOrigem().x, 2) +
                                        std::pow(listaDemandas[j].getOrigem().y - buffer[k].getOrigem().y, 2));
                // Distância entre destinos
                double dDest = std::sqrt(std::pow(listaDemandas[j].getDestino().x - buffer[k].getDestino().x, 2) +
                                        std::pow(listaDemandas[j].getDestino().y - buffer[k].getDestino().y, 2));
                
                if (dOrig > alfa || dDest > beta) {
                    distanciasOk = false;
                    break;
                }
            }

            if (!distanciasOk) {
                break; // Interrompe a avaliação se as restrições espaciais forem violadas.
            }
            
            // Adiciona temporariamente para teste de eficiência.
            buffer[qtdAtual] = listaDemandas[j];
            qtdAtual++;

            Corrida teste;
            teste.construirRota(buffer, qtdAtual, gama);

            // 4. Restrição de Eficiência (Lambda).
            if (teste.getEficiencia() >= lambda) {
                // A combinação é válida: confirma o estado das demandas.
                listaDemandas[j].setEstado(EstadoCorrida::COMBINADA);
                if (qtdAtual > 1) listaDemandas[i].setEstado(EstadoCorrida::COMBINADA);
            } else {
                // Reverte a inserção se a eficiência for insuficiente.
                qtdAtual--;
                break; 
            }
        }

        // Consolida a corrida definitiva e armazena na lista oficial.
        listaCorridas[totalCorridas].construirRota(buffer, qtdAtual, gama);

        // Agendamento inicial: Insere o evento de chegada na primeira parada (origem da primeira demanda).
        double tempoInicio = listaDemandas[i].getTempo();
        escalonador.inserirEvento(Evento(tempoInicio, totalCorridas, 0, TipoEvento::CHEGADA_PARADA));

        totalCorridas++;
    }

    // ---------------------------------------------------------
    // 4. Loop Principal de Simulação (Processamento de Eventos)
    // ---------------------------------------------------------
    
    std::cout << std::fixed << std::setprecision(2);

    while (escalonador.temEventos()) {
        Evento e = escalonador.retirarProximoEvento();
        
        int idC = e.getIdCorrida();
        int idxP = e.getIndiceParada();
        
        // Referência para a corrida associada ao evento.
        Corrida& c = listaCorridas[idC];
        int totalParadas = c.getNumParadas();

        // Verifica se o evento corresponde à última parada da rota.
        if (idxP >= totalParadas - 1) {
            // --- Finalização da Corrida ---
            // Formato de saída: <TempoConclusão> <DistânciaTotal> <NumParadas> <Coordenadas...>
            std::cout << e.getTempo() << " "
                      << c.getDistanciaTotal() << " "
                      << c.getNumParadas();

            // Impressão da sequência de coordenadas visitadas.
            // A estrutura 'Trecho' conecta P1 -> P2.
            // Para reconstruir o caminho completo, imprimimos a origem do primeiro trecho
            // e, subsequentemente, o destino de todos os trechos.
            
            const Trecho* trechos = c.getTrechos();
            
            // Imprime a coordenada inicial (Origem do primeiro trecho).
            if (totalParadas > 0) {
                Ponto p = trechos[0].getParada1().getCoordenadas(); 
                std::cout << " " << p.x << " " << p.y;
            }

            // Itera sobre os trechos imprimindo os destinos (Destino de cada trecho).
            for (int k = 0; k < totalParadas - 1; k++) {
                Ponto p = trechos[k].getParada2().getCoordenadas();
                std::cout << " " << p.x << " " << p.y;
            }

            // O ultimo if e for, sao usados para que a saída seja coerente: A->B->C->D
            
            std::cout << std::endl;

        } else {
            // --- Evento Intermediário ---
            // O veículo chegou a uma parada, mas a rota continua.
            // Calcula o tempo de deslocamento até a próxima parada e agenda o evento futuro.
            
            double tempoTrecho = c.getTrechos()[idxP].getTempoGasto();
            double novoTempo = e.getTempo() + tempoTrecho;

            escalonador.inserirEvento(Evento(novoTempo, idC, idxP + 1, TipoEvento::CHEGADA_PARADA));
        }
    }

    return 0;
}