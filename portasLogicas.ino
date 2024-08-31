  /*
 * Projeto: Controle de Portas Lógicas E e OU
 * Descrição: 
 * Este código é destinado ao controle de LEDs com base em entradas de botões,
 * usando um Arduino para simular portas lógicas E e OU. O circuito é composto por
 * 4 botões e 4 LEDs. A lógica de operação (E ou OU) é determinada pela programação.
 *
 * Funcionamento:
 * - Quando configurado para lógica E, um LED acende apenas se todos os botões 
 *   estiverem pressionados simultaneamente.
 * - Quando configurado para lógica OU, um LED acende se pelo menos um dos botões 
 *   estiver pressionado.
 *
 * Componentes:
 * - 4 Botões conectados aos pinos digitais 2, 3, 4 e 5.
 * - 4 LEDs conectados aos pinos digitais 6, 7, 8 e 9.
 * - Resistores pull-up conectados aos pinos de entrada.
 *
 * Autor: [Eduardo Moletta]
 * Data: [31/08/24]
 *
 * Versão: 1.0
 */

  
  //Saídas 

unsigned char ledI1Pin =2;
unsigned char ledI2Pin =3;
unsigned char ledI3Pin= 4;
unsigned char ledSPin = 5;
unsigned char buzzerPin= 6;

//Entradas
unsigned const char botI1Pin =7;
unsigned const char botI2Pin =8;
unsigned const char botI3Pin= 9;
unsigned const char botSPin = 10;   

// variásveis para armazenar o estado das entradas e saída da Porta lógica 
bool estadoI1 =0;
bool estadoI2=0;
bool estadoI3=0;
bool estadoS;

//váriáveis para perceber os botões se foram clicados 
bool estadoBI1 =0;
bool ultimoEstadoI1 = LOW;
unsigned long lastDebounceTimeI1;


bool estadoBI2=0;
bool ultimoEstadoI2 = LOW;
unsigned long lastDebounceTimeI2;


bool estadoBI3=0;
bool ultimoEstadoI3 = LOW;
unsigned long lastDebounceTimeI3;

bool estadoBS=0;
bool ultimoEstadoS = LOW;
unsigned long lastDebounceTimeS;






unsigned long debounceDelay = 50; 
unsigned long ultimaVez = 0; 


