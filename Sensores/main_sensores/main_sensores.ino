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
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
unsigned char antirrebote1, antirrebote2, antirrebote3, antirrebote4;
unsigned char cuenta_p1, cuenta_p2, cuenta_p3, cuenta_p4, cuenta_parqueos,x;
/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void antirrebotes_parqueo(void);
void display (int numero);
/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/  
//-------interrupcion para cambio de parqueo 1
void ISR_p1(){
  antirrebote1=1;
}
//-------interrupcion para cambio de parqueo 2
void ISR_p2(){
  antirrebote2=1;
}
//-------interrupcion para cambio parqueo 3
void ISR_p3(){
  antirrebote3=1;
}
//-------interrupcion para cambio parqueo 4
void ISR_p4(){
  antirrebote4=1;
}
/*-----------------------------------------------------------------------------
 ------------------------------ S E T   U P -----------------------------------
 -----------------------------------------------------------------------------*/
void setup() {
  //-------ENTRADAS Y SALIDAS
  pinMode(PD_0, INPUT_PULLUP);                                        //parqueo 1
  pinMode(PD_1, INPUT_PULLUP);                                        //parqueo 2
  pinMode(PD_2, INPUT_PULLUP);                                        //parqueo 3
  pinMode(PD_3, INPUT_PULLUP);                                        //parqueo 4
  //-------CONFIGURACION INTERRUPCIONES
  attachInterrupt(digitalPinToInterrupt(PD_0), ISR_p1, FALLING);      //parqueo 1
  attachInterrupt(digitalPinToInterrupt(PD_1), ISR_p2, FALLING);      //parqueo 2
  attachInterrupt(digitalPinToInterrupt(PD_2), ISR_p3, FALLING);      //parqueo 3
  attachInterrupt(digitalPinToInterrupt(PD_3), ISR_p4, FALLING);      //parqueo 4
  //-------CONFIGURACION DE COMUNICACION UART
  Serial.begin(9600);
  Serial3.begin(9600);
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  //-------ANTIRREBOTE DE SENSORES
  antirrebotes_parqueo();
  //-------ENVIO DE DATOS UART
  if (Serial3.available()){
    Serial3.write(cuenta_parqueos+0x30);
    Serial3.write(10);
  }
  Serial.print("P1: ");
  Serial.print(cuenta_p1);
  Serial.print("  |");
  Serial.print("P2: ");
  Serial.print(cuenta_p2);
  Serial.print(" | ");
  Serial.print("P3: ");
  Serial.print(cuenta_p3);
  Serial.print(" | ");
  Serial.print("P4: ");
  Serial.print(cuenta_p4);
  Serial.print(" | ");
  Serial.print("Total parqueos: ");
  cuenta_parqueos=cuenta_p1+cuenta_p2+cuenta_p3+cuenta_p4;
  Serial.println(cuenta_parqueos);
  
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
 void antirrebotes_parqueo(void){
  //-------antirrebote para parqueo 1
  if (digitalRead(PD_0)==0 && antirrebote1==1){
    //antirrebote1=0;
    //Serial.println("parqueo 1 libre");
    cuenta_p1=0;
  }
  else{
    //Serial.println("parqueo 1 ocupado");
    cuenta_p1=1;
  }
  //-------antirrebote para parqueo 2
  if (digitalRead(PD_1)==0 && antirrebote2==1){
    //antirrebote2=0;
    //Serial.println("parqueo 2 libre");
    cuenta_p2=0;
  }
  else{
    //Serial.println("parqueo 2 ocupado");
    cuenta_p2=1;
  }
  //-------antirrebote para parqueo 3
  if (digitalRead(PD_2)==0 && antirrebote3==1){
    //antirrebote3=0;
    //Serial.println("parqueo 3 libre");
    cuenta_p3=0;
  }
  else{
    //Serial.println("parqueo 3 ocupado");
    cuenta_p3=1;
  }
  //-------antirrebote para parqueo 4
  if (digitalRead(PD_3)==0 && antirrebote4==1){
    cuenta_p4=0;
  }
  else{  
    cuenta_p4=1;
  }
 }

//funcion para meter en el 7seg desde la esp-32
//-------funcion para uso de 7 segmentos
/*void display (int numero){
  switch(numero){
    case 0:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,1);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,0);  //G
      break;
    case 1:
      digitalWrite(2,0);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,0);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,0);  //F
      digitalWrite(8,0);  //G
      break;
    case 2:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,0);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,1);  //E
      digitalWrite(7,0);  //F
      digitalWrite(8,1);  //G
      break;
    case 3:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,0);  //F
      digitalWrite(8,1);  //G
      break;
    case 4:
      digitalWrite(2,0);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,0);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,1);  //G
      break;
    case 5:
      digitalWrite(2,1);  //A
      digitalWrite(3,0);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,1);  //G
      break;
    case 6:
      digitalWrite(2,1);  //A
      digitalWrite(3,0);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,1);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,1);  //G
      break;
    case 7:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,0);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,0);  //F
      digitalWrite(8,0);  //G
      break;
    case 8:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,1);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,1);  //G
      break;
    case 9:
      digitalWrite(2,1);  //A
      digitalWrite(3,1);  //B
      digitalWrite(4,1);  //C
      digitalWrite(5,1);  //D
      digitalWrite(6,0);  //E
      digitalWrite(7,1);  //F
      digitalWrite(8,1);  //G
      break;
  }
}*/
