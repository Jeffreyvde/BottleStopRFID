#ifndef RFID_h
#define RFID_h

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

// Copyright Jeffrey van den Elshout
class RFID
{
public:
    RFID();
    RFID(int rstPin, int ssPin);
    String getID();
    int isRFIDAvailable();
    int readBlock(int blockNumber, byte arrayAddress[]);
    void cancelRead();
    void reset();
    String convertToString(byte data[], int length);

    String lastBottleID;
    bool isConnected;

private:
    MFRC522 mfrc522;
    MFRC522::MIFARE_Key key;

    int testRequired;
    int currentTest;
};
#endif