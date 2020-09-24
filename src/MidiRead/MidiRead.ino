#include <SimpleTimer.h>
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();
int d1,d2,tmr0,tmr1,tmr2;
long cnt;
byte type;
bool cr=true;
SimpleTimer Timer;

void htrace() {
  Serial.print(".");
  cr=false;
}
void ltrace() {
  Serial.println("");
  Timer.enable(tmr1);
  cr=true;
}

void setup() {
   MIDI.begin(MIDI_CHANNEL_OMNI);
   Serial.begin(115200);
   Serial.println("MIDI Input Test");
   
   tmr1=Timer.setInterval(3000, htrace);
   tmr2=Timer.setInterval(60000, ltrace);
}

void loop() {
  Timer.run();
  if (MIDI.read()){
    byte type = MIDI.getType();
    d1 = MIDI.getData1();
    d2 = MIDI.getData2();
    if (type < 254) {
      if (!cr) {
        Serial.println("");
        cr=true;
      }
      Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
      Timer.disable(tmr1);
      Timer.restartTimer(tmr2);
    }
  }
}
