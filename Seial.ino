void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  String info;
  for(int i=0;i<9;i++)
  {
    if(info[i]=='0')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='1')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='2')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='3')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='4')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='5')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='6')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='7')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
    if(info[i]=='8')
    {
       pinMode(2+4*i,OUTPUT);
       pinMode(3+4*i,OUTPUT);
       pinMode(4+4*i,OUTPUT);
       pinMode(5+4*i,OUTPUT);
    }
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    String info;
    info=Serial.readStringUntil('\0');
    for(int i=0;i<9;i++)
    {
       if(info[i]=='0')
    {
      digitalWrite(2+4*i,0);
      digitalWrite(3+4*i,0);
      digitalWrite(4+4*i,0);
      digitalWrite(5+4*i,0);
    }
       if(info[i]=='1')
    {
      digitalWrite(2+4*i,1);
      digitalWrite(3+4*i,0);
      digitalWrite(4+4*i,0);
      digitalWrite(5+4*i,0);
    }

     if(info[i]=='2')
    {
      digitalWrite(2+4*i,0);
      digitalWrite(3+4*i,1);
      digitalWrite(4+4*i,0);
      digitalWrite(5+4*i,0);
    }

     if(info[i]=='3')
    {
      digitalWrite(2+4*i,1);
      digitalWrite(3+4*i,1);
      digitalWrite(4+4*i,0);
      digitalWrite(5+4*i,0);
    }

     if(info[i]=='4')
    {
      digitalWrite(2+4*i,0);
      digitalWrite(3+4*i,0);
      digitalWrite(4+4*i,1);
      digitalWrite(5+4*i,0);
    }

     if(info[i]=='5')
    {
      digitalWrite(2+4*i,1);
      digitalWrite(3+4*i,0);
      digitalWrite(4+4*i,1);
      digitalWrite(5+4*i,0);
    }

     if(info[i]=='6')
    {
      digitalWrite(2+4*i,0);
      digitalWrite(3+4*i,1);
      digitalWrite(4+4*i,1);
      digitalWrite(5+4*i,0);
    }
     if(info[i]=='7')
    {
      digitalWrite(2+4*i,1);
      digitalWrite(3+4*i,1);
      digitalWrite(4+4*i,1);
      digitalWrite(5+4*i,0);
    }
     if(info[i]=='8')
    {
      digitalWrite(2+4*i,0);
      digitalWrite(3+4*i,0);
      digitalWrite(4+4*i,0);
      digitalWrite(5+4*i,1);
    }
    
    }
   
  }

}
