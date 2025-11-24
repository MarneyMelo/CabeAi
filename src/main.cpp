#include <iostream>
#include <cmath> // para sqrt e pow na lógica de despacho
#include <iomanip>
#include "../include/demanda.hpp"
#include "../include/corrida.hpp"
#include "../include/escalonador.hpp"

const int MAX_DEMANDAS_SISTEMA = 10000;

int main() {
    //=======================================================
    //1 Leitura dos parametros idem figura 2 enunciado
    //======================================================
    int eta;        // Capacidade do veículo
    double gama;     // Velocidade do veículo
    double delta;    // Intervalo temporal máx. entre corridas combinadas
    double alfa;     // Distância máx. entre origens
    double beta;     // Distância máx. entre destinos
    double lambda;   // Eficiência mínima da corrida combinada
    int numDemandas; // Número total de demandas

    if (!(std::cin >> eta >> gama >> delta >> alfa >> beta >> lambda >> numDemandas)) {
        return 0; // encerra se nao houver todos inputs
    }

    //caso de erro, basta alterar MAX_DEMANDAS_SISTEMA line:7
    if (numDemandas > MAX_DEMANDAS_SISTEMA) {
        std::cerr << "ERRO: Numero de demandas (" << numDemandas 
                  << ") excede o limite maximo suportado (" 
                  << MAX_DEMANDAS_SISTEMA << ")." << std::endl;
        return 1;
    }

    // ---------------------------------
    // 2. Leitura das Demandas
    // ------------------------------
    
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

    // -------------------------------------
    // 3- Lógica de despacho e inicializacao
    // ---------------------------------------
    
    static Corrida listaCorridas[MAX_DEMANDAS_SISTEMA];
    int totalCorridas = 0;
    
    Escalonador escalonador;

    // vector auxiliar para testar combinacoes (tamanho igual a MAX_DEMANDAS_POR_CORRIDA em corrida.hpp)
    static Demanda buffer[50]; 

    for (int i = 0; i < numDemandas; i++) {
        // se a demanda ja foi alocada em outra corrida, pula (ja incrementa o i)
        if (listaDemandas[i].getEstado() != EstadoCorrida::DEMANDADA) {
            continue;
        }

        // nova corrida
        int qtdAtual = 0;
        
        // Adiciona a demanda inicial (c0)
        buffer[qtdAtual] = listaDemandas[i];
        qtdAtual++;
        
        // marca temporariamente enquanto nao é acoplada a outra
        listaDemandas[i].setEstado(EstadoCorrida::INDIVIDUAL);

        // Tenta combinar com as outras demandas
        for (int j = i + 1; j < numDemandas; j++) {
            
            // criterio de tempo (Delta)
            if (listaDemandas[j].getTempo() - listaDemandas[i].getTempo() >= delta) {
                break; // como estao ordenadas cronologicamente, as prox vao falhar
            }

            // Se já foi atendida, ignora (pula incrementando j)
            if (listaDemandas[j].getEstado() != EstadoCorrida::DEMANDADA) {
                continue;
            }

            // criterio de Capacidade (Eta)
            if (qtdAtual >= eta) {
                break;
            }

            // criterios de dist (Alfa e Beta)
            bool distanciasOk = true;
            for (int k = 0; k < qtdAtual; k++) {
                // dist entre origens
                double dOrig = std::sqrt(std::pow(listaDemandas[j].getOrigem().x - buffer[k].getOrigem().x, 2) +
                                        std::pow(listaDemandas[j].getOrigem().y - buffer[k].getOrigem().y, 2));
                // dist entre destinos
                double dDest = std::sqrt(std::pow(listaDemandas[j].getDestino().x - buffer[k].getDestino().x, 2) +
                                        std::pow(listaDemandas[j].getDestino().y - buffer[k].getDestino().y, 2));
                
                if (dOrig > alfa || dDest > beta) {
                    distanciasOk = false;
                    break;
                }
            }

            if (!distanciasOk) {
                break; // nterromper avaliacao se distancia invalida 
            }
                // adiciona para testar eficiencia (Lambda)
                buffer[qtdAtual] = listaDemandas[j];
                qtdAtual++;

                Corrida teste;
                teste.construirRota(buffer, qtdAtual, gama);

                if (teste.getEficiencia() >= lambda) {
                    // aceita a combinacao
                    listaDemandas[j].setEstado(EstadoCorrida::COMBINADA);
                    if (qtdAtual > 1) listaDemandas[i].setEstado(EstadoCorrida::COMBINADA);
                } else {
                    qtdAtual--;
                    break; // Interromper avaliacaoo se eficiencia insuficiente
                }
            
        }

        // cria a corrida definitiva e salva na lista (vai para o output)
        listaCorridas[totalCorridas].construirRota(buffer, qtdAtual, gama);

        // agendar o PRIMEIRO evento desta corrida no escalonador
        // o tempo inicial é o tempo da solicitação da primeira demanda (c0)
        double tempoInicio = listaDemandas[i].getTempo();
        
        // evento: chegada na Parada 0 (PRIMEIRO EMBARQUE)
        // idCorrida = totalCorridas e indiceParada = 0
        escalonador.inserirEvento(Evento(tempoInicio, totalCorridas, 0, TipoEvento::CHEGADA_PARADA));

        totalCorridas++;
        
    }

    // -----------------------------------
    // 4. Loop Principal da Simulação
    // ----------------------------------
    
    std::cout << std::fixed << std::setprecision(2);

    while (escalonador.temEventos()) {
        Evento e = escalonador.retirarProximoEvento();
        
        int idC = e.getIdCorrida();
        int idxP = e.getIndiceParada();
        
        // Ref para a corrida atual
        Corrida& c = listaCorridas[idC];
        int totalParadas = c.getNumParadas();

        // Verifica se é a última parada da corrida
        if (idxP >= totalParadas - 1) {
            // ---!!!! FIM DA CORRIDA:::: Gerar output !!!!---
            // Formato: <TempoConclusao> <Distancia> <NumParadas> <Coords...>
            std::cout << e.getTempo() << " "
                      << c.getDistanciaTotal() << " "
                      << c.getNumParadas();

            // imprime as coordenadas

            // NOTE!!: A estrutura de 'Trechos' armazena (P1->P2)
            // para imprimir todas as paradas (P1, P2, P3...), imprimimos P1 do primeiro trecho
            // e depois P2 de todos os trechos.
            
            const Trecho* trechos = c.getTrechos();
            
            // primeira coordenada (origem do primeiro trecho)
            if (totalParadas > 0) {
                Ponto p = trechos[0].getParada1().getCoordenadas(); // IMPRIME ORIGEM (PARADA 1) DE TRECHO 0
                std::cout << " " << p.x << " " << p.y;
            }

            // Demais coordenadas (destinos dos trechos)
            // Se tem N paradas, tem N-1 trechos
            for (int k = 0; k < totalParadas - 1; k++) {
                Ponto p = trechos[k].getParada2().getCoordenadas();  //K=0 IMPRIME O DESTINO DE TRECHO 0
                                                                     // K= 1 IMPRIME O DESTINO DE TECHO 1
                std::cout << " " << p.x << " " << p.y;
            }
            
            std::cout << std::endl;

        } else {
            // MEIO DA CORRIDA (deslocamento): agendar prox parada ((SALTO NO TEMPO))
            
            // pega o tempo gasto no trecho atual (da parada idxP até idxP+1)
            double tempoTrecho = c.getTrechos()[idxP].getTempoGasto();
            double novoTempo = e.getTempo() + tempoTrecho;

            // insere o próximo evento
            escalonador.inserirEvento(Evento(novoTempo, idC, idxP + 1, TipoEvento::CHEGADA_PARADA));
        }
    }

    return 0;
}