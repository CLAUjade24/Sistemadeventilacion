#include <SPI.h>
#include <Ethernet.h>
#include "DHT11.h"
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

const int control = 9;

#define pinhumedadTemp  6 //Sensor de humedad y humedad.
#define pinluminosidad A4 //Sensor luminosidad.    
DHT11 dht11(pinhumedadTemp);

const int ventilador = 5;
int luminosidad = 0;  

/* Variables para calcular la humedad*/
float temp = 0;     //te
float humedad = 0;

/* Variables para calcular la luminosidad */
const long A = 1000;    
const int B = 15;        
const int Rc = 10;       

int v;   
int ilum;
// Calculo para temperatura  
float voltaje = 0;
float  temperatura = 0;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //Mac address fija
//IPAddress ip(192, 168, 1, 17);
IPAddress ip(192, 168, 1, 92);                     //Asignación dirección ip 

EthernetServer server(80);                        //Asignación de Puerto

String readString; 

void setup() {

  Serial.begin(9600);
  myservo.attach(7);                             //pin para servo control
  pinMode(control, OUTPUT);
  pinMode(ventilador, OUTPUT);
  pinMode(pinluminosidad, INPUT);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 // Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    String valor = "";            //cadena 
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
 
        if (valor.length()<50){
          valor.concat(c);
           // Buscar campo data
          int posicion = valor.indexOf("d");   //data
          String command = valor.substring(posicion);
          
          if(command == "d1=3"){    
          dht11.read(humedad, temp);
           if(temp>23){                         //en caso de que la temperatura sea mayor a 23 el ventilador se enciende
            digitalWrite(control, HIGH);
           } else{ 
            digitalWrite(control, LOW);         //en caso de que sea menor a 23 se apaga

             delay(10000);                      

           }
          }else if(command == "d1=0"){
            myservo.write(0);
            digitalWrite(5, HIGH);    
          }else if(command == "d1=1"){
           myservo.write(90);
           digitalWrite(5, LOW);     
         }else if(command == "d1=2"){
           myservo.write(180);
           digitalWrite(5, LOW);     

          }
        }
  
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 3");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          //Se realiza la lectura de humedad por medio de DHT11, el sensor es capaz de medir la temperatura y luminosidad 
          dht11.read(humedad, temp);
         
          // Calculo para la luminosidad 
          v = analogRead(pinluminosidad);
          ilum = ((long)v * A * 10) / ((long)B * Rc * (1024 - v));
         //Creacion de vista en codigo html para la pagina que se visualiza segun la direccion ip asignada
          client.println(F("<html>\n<head>\n<title>Sistemas Programables</title>\n</head>\n<body style='background-color:#16a085;'>"));
          client.println(F("<center>"));
          client.println(F("<p style='color:#f8f9f9; font-size:20px;font-weight: bold; font-family:Sans-Serif, Helvetica, Arial;'> Sistema de ventilacion </p>"));
          client.println(F("<p style='color:#17202a; font-size:20px;font-weight: bold; font-family:Sans-Serif, Helvetica, Arial;'> Medida Sensores </p>"));
          client.println(F("<div style='color:#f8f9f9; font-size:13px;font-weight: bold; font-family:Sans-Serif, Helvetica, Arial;'>"));
          client.println("Temperatura: ");
          client.println(temp);
          client.println(F("<br />"));
          client.println("Humedad: ");
          client.println(humedad);
          client.println(F("<br />"));
          client.println("Luminosidad: ");
          client.println(ilum);
          client.println(F("<br />"));
          client.println(F("<br/>"));
          client.println(F("<br/>"));
          client.println(F("<button onClick=location.href='./?d1=0' style='width:90px; height:50px'>0°</button>"));
          client.println(F("<button onClick=location.href='./?d1=1' style='width:90px; height:50px'>90°</button>"));
          client.println(F("<button onClick=location.href='./?d1=2' style='width:90px; height:50px'>180°</button>"));
          client.println(F("<button onClick=location.href='./?d1=3' style='width:90px; height:50px'>Activar</button>"));  //d1=2
          client.println(F("<br/>"));
          client.println(F("</div>"));
          client.println(F("</center>\n</body></html>"));
          
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(50);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  
}
