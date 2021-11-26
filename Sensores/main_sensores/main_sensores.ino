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
  //entradas
  pinMode(PD_0, INPUT_PULLUP);                                        //parqueo 1
  pinMode(PD_1, INPUT_PULLUP);                                        //parqueo 2
  pinMode(PD_2, INPUT_PULLUP);                                        //parqueo 3
  pinMode(PD_3, INPUT_PULLUP);                                        //parqueo 4
  //salidas
  pinMode(PB_0, OUTPUT);                                              //led verde p1           
  pinMode(PB_1, OUTPUT);                                              //led roja p1
  pinMode(PE_4, OUTPUT);                                              //led verde p2
  pinMode(PE_5, OUTPUT);                                              //led roja p2
  pinMode(PB_4, OUTPUT);                                              //led verde p3
  pinMode(PA_5, OUTPUT);                                              //led roja p3
  pinMode(PA_6, OUTPUT);                                              //led verde p4
  pinMode(PA_7, OUTPUT);                                              //led roja p4                 
  //-------CONFIGURACION INTERRUPCIONES
  attachInterrupt(digitalPinToInterrupt(PD_0), ISR_p1, FALLING);      //parqueo 1
  attachInterrupt(digitalPinToInterrupt(PD_1), ISR_p2, FALLING);      //parqueo 2
  attachInterrupt(digitalPinToInterrupt(PD_2), ISR_p3, FALLING);      //parqueo 3
  attachInterrupt(digitalPinToInterrupt(PD_3), ISR_p4, FALLING);      //parqueo 4
  //-------CONFIGURACION DE COMUNICACION UART
  Serial.begin(115200);
  Serial3.begin(115200);
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  //-------ANTIRREBOTE DE SENSORES
  antirrebotes_parqueo();
  digitalWrite(PB_0, HIGH);
  //-------ENVIO DE DATOS UART
  if (Serial3.available()){
    Serial3.write(cuenta_parqueos+0x30);
    //Serial3.write(10);                    //separador de coma de caracteres
  }
  cuenta_parqueos=cuenta_p1+cuenta_p2+cuenta_p3+cuenta_p4;
  Serial.println(cuenta_parqueos+0x30);
} 
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
 void antirrebotes_parqueo(void){
  //-------antirrebote para parqueo 1
  if (digitalRead(PD_0)==0 && antirrebote1==1){   //p1 libre
    cuenta_p1=0;
    digitalWrite(PB_0,HIGH);     //verde on
    digitalWrite(PB_0,LOW);     //rojo off
  }
  else{                                           //p1 ocupado
    cuenta_p1=1;
    digitalWrite(PB_0,HIGH);     //verde off
    digitalWrite(PB_0,LOW);     //rojo on
  }
  //-------antirrebote para parqueo 2
  if (digitalRead(PD_1)==0 && antirrebote2==1){   //p2 libre
    cuenta_p2=0;
    digitalWrite(PE_4,HIGH);     //verde on
    digitalWrite(PE_5,LOW);     //rojo off
  }
  else{                                           //p2 ocupado
    cuenta_p2=1;
    digitalWrite(PE_4,HIGH);     //verde off
    digitalWrite(PE_5,LOW);     //rojo on
  }
  //-------antirrebote para parqueo 3
  if (digitalRead(PD_2)==0 && antirrebote3==1){   //p3 libre
    cuenta_p3=0;
    digitalWrite(PB_4,HIGH);     //verde on
    digitalWrite(PA_5,LOW);     //rojo off
  }
  else{                                           //p3 ocupado
    cuenta_p3=1;
    digitalWrite(PB_4,HIGH);     //verde on
    digitalWrite(PA_5,LOW);     //rojo off
  }
  //-------antirrebote para parqueo 4
  if (digitalRead(PD_3)==0 && antirrebote4==1){     //p4 libre
    cuenta_p4=0;
    digitalWrite(PA_6,HIGH);     //verde on
    digitalWrite(PA_7,LOW);     //rojo off
  }
  else{                                             //p4 ocupado
    cuenta_p4=1;
    digitalWrite(PA_6,LOW);     //verde off
    digitalWrite(PA_7,HIGH);     //rojo on
  }
 }
