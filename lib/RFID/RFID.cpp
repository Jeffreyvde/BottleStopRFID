#include "RFID.h"
#include <MFRC522.h>
RFID::RFID()
{
    testRequired = 10;
    currentTest = 0;
}

RFID::RFID(int rstPin, int ssPin)
{
    mfrc522 = MFRC522(ssPin, rstPin);

    SPI.begin();
    mfrc522.PCD_Init();

    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }

    testRequired = 10;
    currentTest = 0;
}

//Check if their is a bottle with an ID
bool RFID::checkID()
{
    //Check if a card is present
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return false;
    }
    currentTest = 0;

    //Read the card that is present
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return false;
    }

    String currentBottleID = "";
    //Places ID in bottleID
    for (int i = 0; i < 4; i++)
    {
        currentBottleID.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    lastBottleID = currentBottleID;
    return true;
}

//Convert a byte[] to String
String RFID::convertToString(byte data[], int length)
{
    String s = "";
    for (uint8_t i = 0; i < length; i++)
    {
        s.concat((char)data[i]);
    }
    return s;
}

//Read specific block
int RFID::readBlock(int blockNumber, byte arrayAddress[])
{
    int largestModulo4Number = blockNumber / 4 * 4;
    int trailerBlock = largestModulo4Number + 3; //determine trailer block for the sector

    //authentication of the desired block for access
    MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("PCD_Authenticate() failed (read): ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return 3; //return "3" as error message
    }

    //reading a block
    byte buffersize = 18;                                                 //we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
    status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize); //&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("MIFARE_read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return 4; //return "4" as error message
    }

    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, blockNumber);
    Serial.println();

    return 1;
}

//Cancel Read if not done it will no longer be able to detect new RFID chips
void RFID::cancelRead()
{
    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}

void RFID::reset()
{
    mfrc522.PCD_Reset();
    mfrc522.PCD_Init();
    SPI.begin();
}