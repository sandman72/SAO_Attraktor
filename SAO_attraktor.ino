/*
  Runs the pixel animation on the Attraktor SAO Badge

  modified 10 Jan 2025
  by Frank Hellmann

  This example code is in the public domain.

  Works with CH32 MCU EVT Boards 1.0.4 or later (WCHLinkRV driver) or WCH32 Boards 0.0.2 (WinUSB driver)

  For the SAO Board you need to reflash the MCU with the WCH-LinkUtility once to disable the NRST functionality on pin PD7:
  "Disable mul-func, PD7 is used for IO func"

  Beware that the Eval Boards use pin PA1 and PA2 for external clock crystal and PD7 for Reset and therefore cannot be used for testing

  Pin PD1 is used for programming via SWDIO

*/

int count = 0;
int mode = 1;

// our output pins for charlieplexing on SAO board
int led_pins[] = {PD2,PD3,PD4,PD5,PD6,PD7,PA1};
int button = PD0;

// clear digital pins
void clear_led() {
  for (int i=0; i<7; i++) { 
    pinMode(led_pins[i], INPUT); 
  }
}

void set_led(int led){
  led=1+led+led/7;
  int row = led/7;
  int col = led%7;
  pinMode(led_pins[row], OUTPUT);
  digitalWrite(led_pins[row], LOW); 
  pinMode(led_pins[col], OUTPUT);
  digitalWrite(led_pins[col], HIGH); 
 }

// the setup function runs once when you press reset or power the board
void setup() {
  // disable external clock and free up pin PA1
  AFIO->PCFR1 = AFIO->PCFR1 & 0xFFFF7FFF;
  // initialize digital pins as floating, eg. input.
  clear_led();
  // initialize button input for mode change
  pinMode(D0,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  clear_led();
  set_led(count++);
  if (count>41) {
    count=0;
    if(mode>1){
      clear_led();
      delay(random(10000));
    }
  }
  if (mode>0) {
    if (count<22) { delayMicroseconds(1500 + count*500); }
    if (count>21) { delayMicroseconds(1500 + (42-count) * 500); }
    //delayMicroseconds(3500);
  }
}
