/*****************************************************************************/
/* Arquivo: MyHoneyBee.ino | Versão 1.0 | Ano: 2022                          */
/*---------------------------------------------------------------------------*/
/* Autor: Prof. Me. Lucas Kriesel Sperotto                                   */
/*---------------------------------------------------------------------------*/
/* E-mail: sperotto@unemat.br                                                */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Descrição: Código fonte embarcado para monitoramento de uma colmeia de    */
/* abelhas nativas usando um ESP32 e o servidor Adafruit IO                  */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*    Compilador:                                                            */
/*    IDE: Arduino v 1.8.19                                                  */
/*                                                                           */
/*****************************************************************************/

/****************************/
/* Inclusão de bibliotecas  */
/****************************/
#include "config.h"
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include "HX711.h"

#define READ_DELAY 58

/**********************************************/
/* Definição dos pinos de ligação dos BMP280  */
/**********************************************/
#define BMP_SCK  (18) //SCL
#define BMP_MISO (19) //SDO
#define BMP_MOSI (23) //SDA
#define BMP_CS_A  (4) //CSB - BMP280 A
#define BMP_CS_B  (5) //CSB - BMP280 B

/**********************************************/
/* Definição dos pinos de ligação do HX711-A  */
/**********************************************/
#define LOADCELL_A_DOUT_PIN 27
#define LOADCELL_A_SCK_PIN 14

/**********************************************/
/* Definição dos pinos de ligação do HX711-B  */
/**********************************************/
#define LOADCELL_B_DOUT_PIN 12
#define LOADCELL_B_SCK_PIN 13

/**********************************************/
/* Definição dos pinos de ligação do HX711-C  */
/**********************************************/
#define LOADCELL_C_DOUT_PIN 25
#define LOADCELL_C_SCK_PIN 26

/**********************************************/
/* Definição dos pinos de ligação do HX711-D  */
/**********************************************/
#define LOADCELL_D_DOUT_PIN 02
#define LOADCELL_D_SCK_PIN 15

/**********************************************/
/* Definição dos pinos de ligação do DHT22-A  */
/**********************************************/
#define DHT_A_DATA_PIN 32 

/**********************************************/
/* Definição dos pinos de ligação do DHT22-B  */
/**********************************************/
#define DHT_B_DATA_PIN 33  

/*************************************/
/* Instanciação dos Sensores BMP280  */
/*************************************/
Adafruit_BMP280 bmp_A(BMP_CS_A, BMP_MOSI, BMP_MISO,  BMP_SCK);// SPI
Adafruit_BMP280 bmp_B(BMP_CS_B, BMP_MOSI, BMP_MISO,  BMP_SCK);// SPI

/************************************/
/* Instanciação dos Sensores DHT22  */
/************************************/
DHT dht_A(DHT_A_DATA_PIN, DHT22);
DHT dht_B(DHT_B_DATA_PIN, DHT22);

/************************************/
/* Instanciação dos Sensores HX711  */
/************************************/
HX711 scale_A;
HX711 scale_B;
HX711 scale_C;
HX711 scale_D;

/**************************************************/
/* Definição das constantes empiricas da balanca  */
/**************************************************/
const long TARA = 2748873;//506168.333333333;
const float ESCALA = 650.092277614858; //668.62;

/************************************/
/* Definição das variáveis globais  */
/************************************/
int temperaturaLida_DHT_A; //temperatura interna (DHT22)
int temperaturaLida_DHT_B; //temperatura externa (DHT22)
int umidadeLida_DHT_A; //umidade interna (DHT22)
int umidadeLida_DHT_B; //umidade externa (DHT22)
int pressaoLida_BMP_A; //pressao interna (BPM280)
int pressaoLida_BMP_B; //pressao interna (BPM280)
int temperaturaLida_BMP_A; //temperatura interna (BPM280)
int temperaturaLida_BMP_B; //temperatura externa (BPM280)
int pesoLido; //peso totalizado das 4 celulas de carga (HX711)

float p_medio(int);

/*******************************************************************/
/* Definição dos ponteiros para gravação dos dados no feed online  */
/*******************************************************************/
AdafruitIO_Feed *temperature_dht_A_Feed = io.feed("myhoneybee.temperatura-dht-interna"); //temperatura interna (DHT22)
AdafruitIO_Feed *temperature_dht_B_Feed = io.feed("myhoneybee.temperatura-dht-externa"); //temperatura externa (DHT22)
AdafruitIO_Feed *humidity_A_Feed = io.feed("myhoneybee.umidade-interna"); //umidade interna (DHT22)
AdafruitIO_Feed *humidity_B_Feed = io.feed("myhoneybee.umidade-externa"); //umidade externa (DHT22)
AdafruitIO_Feed *pressao_A_Feed = io.feed("myhoneybee.pressao-interna"); //pressao interna (BPM280)
AdafruitIO_Feed *pressao_B_Feed = io.feed("myhoneybee.pressao-externa"); //pressao interna (BPM280)
AdafruitIO_Feed *temperature_bmp_A_Feed = io.feed("myhoneybee.temperatura-bmp-interna"); //temperatura interna (BPM280)
AdafruitIO_Feed *temperature_bmp_B_Feed = io.feed("myhoneybee.temperatura-bmp-externa"); //temperatura externa (BPM280)
AdafruitIO_Feed *pesoFeed = io.feed("myhoneybee.peso"); //peso totalizado das 4 celulas de carga (HX711)


