#define sync_pin 2
#define tx_pin 3
#define sync_delay 400 //us

void setup() {
  //Serial.begin(115200);
  pinMode(sync_pin,OUTPUT);
  pinMode(tx_pin,OUTPUT);
  digitalWrite(sync_pin,0);
  digitalWrite(tx_pin,0);
}

  int tx_data(int num){
    digitalWrite(sync_pin,0);
    delayMicroseconds(sync_delay);
    digitalWrite(tx_pin,1);
    delayMicroseconds(sync_delay);
    digitalWrite(tx_pin,0);
    delayMicroseconds(sync_delay);
    digitalWrite(tx_pin,1);
    delayMicroseconds(sync_delay);
    for(int i=0 ;i<16 ;i++){
      bool tx_bit = num & (0x8000 >> i);
      digitalWrite(tx_pin,tx_bit);
      digitalWrite(sync_pin,1);
      delayMicroseconds(sync_delay);
      digitalWrite(sync_pin,0);
      //Serial.print(tx_bit? "1":"0");
    }
    //Serial.println(" ");
  }
  
void loop() {
  for(long int i=32700 ;i<65535 ;i++){
    tx_data(i);
    //Serial.println(i);
    //delay(1);
  }
  
}
