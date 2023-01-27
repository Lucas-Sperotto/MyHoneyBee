/*****************************************************************************/
/* Arquivo: MyHoneyBee.ino | Versão 1.0 | Ano: 2022                          */
/*---------------------------------------------------------------------------*/
/* Autor: Prof. Me. Lucas Kriesel Sperotto                                   */
/*---------------------------------------------------------------------------*/
/* E-mail: sperotto@unemat.br                                                */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Descrição: Código que demonstra como ligar dois sensores BMP280 no        */
/* ESP32 usando protocolo SPI                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*    Compilador:                                                            */
/*    IDE: Arduino v 1.8.19                                                  */
/*                                                                           */
/*****************************************************************************/

/****************************/
/* Inclusão de bibliotecas  */
/****************************/
#include "HX711.h"
#include <LiquidCrystal.h>
#include "DHT.h"

/**********************************************/
/* Definição dos pinos de ligação do HX711-A  */
/**********************************************/
#define LOADCELL_A_DOUT_PIN (2);
#define LOADCELL_A_SCK_PIN  (3);

/**********************************************/
/* Definição dos pinos de ligação do HX711-B  */
/**********************************************/
#define LOADCELL_B_DOUT_PIN (4);
#define LOADCELL_B_SCK_PIN  (5);

/**************************************************/
/* Definição das constantes empiricas da balanca  */
/**************************************************/
const float TARA = 506168.333333333;
const float ESCALA = 668.62;

/************************************/
/* Instanciação do Cristal Liquido  */
/************************************/
LiquidCrystal lcd(12, 11, 9, 8, 7, 6); // Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]

/*********************************/
/* Instanciação do Sensor DHT22  */
/*********************************/
DHT dht(13, DHT22);

float p_medio(int);

/************************************/
/* Instanciação dos Sensores HX711  */
/************************************/
HX711 scale_A;
HX711 scale_B;

/***********************************************/
/* Inicializa e configura sensores e conexoes  */
/***********************************************/
void setup() {

  Serial.begin(57600);

  scale_A.begin(LOADCELL_A_DOUT_PIN, LOADCELL_A_SCK_PIN);
  scale_B.begin(LOADCELL_B_DOUT_PIN, LOADCELL_B_SCK_PIN);
  delay(1000);
  dht.begin();
  delay(1000);

  lcd.begin(16, 2); //Inicializamos o ecrã
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.clear();
  lcd.print("CAIXA DE ABELHA"); //Obtemos o texto pelo ecrã
  lcd.setCursor(0, 1); //Situamos o cursor
  lcd.print("My Honey Bee"); //Obtemos o texto pelo ecrã
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.print("INICIANDO....."); //Obtemos o texto pelo ecrã
  delay(1000);
}

/*****************************************************/
/* Leitura dos dados dos sensores e envio para o LCD */
/*****************************************************/
void loop() {

float p = p_medio(20);

  lcd.clear();
  //Serial.print("Peso: ");
  //Serial.println(p);
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.print("Peso: ");
  lcd.setCursor(0, 1); //Situamos o cursor
  lcd.print(p);
  lcd.print("g");
  delay(3000);


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.clear();
  // Serial.print(F("Humidade: "));
  //Serial.println(h);
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.print("Humidade: ");
  lcd.setCursor(0, 1); //Situamos o cursor
  lcd.print(h);
  lcd.print("%");
  delay(3000);

  lcd.clear();
  // Serial.print("Temperatura: ");
  // Serial.println(t);
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1); //Situamos o cursor
  lcd.print(t);
  lcd.write(B11011111); // Símbolo de grau
  lcd.print("C");

  delay(3000);

  lcd.clear();
  // Serial.print("Heat index: ");
  // Serial.println(hic);
  lcd.setCursor(0, 0); //Situamos o cursor
  lcd.print("Heat index: ");
  lcd.setCursor(0, 1); //Situamos o cursor
  lcd.print(hic);
  lcd.write(B11011111); // Símbolo de grau
  lcd.print("C");
  delay(1000);
}


float p_medio(int n) {
  float media = 0.0;
  if (scale_A.is_ready() && scale_B.is_ready()) {
    for (int i = 0; i < n; i++)
    {
      long reading_A = scale_A.read();
      long reading_B = scale_B.read();
      media =  media + ((((float)(reading_A + reading_B)) - TARA) / ESCALA);
      delay(100);
    }
    return (media / ((float)n));
  } else {
    Serial.println("HX711 not found.");
    return 0.0;
  }
}
