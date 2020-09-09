/*
#define sync_pin 2
#define rx_pin 4

void setup() {
  Serial.begin(115200);
  pinMode(sync_pin,INPUT);
  pinMode(rx_pin,INPUT);
}
*/
int sync_pin = 2,rx_pin = 4;

void rx_setup(int sync,int rx){
  sync_pin = sync;
  rx_pin = rx;
}

int rx_data(){
  char rx_bin[16] = {0};
  int ctrl = 0;
  unsigned int num =0;
    while(1){
      if(ctrl == 0 && digitalRead(rx_pin)){
        ctrl = 1;
      }else if(ctrl == 1 && !digitalRead(rx_pin)){
        ctrl = 2;
      }else if(ctrl == 2 && digitalRead(rx_pin)){
        break;
      }
    }

    for(int i=0 ;i<16 ;i++){
      bool rx_bit = 0;
      while(!digitalRead(sync_pin)){}
      rx_bit = digitalRead(rx_pin);
      rx_bit? rx_bin[i] = '1':rx_bin[i] = '0';
      Serial.print(rx_bit? "1":"0");
      if(rx_bit){
          int pow2 = 1;
          for(int y=15-i; y>0 ;y--){
            pow2*=2;
          } 
          num += pow2;
        }
      while(digitalRead(sync_pin)){}
    }
    //Serial.print(rx_bin);
    //Serial.print("  ");
    //Serial.println(num);
    return num;
}
