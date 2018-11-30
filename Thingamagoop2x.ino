  /*
  Thingamagoop 2 Arduino code
  By Dr. Bleep Nov 2009

  bleeplabs.com

  
  This code was the first thing I made in Arduino and looks it. 
  The nebulophone is a better starting point if you're wanting to make a synth with the atmega328 and arduino
  but it's also a little dated.
  Check out the teesny audio library for the best DIY synth options
  John-Mike Reed Nov 2018
    */

  int pcellPin = 3;
  int ModePot = 5;
  int LedPot = 4;
  int outPin = 9;
  int LedPin = 11;
  int gatePin = 13;
  int buttonPin =12;
  int mval;
  int pcellval;
  int mode;
  long prev1 = 1;
  long prev2 = 1;
  long prev3 = 1;
  int note;
  int modeA;
  int modeAC;
  int interval1;
  int i=1; 
  int r;int k;
  int j=1;
  int rj=1;
  int majscale[32]={238,224,200,178,159,150,133,119,112,100,89,79,75,67,59,56,50,45,40,37,33,30,28,25,22,20,19,17,15,14,13,11};

  int ramp;
  long ledrate;
  long ledrateC;
  long ledpotval;
  int noise;
  long random1;
  long random2;


  byte pwm_tick;
  byte pot_tick;
  byte led_out,cv_out;
  int green = 1;

void setup (){
  digitalWrite(buttonPin, LOW);
  pinMode (12, OUTPUT);
  randomSeed(analogRead(4));

  //Serial.begin(9600);
  TCCR1B = B00000001;
  TCCR2B = B00000001;
  TCCR1A = B00000001;
  TCCR2A = B00000001;

}

void loop(){

/*
if (millis() - prev3 > 20 ) { 
  prev3 = millis(); 

Serial.print(random1);Serial.print("  :  ");Serial.println(mval);
Serial.print(ledpotval); Serial.print("  :  "); Serial.println(ledrateC);

}
*/

// only do one analog read and write per loop


  pot_tick++;
  if(pot_tick>2){
    pot_tick=0;
  }

  if(pot_tick==0){
    ledpotval = analogRead(LedPot);
  }

  if(pot_tick==1){
   mode = analogRead(ModePot); 
 }

 if(pot_tick==2){
  pcellval = analogRead(pcellPin);
  mval = (map(pcellval, 256, 1000, 32 , 0))-5;
  mval = constrain (mval,0,32);
  note = majscale[mval]; 
}


// E
    if (mode <205){  
      TCCR1B = B00000001;

      modeA = map(mode, 0, 204, 20, 150);
      modeAC = constrain (modeA, 20,150);
      if (millis() - prev1 > modeAC ) {   
        prev1 = millis();   
        i++;
        if (i>1){i=0;}
        cv_out= majscale[mval];

}
}
// A

if (mode >=205 && mode<410){  

  TCCR1B = B00000001;
  modeA = map(mode, 205, 410, 300, 1);
  modeAC = constrain (modeA, 1,500);

  if (millis() - prev1 > modeAC ) {      
    prev1 = millis(); 
    i++;
    cv_out= majscale[mval+i];
    if (i>3){
      i=0;

    }
  }
}

// B
if (mode >=410 && mode<615){  
  green =0;
  TCCR1B = B00000001;
  modeA = map(mode, 410, 614, 120, 1);
  modeAC = constrain (modeA, 1,120);

  if (millis() - prev1 > modeAC ) {   
    prev1 = millis(); 
    i++;
    if (i<3){

      cv_out= 0;
    }
    if (i==3){

      cv_out= majscale[mval-3];

    }
    if (i==4){

      cv_out= majscale[mval];

    }
    if (i>4 && i<7){

      cv_out=0;

    }  
    if (i==7){

      cv_out= majscale[mval+3];


    }  
    if (i==8){
      i=0;     
      cv_out= majscale[mval+1];


    }  
  }

}

// X
if (mode >=615 && mode<800){  
  i = 0;
  TCCR1B = B00000001;
  modeA = map(mode, 615, 799, 250, 1);
  modeAC = constrain (modeA, 1,100);

  mval = (map(pcellval, 256, 1000, 0 , 255));
  random1 = random(mval);

  if (millis() - prev1 > modeAC ) {   
    prev1 = millis(); 
    cv_out= random1;

  }
}
if (mode >=800 && mode<819){  
  i = 0;
  TCCR1B = B00000001;

  mval = (map(pcellval, 256, 1000, 0 , 255));
  random1 = random(mval);

  cv_out= random1;


}
if (mode >=819 && mode<921){
  TCCR1B = B0000010;      
  i = 0;
  modeA = map(mode, 819, 920, 1, 100);
  modeAC = constrain (modeA, 1,100);    

  if (millis() - prev1 > modeAC ) {   
    prev1 = millis();   

    cv_out= majscale[mval];

  }

}
if (mode >=921){
  i = 0;
  TCCR1B = B0000011;           

  modeA = map(mode, 921, 1024, 1, 100);
  modeAC = constrain (modeA, 1,100);    

  if (millis() - prev1 > modeAC ) {   
    prev1 = millis();   

    cv_out= majscale[mval];

  }

}


if (ledpotval >=1021)
  {      led_out=255;
//digitalWrite(12, HIGH);
  }

  else  if (ledpotval >512 && ledpotval <1020){
    ledrate = map(ledpotval, 513, 1021, 300 , 1);
    ledrateC = constrain(ledrate, 1,300);
    if (millis() - prev2 > ledrateC) {
      prev2 = millis();

      led_out=rj;
      random2 = random(6);


      if (random2 <2){         
        rj-=32; 

      }
      if (random2 == 2){      
        rj+=32; 

      }
      if (random2 == 3){      
        rj+=64;  

      }
      if (random2 == 4){      
       rj=128;

     }
     if (random2 >= 5){      
       rj=0;

     }

   }
 }

 if (ledpotval <=512){
  ledrate = map(ledpotval, 0, 512, 45000 , 1);
  ledrateC = constrain(ledrate, 1,45000);
  if (micros() - prev2 > ledrateC) {
    prev2 = micros();      


    if (j>0){
      j+=20;    
      led_out=j;

    }
    if (j>=240){
      j=10;    
      //analogWrite(led2Pin, j);

    }  

  }}



  pwm_tick++;
  if(pwm_tick>4){
    pwm_tick=0;
  }

  if (pwm_tick==0){
    analogWrite (10, j+cv_out);
  }

  if(pwm_tick==1){
    analogWrite (12, pcellval<<2);

  }

  if(pwm_tick==2){
    analogWrite(LedPin, led_out);
  }

  if(pwm_tick==2){
    analogWrite(outPin, cv_out);
  }



}




