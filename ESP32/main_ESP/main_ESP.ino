/*------------------------------------------------------------------------------  
Archivo: main_sensores
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
#include <WebServer.h>
/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void display (int numero);      //funcion para 7 segmentos

 /*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
const char* ssid = "Casa Bonilla";  // Enter your SSID here
const char* password = "losbonilla2021";  //Enter your Password here
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

unsigned char recibido_uart1,recibido_uart2,contadorTimer;
char m1;
char readData[2];
int cant = 0x30;
int cant2 = 0x30;
int p1,p2,parqueos;
uint8_t LED1pin = 2;
bool LED1status = LOW;


/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  

/*-----------------------------------------------------------------------------
 --------------------- C O N F I G U R A C I O N  ----------------------------
 -----------------------------------------------------------------------------*/  
void setup() {
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
  //-------PUERTOS SERIALES
  Serial.begin(115200);
  Serial2.begin(115200);
  WiFi.begin(ssid, password);   //se inicia la conexion wifi
  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  //-------se inicia el servidor web
  server.handleClient();
  //-------lectura de puertos seriales
  if (Serial.available()){
    cant = Serial.read();
    p1=cant-0x30;
  }
  if (Serial2.available()){
    cant2 = Serial2.read();
    p2=cant2-0x30;
  }
  parqueos=p1+p2;
  server.send(200, "text/html", SendHTML(parqueos));
  Serial.println(parqueos); 
  display(parqueos);  
  
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
//-------Handler de Inicio página
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(parqueos));
}

//-------
String SendHTML(int wenas) {
  String ptr = "<!DOCTYPE html> <html>\n";

  ptr += "  <head>\n";
  ptr += "    <meta chatset=\"utf_8\">\n";
  ptr += "    <title>PROYECTO 3</title>\n";
  ptr += "    <script>\n";
  ptr += "  <!--\n";
  ptr += "  function timedRefresh(timeoutPeriod) {\n";
  ptr += "  \tsetTimeout(\"location.reload(true);\",timeoutPeriod);\n";
  ptr += "  }\n";
  ptr += "\n";
  ptr += "  window.onload = timedRefresh(5000);\n";
  ptr += "\n";
  ptr += "  //   -->\n";
  ptr += "  </script>\n";
 
  ptr += "      <h1 align='center'>PARQUEO CIT</h1>\n";
  ptr += "      <h2 align='center'>Proyecto 3, Electronica Digital 2 </h2></th>\n";
  ptr += "      <h2 align='center'>Julio Avila, Andy Bonilla, Pablo Herrarte </h2></th>\n";
  switch(wenas){
    case 0:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 0</h2>";
      break;
    case 1:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 1</h2>";
      break;
    case 2:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 2</h2>";
      break;
    case 3:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 3</h2>";
      break;
    case 4:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 4</h2>";
      break;
    case 5:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 5</h2>";
      break;
    case 6:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 6</h2>";
      break;
    case 7:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 7</h2>";
      break;
    case 8:
      ptr += "<h2 align='center'>Cantidad de Parqueos disponibles: 8</h2>";
      break;
  }
  ptr += "<img src='https://cdn.pixabay.com/photo/2016/12/31/01/43/auto-1941988_960_720.png'>";
  ptr += "  </table>\n";
  ptr += "  </html>\n";
  ptr += "";
  return ptr;
}
//-------Handler de not found
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
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
