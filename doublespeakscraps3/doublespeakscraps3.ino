#include <GinSing.h>
#include <Potentiometer.h>
GinSing         GS;
GinSingVoice *  v; 
GinSingMaster * m;
#define rcvPin  4
#define sndPin  3
#define ovfPin  2

#define NumNotes 35
GSNote notes      [NumNotes] = { 
  C_1 , D_1 , E_1 , F_1 , G_1 , A_1 , B_1 , 
  C_2 , D_2 , E_2 , F_2 , G_2 , A_2 , B_2 , 
  C_3 , D_3 , E_3 , F_3 , G_3 , A_3 , B_3 ,
  C_4 , D_4 , E_4 , F_4 , G_4 , A_4 , B_4 ,
  C_5 , D_5 , E_5 , F_5 , G_5 , A_5 , B_5 ,
}; 



int masterpitch = 0;
int breath = 7;


GSAllophone singy[] = {
  _OE, _ENDPHRASE};


int led = 12;  
int ReadyMessage = 0;

Potentiometer potentiometer0 = Potentiometer(A0); 
Potentiometer potentiometer1 = Potentiometer(A1);
Potentiometer potentiometer2 = Potentiometer(A2); 
Potentiometer potentiometer3 = Potentiometer(A3); 
Potentiometer potentiometer4 = Potentiometer(A4); 
Potentiometer potentiometer5 = Potentiometer(A5); 


void setup () {
  GS.begin( rcvPin , sndPin , ovfPin );
  v  = GS.getVoice ();
  m  = GS.getMaster();
  pinMode(led, OUTPUT);
}

void loop () {
  Serial.begin(9800);
  if(!ReadyMessage){
    Serial.println("Calling Ready Message");
    doubleSpeakReady();
    ReadyMessage = 1;
  }
  getMyControls(1);
  doSing(0);

}


void doubleSpeakReady() {
  analogWrite(led, 200);
  Serial.println("I am DoubleSpeak.");
  Serial.println("I am ready.");
  v->begin();
  v->setNote ( D_2 );
  GSAllophone msg[] = { 
    _IE , _A , _M , _PITCHDN,
    _DO , _U , _OB , _OO , _LE, _PITCHDN,
    _SE , _PE , _EE , _EK,
    _IE , _A , _M ,
    _R , _E , _DE , _EE, _ENDPHRASE   };
  v->speak (msg);
  GSAllophone shh[] = { 
    _PA1 , _ENDPHRASE   };
  v->speak   ( shh );

}


void doSing(int debug){

  analogWrite(led, 150);
  Serial.println("Singing");
  v->setNote ( notes[masterpitch] );
  v->speak   (singy);
  delay ( v->getMillis ( singy ) );
  delay(100);
  analogWrite(led, 0);

}


void getMyControls (int debug){


  int p0val = potentiometer0.getValue();
  int p4val =  potentiometer4.getValue();
  int p3val =  potentiometer3.getValue();


  // Pitch Control
  // Custom look up for more space on preferable octaves.

  int DSnote = p4val/98;

  if(p0val>898){
    masterpitch = 0+DSnote;
  }
  else if (p0val<897 && p0val>648){
    masterpitch = 7-DSnote;
  }
  else if (p0val<647 && p0val>398){
    masterpitch = 14-DSnote;
  }
  else if (p0val<397 && p0val>148){
    masterpitch = 21-DSnote;
  }
  else if (p0val<147){
    masterpitch = 28-DSnote;  
  }

  //Phoneme Control
 
  GSAllophone pho[] = {_A,_AA,_AE,_E,_OO, _OU}; 
  
  GSAllophone noiseypho[] = {_CH , _E , _E , _KE , _I , _NGE, _DE , _EE , _A , _KE , _T , _I , _V , _AE , _T , 
     _I , _ED, _F , _AA , _THH , _ER, _GE , _R , _AE , _PO , _F , _R , _UE , _T, _HE , _E , _KE , _SE , _U , _GO ,
     _AA , _NO, _SE , _T , _R , _AU , _BE , _AIR , _EE, _T , _E , _LE , _E , _V , _I , _ZH , _U , _NO, _TH , _OU , 
     _Z , _U , _NE, _U , _NE , _Y, _UE , _ZH , _Y , _U , _W , _OO , _LO, _Z , _AE , _T , _U}; 
  int noiseyS = sizeof(noiseypho);
  int phoS = sizeof(pho);

  int phodiv = 530/phoS;
  int phoInd = p3val/phodiv;
  
  GSAllophone  preSing[] = {};
  
  for (int i = 0; i <breath; i++){
    preSing[i] = pho[phoInd];
    if((i = (breath-1))&&(breath<10)){
      int termi = i+1;
      preSing[termi] = _ENDPHRASE;
    }
  }
  
 if(breath>10){
    int Nrand = random(10);
    Nrand+=breath;
      if(Nrand>15){
        int NrandRun =random(Nrand);
          for(int j; j<NrandRun; j++){
            int NoiseyRand = random(noiseyS);
            int tINT = sizeof(preSing);
            preSing[tINT] = noiseypho[NoiseyRand];
              if(j = (breath-1)){
                  int termj = j+1;
                  preSing[termj] = _ENDPHRASE;
               }
          }
      }       
 }  
  
  
 GSAllophone singy[] ={_ENDPHRASE};
  for (int k=0; k<sizeof(preSing); k++){
      singy[k] = preSing[k];   
     }

  if(debug){
    Serial.println("Potentiometer 0");
    Serial.print("potentiometer0.getValue() ");
    Serial.println(potentiometer0.getValue(),DEC);
    Serial.println("Potentiometer 1");
    Serial.print("potentiometer1.getValue() ");
    Serial.println(potentiometer1.getValue(),DEC);
    Serial.println("Potentiometer 2");
    Serial.print("potentiometer2.getValue() ");
    Serial.println(potentiometer2.getValue(),DEC);
    Serial.println("Potentiometer 3");
    Serial.print("potentiometer3.getValue() ");
    Serial.println(potentiometer3.getValue(),DEC);
    Serial.println("Potentiometer 4");
    Serial.print("potentiometer4.getValue() ");
    Serial.println(potentiometer4.getValue(),DEC);
    Serial.println("Potentiometer 5");
    Serial.print("potentiometer5.getValue() ");
    Serial.println(potentiometer5.getValue(),DEC); 
  } 
}



