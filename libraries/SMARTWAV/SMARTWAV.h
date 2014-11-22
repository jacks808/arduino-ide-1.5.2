/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2012.
THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 IMPORTANT : This library is created for the Arduino 1.0 Software IDE
********************************************************/

#ifndef SMARTWAV_h
#define SMARTWAV_h

#include <inttypes.h>


/********************************************************
 USER DEFINITIONS
********************************************************/
#define TXPIN 3     //software UART Transmit pin - Connect this pin to SmartWAV RX pin
#define RXPIN 2     //software UART Receive pin - Connect this pin to SmartWAV TX pin
#define RESET 4     //reset - Connect this pin to SmartWAV reset pin



/********************************************************
 END OF USER DEFINITIONS - not modify
********************************************************/
//General definitions (not modify)
#define audioOFF 0
#define audioON 1
#define X0.5 0
#define X1.0 1
#define X1.5 2
#define X2.0 3
#define DISABLE 0
#define ENABLE 1
#define MAX 0xFF
#define MED 0xE0
#define MIN 0x00


class SMARTWAV{
	
public:
    SMARTWAV();
	
	void init();
	
	void reset();

	uint8_t sleep(); 
	
	uint8_t getStatus();  

	uint8_t playTracks();	
	
	uint8_t pausePlay();

	uint8_t rewindTrack();

	uint8_t nextTrack();

	uint8_t playTrackName(char[]);

	uint8_t stopTrack();
	
	uint8_t continuousPlay(uint8_t);

	uint8_t volume(uint8_t);
	
	uint8_t setFolder(char[]);

	uint8_t getFileName(char[]);
	
	uint8_t getFolderName(char[]);	

	uint8_t getFileList(char[]);	
	
	uint8_t getFolderList(char[]);		

	uint8_t playSpeed(uint8_t);
	
};

#endif
