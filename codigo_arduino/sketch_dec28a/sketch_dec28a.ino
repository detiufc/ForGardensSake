/*Programa: codigo dos sensores (temperatura, umidade e chuva)
 * Autora: Sayonara Santos
 * biblioteca: https://github.com/adafruit/DHT-sensor-library
*/

#include <DHT.h>

#define pinoUmidade A0
#define pinoChuva A1
#define pinoTemperatura A3
#define dhttipo DHT11

int valorUmidade = 0; //Variavel para armazena o valor do sensor de umidade
int valorChuva = 0; //Variavel para armazena o valor do sensor de chuva
DHT dht(pinoTemperatura, dhttipo);
float valorTemperatura = 0; //Variavel para armazena o valor do sensor de temperatura
String t1 = ";umidade=";
String t2 = ";chuva=";
String t3 = ";temperatura=";
String mensagem;
  
void setup()
{
  // Define os pinos dos sensores como entrada
  pinMode(pinoUmidade, INPUT);
  pinMode(pinoChuva,INPUT);
 
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
 
  valorChuva = analogRead(pinoChuva);
  
  valorUmidade = analogRead(pinoUmidade);
 
  valorTemperatura = dht.readTemperature();  

  mensagem = t1 + valorUmidade + t2 + valorChuva + t3 + valorTemperatura;
 
  Serial.println(mensagem);
  
  delay(10000); 
  
}


void mostraChuva(int chuva){
  Serial.print("Valor - chuva: ");
  Serial.println(chuva);
  
  //max=1024 (seco)  min=0
  if(chuva<400){
  Serial.println("Chuva forte!");
  }
  else if(chuva<600 && chuva>400){
  Serial.println("Chuva moderada!");
  }
  else if(chuva<900 && chuva>600){
  Serial.println("Chuva fraca!");
  }
  else if(chuva>900){
  Serial.println("Sem chuva!");
  }
}


void mostraUmidadeSolo(int umidade){
  Serial.print("Valor - umidade do solo: ");
  Serial.println(umidade);
  
  //max=1024 (seco)  min=0
  if(umidade<400){
  Serial.println("Umidade do solo alta!");
  }
  else if(umidade<800 && umidade>400){
  Serial.println("Umidade do solo moderada!");
  }
  else if(umidade>800){
  Serial.println("Umidade do solo baixa!");
  }
 }


 void mostraTemperatura(float temperatura){
  Serial.print("Valor - temperatura ambiente: ");
  Serial.print(temperatura);
  Serial.println(" Celsius");
}
