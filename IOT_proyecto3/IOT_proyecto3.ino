/*------------------------------------------------------------------------------  
Archivo: IOT_proyecto3
Microcontrolador: ESP32
Autor: Julio Avila, Andy Bonilla y Pablo Herrarte
Compilador: Arduino IDE
Programa: Proyecto 3
Hardware: ESP32
    
Creado: 4 de noviembre de 2021    
Descripcion: parqueo para 8 carros, 4 en una tiva y 4 en otros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 ----------------------------L I B R E R I A S---------------------------------
 -----------------------------------------------------------------------------*/
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <WiFiClient.h>

/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void display (int numero);      //funcion para 7 segmentos
void serial0 (void);            //funcion para recepcion uart0
void serial2 (void);            //funcion para recepcion uart2
 /*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
// SSID & Password
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "12345678";  //Enter Password here
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
int cant = 0x30;
int cant2 = 0x30;
uint8_t LED1pin = 2;
bool LED1status = LOW;
unsigned char recibido_uart1, recibido_uart2;
unsigned char parqueo1, parqueo2, parqueos;
/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  
/*void Serial_ISR0(){
  parqueo1 = Serial.read();
  //Serial.write("INT");
  server.send(200, "text/html", SendHTML(cant));
  return;
}

void Serial_ISR2(){
  parqueo2 = Serial2.read();
  //Serial.write("INT");
  server.send(200, "text/html", SendHTML(cant));
  return;
}*/
/*-----------------------------------------------------------------------------
 --------------------- C O N F I G U R A C I O N  ----------------------------
 -----------------------------------------------------------------------------*/  
void setup(){
  //-------ENTRADAS Y SALIDAS
  pinMode(12, OUTPUT);           //A, arriba
  pinMode(14, OUTPUT);           //B, arriba
  pinMode(27, OUTPUT);           //C, abajo
  pinMode(26, OUTPUT);           //D, abajo
  pinMode(25, OUTPUT);           //E, abajo
  pinMode(33, OUTPUT);           //F, arriba
  pinMode(32, OUTPUT);           //G, abajo
  pinMode(15, OUTPUT);           //transistor 1
  pinMode(2, OUTPUT);           //transistor 2
  //-------CONFIGURACION DE COMUNICACION SERIAL
  Serial.begin(9600);
  Serial2.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(3), Serial_ISR0, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(16), Serial_ISR2, CHANGE);  
  //-------CONFIGURACION DE CONEXION WIFI  
  pinMode(LED1pin, OUTPUT);
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  server.on("/", handle_OnConnect); // página de inicio
  server.onNotFound([]() {                  // si el cliente solicita una uri desconocida
    if (!HandleFileRead(server.uri()))      // enviar archivo desde SPIFF, si existe
      handleNotFound();             // sino responder con un error 404 (no existe)
  });
  //server.onNotFound(handle_NotFound); //si no se encuentra el uri, responder con error 404 (no existe)

  server.begin(); // iniciar servidor
  Serial.println("HTTP server started");
  delay(100);

}

/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); 
  if (Serial.available() && Serial2.available()){            //ver si el puerto esta recibiendo datos
    recibido_uart1 = Serial.read();   //sea lo que recibio se va a variable
    parqueo1=recibido_uart1-0x30;
    recibido_uart2 = Serial2.read();   //sea lo que recibio se va a variable
    parqueo2=recibido_uart2-0x30;
    parqueos=parqueo1+parqueo2;
    digitalWrite(2,0);
    display(parqueos); 
  }
  
  //serial0();    //puerto serial 0, tiva 1
  //serial2();    //puerto serial 2, tiva 2
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
//-------funcion para recepcion uart0
void serial0 (void){
  if (Serial.available()){            //ver si el puerto esta recibiendo datos
    recibido_uart1 = Serial.read();   //sea lo que recibio se va a variable
    switch(recibido_uart1){           //se evalua segun su valor
      case 48:                        //CASO 0, OX48
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(0);
        delay(10);
        break;
      case 49:                        //CASO 1
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(1);
        delay(5);
        break;
      case 50:                        //CASO 2
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(2);
        delay(5);
        break;
      case 51:                        //CASO 3
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(3);
        delay(5);
        break;
      case 52:                         //CASO 4
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(4);
        delay(5);
        break;
      case 53:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(5);
        delay(5);
        break;
      case 54:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(6);
        delay(5);
        break;
      case 55:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(7);
        delay(5);
        break;
      case 56:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(8);
        delay(5);
        break;
    }
    delay(30);
    digitalWrite(2,1);
    digitalWrite(15,0);
    display(recibido_uart2);
  }
}
//-------funcion para recepcion uart2
void serial2 (void){
  if (Serial2.available()){           //ver si el puerto esta recibiendo datos
    recibido_uart2 = Serial2.read();  //sea lo que recibio se va a variable
    switch(recibido_uart2){           //se evalua segun su valor
      case 48:                        //CASO 0
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(0);
        delay(10);
        break;
      case 49:                        //CASO 1 
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(1);
        delay(5);
        break;
      case 50:                        //CASO 2
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(2);
        delay(5);
        break;
      case 51:                        //CASO 3
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(3);
        delay(5);
        break;
      case 52:                        //CASO 4
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(4);
        delay(5);
        break;
    }
    delay(30);
    digitalWrite(2,0);
    digitalWrite(15,1);
    display(recibido_uart1);
  }
              
}

