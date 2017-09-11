
int flow_sensor = 2;
int lastVal = 0;

bool once = false;
unsigned long flowCount = 0;
int HiLo = 0;
int LoHi = 0;
int hiVal = 0;
int delayTick = 10;

void setup() {
  Serial.begin(9600);
  pinMode(flow_sensor, INPUT);
  lastVal = digitalRead(flow_sensor);

  
}

void loop() {

  int flowVal = digitalRead(flow_sensor);
  unsigned long ts;
  byte buf[2];
 
  once = true; // once is switched off
  
  if (flowVal != lastVal) {
    // We are counting the number of LO to HI transition
    // So if last read was LOW and now the read is HI then we
    // know how much water passed thru the meter.
    if (flowVal == HIGH){  
      // lastVal is LOW
      LoHi++;
      flowCount++;
      ts = millis();
      Serial.write((byte *)&ts, sizeof(ts));
      buf[0]=',';
      Serial.write((byte *)buf, 1);
      Serial.write((byte *)&flowCount, sizeof(flowCount));
      Serial.println(" ");
    } 

    if (flowVal == LOW) {
       HiLo++;
       //we don't count this
    }
  }
  lastVal = flowVal;
  delay(delayTick);
}
