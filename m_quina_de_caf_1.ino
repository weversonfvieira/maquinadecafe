
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins


#define start  10
#define bomba  7
#define dosa  8
#define mistura  9

int flag1 = 1;
int flag2 = 0;

const int pinopot = 6;   //Pino ligado ao pino central do potenciometro
int valorpot = 0;  //Armazena valor lido do potenciometro, entre 0 e 1023
const int potenciometro = A0; // pino de entrada do potenciômetro
int valor = 0;
int temperatura;
short segundos1;
void logica();

// --- Protótipo das Funções ---
void showDisp(void);        //Função para exibir corretamente os valores, incluindo o zero à esquerda
void timer();                                        //Função para decrementar variáveis
void temp();


// =============================================================================================================
// --- Variáveis Globais ---
short sec_ = 50, min_ = 59, horas_ = 23;


// =============================================================================================================
// --- Hardware do LCD ---
LiquidCrystal disp(12,  //RS no digital 8
                   11,  //EN no digital 7
                   5,  //D4 no digital 5
                   4,  //D5 no digital 4
                   3,  //D6 no digital 3
                   2); //D7 no digital 2


void setup()
{
  
 Serial.begin(9600);         
  pinMode(pinopot, INPUT);  
  pinMode(start,INPUT);
  pinMode(bomba,OUTPUT);
  pinMode(dosa,OUTPUT);
  pinMode(mistura,OUTPUT);
  
  disp.begin(16, 2);


} //end setup


// --- Loop Infinito ---
void loop()
{
  
  disp.setCursor(0, 0);
  temp();
  timer();
  delay(1000);
  
  digitalRead(start);
  
  if(digitalRead(start)==HIGH){ 
digitalWrite(bomba, LOW);
digitalWrite(dosa, LOW);
digitalWrite(mistura, LOW); 
 
  logica();
  delay(1000);
 }
  
  
}



// =============================================================================================================
// --- Desenvolvimento das Funções ---


// =============================================================================================================
void timer()                                         //Função para decrementar variáveis
{                              
   
   sec_++;                                           //decrementa segundos
   
  
   if(sec_ > 59)                                   //chegou em zero?
   {                                                 //Sim...
       sec_ = 0x00;
       min_++;
     
      if(min_ > 59)                               //chegou em zero?
      {                                              //Sim...
        min_ = 0x00;
        horas_++;                    //minutos e segundos recebem zero
       
      }

   } //end if sec_1
  if(horas_ > 23){
    horas_ = 0x00;
    sec_ = 0x00;
    min_ = 0x00;
  }
       

  showDisp();
  
} //end timer


// =============================================================================================================
void showDisp(void)         //Função para exibir corretamente os valores, incluindo o zero à esquerda
{
  if(horas_ < 10)                                   //minutos menor que 10?
   {                                                 //Sim...
      disp.setCursor(8,1); disp.print('0');         //Posiciona cursor na coluna 12, linha 2 e imprime o '0' à esquerda                        
      disp.setCursor(9,1); disp.print(horas_);     //Posiciona cursor na coluna 13, linha 2 e imprime o valor dos minutos
                                   
   } //end if minutos
   else                                              //senão...
   {                                                 //minutos igual ou maior que 10
      disp.setCursor(8,1); disp.print(horas_);     //Posiciona cursor na coluna 12, linha 2 e imprime o valor dos minutos                         
   } //end else minutos
   
      disp.setCursor(10,1); disp.print(':');         //Posiciona cursor na coluna 14, linha 2 e imprime caractere dois-pontos ':'
                                   
   if(sec_ < 10)                                 //segundos menor que 10?
   {                                                 //Sim...
      disp.setCursor(14,1); disp.print('0');         //Posiciona cursor na coluna 15, linha 2 e imprime o '0' à esquerda                         
      disp.setCursor(15,1); disp.print(sec_);    //Posiciona cursor na coluna 14, linha 2 e imprime o valor dos segundos
                                   
   } //end if segundos
   else                                              //senão...
   {                                                 //segundos igual ou maior que 10
      disp.setCursor(14,1); disp.print(sec_);    //Posiciona cursor na coluna 15, linha 2 e imprime o valor dos segundos                      
   } //end else segundos
  
  if(min_ < 10)                                   //minutos menor que 10?
   {                                                 //Sim...
      disp.setCursor(11,1); disp.print('0');         //Posiciona cursor na coluna 12, linha 2 e imprime o '0' à esquerda                        
      disp.setCursor(12,1); disp.print(min_);     //Posiciona cursor na coluna 13, linha 2 e imprime o valor dos minutos
                                   
   } //end if minutos
   else                                              //senão...
   {                                                 //minutos igual ou maior que 10
      disp.setCursor(11,1); disp.print(min_);     //Posiciona cursor na coluna 12, linha 2 e imprime o valor dos minutos                         
   } //end else minutos
   disp.setCursor(13,1); disp.print(':'); 
  
  

} //end showDisp




void logica(){

  segundos1++;
 digitalRead(start); 
  
  if(segundos1 == 1){
    digitalWrite(bomba, HIGH);
    disp.setCursor(0,0);
    disp.print("Liga bomba    "); //Para que as mensagens não fiquem uma em cima da outra.
    
  }
  if(segundos1 == 2){
    disp.setCursor(0,0);
    digitalWrite(bomba, LOW);
    disp.print("Desligada     ");
    
    }
  
   if(segundos1 == 3){
    
    disp.setCursor(0,0);
    digitalWrite(dosa, HIGH);
    disp.print("Dosando             ");
  }
  if(segundos1 == 4){
 
    disp.setCursor(0,0);
    digitalWrite(dosa, LOW);
   
    
    }
  
   if(segundos1 == 5){
   
    disp.setCursor(0,0);
    digitalWrite(mistura, HIGH);
     //disp.clear();
    disp.print("Misturando      ");
  }
  if(segundos1 == 6){
    delay(500);
    disp.setCursor(0,0);
    digitalWrite(mistura, LOW);
    disp.print("Retire seu cafe           ");
    temp();
    timer();

    }
  
  if(segundos1 >= 6 ){
    logica();
    
  }
  
 
  
  
 //showDisp(min_, sec_, horas_);
  

} 







void temp(){

   valor = analogRead(potenciometro);
  
   temperatura = map(valor, 0, 1023, 100, 1); //Mapeia os valors do 
  //potenciômetro de 0 a 100 graus (está 100,0
  //, pois giro da esquerda para a direita.
  
  
   if(temperatura == 1){
   disp.setCursor(0,1);
   disp.print(temperatura);
   disp.print(" C ");

   }else {
   disp.setCursor(0,1);
   disp.print(temperatura);
   disp.print(" C ");

   delay(100);
   } 
}

