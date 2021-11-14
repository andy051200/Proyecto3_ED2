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
 /*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  

/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  
void setup() {
  //-------ENTRADAS Y SALIDAS
  pinMode(12, OUTPUT);           //A
  pinMode(14, OUTPUT);           //B
  pinMode(27, OUTPUT);           //C
  pinMode(26, OUTPUT);           //D
  pinMode(25, OUTPUT);           //E
  pinMode(33, OUTPUT);           //F
  pinMode(32, OUTPUT);           //G
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  // put your main code here, to run repeatedly:
  display(1);
  delay(1000);
  display(2);
  delay(1000);
  display(3);
  delay(1000);
  display(4);
  delay(1000);
  display(5);
  delay(1000);
  display(6);
  delay(1000);
  display(7);
  delay(1000);
  display(8);
  delay(1000);
  display(9);
  delay(1000);
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
 //-------funcion para uso de 7 segmentos
void display (int numero){
  switch(numero){
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
