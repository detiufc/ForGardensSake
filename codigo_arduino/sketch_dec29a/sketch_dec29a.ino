/*
 * Programa: codigo do atuador (rele e sensor de vazao)
 * Autora: Sayonara
 */

#define pinoVazao 2
#define pinoRele 4

int pulsoAtual = 0; //Variavel para armazenar o sinal do sensor de vazao
int pulsoAnterior = 0; //Variavel para armazenar o sinal do sensor de vazao anterior
float vazao = 0; //Vazao apresentada a cada 1s (L/min)
float mediaVazao = 0; //Vazao apresentada a cada 10s (L/min)
volatile int contaPulsos; //Frequencia do sensor de vazao
int qtdSegundos = 0; //Contador para o envio da mensagem
int tempoMensagem = 10; //Tempo para enviar a mensagem
int inicioIntervalo = 0;
int intervalo = 0; //contador de 1 segundo
String mensagem;


void setup()
{
  pinMode(pinoRele, OUTPUT); 
  digitalWrite(pinoRele,HIGH);
  
  Serial.begin(115200);
  
  pinMode(pinoVazao, INPUT);
  inicioIntervalo = millis();
}


void loop ()
{
  pulsoAtual = digitalRead(pinoVazao);
    
  if(pulsoAtual != pulsoAnterior){
    contaPulsos++;
  }
  
  pulsoAnterior = pulsoAtual;
  intervalo = millis() - inicioIntervalo;
   
  //Calcula a vazao a cada 1s
  if(intervalo == 1000){
    vazao = contaPulsos * 7.5 / 60; //vazao em litros por minuto
    mediaVazao = mediaVazao + vazao;
    qtdSegundos++;
    inicioIntervalo = millis();
    contaPulsos = 0;
  }

  //Calcula a vazao a cada 10 segundos e envia a vazao pela porta serial
  if(qtdSegundos == tempoMensagem){
    mediaVazao = mediaVazao/tempoMensagem;
    Serial.print(mediaVazao);
    qtdSegundos = 0;
    mediaVazao = 0;
    Serial.flush();
   }

  //Verifica se há algum dado no buffer
  if (Serial.available() > 0){
    mensagem = Serial.readString();   
    
    if(mensagem == "IniciaIrrigacao"){
      digitalWrite(pinoRele,LOW);
      }
    if(mensagem == "CancelaIrrigacao"){
      digitalWrite(pinoRele,HIGH);   
      }
   }
   
}
