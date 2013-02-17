
#include <Potentiometer.h>
#include <GinSing.h>                                 // interface headder file
GinSing       GS;                                    // create the class library from which all methods and data are accessed

#define rcvPin  4                                    // this is the pin used for receiving    ( can be either 4 or 12 )
#define sndPin  3                                    // this is the pin used for transmitting ( can be either 3 or 11 ) 
#define ovfPin  2                                    // this is the pin used for overflow control ( can be either 2 or 10 )

GinSingVoice * voice = 0x0;

GinSingSerial speakjet;     // add speakjet for serial - Software Serial can't work with GinSing lib.

Potentiometer potentiometer1 = Potentiometer(A0); 


int led = 12;  



#define numNotes 22  // musical notes to "sing"

GSNote notes[numNotes] = {  C_1, D_1, E_1, F_1, G_1, A_1, B_1, C_2, D_2, E_2, F_2, G_2, A_2, B_2, C_3, D_3, E_3, F_3, G_3, A_3, B_3, C_4, D_4, E_4, F_4, G_4, A_4, B_4, C_5 };

#define NumVowels 22
GSAllophone vowels[NumVowels] =
   {
     _A  , _AA , _AE , _AIR , _AU , _EB , _OB , _OD , _E   ,         // these are the available vowels (mostly)
     _EE , _ER , _I  , _IE  , _EK , _OK , _OE , _OI , _OO , _OU  ,         // usually used at the middle of a word
     _OR , _U  , _UE 
   }; 
   
   
char message[] = {20, 96, 21, 114, 22, 88, 23, 5, 8, 135, 8, 146, 5, 128, 153, 5, 170, 154, 8, 188, 5, 152, 5, 170, 8,128,146,8,135,8,144,5,8,191,162,5,8,134,187};

int ds = 0;
int dv = 0;

void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9800);
  GS.begin ( rcvPin , sndPin , ovfPin );             // start the device ( you probably already know that by now )
  speakjet.config (12,11,0xff);
  voice = GS.getVoice();                             // get the voice mode interface; in this example we share it for all functions
  voice->begin();                                    // enter voice mode                                         // make up some chants   
  speakjet.begin(9800);  
}

void loop(){
  dv = potentiometer1.getValue();
  GSAllophone  phrase[] = { vowels[dv] , _ENDPHRASE };
  voice->setNote ( (GSNote) notes [ ds ] ); 
  voice->speak   ( phrase );
  GSAllophone shutup[] = { _PA1 , _ENDPHRASE };                    // tell the voice to stop
  voice->speak   ( shutup );                                       // make it stop 
  while ( !GS.isReady() ) delay ( 1 );  
  delay(100);
}
