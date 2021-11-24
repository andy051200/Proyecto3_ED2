/*------------------------------------------------------------------------------  
Archivo: main_sensores
Microcontrolador: TM4C123
Autor: Julio Avila, Andy Bonilla y Pablo Herrarte
Compilador: Energia 1.8.11E23
Programa: Proyecto 3
Hardware: Launchpad Tiva C
    
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

/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  
void Serial_ISR(){
  cant = Serial.read();
  //Serial.write("INT");
  server.send(200, "text/html", SendHTML(cant));
  return;
}

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
  attachInterrupt(digitalPinToInterrupt(3), Serial_ISR, CHANGE);
    
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
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
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
  ptr += "<h3>Julio Avila - Andy Bonilla</h3>";
  switch(cant1){
    case 0x30:
    ptr += "<h3>Cantidad de Parqueos disponibles: 0</h3>";
    break;
    case 0x31:
    ptr += "<h3>Cantidad de Parqueos disponibles: 1</h3>";
    break;
    case 0x32:
    ptr += "<h3>Cantidad de Parqueos disponibles: 2</h3>";
    break;
    case 0x33:
    ptr += "<h3>Cantidad de Parqueos disponibles: 3</h3>";
    break;
    case 0x34:
    ptr += "<h3>Cantidad de Parqueos disponibles: 4</h3>";
    break;
    case 0x35:
    ptr += "<h3>Cantidad de Parqueos disponibles: 5</h3>";
    break;
    case 0x36:
    ptr += "<h3>Cantidad de Parqueos disponibles: 6</h3>";
    break;
    case 0x37:
    ptr += "<h3>Cantidad de Parqueos disponibles: 7</h3>";
    break;
    case 0x38:
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
