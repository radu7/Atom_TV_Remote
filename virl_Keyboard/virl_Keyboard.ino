// demo

int state = 0;

void setup()
{
    Serial1.begin(9600);
    pinMode(13, OUTPUT);
    
    while(!Serial1);
    
    Keyboard.begin();

}


void loop()
{
    delay(100);
    setUartDta();
}

void setUartDta()
{
    while(Serial1.available())
    {
        char tmp = Serial1.read();
        
        if(tmp == 'r')              // right
        {
            while(Serial1.available())
            {
                tmp = Serial1.read();
            }
            digitalWrite(13, HIGH);
            Keyboard.press(KEY_RIGHT_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }
        else if(tmp = 'l')
        {
            while(Serial1.available())
            {
                tmp = Serial1.read();
            }
            
            digitalWrite(13, LOW);
            
            Keyboard.press(KEY_LEFT_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }
    }
}
