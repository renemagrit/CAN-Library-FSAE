#include "CANlibrary.h"


extern CAN can;
extern Serial pc;
Ticker tick1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!! nije hteo da se prevede kao extern
Ticker tick2;
Ticker tick3;

/******************************************
 - - - - - VAZNO! - - - - -
 IDjevi se tumace u decimalnom brojnom sistemu
  - can_flag niz treba namestiti adrese da idu u u intervalu od 0-15 celobrojno
  - tj, mogle bi da se i koriste one od 2000h ali tipa da to se oduzima 
    nekom celobrojom konstantom koja ce davati oseg adresa od 0 do 15
*/


bool can_flag[16];
CANMessage msgs[1024];
char data[8],data1[8],data2[8],data3[8];
char idTX=0,idTX1=0,idTX2=0,idTX3=0;
float msgInterval1=0,msgInterval2=0,msgInterval3=0;

void can_initRX(){
   // pc.printf("u RX sam\r\n");
    can.attach(can_msg_receive, CAN::RxIrq); 
}
void can_msg_receive(){  
   // CAN RX Interrupt Function
    //pc.printf(" I N T RA P T \r\n");
    CANMessage tmpMsg;
    if (can.read(tmpMsg)) {                 //Detect message
        //pc.printf("p r i m i o \r\n");
        can_flag[tmpMsg.id]=true;
       // msgs[tmpMsg.id]=tmpMsg;
        //pc.printf("PRIMLJEN id: %d\r\n",tmpMsg.id);
        if(tmpMsg.id >= 8192){
            msgs[(tmpMsg.id % 8192)]=tmpMsg;  
        }else{
            msgs[tmpMsg.id]=tmpMsg;  
        }
        
    }
};

uint16_t get_data(char id, char indeks){
   return msgs[id].data[indeks<<1] | (msgs[id].data[(indeks << 1) + 1] << 8);
}

bool check_flag(char id){
    bool ret = can_flag[id];
    can_flag[id]=false;
    return ret;
}


//-------------------------------------------------------------------
//-------------------------------------------------------------------
// Funkcije slanja poruka:
void canTX_set_Interval(float inter){ 
    
    //Zadavanje fiksnog intervala slanja CAN poruke
    //Vrednost je realna. Jedinica zadavanja je u sekundama.
    msgInterval1=inter;
}

void canTX_set_Interval_1(float inter){ 
    
    //Zadavanje fiksnog intervala slanja CAN poruke
    //Vrednost je realna. Jedinica zadavanja je u sekundama.
    msgInterval1=inter;
}

void canTX_set_Interval_2(float inter){ 
    
    //Zadavanje fiksnog intervala slanja CAN poruke
    //Vrednost je realna. Jedinica zadavanja je u sekundama.
    msgInterval2=inter;
}

void canTX_set_Interval_3(float inter){ 
    
    //Zadavanje fiksnog intervala slanja CAN poruke
    //Vrednost je realna. Jedinica zadavanja je u sekundama.
    msgInterval3=inter;
}
void  can_initTX(char idtx){
    
    //Fukcija koja zadaje fiksnu adresu slanja poruke
    idTX1=idtx;
}

void  can_initTX1(char idtx){
    
    //Fukcija koja zadaje fiksnu adresu slanja poruke
    idTX1=idtx;
}

void  can_initTX2(char idtx){
    
    //Fukcija koja zadaje fiksnu adresu slanja poruke
    idTX2=idtx;
}

void  can_initTX3(char idtx){
    
    //Fukcija koja zadaje fiksnu adresu slanja poruke
    idTX3=idtx;
}
void can_msg_send(){
    
    /*
     *  Fukcija koja salje podatke na CAN mrezu po zadatom,setovanom, IDju. 
     *  Duzina poruke podesena je fiksno na 8B.
     */
    can.write(CANMessage((uint16_t)idTX1, data1, 8));
}
void can_msg_send1(){
    
    /*
     *  Fukcija koja salje podatke na CAN mrezu po zadatom,setovanom, IDju. 
     *  Duzina poruke podesena je fiksno na 8B.
     */
    can.write(CANMessage((uint16_t)idTX1, data1, 8));
}
void can_msg_send2(){
    
    /*
     *  Fukcija koja salje podatke na CAN mrezu po zadatom,setovanom, IDju. 
     *  Duzina poruke podesena je fiksno na 8B.
     */
    can.write(CANMessage((uint16_t)idTX2, data2, 8));
}
void can_msg_send3(){
    
    /*
     *  Fukcija koja salje podatke na CAN mrezu po zadatom,setovanom, IDju. 
     *  Duzina poruke podesena je fiksno na 8B.
     */
    can.write(CANMessage((uint16_t)idTX3, data3, 8));
}

