#include <Bounce.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       oneB;           //xy=465,1775
AudioSynthWaveform       twoB;           //xy=470,1808
AudioSynthNoisePink      noiseA;         //xy=473,1682
AudioSynthWaveform       oneA;           //xy=475,1628
AudioSynthWaveform       twoA;           //xy=476,1657
AudioSynthWaveform       oneC;           //xy=478,1937
AudioSynthNoisePink      noiseB;         //xy=479,1851
AudioSynthWaveform       twoC;           //xy=479,1975
AudioSynthNoisePink      noiseC;         //xy=480,2010
AudioSynthWaveform       twoH;           //xy=492,2815
AudioSynthWaveform       oneH;           //xy=497,2773
AudioSynthNoisePink      noiseD;         //xy=502,2203
AudioSynthWaveform       oneD;           //xy=504,2131
AudioSynthWaveform       twoD;           //xy=504,2165
AudioSynthWaveform       twoE;           //xy=504,2346
AudioSynthWaveform       twoG;           //xy=503,2661
AudioSynthWaveform       oneE;           //xy=505,2310
AudioSynthNoisePink      noiseG;         //xy=504,2699
AudioSynthWaveform       twoF;           //xy=505,2492
AudioSynthNoisePink      noiseF;         //xy=505,2535
AudioSynthWaveform       oneG;           //xy=505,2626
AudioSynthNoisePink      noiseH;         //xy=508,2864
AudioSynthWaveform       oneF;           //xy=511,2456
AudioSynthNoisePink      noiseE;         //xy=519,2390
AudioMixer4              Hmixer;         //xy=621,2800
AudioMixer4              Amixer;         //xy=639,1660
AudioMixer4              Gmixer;         //xy=648,2639
AudioMixer4              Fmixer;         //xy=650,2477
AudioMixer4              Bmixer;         //xy=654,1778
AudioMixer4              Cmixer;         //xy=655,1977
AudioMixer4              Dmixer;         //xy=670.2857284545898,2125.9999980926514
AudioMixer4              Emixer;         //xy=676,2315
AudioFilterStateVariable Hfilter;        //xy=698.5713996887207,2737.14284324646
AudioFilterStateVariable Gfilter;        //xy=708.5714416503906,2581.4286317825317
AudioFilterStateVariable Afilter;        //xy=741,1563
AudioFilterStateVariable Cfilter;        //xy=746.285701751709,1906.0000553131104
AudioFilterStateVariable Efilter;        //xy=749.9999885559082,2239.9999618530273
AudioFilterStateVariable Bfilter;        //xy=760.5714225769043,1734.8571662902832
AudioEffectEnvelope      envelope8;      //xy=758,2787
AudioFilterStateVariable Dfilter;        //xy=769.9999999999999,2070
AudioFilterStateVariable Ffilter;        //xy=775.7143783569336,2464.285671234131
AudioEffectEnvelope      envelope6;      //xy=786,2392
AudioEffectEnvelope      envelope3;      //xy=811,1988
AudioEffectEnvelope      envelope5;      //xy=816,2309
AudioEffectEnvelope      envelope1;      //xy=826,1658
AudioEffectEnvelope      envelope4;      //xy=826,2126
AudioEffectEnvelope      envelope2;      //xy=835,1783
AudioEffectEnvelope      envelope7;      //xy=835,2547
AudioAnalyzePeak         peak8;          //xy=895,2752
AudioAnalyzePeak         peak7;          //xy=931,2617
AudioAnalyzePeak         peak6;          //xy=932,2427
AudioAnalyzePeak         peak3;          //xy=941,1961
AudioAnalyzePeak         peak1;          //xy=952,1617
AudioAnalyzePeak         peak2;          //xy=958,1747
AudioAnalyzePeak         peak5;          //xy=976,2268
AudioAnalyzePeak         peak4;          //xy=983,2096
AudioMixer4              mixer1;         //xy=1113,1931
AudioMixer4              mixer2;         //xy=1199,2548
AudioMixer4              mixer3;         //xy=1225.6667556762695,2033.3333358764648
AudioEffectDelay         delay1;         //xy=1261.6667556762695,2243.3332595825195
AudioMixer4              mixer4;         //xy=1408.3334350585938,2245.0000076293945
AudioEffectChorus        chorus1;        //xy=1438.333309173584,2001.6665840148926
AudioOutputI2S           i2s1;           //xy=1598.3333148956299,2163.333251953125
AudioConnection          patchCord1(oneB, 0, Bmixer, 0);
AudioConnection          patchCord2(twoB, 0, Bmixer, 1);
AudioConnection          patchCord3(noiseA, 0, Amixer, 2);
AudioConnection          patchCord4(oneA, 0, Amixer, 0);
AudioConnection          patchCord5(twoA, 0, Amixer, 1);
AudioConnection          patchCord6(oneC, 0, Cmixer, 0);
AudioConnection          patchCord7(noiseB, 0, Bmixer, 2);
AudioConnection          patchCord8(twoC, 0, Cmixer, 1);
AudioConnection          patchCord9(noiseC, 0, Cmixer, 2);
AudioConnection          patchCord10(twoH, 0, Hmixer, 1);
AudioConnection          patchCord11(oneH, 0, Hmixer, 0);
AudioConnection          patchCord12(noiseD, 0, Dmixer, 2);
AudioConnection          patchCord13(oneD, 0, Dmixer, 0);
AudioConnection          patchCord14(twoD, 0, Dmixer, 1);
AudioConnection          patchCord15(twoE, 0, Emixer, 1);
AudioConnection          patchCord16(twoG, 0, Gmixer, 1);
AudioConnection          patchCord17(oneE, 0, Emixer, 0);
AudioConnection          patchCord18(noiseG, 0, Gmixer, 2);
AudioConnection          patchCord19(twoF, 0, Fmixer, 1);
AudioConnection          patchCord20(noiseF, 0, Fmixer, 2);
AudioConnection          patchCord21(oneG, 0, Gmixer, 0);
AudioConnection          patchCord22(noiseH, 0, Hmixer, 2);
AudioConnection          patchCord23(oneF, 0, Fmixer, 0);
AudioConnection          patchCord24(noiseE, 0, Emixer, 2);
AudioConnection          patchCord25(Hmixer, 0, Hfilter, 0);
AudioConnection          patchCord26(Amixer, 0, Afilter, 0);
AudioConnection          patchCord27(Gmixer, 0, Gfilter, 0);
AudioConnection          patchCord28(Fmixer, 0, Ffilter, 0);
AudioConnection          patchCord29(Bmixer, 0, Bfilter, 0);
AudioConnection          patchCord30(Cmixer, 0, Cfilter, 0);
AudioConnection          patchCord31(Dmixer, 0, Dfilter, 0);
AudioConnection          patchCord32(Emixer, 0, Efilter, 0);
AudioConnection          patchCord33(Hfilter, 0, envelope8, 0);
AudioConnection          patchCord34(Gfilter, 0, envelope7, 0);
AudioConnection          patchCord35(Afilter, 0, envelope1, 0);
AudioConnection          patchCord36(Cfilter, 0, envelope3, 0);
AudioConnection          patchCord37(Efilter, 0, envelope5, 0);
AudioConnection          patchCord38(Bfilter, 0, envelope2, 0);
AudioConnection          patchCord39(envelope8, 0, mixer2, 3);
AudioConnection          patchCord40(envelope8, peak8);
AudioConnection          patchCord41(Dfilter, 0, envelope4, 0);
AudioConnection          patchCord42(Ffilter, 0, envelope6, 0);
AudioConnection          patchCord43(envelope6, 0, mixer2, 1);
AudioConnection          patchCord44(envelope6, peak6);
AudioConnection          patchCord45(envelope3, 0, mixer1, 2);
AudioConnection          patchCord46(envelope3, peak3);
AudioConnection          patchCord47(envelope5, 0, mixer2, 0);
AudioConnection          patchCord48(envelope5, peak5);
AudioConnection          patchCord49(envelope1, peak1);
AudioConnection          patchCord50(envelope1, 0, mixer1, 0);
AudioConnection          patchCord51(envelope4, 0, mixer1, 3);
AudioConnection          patchCord52(envelope4, peak4);
AudioConnection          patchCord53(envelope2, 0, mixer1, 1);
AudioConnection          patchCord54(envelope2, peak2);
AudioConnection          patchCord55(envelope7, 0, mixer2, 2);
AudioConnection          patchCord56(envelope7, peak7);
AudioConnection          patchCord57(mixer1, 0, mixer3, 0);
AudioConnection          patchCord58(mixer2, 0, mixer3, 1);
AudioConnection          patchCord59(mixer3, chorus1);
AudioConnection          patchCord60(mixer3, delay1);
AudioConnection          patchCord61(delay1, 0, mixer4, 0);
AudioConnection          patchCord62(delay1, 1, mixer4, 1);
AudioConnection          patchCord63(delay1, 2, mixer4, 2);
AudioConnection          patchCord64(mixer4, 0, mixer3, 2);
AudioConnection          patchCord65(chorus1, 0, i2s1, 0);
AudioConnection          patchCord66(chorus1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=950,2894
// GUItool: end automatically generated code
// GUItool: end automatically generated code



//waveforms
AudioSynthWaveform *voiceOne[8] = {
  &oneA,&oneB,&oneC,
  &oneD,&oneE,&oneF,
  &oneG,&oneH,
};

//waveforms
AudioSynthWaveform *voiceTwo[8] = {
  &twoA,&twoB,&twoC,
  &twoD,&twoE,&twoF,
  &twoG,&twoH,
};

//waveforms
AudioSynthNoisePink *noise[8] = {
  &noiseA,&noiseB,&noiseC,
  &noiseD,&noiseE,&noiseF,
  &noiseG,&noiseH,
};

//filter envelope
AudioEffectEnvelope *envs[8] = {
  &envelope1,&envelope2,&envelope3,&envelope4,
  &envelope5,&envelope6,&envelope7,&envelope8,
};

//peaks
AudioAnalyzePeak *peaks[8] = {
  &peak1,&peak2,&peak3,&peak4,
  &peak5,&peak6,&peak7,&peak8,
};

//voice mixers
AudioMixer4 *voice_mixers[8] = {
  &Amixer,&Bmixer,&Cmixer,&Dmixer,
  &Emixer,&Fmixer,&Gmixer,&Hmixer,
};

AudioFilterStateVariable *lfo_filter[8]={
  &Afilter,&Bfilter,&Cfilter,&Dfilter,
  &Efilter,&Ffilter,&Gfilter,&Hfilter,
  
};
//frequencies for each of the "waveforms" or voices-
float frequency[8];
float voicePeaks[8];
int voiceNum;
bool voiceUsed[8] = {false};
const float DIV127 = (1.0 / 127.0);

//KNOBS
int voice_one_knob = 21;
int voice_two_knob = 20;
int attack_knob = 19;
int release_knob = 18;
int filter_freq_knob=17;
int filter_res_knob = 16;

//int delay_feedback_knob = 15;
//int detune_knob = 14;

//BUTTON
int shift_button = 10;

float octave =1;

int attack_val =10;
int decay_val =100;
float sustain_val =0.1;
int release_val =100;

float voice_one_val =0.5;
float detune =0.0;
float noise_voice = 0.0;

float delay_feedback= 0.0;
float delay_time = 0.0;

unsigned int LFOspeed = 2000;
float LFOpitch = 1;
float LFOdepth = 0;
byte LFOmodeSelect = 0;
int FILfreq =  10000;
float FILfactor = 1;


///CHORUS INITS////

// Number of samples in each delay line
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delayline[CHORUS_DELAY_LENGTH];
// number of "voices" in the chorus which INCLUDES the original voice
int n_chorus = 1;


int lowestAmp(){
  int index = 0;
  for (int i = 0; i < 8; i++){
    if (!voiceUsed[i]) return i;
    if ((voicePeaks[i] < voicePeaks[index])) {
      index = i;
    }
  }
  
  return index;
}

float mapfloat(long x, long in_min, long in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void OnNoteOn(byte channel, byte note, byte velocity){
  Serial.println("aONNOTEON: ");
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  AudioNoInterrupts();
  voiceNum = lowestAmp();
  voiceUsed[voiceNum] = freq;
  frequency[voiceNum] = freq; 
  
  Serial.print("NOTEON: ");
  Serial.println(voiceNum);
  
  envs[voiceNum]->noteOn();
  AudioInterrupts();
  oscSet();
  LFOupdate(true, LFOmodeSelect, FILfactor, LFOdepth);
}


void OnNoteOff(byte channel, byte note, byte velocity){
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  AudioNoInterrupts();
   for (int i = 0; i < 8; ++i){
    if( (frequency[i]== freq) && (voiceUsed[i])){
        voiceUsed[i] = 0;
        envs[i]->noteOff();
        Serial.print("NOTEOFF: ");
        Serial.println(i);
     }
   }
  AudioInterrupts();
};

void set_voice_mix(float voice_one, float voice_two, float noise_val){
  Amixer.gain(0, voice_one);
  Amixer.gain(1, voice_two);
  Amixer.gain(2, noise_val);
      
  Bmixer.gain(0, voice_one);
  Bmixer.gain(1, voice_two);
  Bmixer.gain(2, noise_val);
  
  Cmixer.gain(0, voice_one);
  Cmixer.gain(1, voice_two);
  Cmixer.gain(2, noise_val); 

  Dmixer.gain(0, voice_one);
  Dmixer.gain(1, voice_two);
  Dmixer.gain(2, noise_val); 

  Emixer.gain(0, voice_one);
  Emixer.gain(1, voice_two);
  Emixer.gain(2, noise_val); 
  
  Fmixer.gain(0, voice_one);
  Fmixer.gain(1, voice_two);
  Fmixer.gain(2, noise_val); 
  
  Gmixer.gain(0, voice_one);
  Gmixer.gain(1, voice_two);
  Gmixer.gain(2, noise_val); 
  
  Hmixer.gain(0, voice_one);
  Hmixer.gain(1, voice_two);
  Hmixer.gain(2, noise_val); 
}

//Bounce shift_b = Bounce(shift_button, 10);

void setup() {
  
  
  Serial.begin(9600); 
  AudioMemory(150);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  // put your setup code here, to run once:
  
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  for (int i=0; i <8; i++){
   //Envelopes
   envs[i]->delay(0);
   envs[i]->attack(10);
   envs[i]->decay(100);
   envs[i]->hold(0);
   envs[i]->sustain(1);
   envs[i]->release(10);
   envs[i]->releaseNoteOn(6);
   voiceOne[i]->begin(0.25,0,WAVEFORM_SINE);
   voiceTwo[i]->begin(0.25,0,WAVEFORM_SINE);
   noise[i]->amplitude(noise_voice);

  }
  

  
  mixer1.gain(0, 0.25);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);
  mixer2.gain(0, 0.25);
  mixer2.gain(1, 0.25);
  mixer2.gain(2, 0.25);
  mixer2.gain(3, 0.25);
  
  mixer3.gain(0, 0.33);
  mixer3.gain(1, 0.33);
  mixer3.gain(2, 0.33);

  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0.5);
 mixer4.gain(2, 0.5);
  
//delay-
  delay1.delay(0,0);
  set_voice_mix(0.3,0.3,0.3);
  
  //KNOBS


  chorus1.begin(delayline,CHORUS_DELAY_LENGTH,1);

//  reverb1.reverbTime(0);
  pinMode(shift_button, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    //MIDI In
//    Serial.println(analogRead(attack_knob));
  usbMIDI.read();
  AudioNoInterrupts();
// 
  LFOupdate(false, LFOmodeSelect, FILfactor, LFOdepth);
  



//  if (shift_b.update()){
//    if (shift_b.fallingEdge()){
//      delay_feedback = mapfloat(analogRead(delay_knob), 0, 1023, 0, 0.3);
//    }
//    delay(100);
//  }

//  set_voice_mix(voice_one_val, 1-voice_one_val, noise_voice);

    updateKnob();
    
    
    delay1.delay(0, delay_time);
    delay1.delay(1, delay_time);
    delay1.delay(2, delay_time);
    mixer3.gain(2, delay_feedback);

 
  
  for (int i=0; i <8; i++){
  
    oscSet();   
    envs[i]->attack(attack_val);
    envs[i]->release(release_val);
    envs[i]->decay(decay_val);
    envs[i]->sustain(sustain_val);
    
    if(peaks[i]->available()){
      voicePeaks[i] = peaks[i]->read();
    }
    
  }
  
  
   AudioInterrupts();
}   


void updateKnob(){

  attack_val = map(analogRead(attack_knob), 0, 1023, 20, 11000);
////  Serial.println(attack_val);

  release_val = map(analogRead(release_knob), 0, 1023, 100, 11000);
//  sustain_val = map(analogRead(release_knob), 0, 1023, 100, 11000);
  for (int p=0;p<8;p++){
  voiceOne[p]->amplitude(mapfloat(analogRead(voice_one_knob), 0, 1023, 0.0, 1.0) );
  voiceTwo[p]->amplitude(mapfloat(analogRead(voice_two_knob), 0, 1023, 0.0, 1.0) );
//  lfo_filter[p]->frequency(map(analogRead(filter_freq_knob), 0 ,127, 0, 10000));
//  lfo_filter[p]->resonance(mapfloat(analogRead(filter_res_knob), 0 ,127, 0.7, 5.0));
  }


////  delay_feedback = mapfloat(analogRead(delay_feedback_knob), 0 ,127, 0, 0.33);
//
//  detune = mapfloat(analogRead(detune_knob), 0, 1023, 0.0, 10.0);

  
}
void myControlChange(byte channel, byte control, byte value) {
  Serial.println(channel);
  Serial.println(value);
  switch (control) {
    case 100:
      for (int p = 0; p<8; p++ ){
        voiceOne[p]->amplitude(value * DIV127);
      }
        break;
  
    case 101:
        
      for (int p = 0; p<8; p++ ){
        voiceTwo[p]->amplitude(value * DIV127);
      }
      break;

    case 102:
      for (int p = 0; p<8; p++ ){
        noise[p]->amplitude(value * DIV127);
      }
      break;

    case 103:
      switch (value) {
        case 0:
          octave = 0.25;
          break;
        case 1:
          octave = 0.5;
          break;
        case 2:
          octave = 1;
          break;
        case 3:
          octave = 2;
          break;
        case 4:
          octave = 4;
          break;
      }

      break;

    case 104:
     attack_val = 3000 * (value * DIV127);
//      for (int i=0; i <8; i++){
//        envs[i]->attack(3000 * (value * DIV127));
//      }
      break;

    case 105:
      decay_val = (3000 * (value * DIV127));
      break;

    case 106:
      sustain_val = (value * DIV127);
      break;

    case 107:
      release_val = map(value, 0, 127, 100, 11000);
     
      break;

    case 108:
      switch (value) {
        case 0:
          for (int i=0; i <8; i++){
            voiceOne[i]->begin(0.25,0,WAVEFORM_SINE);
          }
          break;
        case 1:
          for (int i=0; i <8; i++){
            voiceOne[i]->begin(0.25,0,WAVEFORM_TRIANGLE);
          }          
          break;
        case 2:
          for (int i=0; i <8; i++){
            voiceOne[i]->begin(0.25,0,WAVEFORM_SAWTOOTH);
          }    
          break;
        case 3:
          for (int i=0; i <8; i++){
            voiceOne[i]->begin(0.25,0,WAVEFORM_PULSE);
          }   
          break;
      } 
      oscSet();
      break;
    case 109:
      switch (value) {
        case 0:
          for (int i=0; i <8; i++){
            voiceTwo[i]->begin(0.25,0,WAVEFORM_SINE);
          }
          break;
        case 1:
          for (int i=0; i <8; i++){
            voiceTwo[i]->begin(0.25,0,WAVEFORM_TRIANGLE);
          }          
          break;
        case 2:
          for (int i=0; i <8; i++){
            voiceTwo[i]->begin(0.25,0,WAVEFORM_SAWTOOTH);
          }    
          break;
        case 3:
          for (int i=0; i <8; i++){
            voiceTwo[i]->begin(0.25,0,WAVEFORM_PULSE);
          }   
          break;
      }
     case 111:
     
        FILfactor = value * DIV127;
        FILfreq = 10000 * (value * DIV127);
        if (LFOmodeSelect < 1 || LFOmodeSelect > 5){
          for (int i=0; i <8; i++){
         lfo_filter[i]->frequency(FILfreq);
        }
       }
      break;

    case 112:
       for (int i=0; i <8; i++){
        lfo_filter[i]->resonance((4.3 * (value * DIV127)) + 0.7);
       }
      
      break;
      
    case 114:
      {
        float xSpeed = value * DIV127;
        xSpeed = pow(100, (xSpeed - 1));
        LFOspeed = (70000 * xSpeed);
        break;
      }

    case 115:
      LFOdepth = value * DIV127;
      break;

    case 116:
      LFOmodeSelect = value;
      break;
      
     case 117:
      delay_time = map(value,0,127,0,3000);
      break;

    case 118:
      delay_feedback = mapfloat(value, 0 ,127, 0, 0.33);
      break;
      
  }
}

void LFOupdate(bool retrig, byte mode, float FILtop, float FILbottom) {
  static float LFO = 0;
  static unsigned long LFOtime = 0;
  static bool LFOdirection = false;
  unsigned long currentMicros = micros();
  static bool LFOstop = false;
  static float LFOrange = 0;
  static byte oldMode = 0;
  static bool retriggered = false;

  if (retrig == true) retriggered = true;


  if (currentMicros - LFOtime >= LFOspeed) {
    LFOtime = currentMicros;

    if (mode != oldMode) {
      if (mode == 0 || mode == 8) {
        LFOpitch = 1;
        oscSet();

       for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(FILfreq);
       }
      }
      else if (mode >= 1 || mode <= 7) {
        LFOpitch = 1;
        oscSet();
      }
      else if (mode >= 9 || mode <= 13) {
        
       for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(FILfreq);
       }
      }
      oldMode = mode;
    }

    LFOrange = FILtop - FILbottom;
    if (LFOrange < 0) LFOrange = 0;

    // LFO Modes
    switch (mode) {

      case 0: //Filter OFF
        return;
        break;
      case 1: //Filter FREE

        for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
       }
        break;
      case 2: //Filter DOWN
        if (retriggered == true) {
          LFOdirection = true;
          LFO = 1.0;
        }
       for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
       }
        break;
      case 3: //Filter UP
        if (retriggered == true) {
          LFOdirection = false;
          LFO = 0;
        }       
        for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
       }
        break;
      case 4: //Filter 1-DN
        if (retriggered == true) {
          LFOstop = false;
          LFOdirection = true;
          LFO = 1.0;
        }
        if (LFOstop == false){
       for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
       }
        }
        break;
      case 5: //Filter 1-UP
        if (retriggered == true) {
          LFOstop = false;
          LFOdirection = false;
          LFO = 0;
        }
        if (LFOstop == false){
        for (int i=0; i <8; i++){
        lfo_filter[i]->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
       }
        }
        break;
      case 8: //Pitch OFF
        return;
        break;
      case 9: //Pitch FREE
        LFOpitch = (LFO * LFOdepth) + 1;
        oscSet();
        break;
      case 10: //Pitch DOWN
        if (retriggered == true) {
          LFOdirection = true;
          LFO = 1.0;
        }
        LFOpitch = (LFO * LFOdepth) + 1;
        oscSet();
        break;
      case 11: //Pitch UP
        if (retriggered == true) {
          LFOdirection = false;
          LFO = 0;
        }
        LFOpitch = (LFO * LFOdepth) + 1;
        oscSet();
        break;
      case 12: //Pitch 1-DN
        if (retriggered == true) {
          LFOstop = false;
          LFOdirection = true;
          LFO = 1.0;
        }
        if (LFOstop == false) {
          LFOpitch = (LFO * LFOdepth) + 1;
          oscSet();
        }
        break;
      case 13: //Pitch 1-UP
        if (retriggered == true) {
          LFOstop = false;
          LFOdirection = false;
          LFO = 0;
        }
        if (LFOstop == false) {
          LFOpitch = (LFO * LFOdepth) + 1;
          oscSet();
        }
        break;
    }

    retriggered = false;

    // Update LFO
    if (LFOdirection == false) { //UP
      LFO = (LFO + 0.01);
      if (LFO >= 1) {
        LFOdirection = true;
        LFOstop = true;
      }
    }

    if (LFOdirection == true) { //Down
      LFO = (LFO - 0.01);
      if (LFO <= 0) {
        LFOdirection = false;
        LFOstop = true;
      }
    }
  }
}
void oscSet() {
    for (int i=0; i <8; i++){
  voiceOne[i]->frequency(frequency[i] );
  voiceTwo[i]->frequency(frequency[i] * octave * LFOpitch);
    }
}