/***********************************************/
/* Inicializa e configura sensores e conexoes  */
/***********************************************/
void setup() {

  Serial.begin(9600);
  while ( !Serial ) delay(100);   // aguarda conexão

  Serial.println("Teste do BMP280");

  bmp_A.begin();// inicia sensor A
  bmp_B.begin();// inicia sensor B

  scale_A.begin(LOADCELL_A_DOUT_PIN, LOADCELL_A_SCK_PIN);
  scale_B.begin(LOADCELL_B_DOUT_PIN, LOADCELL_B_SCK_PIN);
  scale_C.begin(LOADCELL_C_DOUT_PIN, LOADCELL_C_SCK_PIN);
  scale_D.begin(LOADCELL_D_DOUT_PIN, LOADCELL_D_SCK_PIN);

  dht_A.begin();
  dht_B.begin();

  /* Default settings from datasheet. */
  bmp_A.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  /* Default settings from datasheet. */
  bmp_B.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

/***********************************************************************************/
/* Leitura dos dados dos sensores e envio para a porta serial e para o feed online */
/***********************************************************************************/
void loop() {

  io.run();

  //leitura dos dados dos sensores
  temperaturaLida_DHT_A = dht_A.readTemperature(); //leitura da temperatura do dht interno
  temperaturaLida_DHT_B = dht_B.readTemperature(); //leitura da temperatura do dht externo
  umidadeLida_DHT_A = dht_A.readHumidity(); //leitura da umidade do dht interno
  umidadeLida_DHT_B = dht_B.readHumidity(); //leitura da umidade do dht externo
  pressaoLida_BMP_A = bmp_A.readPressure(); //leitura da pressao do bmp interno
  pressaoLida_BMP_B = bmp_B.readPressure(); //leitura da pressao do bmp externo
  temperaturaLida_BMP_A = bmp_A.readTemperature(); //leitura da temperatura do bmp interno
  temperaturaLida_BMP_B = bmp_B.readTemperature(); //leitura da temperatura do bmp externo
  pesoLido = p_medio(20); //chamada da funcao que efetua a leitura do peso

  //envio dos dados lidos para a porta serial
  Serial.print("Temperatura Interna DHT = "); Serial.print(temperaturaLida_DHT_A); Serial.println(" ºC");
  Serial.print("Temperatura Externa DHT = "); Serial.print(temperaturaLida_DHT_B); Serial.println(" ºC");
  Serial.print("Umidade Interna DHT = "); Serial.print(umidadeLida_DHT_A); Serial.println(" %");
  Serial.print("Umidade Externa DHT = "); Serial.print(umidadeLida_DHT_B); Serial.println(" %");
  Serial.print("Pressão A = "); Serial.print(pressaoLida_BMP_A); Serial.println(" Pa");
  Serial.print("Pressão B = "); Serial.print(pressaoLida_BMP_B); Serial.println(" Pa");
  Serial.print("Temperatura Interna BMP = "); Serial.print(temperaturaLida_BMP_A); Serial.println(" ºC");
  Serial.print("Temperatura Externa BMP = "); Serial.print(temperaturaLida_BMP_B); Serial.println(" ºC");
  Serial.print("Peso = "); Serial.print(pesoLido); Serial.println(" g");
  Serial.println(); Serial.println();

  //envio dos dados lidos para o feed online
  temperature_dht_A_Feed->save(temperaturaLida_DHT_A);// = io.feed("myhoneybee.temperatura-dht-externa"); //temperatura interna (DHT22)
  temperature_dht_B_Feed->save(temperaturaLida_DHT_B);// = io.feed("myhoneybee.temperatura-dht-interna"); //temperatura externa (DHT22)
  humidity_A_Feed->save(umidadeLida_DHT_A);// = io.feed("myhoneybee.umidade-interna"); //umidade interna (DHT22)
  humidity_B_Feed->save(umidadeLida_DHT_B);// = io.feed("myhoneybee.umidade-externa"); //umidade externa (DHT22)
  pressao_A_Feed->save(pressaoLida_BMP_A);// = io.feed("myhoneybee.pressao-externa"); //pressao interna (BPM280)
  pressao_B_Feed->save(pressaoLida_BMP_B);// = io.feed("myhoneybee.pressao-interna"); //pressao interna (BPM280)
  temperature_bmp_A_Feed ->save(temperaturaLida_BMP_A);//= io.feed("myhoneybee.temperatura-bmp-externa"); //temperatura interna (BPM280)
  temperature_bmp_B_Feed->save(temperaturaLida_BMP_B);// = io.feed("myhoneybee.temperatura-bmp-interna"); //temperatura externa (BPM280)
  pesoFeed->save(pesoLido);// = io.feed("myhoneybee.peso"); //peso totalizado das 4 celulas de carga (HX711)

  //tempo entre loop
  delay(READ_DELAY * 1000);
}


float p_medio(int n) {
  float media = 0.0;
  if (scale_A.is_ready() && scale_B.is_ready() && scale_C.is_ready() && scale_D.is_ready()) {
    //if (scale_A.is_ready()) {
    for (int i = 0; i < n; i++)
    {
      long reading_A = scale_A.read();
      long reading_B = scale_B.read();
      long reading_C = scale_C.read();
      long reading_D = scale_D.read();
      media =  media + (((float)((reading_A + reading_B + reading_C + reading_D) - TARA)) / ESCALA);
      delay(100);
    }
    return (media / ((float)n));
  } else {
    Serial.println("HX711 not found.");
    return 0.0;
  }
}
