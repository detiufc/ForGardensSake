/*
 * Programa: codigo do atuador (rele e sensor de vazao)
 * Autora: Sayonara
 */

#define pinoVazao 2
#define pinoRele 4

int pulsoAtual = 0; //Variavel para armazenar o sinal do sensor de vazao
int pulsoAnterior = 0; //Variavel para armazenar o sinal do sensor de vazao anterior
float vazao = 0; //Vazao apresentada a cada 1s (L/H)
float mediaVazao = 0; //Vazao apresentada a cada 1min (L/H)
volatile int contaPulsos; //Frequencia do sensor de vazao
int qtdSegundos = 0; //Contador de 1 minuto
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
    vazao = contaPulsos * 7.5; //7,5: razao entre vazao e frequencia
    mediaVazao = mediaVazao + vazao;
    qtdSegundos++;
    inicioIntervalo = millis();
    contaPulsos = 0;
      
    //Serial.print("Vazao atual: ");
    //Serial.print(vazao); //Vazão de 1s
    //Serial.println(" L/min.");
  }

  //Calcula a vazao a cada 1min e envia a vazao pela porta serial
  if(qtdSegundos == 60){
    mediaVazao = mediaVazao/60;
    //Serial.println("----------------------\n Media da vazao em 1 minuto: ");
    Serial.print(mediaVazao);
    //Serial.println("----------------------");
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
