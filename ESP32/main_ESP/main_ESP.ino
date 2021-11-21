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

/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void display (int numero);
void configurarTimer(void);

 /*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
#define prescaler 80
hw_timer_t *timer = NULL;
unsigned char recibido_uart1,recibido_uart2,contadorTimer;
char m1;
char readData[2];
/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  
void IRAM_ATTR ISRTimer0() //interrupción para timer de displays
{
  contadorTimer++; //aumenta el contador de timer

  if (contadorTimer > 2) //si es mayor a 2 regresa a cero
  {
    contadorTimer = 0;
  }
}
/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
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
  //pinMode(4, OUTPUT);           //transistor 3+
  digitalWrite(12,0);  //A
  digitalWrite(14,0);  //B
  digitalWrite(27,0);  //C
  digitalWrite(26,0);  //D
  digitalWrite(25,0);  //E
  digitalWrite(33,0);  //F
  digitalWrite(32,0);  //G
  Serial.begin(9600);
  Serial2.begin(9600);
  configurarTimer();
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  if (Serial.available()){
    recibido_uart1 = Serial.read();
    switch(recibido_uart1){
      case 48:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(0);
        delay(10);
          break;
      case 49:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(1);
        delay(5);
        break;
      case 50:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(2);
        delay(5);
        break;
      case 51:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(3);
        delay(5);
        break;
      case 52:
        digitalWrite(2,0);
        digitalWrite(15,1);
        display(4);
        delay(5);
        break;
    }
    delay(30);
    digitalWrite(2,1);
    digitalWrite(15,0);
    display(9-recibido_uart1);
  }
  if (Serial2.available()){
    recibido_uart2 = Serial2.read();
    switch(recibido_uart2){
      case 48:
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(0);
        delay(10);
        break;
      case 49:
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(1);
        delay(5);
        break;
      case 50:
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(2);
        delay(5);
        break;
      case 51:
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(3);
        delay(5);
        break;
      case 52:
        digitalWrite(2,1);
        digitalWrite(15,0);
        display(4);
        delay(5);
        break;
    }
    delay(30);
    digitalWrite(2,0);
    digitalWrite(15,1);
    display(8-recibido_uart2);
  }

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
//---
void configurarTimer(void) //Timer para displays
{
  //Fosc = 80MHz = 80,000,000 Hz
  //Fosc / Prescaler = 80,000,000 / 80 = 1,000,000
  //Tosc = 1/Fosc = 1uS

  //Timer 0, prescaler = 80, flanco de subida
  timer = timerBegin(0, prescaler, true);

  //Handler de la interrupción
  timerAttachInterrupt(timer, &ISRTimer0, true);

  //Tic = 1uS     1ms = 1000uS
  timerAlarmWrite(timer, 1000, true);

  //Inicia alarma
  timerAlarmEnable(timer);
}
