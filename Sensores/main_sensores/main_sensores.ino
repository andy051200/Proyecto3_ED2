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
unsigned char cuenta_p1, cuenta_p2, cuenta_p3, cuenta_p4;
/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void antirrebotes_parqueo(void);
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
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  // put your main code here, to run repeatedly: 
  
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
 void antirrebotes_parqueo(void){
  //-------antirrebote para parqueo 1
  if (digitalRead(PD_0)==0 && antirrebote1==1){
    antirrebote1=0;
    Serial.println("Boton para ");
  }
  //-------antirrebote para parqueo 2
  if (digitalRead(PD_1)==0 && antirrebote2==1){
    antirrebote2=0;
    Serial.println("Boton para ");
  }
  //-------antirrebote para parqueo 3
  if (digitalRead(PD_2)==0 && antirrebote3==1){
    antirrebote3=0;
    Serial.println("Boton para ");
  }
  //-------antirrebote para parqueo 4
  if (digitalRead(PD_3)==0 && antirrebote4==1){
    antirrebote4=0;
    Serial.println("Boton para ");
  }
 }
