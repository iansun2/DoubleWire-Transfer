byte  rsync_pin = 2,
      rx_pin = 4,
      tsync_pin =2,
      tx_pin = 3,
      tsync_delay = 50;

void rx_setup(byte syncpin ,byte rxpin){
  rsync_pin = syncpin;
  rx_pin = rxpin;
  pinMode(rsync_pin,INPUT);
  pinMode(rx_pin,INPUT);
}

void tx_setup(byte syncpin ,byte txpin ,byte syncdelay){
  tsync_pin = syncpin;
  tx_pin = txpin;
  tsync_delay = syncdelay;
  pinMode(tsync_pin,OUTPUT);
  pinMode(tx_pin,OUTPUT);
  pinMode(tsync_delay,OUTPUT);
}

unsigned int rx_data(){
  byte ctrl = 0;
  unsigned int num =0;
    while(1){
      if(digitalRead(rsync_pin)){
        ctrl = 0;
      }else if(ctrl == 0 && digitalRead(rx_pin)){
        ctrl = 1;
      }else if(ctrl == 1 && !digitalRead(rx_pin)){
        ctrl = 2;
      }else if(ctrl == 2 && digitalRead(rx_pin)){
        break;
      }
    }
    for(byte i=0 ;i<16 ;i++){
      bool rx_bit = 0;
      while(digitalRead(rsync_pin) == i%2){}
      rx_bit = digitalRead(rx_pin);
      //Serial.print(rx_bit? "1":"0");
      if(rx_bit){
          int pow2 = 1;
          for(byte y=15-i; y>0 ;y--){
            pow2*=2;
          } 
          num += pow2;
        }
    }
    //if(num == 65535){tx_setup(tsync_pin,tx_pin,50);}
    //Serial.print("  ");
    return num;
}

void tx_data(unsigned int num){
    digitalWrite(tsync_pin,0);
    digitalWrite(tx_pin,1);
    delayMicroseconds(tsync_delay);
    digitalWrite(tx_pin,0);
    delayMicroseconds(tsync_delay);
    digitalWrite(tx_pin,1);
    delayMicroseconds(tsync_delay);
    for(byte i=0 ;i<16 ;i++){
      bool tx_bit = num & (0x8000 >> i);
      digitalWrite(tx_pin,tx_bit);
      digitalWrite(tsync_pin,(i+1)%2);
      delayMicroseconds(tsync_delay);
      //Serial.print(tx_bit? "1":"0");
    }
    //Serial.println(" ");
  }