void setup() {
  // onfigura porta serial 
  Serial.begin(9600);

  //configura as saídas 
  pinMode(ledI1Pin,OUTPUT);
  pinMode(ledI2Pin,OUTPUT);
  pinMode(ledI3Pin,OUTPUT);
  pinMode(ledSPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  //condigura as entradas 
  pinMode(botI1Pin,INPUT);
  pinMode(botI2Pin,INPUT);
  pinMode(botI3Pin,INPUT);
  pinMode(botSPin,INPUT);

  //LIGA TODOS OS LED e buzzer POR 2 SEGUNDOS {
  digitalWrite(ledI1Pin,HIGH);
  digitalWrite(ledI2Pin,HIGH);
  digitalWrite(ledI3Pin,HIGH);
  digitalWrite(ledSPin,HIGH);
  digitalWrite(buzzerPin, 1);
  delay(2000);

  digitalWrite(ledI1Pin,LOW);
  digitalWrite(ledI2Pin,LOW);
  digitalWrite(ledI3Pin,LOW);
  digitalWrite(ledSPin,LOW);
 digitalWrite(buzzerPin,0);
  //LIGA TODOS OS LED POR 2 SEGUNDOS }

}

//função para emitir o barulho de sim ou não 
void ligaBuzzer(bool estado){
        if(estado == false){
           digitalWrite(buzzerPin, 1);  
           delay(100);
           digitalWrite(buzzerPin,0);
           delay(100);
            digitalWrite(buzzerPin, 1);
          delay(200);
        }else{
            digitalWrite(buzzerPin, 1);
          delay(500);
        }
        digitalWrite(buzzerPin,0);                                                
}

//quando apertar algum botão vem aqui e de acordo com o botão pressionado toma a decisão 
void apertouBotao(unsigned char botao){
  //botI1Pin
  //botI2Pin
  //botI3Pin
  //botSPin
  switch(botao){
    case botI1Pin:
      estadoI1 = !estadoI1;
      ligaBuzzer(estadoI1);
    break;  
    case botI2Pin:
      estadoI2 = !estadoI2;
      ligaBuzzer(estadoI2);
    break;  
    case botI3Pin:
      estadoI3 = !estadoI3;
      ligaBuzzer(estadoI3);
    break;
    
    case botSPin:
       ligaBuzzer(estadoS);
    break;
  }




}


void loop() {
//Trecho de código para Dbug na porta serial
  if ((millis() - ultimaVez) > 2000) {
    Serial.print("Estado porta 1:");
    Serial.println(estadoI1);
    Serial.print("Estado porta 2:");
    Serial.println(estadoI2);
    Serial.print("Estado porta 3:");
    Serial.println(estadoI3);
    Serial.print("Estado Saida:");
    Serial.println(estadoS);
    ultimaVez = millis();

  }
    //trecho para perceber se um botão foi precionado
  int lendo1 = digitalRead(botI1Pin);
  int lendo2 = digitalRead(botI2Pin);
  int lendo3 = digitalRead(botI3Pin);
  int lendoS = digitalRead(botSPin);

  if (lendo1 != ultimoEstadoI1) {
     // reset the debouncing timer
    lastDebounceTimeI1 = millis();
  }
  if (lendo2 != ultimoEstadoI2) {
     // reset the debouncing timer
    lastDebounceTimeI2 = millis();
  }
  if (lendo3 != ultimoEstadoI3) {
     // reset the debouncing timer
    lastDebounceTimeI3 = millis();
  }
  if (lendoS != ultimoEstadoS) {
     // reset the debouncing timer
    lastDebounceTimeS = millis();
  }

  //ver botao 1
  if ((millis() - lastDebounceTimeI1) > debounceDelay) {
    if (lendo1 != estadoBI1) {
      estadoBI1 = !estadoBI1;
    }
    if(!estadoBI1){
      apertouBotao(botI1Pin);
    } 
   
  }
  //ver botao 2
  if ((millis() - lastDebounceTimeI2) > debounceDelay) {
    if (lendo2 != estadoBI2) {
      estadoBI2 = !estadoBI2;
    }
    if(!estadoBI2){
      apertouBotao(botI2Pin);
    } 
  }
  //ver botao 3
  if ((millis() - lastDebounceTimeI3) > debounceDelay) {
    if (lendo3 != estadoBI3) {
      estadoBI3 = !estadoBI3;
    }
    if(!estadoBI3){
      apertouBotao(botI3Pin);
    } 
  }
   //ver botao saida
  if ((millis() - lastDebounceTimeS) > debounceDelay) {
    if (lendoS != estadoBS) {
      estadoBS = !estadoBS;
    }
    if(!estadoBS){
      apertouBotao(botSPin);
    } 
  }
  ultimoEstadoI1 = lendo1;
  ultimoEstadoI2 = lendo2;
  ultimoEstadoI3 = lendo3;
  ultimoEstadoS = lendoS;
 //Termina de ler os botões aqui 
  
  //vamos calcular a saída da porta
  estadoS = estadoI1 && estadoI2 && estadoI3; // PORTA E
  //estadoS = estadoI1 || estadoI2 || estadoI3;   //PORTA OU
  //estadoS = !estadoI1;  //PORTA NAO 

  //agora atualiza os LEDs com entradas e saídas
  digitalWrite(ledI1Pin,estadoI1);
  digitalWrite(ledI2Pin,estadoI2);
  digitalWrite(ledI3Pin,estadoI3);
  digitalWrite(ledSPin,estadoS);
}

