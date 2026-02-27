#ifndef FSM_H
#define FSM_H

// Definição dos estados da Máquina de Estados Finita (FSM)
enum EcoSortState {
    IDLE,
    DETECCAO,
    ABERTURA_TAMPA,
    CAPTURA,
    CLASSIFICACAO,
    DECISAO,
    ACAO,
    FECHAMENTO,
    ERRO
};

// Classe para gerenciar a FSM
class EcoSortFSM {
public:
    EcoSortFSM();
    void begin();
    void run();
    void transitionTo(EcoSortState newState);
    EcoSortState getCurrentState();

private:
    EcoSortState currentState;
    unsigned long stateEntryTime;

    void handleIdle();
    void handleDeteccao();
    void handleAberturaTampa();
    void handleCaptura();
    void handleClassificacao();
    void handleDecisao();
    void handleAcao();
    void handleFechamento();
    void handleError();
};

#endif // FSM_H
