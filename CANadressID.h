#ifndef _CAN_IDADRESS_H_
#define _CAN_IDADRESS_H_
/*
 *  CANadreess.h sadrzi macro functions za svaki podatak:
 *      - ID sa kojeg se cita
 *      - poziciju u poruci
 * 
 *  Ovo se koristi pri funkciji: uint16_t get_data(char, char);
 *  - prvi argument je ID sa kojeg se cita
 *  - drugi argument je pozicija podatka u poruci
 *  Jedna CAN poruka moze da procita 4 podatka velicine 2B i pozicija koja je u
 *  opsegu od 0 do 3. 
 *
 *  Svaki novipodatak se "kaci" na CAN tako sto mu se upise ID i adresa ovde
 *
*/

//MACRO potpis: ID,POS

#define DTA1_RPM 0,0
#define DTA1_TPS 0,1
#define DTA1_WaterTemp 0,2
#define DTA1_AirTemp 0,3

#define DTA2_MAP 1,0
#define DTA2_Lambda 1,1
#define DTA2_Speed 1,2
#define DTA2_OilPres 1,3

#define DTA3_OilTemp 2,1
#define DTA3_ Volts 2,2

#define DTA4_Gear 3,0

//#define DTA5_ 4,0

#define DTA6_Crank 5,2

#define LVDT_FRONT_FLLVDT0 4096,0
#define LVDT_FRONT_FLLVDT1 4096,1

#define LVDT_REAR_RLLVDT0 4097,0
#define LVDT_REAR_RLLVDT1 4097,1

#define BRAKES 4097,0

#endif
