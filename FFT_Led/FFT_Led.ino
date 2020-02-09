#include <arduinoFFT.h>

#define SAMPLES 64            //Must be a power of 2
#define DATA_PIN  11  // Data pin to communicate with display
#define CS_PIN    10  // Control pin to communicate with display
#define  xres 3      // Total number of  columns in the display, must be <= SAMPLES/2

 
double vReal[SAMPLES];
double vImag[SAMPLES];
char data_avgs[xres];


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


arduinoFFT FFT = arduinoFFT();                                    // FFT object
 


void setup() {
    Serial.begin(115200);
    ADCSRA = 0b11100101;      // set ADC to free running mode and set pre-scalar to 32 (0xe5)
    ADMUX = 0b00000000;       // use pin A0 and external voltage reference
    delay(50);            // wait to get reference voltage stabilized
}
 
void loop() {
   // ++ Sampling
   for(int i=0; i<SAMPLES; i++)
    {
      while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
      ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
      //int value = ADC - 512 ;                 // Read from ADC and subtract DC offset caused value
      vReal[i]= ADC;                      // Copy to bins after compressing
      vImag[i] = 0;                         
    }
    // -- Sampling

 
    // ++ FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    // -- FFT

    
    // ++ re-arrange FFT result to match with section of frequencies
    int step = (SAMPLES/2)/xres; 
    int c=0;
    for(int i=0; i<(SAMPLES/2); i+=step)  
    {
      data_avgs[c] = 0;
      for (int k=0 ; k< step ; k++) {
          Serial.print(i+k); // the starting frequency
          Serial.print("\t"); //
          Serial.println(vReal[i+k]); // the spectrum value
          data_avgs[c] = data_avgs[c] + vReal[i+k];
      }
      data_avgs[c] = data_avgs[c]/step; 
      c++;
    }
    // -- re-arrange FFT result to match with no. of columns on display ( xres )

    
    // ++ send to display according measured value 
    for(int i=0; i<xres; i++)
    {
      //data_avgs[i] = constrain(data_avgs[i],0,80);            // set max & min values for buckets
      data_avgs[i] = map(data_avgs[i], 0, 1023, 0, 255);        // remap averaged values to yresu
   
      /*
       * THis is where you change RGB strip accordininglg
       */
     }
     // -- send to display according measured value 
     
} 