//-------funcion para uso de 7 segmentos
void display (int numero){
  switch(numero){
    case 10:
      digitalWrite(12,0);  //A
      digitalWrite(14,0);  //B
      digitalWrite(27,0);  //C
      digitalWrite(26,0);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,0);  //F
      digitalWrite(32,0);  //G
      break;
    case 0:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,1);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,0);  //G
      break;
    case 1:
      digitalWrite(12,0);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,0);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,0);  //F
      digitalWrite(32,0);  //G
      break;
    case 2:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,0);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,1);  //E
      digitalWrite(33,0);  //F
      digitalWrite(32,1);  //G
      break;
    case 3:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,0);  //F
      digitalWrite(32,1);  //G
      break;
    case 4:
      digitalWrite(12,0);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,0);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,1);  //G
      break;
    case 5:
      digitalWrite(12,1);  //A
      digitalWrite(14,0);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,1);  //G
      break;
    case 6:
      digitalWrite(12,1);  //A
      digitalWrite(14,0);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,1);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,1);  //G
      break;
    case 7:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,0);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,0);  //F
      digitalWrite(32,0);  //G
      break;
    case 8:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,1);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,1);  //G
      break;
    case 9:
      digitalWrite(12,1);  //A
      digitalWrite(14,1);  //B
      digitalWrite(27,1);  //C
      digitalWrite(26,1);  //D
      digitalWrite(25,0);  //E
      digitalWrite(33,1);  //F
      digitalWrite(32,1);  //G
      break;
  }
}
/*-----------------------------------------------------------------------------
 -------------------- P R O C E S A D O R   H T M L ---------------------------
 -----------------------------------------------------------------------------*/
//SABER PERO LA PEGUE XD
void handle_OnConnect() { 
  server.send(200, "text/html", SendHTML(cant)); //responde con un OK (200) y envía HTML
}
 
//-------PARA CUANDO SE CONECTE AL SERVIDOR
String SendHTML(uint8_t cant1) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<title>PARQUEO - CIT</title>";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}";
  ptr += "</style>";
  ptr += "</head>";
  ptr += "<body>";
  ptr += "<h1>PARQUEO - CIT &#128664</h1>";
  ptr += "<h2>Electrónica Digital 2 - Proyecto 3</h2>";
  ptr += "<h3>Julio Avila - Andy Bonilla - Pablo Herrarte</h3>";
  switch(recibido_uart1){
    case 48:
    ptr += "<h3>Cantidad de Parqueos disponibles: 0</h3>";
    break;
    case 49:
    ptr += "<h3>Cantidad de Parqueos disponibles: 1</h3>";
    break;
    case 50:
    ptr += "<h3>Cantidad de Parqueos disponibles: 2</h3>";
    break;
    case 51:
    ptr += "<h3>Cantidad de Parqueos disponibles: 3</h3>";
    break;
    case 52:
    ptr += "<h3>Cantidad de Parqueos disponibles: 4</h3>";
    break;
    case 53:
    ptr += "<h3>Cantidad de Parqueos disponibles: 5</h3>";
    break;
    case 54:
    ptr += "<h3>Cantidad de Parqueos disponibles: 6</h3>";
    break;
    case 55:
    ptr += "<h3>Cantidad de Parqueos disponibles: 7</h3>";
    break;
    case 56:
    ptr += "<h3>Cantidad de Parqueos disponibles: 8</h3>";
    break;
    default:
    ptr += "<h3>Cantidad de Parqueos disponibles: 8</h3>";
  }
  
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//-------CUANDO NO LO ENCUENTRE, ERROR 404
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
//-------LECTOR DE ARCHIVOS SPIFFS
String GetContentType(String filename)
{
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

//------- Enviar al servidor el archivo desde SPIFFS
void ServeFile(String path)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, GetContentType(path));
  file.close();
}

//-------Enviar al servidor el archivo desde SPIFFS
void ServeFile(String path, String contentType)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, contentType);
  file.close();
}

//-------Handler de not found
bool HandleFileRead(String path)
{
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);

  if (SPIFFS.exists(path))
  {
    ServeFile(path);
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
