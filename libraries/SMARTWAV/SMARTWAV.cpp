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

#include <avr/interrupt.h>
#include <Arduino.h> 

#include "SMARTWAV.h"

// SMART WAV DEFAULT BAUD RATE: 9600bps
// Be sure to assign correct pins to TXPIN, RXPIN and Reset in SMARTWAV.h file
/*default pin assignation in SMARTWAV.h:
#define TXPIN 3     //software UART Transmit pin - Connect this pin to SmartWAV RX pin
#define RXPIN 2     //software UART Receive pin - Connect this pin to SmartWAV TX pin
#define RESET 4     //reset - Connect this pin to SmartWAV reset pin
*/

/*---------------------------------------------------------*/
/* 9600bps putchar Software UART Sub-routine                             */
/*---------------------------------------------------------*/
static void sendData(uint8_t DataSenTr)//Sends a UART character by software
{
 uint8_t i=0;  
 
 digitalWrite(TXPIN, LOW);     //set the pin low
 delayMicroseconds(99);                //102us plus instructions time = 104us
 for(i=0;i<8;i++){
  if(DataSenTr & 0x01){
	  digitalWrite(TXPIN, HIGH);     //set the pin high
  }else{
	  digitalWrite(TXPIN, LOW);     //set the pin low
  }
  DataSenTr= DataSenTr>>1;     //Rotate right one bit
  delayMicroseconds(98);               //102us plus instructions time = 104us
 }
 digitalWrite(TXPIN, HIGH);     //set the pin high
 //delayMicroseconds(98);                //101us plus instructions time = 104us 
}

/*---------------------------------------------------------*/
/* 9600bps getchar Software UART Sub-routine                             */
/*---------------------------------------------------------*/
static uint8_t receiveData()     //Receives a UART character by software
{
 uint8_t i=0;
 uint8_t Data=0; 

 while(digitalRead(RXPIN));              //Wait for Start Bit
 delayMicroseconds(148);                //Delay of 151us to read at the middle of the bits
 for(i=0;i<8;i++){
  if(digitalRead(RXPIN)){
   Data= Data >> 1;              //Rotate left 0
   Data= Data | 0x80;            //Set 1 to bit		
  }else{                         //else bit received is 1
   Data= Data >> 1;              //Rotate left 0
   Data= Data | 0x00;            //Set 1 to bit	
  }
  delayMicroseconds(98);                 //100us plus instructions time = 104us
 }
 return Data;                     //Return received character
}

SMARTWAV::SMARTWAV(){
  init();
}

/********** high level commands, for the user! */
void SMARTWAV::init(){           //configure the arduino board for SMARTWAV board
	digitalWrite(TXPIN, HIGH);     //set the pin low
	pinMode(TXPIN,OUTPUT);
	pinMode(RXPIN,INPUT);
	pinMode(RESET, OUTPUT); 
	digitalWrite(RESET, HIGH);   //set the pin to 5v to avoid reset 
}

void SMARTWAV::reset(){          //Reset the SMARTWAV board
  digitalWrite(RESET, LOW);      //set the pin to GND to reset 
  delay(500); 
  digitalWrite(RESET, HIGH);     //set the pin to 5v to end reset
  delay(500);	
} 

uint8_t SMARTWAV::sleep(){       //Send SMARTWAV to sleep mode, if already on sleep mode, then awake SmartWAV
  sendData('Z'); 
  return receiveData();  
}	

uint8_t SMARTWAV::getStatus(){   //Asks for active/play status
  unsigned char x;
  sendData('A');  
  x=receiveData();
  receiveData();
  return x;
}
 
uint8_t SMARTWAV::playTracks(){       //Start playing any song on current Folder/Dir
  sendData('T'); 
  return receiveData();
}	

uint8_t SMARTWAV::pausePlay(){       //Pause current track, if already paused, resumes playing. If called when no playing, returns NAK 'F'
  sendData('P'); 
  return receiveData();
}	

uint8_t SMARTWAV::rewindTrack(){       //Rewind current track. If called when no playing, returns NAK 'F'
  sendData('R'); 
  return receiveData();
}	

uint8_t SMARTWAV::nextTrack(){       //Switch to next track. If called when no playing, returns NAK 'F'
  sendData('N'); 
  return receiveData();
}

uint8_t SMARTWAV::playTrackName(char name[]){       //play an Audio file contained on the micro SD card with the given name.
  uint8_t counter=0;
  
  sendData('F'); 
  while(1){
	sendData(name[counter]);
	delayMicroseconds(98);                //101us plus instructions time = 104us
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return receiveData();
}
		
uint8_t SMARTWAV::stopTrack(){       //Stops current track and all audio, Clears "Continue Play Flag". If called when no playing, returns NAK 'F'
  sendData('S');  
  return receiveData();
}		

uint8_t SMARTWAV::continuousPlay(uint8_t enable){       //Enables/Disables Continuous play flag
  unsigned char aux;
  sendData('C'); 
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData(enable); // Enable-Disable
  aux=receiveData();
  receiveData();
  return aux;
}

uint8_t SMARTWAV::volume(uint8_t vol){       //Change current audio Volume
  sendData('V'); 
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData(vol);
  return receiveData();
}	

uint8_t SMARTWAV::setFolder(char name[]){        //Set/Enters inside a folder/path on the micro SD card with the given name.
  uint8_t counter=0;
  
  sendData('D'); 
  while(1){
	sendData(name[counter]);
	delayMicroseconds(98);                //101us plus instructions time = 104us	
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return receiveData();
}

uint8_t SMARTWAV::getFileName(char name[]){ //Reads the name of the current/ last audio file being played on the SMARTWAV, and stores it on the name[] buffer.
  uint8_t counter=0;
  
  sendData('I');
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData('S');  
   //receive all the file name
  while(1){
	name[counter]=receiveData();
    if(name[counter]==0x00){
		break;
	}
	counter++;
  }    
  return receiveData();
}

uint8_t SMARTWAV::getFolderName(char name[]){ //Reads the name of the current folderDir/path name the SMARTWAV, and stores it on the name[] buffer.
  uint8_t counter=0;
  
  sendData('I');
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData('D');  
   //receive all the folder name
  while(1){
	name[counter]=receiveData();
    if(name[counter]==0x00){
		break;
	}
	counter++;
  }    
  return receiveData();
}

uint8_t SMARTWAV::getFileList(char list[]){ //Reads all the names of the .WAV files on the current folder/dir on the SMARTWAV, and stores it on the list[] buffer separated by comma ','.
  uint8_t counter=0;
  
  sendData('I');
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData('L');  
   //receive all the file names
  while(1){
	list[counter]=receiveData();
    if(list[counter]==0x00){
		break;
	}
	counter++;
  }    
  return receiveData();
}

uint8_t SMARTWAV::getFolderList(char list[]){ //Reads all the folders on the current folder/dir on the SMARTWAV, and stores it on the list[] buffer separated by comma ','.
  uint8_t counter=0;
  
  sendData('I');
  delayMicroseconds(98);                //101us plus instructions time = 104us  
  sendData('X');  
   //receive all the folder names
  while(1){
	list[counter]=receiveData();
    if(list[counter]==0x00){
		break;
	}
	counter++;
  }    
  return receiveData();
}

uint8_t SMARTWAV::playSpeed(uint8_t speed){     //Change current Play Speed: X0.5, X1, X1.5, X2, if track ends, play speed returns to 1.0X
  sendData('M');
  delayMicroseconds(98);                //101us plus instructions time = 104us
  sendData(speed);
  receiveData();
  return receiveData();
}	



