#include <GinSing.h>
#include <Potentiometer.h>

GinSing         GS;
GinSingVoice *  v; 
GinSingMaster * m;
#define rcvPin  4
#define sndPin  3
#define ovfPin  10




#define NumNotes 35
GSNote notes      [NumNotes] = { 
  C_1 , D_1 , E_1 , F_1 , G_1 , A_1 , B_1 , 
  C_2 , D_2 , E_2 , F_2 , G_2 , A_2 , B_2 , 
  C_3 , D_3 , E_3 , F_3 , G_3 , A_3 , B_3 ,
  C_4 , D_4 , E_4 , F_4 , G_4 , A_4 , B_4 ,
  C_5 , D_5 , E_5 , F_5 , G_5 , A_5 , B_5 ,
}; 

GSAllophone pho[] = {_A,
_AA,
_AE,
_AIR,
_AU,
_BE,
_BO,
_EB,
_OB,
_CH,
_DE,
_DO,
_ED,
_OD,
_E,
_EE,
_ER,
_F,
_GE,
_GO,
_HE,
_HO,
_I,
_IE,
_J,
_KE,
_KO,
_EK,
_OK,
_LE,
_LO,
_M,
_NE,
_NO,
_NGE,
_NGO,
_OE,
_OI,
_OO,
_OU,
_OR,
_PE,
_PO,
_R,
_SE,
_SO,
_SH,
_T,
_TH,
_THH,
_TS,
_U,
_UE,
_V,
_W,
_Y,
_Z,
_ZH};

int phocount = sizeof(pho);

int potmax = 1023;
int masterpitch = 0;
int breathmax = 10;
int breath = 0;
int breathint = potmax/breathmax;
int currentbreathlength =0;
int noisechannels = 8;
int noiseint = potmax/noisechannels;
int currentnoisechannel = 0;
int scale = 7;
int noteint = potmax/scale;
int currentnote =0;
int octaves = NumNotes/scale;
int octaveint = potmax/octaves;
int currentoctave = 0;
int ddelay =10;
int ddelaymax = 100;
int ddelayint = potmax/ddelaymax;

GSAllophone singy[] = {
  _OO, _OU, _OO, _OE,  _ENDPHRASE};


int led = 12;  
int ReadyMessage = 0;

Potentiometer potentiometer0 = Potentiometer(A0); 
Potentiometer potentiometer1 = Potentiometer(A1);
Potentiometer potentiometer2 = Potentiometer(A2); 
Potentiometer potentiometer3 = Potentiometer(A3); 
Potentiometer potentiometer4 = Potentiometer(A4); 



void setup () {
  GS.begin( rcvPin , sndPin , ovfPin );
  v  = GS.getVoice ();
  m  = GS.getMaster();
  pinMode(led, OUTPUT);
}

void loop () {
  Serial.begin(9800);
  if(!ReadyMessage){
    doubleSpeakReady();
    ReadyMessage = 1;
  }
  getMyControls();
  doSing();
  delay(ddelay);
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


void getMyControls (){
  int octavepot = potentiometer0.getValue();
  currentoctave = octavepot/octaveint;
  int noisepot =  potentiometer1.getValue();
  currentnoisechannel = noisepot/noiseint;
  int breathpot =  potentiometer2.getValue();
  currentbreathlength = breathpot/breathint;
  int ddelaypot =  potentiometer3.getValue();
  ddelay = ddelaypot/ddelayint; 
  int notepot =  potentiometer4.getValue();
  currentnote = notepot/noteint;
  masterpitch = (currentoctave*octaves)+currentnote;
}

void doSing (){
  analogWrite(led, 180);
  v->setNote ( notes[masterpitch] );
   if(currentnoisechannel<=1){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_OO,_OE,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_OE,_OO,_OO,_OU,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_OO,_OU,_OO,_OU,_HO,_HO,_OO,_HO,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_OO,_OO,_OO,_OO,_OO,_PITCHDN,_HO,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }   
   }else if(currentnoisechannel==2){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_AA, _AE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_AE,_AA,_AA,_AE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_AE,_AA,_IE,_AE,_AA,_AA,_PITCHDN,_AE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_AU,_OO,_AA,_AA,_AA,_PITCHDN,_HO,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
   }else if(currentnoisechannel==3){
      if(currentbreathlength<=2){
       GSAllophone singy[] = {_OO, _OE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_OE,_OO,_OO,_OU, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_OO,_OU,_OO,_OU,_HO,_HO,_OO,_HO, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
       GSAllophone singy[] = {_OO,_OO,_OO,_OO,_OO,_PITCHDN,_HO,_ENDPHRASE};
     }  
   }else if(currentnoisechannel==4){
      if(currentbreathlength<=2){
       GSAllophone singy[] = {_E, _EE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_E,_EE,_EE,_E, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_Y,_EE,_E,_EE,_E,_EE,_EE,_E, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_Y,_E,_AE,_EE,_EE, _E, _PITCHDN,_AE,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
   }else if(currentnoisechannel==5){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_NGE, _Y, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_PE,_E,_PE,_LE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_KO,_LO,_OO,_KO,_Z,_HO,_TH,_THH, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_BE,_AE, _BE,_OO,_PITCHDN,_HO,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
   }else if(currentnoisechannel==6){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_W, _OE, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_OE,_W,_OO,_W, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_W,_TS,_W,_W,_TS,_J,_OO, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_J,_TS,_W,_TS,_J,_ER,_PITCHDN,_W,_AE,_TS,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
   }else if(currentnoisechannel==7){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_THH,_EK,_ER, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_ER,_R,_ER,_R,_THH, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_EK,_EK,_DO,_THH,_EK,_EK,_EK,_EK, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_ER,_R,_R,_THH,_EK,_DO,_DO,_PITCHDN,_DO,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
   }else if(currentnoisechannel>=8){
     if(currentbreathlength<=2){
       GSAllophone singy[] = {_ZH,_ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>2)&&(currentbreathlength<=5)){
       GSAllophone singy[] = {_EK,_BENDUP,_EK, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>5)&&(currentbreathlength<=7)){
       GSAllophone singy[] = {_DE,_DE,_F,_SO, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }else if((currentbreathlength>7)&&(currentbreathlength<=10)){
       GSAllophone singy[] = {_GE,_THH,_EB,_Y,_TH,_OI,_BENDDN, _OI, _ENDPHRASE};
       v->speak   (singy);
       delay ( v->getMillis ( singy ) );
     }  
  }
  
   analogWrite(led, 0);
}

