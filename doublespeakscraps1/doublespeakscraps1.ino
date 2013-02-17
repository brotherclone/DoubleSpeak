// -------------------------------------------------------------------------------------------------------------------------
// demo - run through some of the GinSing features
// -------------------------------------------------------------------------------------------------------------------------

#include <GinSing.h>

GinSing         GS;

GinSingVoice *  v; 
GinSingMaster * m;


#define rcvPin  4
#define sndPin  3
#define ovfPin  2

// -------------------------------------------------------------------------------------------------------------------------
//  setup - system entry point for intialization
// -------------------------------------------------------------------------------------------------------------------------

void setup ()
{
  GS.begin( rcvPin , sndPin , ovfPin );
  
  v  = GS.getVoice ();
  m  = GS.getMaster();
  
}

void loop ()
{

  doSing       (); 

}



void doSing()
{
  GSAllophone oh1[] = {_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE,_OE, };
  GSAllophone oh2[] = {_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO,_OO, };
  GSAllophone ee1[] = {_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE,_IE, };
  GSAllophone ee2[] = {_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE,_EE, };

  #define NumNotes 22
  GSNote notes      [NumNotes] = { C_2 , D_2 , E_2 , F_2 , G_2 , A_2 , B_2 , 
                                   C_3 , D_3 , E_3 , F_3 , G_3 , A_3 , B_3 ,
                                   C_4 , D_4 , E_4 , F_4 , G_4 , A_4 , B_4 , C_5 };
                                    
  GSAllophone* names[7] = { ee2 };
  
    
   // sing up the scale
    
    for ( int noteIdx = 0; noteIdx < NumNotes; noteIdx++ )
    {
      v->setNote ( notes [ noteIdx ] );
      v->speak   ( names [ noteIdx % 7 ] );
      
      delay ( 1000 );

    }
   delay ( 10000 ); 
}



 
