//---------------------- adapt as needed---------------------------------------------
int dim = 8 //dim x dim x dim cube
int dimPlane=64
int amountZSR=1 // amount of SRs (Shift Registers) for selecting a plane (Zaxis)
int amountXYSR=8 // amount of SRs to drive all leds in 1 plane (dim x dim)
//-----------------------------------------------------------------------------------

int data[dimPlane]={}

int latchPinZ[amountZSR]={} #check digital pin nrs
int latchPinXY[amountXYSR]={}
int clockPinZ[amountZSR]={}
int clockPinXY[amountXYSR]={}
int dataPinZ[amountZSR]={}
int dataPinXY[amountXYSR]={}

//byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

unsigned long previousTime1 = millis();
long timeInterval1 = 1000;
unsigned long previousTime2 = millis();
long timeInterval2 = 1000;
int SR= 0
int PL= 0

void setup() {
  // Set all the pins of 74HC595 as OUTPUT
  for(int i = 0; i<amountZSR+1; i++)
  {
    pinMode(latchPinZ[i], OUTPUT);
    pinMode(clockPinZ[i], OUTPUT);
    pinMode(dataPinZ[i], OUTPUT);
  } 
  for(int i = 0; i<amountXYSR+1; i++)
  {
    pinMode(latchPinXY[i], OUTPUT);
    pinMode(clockPinXY[i], OUTPUT);
    pinMode(dataPinXY[i], OUTPUT);
  } 
}

void loop() {
  // keep track of time
  unsigned long currentTime = millis();

  //altijd doen:
  getData() //store nieuwe data in de data var die je vorige keer weggeschreven hebt
  sendDataToSR(SR) // send data to 1 vd shift regs
  SR=SR+1

  //als plane bijna volledig ingeladen
  if(SR == dimPlane-1){
    deselectPlane() //leg alle planes af (zodat strx als nieuw plane aan gaat er geen 2 tegelijk aan staan)
  }

  //na 1 plane:
  if (SR == dimPlane){//SR is 0 voor 1e SR, enz
    //event wacht hier 1 clockcyclus (test of dit nodig is)
    latchSRs() //hele plane zit in de SRs nu mag de data ook naar output SR
    selectPlane(PL) //zet ook het plane aan
    PL=PL+1
    SR=0 //start voor volgende plane inladen terug bij SR 0
    }
  }

  //na een volledige cube
  if (PL == dim){
    PL=0 
    //hier nieuwe data inladen zou ik niet doen als dit te lang duurt (als we het zelf construeren op het moment) als het uit geheugen gehaald wordt is het veel sneller en kan je dat mss wel doen
    //nu laden we eigl constant nieuwe data in (uit geheugen) per 8 1/0'en 
  }
  /* //later kunnen we ipv taken te doen als SR of PL aan een bepaald getal zitten, werken met timing, dan is er zeker een vaste framerate enzo
  // task 1 : load data to be printed to leds
  if(currentTime - previousTime1 > timeInterval1) {
    previousTime1 = currentTime;
     // updates 

  // task 2
  if(currentTime - previousTime2 > timeInterval2) {
    previousTime2 = currentTime;
    */

}
