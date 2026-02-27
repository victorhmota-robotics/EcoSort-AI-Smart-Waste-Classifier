# Pinagem Oficial do Projeto EcoSort

Este documento detalha a pinagem oficial para o projeto EcoSort, utilizando o microcontrolador ESP32-S3-WROOM e seus periféricos. A escolha dos pinos foi feita considerando as funcionalidades de cada componente e as melhores práticas para o ESP32-S3, evitando pinos de strapping para funções críticas e utilizando os recursos de hardware de forma eficiente.

## 1. ESP32-S3-WROOM

O ESP32-S3-WROOM é o microcontrolador central do sistema, responsável por todas as operações de controle, processamento e comunicação.

## 2. Câmera OV2640 (DVP)

A câmera OV2640 é utilizada para a captura de imagens dos resíduos. A pinagem a seguir é uma configuração comum para módulos de câmera com ESP32-S3.

| Função do Pino | Pino ESP32-S3 | Observações |
|---|---|---|
| D0 | GPIO5 | Pinos de Dados da Câmera |
| D1 | GPIO6 | |
| D2 | GPIO7 | |
| D3 | GPIO8 | |
| D4 | GPIO9 | |
| D5 | GPIO10 | |
| D6 | GPIO11 | |
| D7 | GPIO12 | |
| PCLK | GPIO3 | Clock de Pixel (Cuidado com pino de strapping) |
| VSYNC | GPIO4 | Sincronização Vertical |
| HREF | GPIO2 | Sincronização Horizontal |
| XCLK | GPIO1 | Clock Externo |
| PWDN | GPIO45 | Power Down |
| RESET | GPIO46 | Reset (Cuidado com pino de strapping) |
| SIOD | GPIO17 | I2C Data para Câmera (SDA) |
| SIOC | GPIO18 | I2C Clock para Câmera (SCL) |

**Nota sobre GPIO3 e GPIO46:** Estes são pinos de strapping no ESP32-S3. Embora possam ser usados como GPIOs, é importante ter cuidado com o estado deles durante o boot para evitar comportamentos inesperados. Em um projeto educacional/MVP, seu uso pode ser aceitável, mas em aplicações críticas, deve-se preferir outros pinos.

## 3. Servos SG90 (6 no total)

Os servos SG90 são controlados via PWM. O ESP32-S3 possui múltiplos canais PWM que podem ser mapeados para a maioria dos GPIOs.

| Função do Servo | Pino ESP32-S3 (PWM) | Observações |
|---|---|---|
| Servo da Tampa Principal | GPIO14 | Controle da tampa de entrada |
| Servo da Porta da Câmara de Análise | GPIO15 | Controle da porta interna da câmara |
| Servo Compartimento Papel | GPIO16 | |
| Servo Compartimento Plástico | GPIO19 | |
| Servo Compartimento Metal | GPIO20 | |
| Servo Compartimento Vidro | GPIO21 | |

## 4. Sensores Ultrassônicos HC-SR04 (5 no total)

Cada sensor ultrassônico requer dois pinos GPIO: um para Trigger (saída) e um para Echo (entrada).

| Função do Sensor | Pino Trigger ESP32-S3 | Pino Echo ESP32-S3 | Observações |
|---|---|---|---|
| Sensor de Aproximação | GPIO33 | GPIO34 | Detecta a presença de um objeto |
| Sensor Nível Papel | GPIO35 | GPIO36 | Monitora o nível do compartimento de papel |
| Sensor Nível Plástico | GPIO37 | GPIO38 | Monitora o nível do compartimento de plástico |
| Sensor Nível Metal | GPIO39 | GPIO40 | Monitora o nível do compartimento de metal |
| Sensor Nível Vidro | GPIO41 | GPIO42 | Monitora o nível do compartimento de vidro |

## 5. Interface

### Display OLED 0.96” (I2C)

O display OLED utiliza o protocolo I2C para comunicação. Serão utilizados os pinos I2C padrão do ESP32-S3.

| Função do Pino | Pino ESP32-S3 | Observações |
|---|---|---|
| SDA | GPIO8 | Data I2C |
| SCL | GPIO9 | Clock I2C |

**Nota:** Os pinos GPIO8 e GPIO9 foram escolhidos para o I2C do OLED para evitar conflito com os pinos I2C da câmera (GPIO17 e GPIO18) e para liberar outros GPIOs para os servos e sensores. O ESP32-S3 possui múltiplos conjuntos de pinos I2C que podem ser configurados.

### LED Branco

O LED branco é usado para iluminar a câmara de análise.

| Função do Pino | Pino ESP32-S3 | Observações |
|---|---|---|---|
| LED Branco | GPIO48 | Saída digital para controle do LED |

## Resumo da Pinagem

| Componente | Função | Pinos ESP32-S3 |
|---|---|---|
| Câmera OV2640 | Dados | D0-D7 (GPIO5-GPIO12) |
| | Controle | PCLK (GPIO3), VSYNC (GPIO4), HREF (GPIO2), XCLK (GPIO1), PWDN (GPIO45), RESET (GPIO46) |
| | I2C | SIOD (GPIO17), SIOC (GPIO18) |
| Servos SG90 | PWM | GPIO14, GPIO15, GPIO16, GPIO19, GPIO20, GPIO21 |
| Sensores HC-SR04 | Trigger/Echo | GPIO33/GPIO34, GPIO35/GPIO36, GPIO37/GPIO38, GPIO39/GPIO40, GPIO41/GPIO42 |
| Display OLED | I2C | SDA (GPIO8), SCL (GPIO9) |
| LED Branco | Digital Output | GPIO48 |

Esta pinagem serve como base para o desenvolvimento do esquema elétrico e do firmware do projeto EcoSort.
