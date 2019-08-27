#ifndef Function_h
#define Function_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Motor{
    int encoder[4];
    int addrL, addrR;
    
  public:

    Motor(void){
      readEncoder();
      addrL = 0;
      addrR = 0;
      pinMode(ENCR1, INPUT);
      pinMode(ENCR2, INPUT);
      pinMode(ENCL1, INPUT);
      pinMode(ENCL2, INPUT);
      pinMode(DRL1, OUTPUT);
      pinMode(DRL2, OUTPUT);
      pinMode(DRR1, OUTPUT);
      pinMode(DRR2, OUTPUT);
    }

    int readEncoder(void){
      int arr[4];
      arr[0] = digitalRead(ENCL1);
      arr[1] = digitalRead(ENCL2);
      arr[2] = digitalRead(ENCR1);
      arr[3] = digitalRead(ENCR2);
      for(int i=0;i<4;i++){
        encoder[i] = arr[i];
      }
      return arr;
    }

    void update(void){
      int temp[4];
      for(int i=0;i<4;i++){
        temp[i] = encoder[i];
      }
      readEncoder();

      if(temp[0] == 0 and temp[1] == 1){
        if(encoder[0] == 0 and encoder[1] == 0){addrL++;}
        if(encoder[0] == 1 and encoder[1] == 1){addrL--;}
      }

      if(temp[2] == 0 and temp[3] == 1){
        if(encoder[2] == 0 and encoder[3] == 0){addrL++;}
        if(encoder[2] == 1 and encoder[3] == 1){addrL--;}
      }
    }
  
    void drive(int l,int r){
      if(l > 255 or r > 255){
        return;
      }
      if (l == 0){
        analogWrite(DRL1, 255);
        analogWrite(DRL2, 255);
      }
      if (r == 0){
        analogWrite(DRR1, 255);
        analogWrite(DRR2, 255);
      }
      if (l > 0){
        analogWrite(DRL1, l);
        analogWrite(DRL2, 0);
      }
      if (l < 0){
        analogWrite(DRL1, 0);
        analogWrite(DRL2, l);
      }
      if (r > 0){
        analogWrite(DRR1, r);
        analogWrite(DRR2, 0);
      }
      if (r < 0){
        analogWrite(DRR1, 0);
        analogWrite(DRR2, r);
      }
    }
};




#endif
