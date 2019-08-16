#ifndef _CANLIBRARY_H_
#define _CANLIBRARY_H_

#include "mbed.h"

/**

 * Univerznalna CAN library, Datum: 27.2.2019.
 *
 * @Nikola Milenic @Marta Avramovic
 * CAN slanje i citanje poruka 
*/

/*//CAN Identificators
#define DTA_1   0x2000
#define DTA_2   0x2001
#define DTA_3   0x2002
#define DTA_4   0x2003
#define DTA_5   0x2004
#define DTA_6   0x2006
// This IDs can be changed as they are our own IDs
#define LVDT_FRONT  0x1000
#define LVDT_REAR   0x1001
#define BRAKES  0x1002
// If we add some other IDs in the vehicle add td*/
#define TEST 14,3


//List of functions

//-----------------------------------------
/*   inicijalizacija CAN prijema poruka   */
//----------------------------------------
void can_initRX();

//----------------------------------------
/*          Funkcije Prijema            */
//----------------------------------------
void can_msg_receive(); 
uint16_t get_data(char, char);
bool check_flag(char);

//----------------------------------------
/*          Funkcije Slanja           */
//----------------------------------------
void canTX_set_Interval(float);
void canTX_set_Interval_1(float);
void canTX_set_Interval_2(float);
void canTX_set_Interval_3(float);
void can_initTX(char);
void can_initTX1(char);
void can_initTX2(char);
void can_initTX3(char);
void can_msg_send();
void can_msg_send1();
void can_msg_send2();
void can_msg_send3();
void can_msg_send_tick();
void can_msg_send_tick1();
void can_msg_send_tick2();
void can_msg_send_tick3();
void pack_data(uint16_t, char);
void pack_data(char, char);
void pack_data1(uint16_t, char);
void pack_data1(char, char);
void pack_data2(uint16_t, char);
void pack_data2(char, char);
void pack_data3(uint16_t, char);
void pack_data3(char, char);

#endif