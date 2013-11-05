// demo..

#include <Streaming.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12);

void setup()
{
    Serial.begin(115200);
    mySerial.begin(9600);
    
    cout << "hello world" << endl;
}


void loop()
{
    while (mySerial.available() > 0) 
    {
        char inByte = mySerial.read();
        Serial.write(inByte);
    }
}