void can_msg_send_tick(){
    
    //Funkcija koja se poziva za slanje poruka u okviru fiksnog intervala
    idTX=idTX1;
     //strcpy(data,data1);
    tick1.attach(can_msg_send1, msgInterval1);
}
void can_msg_send_tick1(){
    
    //Funkcija koja se poziva za slanje poruka u okviru fiksnog intervala
    idTX=idTX1;
     //strcpy(data,data1);
    tick1.attach(can_msg_send1, msgInterval1);
}
void can_msg_send_tick2(){
    
    //Funkcija koja se poziva za slanje poruka u okviru fiksnog intervala
    idTX=idTX2;
    //strcpy(data,data2);
    tick2.attach(can_msg_send2, msgInterval2);
}
void can_msg_send_tick3(){
    
    //Funkcija koja se poziva za slanje poruka u okviru fiksnog intervala
    idTX=idTX3;
    //strcpy(data,data3);
    tick3.attach(can_msg_send3, msgInterval3);
}
//----------------------------------------------------------------------------
/*  Pomocne funkcije za pakovanje podataka prilikom slanja:
 *  Ove funkcije omogućavaju da automatsko pakovanje u razlicite velicine poruke 
 *  u zavisnosti od tipa i pozicije na kojoj treba poslati podatak.
 *
 *  Realizovane su za dva tipa: 
 *      -unit16_t (automatsko pakovanje u dva podatka od po 1B)
 *      -char
 * 
 *  Format: dta = vrednost koju saljemo kao podatak CANom, pos = pozicija u CAN
 *  poruci.
 * 
 *  CAN poruka: (IDslanja, DD7, DD6, DD5, DD4, DD3,DD2, DD1, DD0)
 *  Velicina podataka (DD7...DD0) je od po 1Byte.
 *  Maximalno se mogu poslati 4 podatka od po 2B (pos polje u opsegu od 0 do 3) 
 *  ili 8 od po 1B (pos polje u opsegu od 0 do 7). 
 */
void pack_data(uint16_t dta, char pos){
    
    //Pakuje unit16_t u dva podatka od po 1B, na poziciji pos u CAN poruci
    data1[pos<<1] = dta;
    data1[(pos<<1)+1] = dta >> 8;
}

void pack_data1(uint16_t dta, char pos){
    
    //Pakuje unit16_t u dva podatka od po 1B, na poziciji pos u CAN poruci
    data1[pos<<1] = dta;
    data1[(pos<<1)+1] = dta >> 8;
}

void pack_data1(char dta, char pos){
     
     //Pakuje char u jedan podatka od 1B, na poziciji pos u CAN poruci
    data1[pos<<1] = dta;
}

void pack_data2(uint16_t dta, char pos){
    
    //Pakuje unit16_t u dva podatka od po 1B, na poziciji pos u CAN poruci
    data2[pos<<1] = dta;
    data2[(pos<<1)+1] = dta >> 8;
}

void pack_data2(char dta, char pos){
     
     //Pakuje char u jedan podatka od 1B, na poziciji pos u CAN poruci
    data2[pos<<1] = dta;
}

void pack_data3(uint16_t dta, char pos){
    
    //Pakuje unit16_t u dva podatka od po 1B, na poziciji pos u CAN poruci
    data3[pos<<1] = dta;
    data3[(pos<<1)+1] = dta >> 8;
}

void pack_data3(char dta, char pos){
     
     //Pakuje char u jedan podatka od 1B, na poziciji pos u CAN poruci
    data3[pos<<1] = dta;
}


