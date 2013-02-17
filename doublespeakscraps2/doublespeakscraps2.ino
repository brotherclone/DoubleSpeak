#include <GinSing.h>
GinSing         GS;
GinSingVoice *  v; 
GinSingMaster * m;
#define rcvPin  4
#define sndPin  3
#define ovfPin  2

void setup () {
  GS.begin( rcvPin , sndPin , ovfPin );
  v  = GS.getVoice ();
  m  = GS.getMaster();
  
}

void loop () {
  //doSing       (); 
  doubleSpeakReady();
}


void doubleSpeakReady() {
   v->begin();

  v->setNote ( D_2 );

   GSAllophone msg[] = { _IE , _A , _M ,
                           _DO , _U , _OB , _OO , _LE,
                           _SE , _PE , _EE , _EK,
                           _IE , _A , _M ,
                          _R , _E , _DE , _EE, _ENDPHRASE };
    
    v->setBlendSpeed ( 0.09f );
    v->speak (msg);
    
    delay ( v->getMillis (msg ) + 500 );
  
}


void doSing(){
  GSAllophone oh1[] = {_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE, };
  GSAllophone oh2[] = {_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO, };
  GSAllophone ee1[] = {_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE, };
  GSAllophone ee2[] = {_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE, };

  #define NumNotes 38
  GSNote notes      [NumNotes] = { C_1 , D_1 , E_1 , F_1 , G_1 , A_1 , B_1 , 
                                   C_2 , D_2 , E_2 , F_2 , G_2 , A_2 , B_2 , 
                                   C_3 , D_3 , E_3 , F_3 , G_3 , A_3 , B_3 ,
                                   C_4 , D_4 , E_4 , F_4 , G_4 , A_4 , B_4 ,
                                   C_5 , D_5 , E_5 , F_5 , G_5 , A_5 , B_5 ,
                                 };
                                    
  GSAllophone* names[7] = {oh2 };
  
  
      v->setNote ( notes [ 17 ] );
      v->speak   ( names [ 0 ] ); 
   delay ( 15050 ); 
}



 
