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
int breathmax = 20;
int breath = 1;
int potmax =1023;
int scale = 7;
int octaves = NumNotes/scale;

GSAllophone singy[] = {};


int led = 12;  
int ReadyMessage = 0;
//GingSing Octave Control
Potentiometer potentiometer0 = Potentiometer(A0);
//GingSing Breath Control
Potentiometer potentiometer1 = Potentiometer(A1);

Potentiometer potentiometer2 = Potentiometer(A2); 
Potentiometer potentiometer3 = Potentiometer(A3);
//GingSing Note Control
Potentiometer potentiometer4 = Potentiometer(A4); 
GSAllophone pho[] = {_A,_AA,_AE,_E,_OO, _OU, _A,_AA,_AE,_E,_OO, _OU, _A,_AA,_AE,_E,_OO, _OU, _A,_AA,_AE,
      _E,_OO, _OU, _A,_AA,_AE,_E,_OO, _OU, _A,_AA,_AE,_E,_OO, _OU, _A,_AA,_AE,_E,_OO, _OU, _CH , _E , _E , _KE ,
      _I , _NGE, _DE , _EE , _A , _KE , _T , _I , _V , _AE , _T , _I , _ED, _F , _AA , _THH , _ER, _GE , _R , _AE ,
      _PO , _F , _R , _UE , _T, _HE , _E , _KE , _SE , _U , _GO , _AA , _NO, _SE , _T , _R , _AU , _BE , _AIR , _EE,
      _T , _E , _LE , _E , _V , _I , _ZH , _U , _NO, _TH , _OU ,  _Z , _U , _NE, _U , _NE , _Y, _UE , _ZH , _Y , _U ,
      _W , _OO , _LO, _Z , _AE , _T , _U, _A,_AA,_AE,_E,_OO, _OU}; 


void setup () {
  GS.begin( rcvPin , sndPin , ovfPin );
  v  = GS.getVoice ();
  m  = GS.getMaster();
  pinMode(led, OUTPUT);
  randomSeed(analogRead(A5)); 
  
}

void loop () {
  Serial.begin(9800);
  if(!ReadyMessage){
    //doubleSpeakReady();
    ReadyMessage = 1;
  }
  getMyControls();
  doSing();
  delay (100);
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


void doSing(){
  analogWrite(led, 120);
  v->setNote ( notes[masterpitch] );
  v->speak   (singy);
  delay ( v->getMillis ( singy ) );
  analogWrite(led, 0);
}


void getMyControls(){


  int p0val = potentiometer0.getValue();
  int p1val = potentiometer1.getValue();
  int p2val = potentiometer2.getValue();
  int p4val =  potentiometer4.getValue();
  int p3val =  potentiometer3.getValue();
  
  int noteinc = potmax/scale;
  int octinc = potmax/octaves;
  int DSoctave = p0val/octinc;
  int DSnote = p4val/noteinc;
  int breathinc =potmax/breathmax;
  int breath = p1val/breathinc;
 
 
  masterpitch = (DSoctave*octaves)+DSnote;
  
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
}

