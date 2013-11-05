// demo of

#include <BeaconDrive.h>
#include <Wire.h>
#include <MMA7660.h>
#include <Sleep_n0m1.h>
#include <avr/wdt.h>
 
#define wdt_init(X)     wdt_enable(X)
#define feed()          wdt_reset()

#define LEDON()     digitalWrite(13, HIGH)
#define LEDOFF()    digitalWrite(13, LOW)

MMA7660 acc;


void sendDta(unsigned char code)
{
    Serial1.write(code);
}

void setup()
{
    BcnDrive.init();
    BcnDrive.sysPowerOn();
    
    delay(200);
    
    acc.init();
    
    pinMode(13, OUTPUT);

    Serial1.begin(9600);
    while(!Serial1);
    
    wdt_init(WDTO_2S);                  // 1s
    feed();
    
}

int getAcc()
{
    float ax, ay, az;
    acc.getAcceleration(&ax, &ay, &az);
    
    int ayy = ay*100;

    return ayy;
}

void loop()
{


    if(abs(getAcc()) > 130)
    {
            
        long timer1 = millis();
        long timer2 = 0;
        int lastDta = 0;
        while(1)
        {
            int tmp = getAcc();

            if(abs(getAcc()) < 100)
            {
                timer2 = millis();
                if((timer2-timer1)>155)
                {
                    if(lastDta > 0)
                    {
                        Serial1.println("right");
                    }
                    else
                    {
                        Serial1.println("left");
                    }
                    BcnDrive.beepOn();
                    LEDON();
                    //feed();
                    delay(100);
                    BcnDrive.beepOff();
                    LEDOFF();
                    break;
                }
            }
            else
            {
                lastDta = tmp;
                timer1 = millis();
            }
            
            //feed();
            delay(50);

        }
    }

    feed();
    //LEDON();
    delay(25);
    //LEDOFF();
    delay(25);
    buttonManage();

}

void buttonManage()
{
    long timer1 = millis();
    
    //feed();
    
    if(!digitalRead(PINSYSBUTT))
    {
    

        while(!digitalRead(PINSYSBUTT))
        {
            long timer2 = millis();
            if((timer2-timer1)>600)
            {
                BcnDrive.beepOn();
                //feed();
                delay(200);
                BcnDrive.beepOff();
                BcnDrive.sysPowerOff();
                
                while(1)
                {
                    BcnDrive.sysPowerOff();
                }
            }
            //feed();
            delay(50);
        }
        
        long timer2  = millis();
        
        long d_timer = timer2 - timer1;

        if(d_timer > 100)
        {
            // add code here
        }
        
        
    }
    
    //feed();
}
