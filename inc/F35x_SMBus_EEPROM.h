//-----------------------------------------------------------------------------
// Includes and Device-Specific Parameters
//-----------------------------------------------------------------------------
#ifndef __F35x_SMBus_EEPROM_H
#define __F35x_SMBus_EEPROM_H

#include <C8051F350.h>
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
#define  SYSCLK       24500000          // SYSCLK frequency in Hz

#define  SMB_FREQUENCY  50000          // Target SCL clock rate
                                       // This example supports between 10kHz
                                       // and 100kHz

#define  WRITE          0x00           // SMBus WRITE command
#define  READ           0x01           // SMBus READ command

// Device addresses (7 bits, lsb is a don't care)
#define  EEPROM_ADDR    0xA0           // Device address for slave target
                                       // Note: This address is specified
                                       // in the Microchip 24LC02B
                                       // datasheet.

// SMBus Buffer Size
#define  SMB_BUFF_SIZE  0x08           // Defines the maximum number of bytes
                                       // that can be sent or received in a
                                       // single transfer

// Status vector - top 4 bits only
#define  SMB_MTSTA      0xE0           // (MT) start transmitted
#define  SMB_MTDB       0xC0           // (MT) data byte transmitted
#define  SMB_MRDB       0x80           // (MR) data byte received
// End status vector definition

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
unsigned char* pSMB_DATA_IN;           // Global pointer for SMBus data
                                       // All receive data is written here

unsigned char SMB_SINGLEBYTE_OUT;      // Global holder for single byte writes.

unsigned char* pSMB_DATA_OUT;          // Global pointer for SMBus data.
                                       // All transmit data is read from here

unsigned char SMB_DATA_LEN;            // Global holder for number of bytes
                                       // to send or receive in the current
                                       // SMBus transfer.

unsigned char WORD_ADDR;               // Global holder for the EEPROM word
                                       // address that will be accessed in
                                       // the next transfer

unsigned char TARGET;                  // Target SMBus slave address

bit SMB_BUSY = 0;                      // Software flag to indicate when the
                                       // EEPROM_ByteRead() or
                                       // EEPROM_ByteWrite()
                                       // functions have claimed the SMBus

bit SMB_RW;                            // Software flag to indicate the
                                       // direction of the current transfer

bit SMB_SENDWORDADDR;                  // When set, this flag causes the ISR
                                       // to send the 8-bit <WORD_ADDR>
                                       // after sending the slave address.


bit SMB_RANDOMREAD;                    // When set, this flag causes the ISR
                                       // to send a START signal after sending
                                       // the word address.
                                       // For the 24LC02B EEPROM, a random read
                                       // (a read from a particular address in
                                       // memory) starts as a write then
                                       // changes to a read after the repeated
                                       // start is sent. The ISR handles this
                                       // switchover if the <SMB_RANDOMREAD>
                                       // bit is set.

bit SMB_ACKPOLL;                       // When set, this flag causes the ISR
                                       // to send a repeated START until the
                                       // slave has acknowledged its address

// 16-bit SFR declarations
// P0.0 -> SDA (SMBus)
// P0.1 -> SCL (SMBus)
//
//
// P2.0 -> C2D (debug interface)
sfr16    TMR3RL   = 0x92;              // Timer3 reload registers
sfr16    TMR3     = 0x94;              // Timer3 counter registers


sbit SDA = P0^0;                       // SMBus on P0.0
sbit SCL = P0^1;                       // and P0.1


//-----------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------
void SMBus_EEPROM_Init(void);//SMBUS×Ü³õÊ¼»¯

void SMBus_Init(void);
void Timer1_Init(void);
void Timer3_Init(void);
void SMBus_PORT_Init (void);

void SMBus_ISR(void);
void Timer3_ISR(void);

void EEPROM_ByteWrite(unsigned char addr, unsigned char dat);
void EEPROM_WriteArray(unsigned char dest_addr, unsigned char* src_addr,
                       unsigned char len);
unsigned char EEPROM_ByteRead(unsigned char addr);
void EEPROM_ReadArray(unsigned char* dest_addr, unsigned char src_addr,
                      unsigned char len);

#endif

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------