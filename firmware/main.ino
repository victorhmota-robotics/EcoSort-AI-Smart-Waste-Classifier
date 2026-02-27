#include "fsm.h"
#include "pins.h"

// Instância da Máquina de Estados Finita
EcoSortFSM ecoSortFSM;

void setup() {
  // Inicializa a comunicação serial para depuração
  Serial.begin(115200);
  while (!Serial); // Aguarda a porta serial abrir

  Serial.println("\nIniciando EcoSort...");

  // Inicializa a FSM e seus módulos internos
  ecoSortFSM.begin();

  // Outras inicializações de hardware podem vir aqui
  // Ex: pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Executa a lógica da Máquina de Estados
  ecoSortFSM.run();

  // Pequeno delay para evitar sobrecarga da CPU em simulações simples
  // Em um sistema real, isso seria gerenciado pelos tempos de transição da FSM
  delay(10);
}
