byte sync_pin = 2,rx_pin = 4;

void rx_setup(byte sync,byte rx){
  sync_pin = sync;
  rx_pin = rx;
}

unsigned int rx_data(){
  byte ctrl = 0;
  unsigned int num =0;
    while(1){
        
      if(digitalRead(sync_pin)){
        ctrl = 0;
      }
      else if(ctrl == 0 && digitalRead(rx_pin)){
        ctrl = 1;
      }else if(ctrl == 1 && !digitalRead(rx_pin)){
        ctrl = 2;
      }else if(ctrl == 2 && digitalRead(rx_pin)){
        break;
      }
    }
    for(byte i=0 ;i<16 ;i++){
      bool rx_bit = 0;
      while(digitalRead(sync_pin) == i%2){}
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
   
    //Serial.print("  ");
    return num;
}
