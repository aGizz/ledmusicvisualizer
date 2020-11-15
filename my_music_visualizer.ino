//Tells arduino that it needs the fastLED library
#include <FastLED.h>

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

//How many LEDs?
#define NUM_LEDS 150
//Which pin are the lights in
#define DATA_PIN 6
//Led type
#define LED_TYPE WS2812B
//what order the colors are in
#define COLOR_ORDER GRB
//starting brightness
#define BRIGHTNESS 250
//Memory or something? idk
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int i;

//variable for scrolling color
int k;





void setup() {
/********************************SHIELD SETUP*************************/
 //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  digitalWrite(RESET, LOW);
  delay(5);

  Serial.begin(9600);
/*******************************LED SETUP********************************/

FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.setBrightness( BRIGHTNESS );


  //start everything as black
    FastLED.showColor(CRGB::Black);
}

void loop() {
/***********************************************************SHIELD THANGS**********************************************/

    Read_Frequencies(); //execute user defined function
    Graph_Frequencies(); //execute user defined function
    
    //lights  
if ((Frequencies_One[i] + Frequencies_Two[i]) / 2 > 1){
  
  //First frequency and Segment
   for (int f = 0; f < NUM_LEDS / 7 * 1; f++) {
  leds[f] = CHSV(0,255,(Frequencies_One[1] + Frequencies_Two[1]) / 10);
  }

  //Second frequency and Segment
  for (int s = NUM_LEDS / 7 * 1; s < NUM_LEDS / 7 * 2; s++) {
  leds[s] = CHSV(21,255,(Frequencies_One[2] + Frequencies_Two[2]) / 12);
  }

  //Third frequency and Segment
  for (int t = NUM_LEDS / 7 * 2; t < NUM_LEDS / 7 * 3; t++) {
  leds[t] = CHSV(43,255,(Frequencies_One[3] + Frequencies_Two[3]) / 14);
  }

  //Fourth frequency and Segment
  for (int o = NUM_LEDS / 7 * 3; o < NUM_LEDS / 7 * 4; o++) {
  leds[o] = CHSV(85,255,(Frequencies_One[4] + Frequencies_Two[4]) / 16);
  }

  //Fifth frequency and Segment
  for (int h = NUM_LEDS / 7 * 4; h < NUM_LEDS / 7 * 5; h++) {
  leds[h] = CHSV(127,255,(Frequencies_One[5] + Frequencies_Two[5]) / 10);
  }

  //Sixth frequency and Segment
  for (int x = NUM_LEDS / 7 * 5; x < NUM_LEDS / 7 * 6; x++) {
  leds[x] = CHSV(169,255,(Frequencies_One[6] + Frequencies_Two[6]) / 8.5);
  }

  //Seventh frequency and Segment
  for (int v = NUM_LEDS / 7 * 6; v < NUM_LEDS; v++) {
  leds[v] = CHSV(184,255,(Frequencies_One[7] + Frequencies_Two[7]) / 4.5);
  }

  FastLED.show();
}
else {
FastLED.showColor(CRGB::Black);
}

//reduces twitchyness
  delay(3);
  }


///////////////user defined things//////////////////////

  //Defining Read_Frequencies
  void Read_Frequencies() {
    digitalWrite(RESET, HIGH);
    delayMicroseconds(200);
    digitalWrite(RESET, LOW);
    delayMicroseconds(200);
  
    //Read frequencies for each band
    for (freq_amp = 0; freq_amp < 7; freq_amp++)
    {
      digitalWrite(STROBE, HIGH);
      delayMicroseconds(50);
      digitalWrite(STROBE, LOW);
      delayMicroseconds(50);
  
      Frequencies_One[freq_amp] = analogRead(DC_One);
      Frequencies_Two[freq_amp] = analogRead(DC_Two);
    }
  }
  //Defining Graph_Frequencies
  void Graph_Frequencies() {
    for (i = 0; i < 7; i++)
    {
      Serial.print( (Frequencies_One[i] + Frequencies_Two[i]) / 2 );
      Serial.print("    ");
    }
    Serial.println();
}
