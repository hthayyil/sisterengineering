


/*
   Clock project using two MX7219 matrix displays and the AdaFruit FX Soundboard
   Provides date, time, temp, humidity and event notifications in rotating order
   Also can chime in multiple ways, including Westminster chimes
   Chimes are provided by Adafruit FX Soundboard in GPIO mode
   There are some conditional options:
      Davids_Clock changes some of the events and notifications 
      Extra_Display uses a small Adafruit 1306 OLED to continuously show date and time while the main display
      rolls through its iterations
      DDT includes a couple of small debugging (get it?) routines and opens serial terminal

*/




// Code to set up the clock
// Pushbutton 1 is the toggler , cycle between  year, month, day, hours, minutes, seconds
// Pushbutton 2 is the increment up one
// Pushbutton 3 is the decrement down one

// Chime setup for toggle switch
//  Center = No chimes
//  Up = Westminster hours + quarterly
//  Down = Simple Bell (hours and 1/2 hour)

//      Comment out next line to leave out the little show 

#define showoffcode                                       // include "show off" graphics and music for Easter Egg 

//#define Davids_Clock                                      // if this is david's clock slightly different announcements



#define DSTChange                                           // Adjust clock for Daylight Savings Time events

#define DDT                                               // simple debug tools (print string, print string and value, same with NL)


// Clock "ID's" for temperature and humidity adjustment 
//*********************** Define only one of these!   ***********************
//#define Clock_1                                     // First wine box clock (mine)
//#define Clock_2                                     // 2nd wine box clock (For David)
#include <ThreeWire.h>  
#define Clock_3                                     // Acrylic long matrix clock (Mercer Island)
#include <RtcDS1302.h>
// include the libraries for LCD Display, DHT-11 Temperature/humidity sensor and DS3231 RTC and
// include libraries for MX7219 mult-unit matrix display
//#include "DHT.h"
#include <Wire.h>
#include <MD_MAX72xx.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>


// Set up output functions

#define DHTPIN 9     //Temp Humidity sensor on pin 9
#define DHTTYPE DHT11   // DHT 11 because the sensor is that type

// Initialize DHT sensor for normal 16mhz Arduino
//DHT dht(DHTPIN, DHTTYPE);
Adafruit_AM2320 dht = Adafruit_AM2320();
// Initialize for Adafruit DS3231 RTC real time clock

ThreeWire myWire(4,5,2);
RtcDS1302<ThreeWire> rtc(myWire);


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW                             // NOTE: This parameter differs by vendor
#define MAX_DEVICES 8                                                   // 2 x 4 matrices per unit (These are Wangdd22 from Amazon)

//Pins for Arduino Uno
#define CLK_PIN   13  // or SCK  (this is for the UNO, different for the Me ga
#define DATA_PIN  11  // or MOSI
#define CS_PIN   10  // or SS


//Pins for Arduino Mega
//#define CLK_PIN  52  // or SCK  13
//#define DATA_PIN  51  // or MOSI   11
//#define CS_PIN   53  // or SS 10


// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display
#define  DELAYTIME  100  // in milliseconds

// Text parameters
#define CHAR_SPACING  1 // pixels between characters
const int BufferStringLength = 31;
char BufferString [BufferStringLength];                 //used to construct printouts
#define DecToAscii  48                  // convert number to ascii (add as a constant)
char DegreeSign = '~';               // for display of 'degrees' after temperature
int TDigits[4] = {0, 0, 0, 0};          // used to convert four digits to four chacacters
#define TDOnes  3                       // positions in arrays and templates
#define TDTens  2
#define TDHundreds 1
#define TDThousands 0
#define sunday  0                         // used for events, floating events and holidays
#define monday  1                         // just for readability
#define tuesday 2
#define wednesday 3
#define thursday  4
#define friday 5
#define saturday 6
#define january 1
#define february 2
#define march 3
#define april 4
#define may 5
#define june 6
#define july 7
#define august 8
#define september 9
#define october 10
#define november 11
#define december 12

int DSTAdjust = 0;                          // will be +1 for Spring and -1 for Fall (Spring ahead and fall back!)

//Template Strings and pointers

const int LOTS = 13;                    // Length of TimeString (without terminator)
char TimeString[LOTS + 1 ] = {' ', ' ', '1', '2', ':', '3', '1', ':', '4', '5', ' ', 'P', 'M', '\0'};
char DateString[ ] = {'1', '2', '/', '3', '1', '/', '2', '0', '1', '9', '\0'};
char TempString[ ] = {'T', 'e', 'm', 'p', ' ', '7', '2', '.','0', DegreeSign,'F', '\0'};
char HumidString[ ] = {'H', 'u', 'm', ' ', '2', '5', '.', '0', '%', '\0'};
const int THptr = 2;                                                // Pointers within the strings
const int TMptr = 5;                                                // for loading values
const int TSptr = 8;
const int TAMPMptr = 11;
const int DMptr = 0;
const int DDptr = 3;
const int DYptr = 6;
const int TEMPptr = 5;
const int HUMIDptr = 4;

// Differentiated Displays

const int DisplayTime = 0;
const int DisplayDate = 2;
const int DisplayDOW  = 1;
const int DisplayTemp = 3;
const int DisplayHumid = 4;
const int DisplayEvent = 5;
const int DisplayEventRepeat = 2;                         //times to repeat the scrolling 'event' display
const int DisplaySize = 6;                                // Nunber of different displays
int DisplayIndex = DisplayTime;                                    // display we are on at the time
const int DisplayDelayArray[DisplaySize] = {100, 50, 30, 30, 30, 20}; // multiplier for each event
const int DisplayDelay = 100;                              // milliseconds to leave each display * its multiplier
unsigned long DisplayTimer;                               // used to time each matrix display

char daysOfTheWeek[7][12 ] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


 #ifndef Davids_Clock 

const int eventnumber = 50;         // number of events and remember: No strings longer than 30 characters!

int eventmonth [eventnumber] = {june, april, november, february, july, december, november, june, december, june, december, january,
                                september, october, march, february, february, july,december, february, december, january, january, february,
                                march,april,april,april,april,may,may,may,may,june,june,june,july,july,october, september, may, april,
                                march,february,march,october,march,november,august,october
                };
int eventday [eventnumber] = {11, 1, 23, 12, 4, 3, 12, 29, 25, 16, 31, 1, 3, 31, 17, 14, 2, 14, 30,12,21,5,18,18,6,7,12,15,24,1,5,20,30,14,14,21,
                              22,24,29,28,18,26,14,3,27,12,30,5,5,4};
                              
char* eventdescription [eventnumber]  =
{ "Dana's Anniversary", "April Fool's Day", "Joan's Birthday", "Sydney's Birthday", "July 4th!", "Dana's Birthday",
  "David's Birthday", "Our Anniversary", "Merry Christmas", "Leah's Birthday", "New Year's Eve", "New Year's Day",
  "Forrest's Birthday", "Happy Halloween", "Saint Patrick's Day", "Valentine's Day", "Groundhog Day", "Bastille Day", "Linsey's Birthday",
  "Irwin's Birthday", "Winter Solstice", "National Bird Day", "National Winnie the Pooh Day", "National Drink Wine Day","National Oreo Day",
  "National Beer Day","Grilled Cheese Day", "Tax Day","National DNA Day", "May Day", "Cinco de Mayo", "World Bee Day", "World MS Day",
  "National Bourbon Day", "Flag Day", "Summer Solstice","National Hot Dog Day", "National Tequila Day","National Cat Day", "National Drink Beer Day",
  "National Whisky Day", "Nat'l Audubon Day", "National Pi Day", "Nat'l Women Physicians Day", "National Paella Day", "National Gumbo Day",
  "National Doctors Day", "National Doughnut Day", "National Oyster Day", "National Taco Day"
};
#endif

bool event;                     // logic flag "on" = event found
int eventindex;                 // and the event we found
const int maxevents = 3;          // maximum of three events (real and floating combined)
char* eventstrings[maxevents] ;    // used to store displayed events
String floatstring = "                              "; // used for floating events (e.g., Thanksgiving)

#define pb1pin 6             //  Pin assignments for reset, increment and decrement
#define pb2pin 7
#define pb3pin 8

#define showoffbuttonpin 7                           // invoke showing off the matrix display

#define DoWestminster 5
#define DoHoursOnly 6
#define silent  0                                 // no chiming at all
#define hoursonly  1                              // no prelude, just chime number of hours and half hour single chime
#define westminster 2                            // hours + Westminster prelude per quarter
int ChimeValue = silent;                         // default to silent


const int LEDpin = A0;                 // Pin assignment for analog reading LDR for LED brightness
const int minbright = 0;              // MAX_BRIGHT for this module is 15
const int midbright = 1;              // but these values "seem" to work
const int maxbright = 4;




int setupindex = 0;                 // first thing to set if required
bool insetupmode = true;           // and assume RTC is set, OK, etc., and no 'set' required
bool setinsetup = false;            // flag set to true at interrupt level to go back into setup mode

// date time array for setting, reading, displaying

#define setsize   6            // size of the setting array
#define setyear   0            // index name for each element
#define setmonth   1
#define setday   2
#define sethour   3
#define setminute   4
#define setsecond   5

int setarray [setsize] = {2019, 1, 1, 1, 1, 0};  // set year, month, day,  hour, minutes, seconds
int lowlimit [setsize] = {2019, 1, 1, 0, 1, 0}; // lower limit for each
int highlimit [setsize] = {2080, 12, 31, 23, 59, 59};  //high limit for each
const int setdesclength = 4;                            // maximum length of 'set' descriptor
char setdesc [setsize] [setdesclength] = {"Yr ", "Mon", "Day", "Hr ", "Min", "Sec"};


#define cqtr0   1        //  Chime the hour
#define cqtr1   2        //  Chime the quarter hour
#define cqtr2   3        //  Chime the half hour
#define cqtr3   4         // Chime the 3/4 hour

const int BounceDelay = 250;                // Not really 'bounce', its a change of state detection

int i;                          // generic index variable

int dayoftheweek;               // stored day of the week (0-6, 0 = Sunday)

int phours;                     // for print conversion of military time

float temperaturef;             // farenheit temperature back
int temperature;                  // integer version of temperature for matrix
float temperaturec;             // centrigade temperature back (not used)

float humidityf;                 // and humidity
int humidity  ;                 // and same as temp

// The DHT sensors are cheap and inaccurate so these are 'custom' adjustments

#ifdef Clock_1                // first wine box clock
float tempadjust = -2.0;      // temperature adjustment for sensor (I found it didn't read right against 'comps')
float humidadjust = +7.0;     // humidity adjustment
#endif

#ifdef Clock_2                  // second wine box clock for David
float tempadjust = -1.0;      // temperature adjustment for sensor
float humidadjust = -3.0;
#endif

#ifdef Clock_3                // clear clock in Mercer Island office
float tempadjust =  -1.0;
float humidadjust = +8.0;      
#endif    


#ifdef DDT    

// debugging tools
void DDTl(String st, int vt) {                     // Print descriptor and value and new line
  DDTv(st, vt);
  Serial.println(" ");
}
void DDTv(String st, int vt) {                     // Print descriptor and value
  Serial.print("  ");
  Serial.print(st);
  Serial.print("  ");
  Serial.print(vt);
}
void DDTt(String st) {                     // Print descriptor and value and new line
  Serial.println(st);
}
void DDTs(String st, int vt) {                     // Print descriptor and value
  Serial.print("  ");
  Serial.print(st);
  Serial.print("  ");
  Serial.print(vt);
}
#endif //DDT//

void LEDBrightness() {
  mx.control(MD_MAX72XX::INTENSITY, midbright);
//  
//  int LEDvalue;
//  LEDvalue  = analogRead(LEDpin);                                       // Read LDR value (may need to play with values)
//  DDTs("LED value",LEDvalue);
//  LEDvalue = map(LEDvalue, 0, 1023, 0, MAX_INTENSITY);              //map to valid value for brightness  (max intensity is 15 btw)
//  if (LEDvalue <= 11) {
//    mx.control(MD_MAX72XX::INTENSITY, minbright);}
//    else if (LEDvalue > 13 ) {
//    mx.control(MD_MAX72XX::INTENSITY, maxbright); }
//    else
//  {mx.control(MD_MAX72XX::INTENSITY, midbright); }
//  DDTl("Mapped LED value", LEDvalue);
//
  

}  //end of LEDbrightness

void setup()
// put your setup code here, to run once:

{
  Wire.begin();                     // initialize I2C interface
  dht.begin();                      // initialize the temp/humidity sensor
  mx.begin();                      // and MX7219 display
  Serial.begin (9600);            //Terminal monitor printing for debugging



  pinMode(pb1pin, INPUT_PULLUP);  // The three pushbuttons - reset
  pinMode(pb2pin, INPUT_PULLUP);   // increment
  pinMode(pb3pin, INPUT_PULLUP);   // decrement

//  pinMode (DoWestminster, INPUT_PULLUP);            // When pulled 'low' we want Westminster chimes


  // set up interupt for PB1                                               // if PB1 is pushed, it'll pick up on next release from Matrix display
  attachInterrupt(digitalPinToInterrupt(pb1pin), SetToSetup, FALLING);     // and re-enter setup mode (after the end of current display)

  rtc.Begin();
  if (!rtc.GetIsRunning()) {                        // check that clock is there
    Serial.print("Couldnt find rtc");
    scrollText("Couldn't find RTC");       // clock missing is a fatal error
    while (1);
  }

  if (rtc.IsDateTimeValid() == false) {           // if power lost force a setup, else load 'current' values and
    scrollText("RTC lost power!");
    delay(1000);
    scrollText("Replace battery?");
    delay(1000);
    scrollText("Setup Mode: ");
    setupindex = setyear - 1;         // setup differently (becuase it will increment)
    insetupmode = true;
    for (i = 0; i < setsize; i++) {
      setarray[i] = lowlimit[i];
    }
      } else                                                      // else reload from RTC
  { RtcDateTime (setarray[setyear], setarray[setmonth], setarray[setday], setarray[sethour], setarray[setminute], setarray[setsecond])  = rtc.GetDateTime();
    insetupmode = false;                                                        // not in setup mode, and
    setinsetup = false;                                                          //no interrupt
  }

  // Two alternative modes of setting date and time (for debugging, just un-comment):
  // This line sets the RTC to the date & time this sketch was compiled
  //    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  //   rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        LEDBrightness();                                                          // Do an initial check for room brightness
}      // end of setup

void loop() {                                                             // Main code divided into setup mode and non-setup mode
  Serial.print("looping");
  while (insetupmode) {                                                    // code for setting time, date set, etc.
    Serial.println("IN SET UP");
    // Read the increment button

    if (digitalRead(pb2pin) == LOW) {
      Serial.println("pressed pin 2");
      setarray[setupindex]++;            // read increment of current item
      delay(BounceDelay);
      if (setarray[setupindex] > highlimit[setupindex]) {
        setarray[setupindex] = lowlimit[setupindex];
      }
      ShowValue(setupindex, setdesc[setupindex]);                         // and display description and value
    }

    // Read the decrement Button
    if (digitalRead(pb3pin) == LOW) {
      Serial.println("pressed pin 3");
      setarray[setupindex]--;                  // read decrement of value
      delay(BounceDelay);
      if (setarray[setupindex] < lowlimit[setupindex]) {
        setarray[setupindex] = highlimit[setupindex];
      }
      ShowValue(setupindex, setdesc[setupindex]);                              // and display description and value
    }

    // Read for another increment of index

    if (digitalRead(pb1pin) == LOW) {             // Rolling through Chime, Year, Month, Day, Hour, Minutes, Seconds
      Serial.println("pressed pin 1");
      setupindex++ ;                            // increment index
      delay(BounceDelay);
      if (setupindex < setsize) {
        ShowValue(setupindex, setdesc[setupindex]); // show description and value if in bounds
      }
      if (setupindex >= setsize) {                               // and finally exiting setup mode after setting chime, date and time
        rtc.SetDateTime(RtcDateTime(setarray[setyear], setarray[setmonth], setarray[setday], setarray[sethour], setarray[setminute], setarray[setsecond]));
        insetupmode = false;
        DisplayIndex = DisplayTime;
      }  //exit setup mode when done
    }

  }  // End of "While" for setup

  // Begin regular loop for date, time, temp humidity and event  display

  while (!insetupmode) {
    Serial.print("NIT IN SETUP");
    GetTempandHumid();                                            // read temperature and humidity from sensor
    
  //  ChimeValue = ReadChimeSetting();                               // read SPDT Center off switch for silent, westminster or hours only (and 1/2)
    
    GetTheDate();                                                 // load date array from RTC for a chime/bell check
    
   // CheckForChime();                                              // Check for a chime event between displays

   // CheckForEvent(setarray[setmonth], setarray[setday], dayoftheweek);    // check for static and floating events
              
    MatrixDisplay();                                              // Do whatever display is required on the MX7219

    //LEDBrightness();                                                // Good place to check for change in room brightness

    // end of display update logic

    // Read a potential request for an entry into setup from PB 1
    if ((digitalRead(pb1pin) == LOW) || setinsetup) {                // to see if we go back to setup mode
      Serial.println("Read from pin 1");
      insetupmode = true;                                             // via a pushbutton or the interrupt
      setinsetup = false;                                              // clear the interrupt flag
      setupindex = 0;                                                 // re-initialize to 'Year' in setup
      DisplayIndex = DisplayTime;                                       // and go back to time display when exit setup
      scrollText("Setup Mode: ");
      delay(2000);
      ShowValue(setupindex, setdesc[setupindex]);                     // show the first setup item (Year)
      delay(BounceDelay);
    }

  } // end of not in setup
}  // end of sketch

void ShowValue(int myindex, String setdescription)                                    // Display while in setup mode
{                                                                                   // shows what item is setting and its value

  for (int i = 0; i < BufferStringLength; i++) {BufferString[i] = ' ';}            // clear buffer
  setdescription.toCharArray(BufferString, setdesclength);                                       // move description to output buffer
  LoadNumber(setarray[setupindex]);
  BufferString[setdesclength-1] = ' ';
  for (int i = 0; i <setdesclength; i++) {BufferString[i + setdesclength] = TDigits[i];}
  if (myindex != setyear) {                                                           // only the year is 4 digits, else 2
    BufferString[4] = ' ';                                                            
    BufferString[5] = ' ';
    if (BufferString[6] == '0') {BufferString[6] = ' ';}                             // and suppress leading 0 for 2 digit numbers too
  }
  BufferString[8] = '\0';                                                          // and terminate
  printText(BufferString, 7, false);


}  // End of Show Value
void scrollText(char *p)                                                                      // copied from library
{
  uint8_t charWidth;
  uint8_t cBuf[8];  // this should be ok for all built-in fonts
  mx.clear();
  while (*p != '\0')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (uint8_t i = 0; i <= charWidth; i++) // allow space between characters
    {mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(DELAYTIME);}
  }
}  // End of Scroll Text
void LoadNumber(int numtoload) {                                            // Converts number to four digit Ascii array
  int tempnum = numtoload;
  for (int i = 3; i >= 0; i--) {
    TDigits[i] = (tempnum % 10) + DecToAscii;;
    tempnum = tempnum / 10;
  }
}  // end of LoadNumber
void printText(char *pMsg, int LOS, bool CenterJustify)                                   // copied and modified from library
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
// And center justified if third argument is "true"
{
  uint8_t modStart = 0;
  uint8_t modEnd = MAX_DEVICES - 1;
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;
  int pixelcount = 0;
  int ccounter = LOS;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {   switch (state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file

        showLen = mx.getChar(*pMsg++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
        if (ccounter > 0) {
          pixelcount = (pixelcount + showLen) + CHAR_SPACING;
          ccounter--;
        }
        curLen = 0;
        state++;
      // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns

        curLen = 0;

        state++;
      // fall through

      case 3:  // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  if (CenterJustify) {
    for (int i = 1; i <= (((MAX_DEVICES * COL_SIZE) - pixelcount) / 2); i++) {
      mx.transform( MD_MAX72XX::TSR);
    }
  }
  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
void Scrollup() {                                                                            // used to 'wipe' previous display
  for (uint8_t i = 0; i < 8; i++) {
    mx.transform(MD_MAX72XX::TSU); delay(2 * DELAYTIME);
    delay(DELAYTIME);
  }
} // End of Scrollup
void printCenter(String StringtoPrint)                                    // Loads the print buffer and centers it
{
  int LOS = StringtoPrint.length();                                          // Get the string's length
  for (int i = 0; i < BufferStringLength; i++) {
    BufferString[i] = ' '; // clear buffer
  }
  for (int i = 0; i < LOS; i++) {
    BufferString[i] = StringtoPrint[i];        // transfer
    printText(BufferString, LOS, true);                                       // Print, providing length of string and "Yes, center"

  }
}  // End of Center and Load

void MatrixDisplay() {                                                           // Main display routine for display sequences
  Serial.print("in miatrixsd");
  Scrollup();                                                                   // Clear last display
  if (DisplayIndex >= DisplaySize) {
    DisplayIndex = DisplayTime; // reset if at the end
  }
  DisplayTimer = DisplayDelayArray[DisplayIndex] * DisplayDelay;                // set individual display time
  
  switch (DisplayIndex) {                                                       // and do next display

    case DisplayTime:    // Dislay the time
      do                                                                          // time is different in that there's a constant
      {        
        DisplayTimer = DisplayTimer - 1;
        // update of time during display and also play chime, bell etc.
        GetTheDate();                                                               // Get Current Time
        LoadNumber(phours);                                                         // Load the 4 digit character array from number
        TimeString[THptr] = TDigits[TDTens];                                        // left digit of the two digit hour
        TimeString[THptr + 1] = TDigits[TDOnes];                                    // rightmost digit
        if (TimeString[THptr] == '0') {
          TimeString[THptr] = ' '; // eliminate leading zero
        }
        LoadNumber(setarray[setminute]);                                             // do same for minutes
        TimeString[TMptr] = TDigits[TDTens];                                          // except no need to do space for zero
        TimeString[TMptr + 1] = TDigits[TDOnes];
        LoadNumber(setarray[setsecond]);                                              // seconds then
        TimeString[TSptr] = TDigits[TDTens];
        TimeString[TSptr + 1] = TDigits[TDOnes];
        if (setarray[sethour] < 12)                                                   // and AM vs PM
        {TimeString[TAMPMptr] = 'A';}
        else
        {TimeString[TAMPMptr] = 'P';}
        printText(TimeString, LOTS, false);                                           // Keep position (no centering) because time keeps updating during display and chimes
        Serial.println(DisplayTimer);

      } while (DisplayTimer > 0);                         // leave this display when no sound or no delay left
      DisplayIndex++ ;                                                                // then move on to next display item
      break;

    case DisplayDate:                         // Month, Day and Year Display
      LoadNumber(setarray[setmonth]);
      DateString[DMptr] = TDigits[TDTens];
      if (DateString[DMptr] == '0') {
        DateString[DMptr] = ' ';
      }
      DateString[DMptr + 1] = TDigits[TDOnes];
      LoadNumber(setarray[setday]);
      DateString[DDptr] = TDigits[TDTens];
      DateString[DDptr + 1] = TDigits[TDOnes];
      LoadNumber(setarray[setyear]);
      for (int i = 0; i < 4; i++) {
        DateString[DYptr + i] = TDigits[i];
      }
      printCenter(DateString);
      CommonDelay(DisplayTimer);
      DisplayIndex++ ;
      break;

    case DisplayDOW:                                                               //  Just display the day of week string
      printCenter(daysOfTheWeek[dayoftheweek]);
      CommonDelay(DisplayTimer);
      DisplayIndex++ ;
      break;

    case DisplayTemp:                                                          // Temperature display
      LoadNumber(temperature);
      TempString[TEMPptr] = TDigits[TDHundreds];
      TempString[TEMPptr + 1] = TDigits[TDTens];
      TempString[TEMPptr + 3] = TDigits[TDOnes];
      printCenter(TempString);
      CommonDelay(DisplayTimer);
      DisplayIndex++ ;
      break;

    case DisplayHumid:                        // Humidity display
      LoadNumber(humidity);
      HumidString[HUMIDptr] = TDigits[TDHundreds];
      HumidString[HUMIDptr + 1] = TDigits[TDTens];
      HumidString[HUMIDptr + 3] = TDigits[TDOnes];
      printCenter(HumidString);
      CommonDelay(DisplayTimer);
      DisplayIndex++ ;
      break;

    case DisplayEvent:                                          // Event Display
      if (event) {                                                // "Real" events repeat 3 times
          if (eventindex > 0 ) {                                  // for case where there is more than one event 
              while (eventindex >= 0)
                  {scrollText(eventstrings[eventindex]);                        // scroll each of them once
                  if (eventindex > 0) {
                     delay(DisplayDelay * 6);
                     printCenter("and");
                     delay(DisplayDelay * 6);}
                   eventindex--;                                                // and decrement
                   delay(DisplayDelay * 2);
                  }
          }
          else {                                                      // case of only one event -- repeat it for readability
            for (int i = 1; i <= DisplayEventRepeat; i++) {          // scroll either static or floating event 
            scrollText(eventstrings[eventindex]);                     // the index is 0 (greater than zero if multiple events)
          } 
          delay(DisplayDelay * 4);
        }
          }                                                             // end of "if event" logic
            if (!event){                                                // Scroll Default message only once
      
              }                                                         // end of "if not event" above                              
      CommonDelay(DisplayTimer);
      DisplayIndex++ ;
      break;

    default:
      scrollText("Should never get here");
      while (1);

  }    //  End of Switch

}  // End of MatrixDisplay

//  RtcDateTime now = rtc.GetDateTime();
//  setarray[setyear] = now.Year();
//  setarray[setmonth] = now.Month();
//  setarray[setday] = now.Day();
//  setarray[sethour] = now.Hour();
//  setarray[setminute] = now.Minute();
//  setarray[setsecond] = now.Second();
//  dayoftheweek = now.DayOfWeek();
  
//#ifdef DSTChange                                                            // Check for DST begin and end 
//    if (DSTAdjust !=0)                                     // checking for event will set if appropriate
//      {if (setarray[sethour] == 2 && setarray[setminute] == 1 )            // adjust at 2am (plus 1 to give it time to chime at 2am)
//           {setarray[sethour] = setarray[sethour]+DSTAdjust;                                // Adjust for DST begin or end
//            rtc.SetDateTime(RtcDateTime(setarray[setyear],setarray[setmonth],setarray[setday],setarray[sethour],setarray[setminute],setarray[setsecond])); // and adjust time
//            for (int i = 1; i<=4; i++){
//              if (DSTAdjust < 0) {scrollText("Falling Back One Hour");} else {scrollText("Springing Ahead One Hour");}
//            delay(1000);}}}
//                                                                                
//#endif DSTChange

 void GetTheDate() {                                                          // Read RTC into array
  RtcDateTime now = rtc.GetDateTime();
  setarray[setyear] = now.Year();
  setarray[setmonth] = now.Month();
  setarray[setday] = now.Day();
  setarray[sethour] = now.Hour();
  setarray[setminute] = now.Minute();
  setarray[setsecond] = now.Second();
  dayoftheweek = now.DayOfWeek();
  if (setarray[sethour] <= 12)              // convert military time to am pm
  {
    phours = setarray[sethour];
  }
  else
  {phours = setarray[sethour] - 12;}
  if (phours <= 0) { phours = 12;  }            // don't print 0 for midnite, print "12"
 
}   // End of Get The Date
void GetTempandHumid(){                         // Temperature and humidity update

    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    humidityf = dht.readHumidity()+humidadjust;
    Serial.print("humidity: ");
    Serial.println(humidityf);
    // Read temperature as Fahrenheit
    temperaturef = (dht.readTemperature()) + tempadjust;  // read and correct for inaccuracy in sensor
    Serial.print("temp: ");
    Serial.println(temperaturef);
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidityf) || isnan(temperaturec) || isnan(temperaturef)) {
      temperaturef = 0;              // use 0 as a no-read
      humidityf = 0;                  // error indication
    }
    temperature = temperaturef * 10.0;          // get read for matrix printout
    humidity = humidityf * 10.0;
}   // end of Temperature and Humidity update

void SetToSetup() {                               // interrupt level back to setup
  if ((!insetupmode) && (!setinsetup)) {                              // skip if we are already in Setup mode or have seen the interrupt
    setinsetup = true;                              // Go back into setup at next loop
    DisplayTimer = 0;
  }                                // and zero the timer to speed that up if you can
}  // SetToSetup

void CommonDelay(long int MyDelay) {                          // Common delay routine
  DisplayTimer = MyDelay;
  Serial.println("delayin");
  do {
    DisplayTimer = DisplayTimer - DisplayDelay;
    delay(DisplayDelay);
    GetTheDate();        
    Serial.println("done delayin");
    // load date array from RTC for a chime/bell check
  //  CheckForChime();                                              // if a chime happens, setup to end delay
  } while (DisplayTimer > 0);    // repeat while still time and no interrupt and no sound waiting
  //  if (SoundQueueCtr > 0){DisplayIndex = DisplayTime-1;}                       // if leaving due to chime, go directly to time
} // End of CommonDelay





// Routine to check for 'real' (static) events and floating events (e.g., Memorial Day, Thanksgiving, Mother's Day and Fathers Day)

/* Memorial Day is Last Monday in May
    Thanksgiving is 4th Thursday in November
    Mother's Day is 2nd Sunday in May
    Father's Day is 3rd Sunday in June
    MLK Day is 3rd Monday in February
    Memorial Day is last Monday in May
    Labor Day is first Monday in September
    Daylight Savings Times starts 2nd Sunday in March
    Daylight Savings Times ends first Sunday in November
    Indigenous People's Day is second Monday in October (also its Columbus Day)
    Oktoberfest is 3rd Saturday in September
    Election Day is first Tuesday in November
    National Ice Cream Day is 3rd Sunday in July

*/

void CheckForEvent(int m, int d, int dow) {                          // called with Month, Day within month and day of the week (0 = Sunday)

  event = false;                                                      // assume neither static or floating
  eventindex = -1;                                                      // initial index to eventstrings

  //  Static event check
                                                                           
      for (int i = 0; i < eventnumber; i++) {                                               // then check the static events
        if ((setarray[setmonth] == eventmonth[i]) && (setarray[setday] == eventday[i]))
        { event = true;                                                // set if match on month and day
          eventindex++;                                                 // found one!
          eventstrings[eventindex] = eventdescription[i];                 // store pointer to static event description
        }
      }

  //  Floating event check

  floatstring = "none";                                                                   // initialize string 
  DSTAdjust = 0;                                                                          // assume its not DST change date
  
  if ((dow == thursday) && (m == november) && (d >= 22) && (d <= 28)) {                         // Thanksgiving
    floatstring = "Thanksgiving"; }
  else if ((dow == sunday) && (m == may) && (d >= 8) && (d <= 14)) {                    // Mother's Day
    floatstring = "Mother's Day";}
  else if ((dow == sunday) && (m == june) && (d >= 15) && (d <= 21)) {                 //Father's Day
    floatstring = "Father's Day";}
  else if ((dow == monday) && (m == january) && (d >= 15) && (d <= 21)) {               //MLK Day
    floatstring = "Martin Luther King Day";}
  else if ((dow == saturday) && (m == october) && (d >= 15) && (d <= 21)) {               //Oktoberfest starts
    floatstring = "Oktoberfest Begins";}
  else if ((dow == sunday) && (m == july) && (d >= 15) && (d <= 21)) {               //Oktoberfest starts
    floatstring = "National Ice Cream Day";}
  else if ((dow == monday) && (m == february) && (d >= 15) && (d <= 21)) {             //President's Day
    floatstring = "President's Day!";}
  else if ((dow == monday) && (m == september) && (d <= 7) ) {                        //Labor Day
    floatstring = "Labor Day";}
  else if ((dow == tuesday) && (m == november) && (d <= 7) ) {                        //Election Day
    floatstring = "Election Day";}
  else if ((dow == monday) && (m == october) && (d >= 8) && (d <= 14) ) {            //Indigenous People's Day
    floatstring = "Indigenous People's Day";}
  else if ((dow == monday) && (m == may) && (d + 7 > 31) ) {                        //Memorial Day
    floatstring = "Memorial Day";}
  else if ((dow == sunday) && (m == march) && (d >= 8) && (d <= 14)) {              // DST begins
    floatstring = "DST Begins Today";
    DSTAdjust = +1;}                                                                   // Set Daylight Savings Time (Spring ahead!)
  else if ((dow == sunday) && (m == november) && (d <= 7) ) {                       //DST ends
    floatstring = "DST Ends Today";
    DSTAdjust = -1;}                                                                 // Set Daylight Savings Time (Fall back!)

  if (floatstring != "none" ) {                                                     // did we load anything?
     event = true;                                                                  // if so, then we have one
     eventindex++;                                                                  // so load it into event display queue
     eventstrings[eventindex] = floatstring.c_str(); }                                // store pointer to static event description

}  // end of floatingevent



//void scrollText(char *p)                                                                      // copied from library
//{
//  uint8_t charWidth;
//  uint8_t cBuf[8];  // this should be ok for all built-in fonts
//  mx.clear();
//  while (*p != '\0')
//  {
//    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
//
//    for (uint8_t i = 0; i <= charWidth; i++) // allow space between characters
//    {mx.transform(MD_MAX72XX::TSL);
//      if (i < charWidth)
//        mx.setColumn(0, cBuf[i]);
//      delay(DELAYTIME);}
//  }
//}  // End of Scroll Text

//void printText(char *pMsg, int LOS, bool CenterJustify)                                   // copied and modified from library
//// Print the text string to the LED matrix modules specified.
//// Message area is padded with blank columns after printing.
//// And center justified if third argument is "true"
//{
//  uint8_t modStart = 0;
//  uint8_t modEnd = MAX_DEVICES - 1;
//  uint8_t   state = 0;
//  uint8_t   curLen;
//  uint16_t  showLen;
//  uint8_t   cBuf[8];
//  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;
//  int pixelcount = 0;
//  int ccounter = LOS;
//
//  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
//
//  do     // finite state machine to print the characters in the space available
//  {   switch (state)
//    {
//      case 0: // Load the next character from the font table
//        // if we reached end of message, reset the message pointer
//        if (*pMsg == '\0')
//        {
//          showLen = col - (modEnd * COL_SIZE);  // padding characters
//          state = 2;
//          break;
//        }
//
//        // retrieve the next character form the font file
//
//        showLen = mx.getChar(*pMsg++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
//        if (ccounter > 0) {
//          pixelcount = (pixelcount + showLen) + CHAR_SPACING;
//          ccounter--;
//        }
//        curLen = 0;
//        state++;
//      // !! deliberately fall through to next state to start displaying
//
//      case 1: // display the next part of the character
//        mx.setColumn(col--, cBuf[curLen++]);
//
//        // done with font character, now display the space between chars
//        if (curLen == showLen)
//        {
//          showLen = CHAR_SPACING;
//          state = 2;
//        }
//        break;
//
//      case 2: // initialize state for displaying empty columns
//
//        curLen = 0;
//
//        state++;
//      // fall through
//
//      case 3:  // display inter-character spacing or end of message padding (blank columns)
//        mx.setColumn(col--, 0);
//        curLen++;
//        if (curLen == showLen)
//          state = 0;
//        break;
//
//      default:
//        col = -1;   // this definitely ends the do loop
//    }
//  } while (col >= (modStart * COL_SIZE));
//
//  if (CenterJustify) {
//    for (int i = 1; i <= (((MAX_DEVICES * COL_SIZE) - pixelcount) / 2); i++) {
//      mx.transform( MD_MAX72XX::TSR);
//    }
//  }
//  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
//}
//void printCenter(String StringtoPrint)                                    // Loads the print buffer and centers it
//{
//  int LOS = StringtoPrint.length();                                          // Get the string's length
//  for (int i = 0; i < BufferStringLength; i++) {
//    BufferString[i] = ' '; // clear buffer
//  }
//  for (int i = 0; i < LOS; i++) {
//    BufferString[i] = StringtoPrint[i];        // transfer
//    printText(BufferString, LOS, true);                                       // Print, providing length of string and "Yes, center"
//
//  }
//}  // End of Center and Load
//
//void ShowValue(int myindex, String setdescription)                                    // Display while in setup mode
//{                                                                                   // shows what item is setting and its value
//
//  for (int i = 0; i < BufferStringLength; i++) {BufferString[i] = ' ';}            // clear buffer
//  setdescription.toCharArray(BufferString, setdesclength);                                       // move description to output buffer
//  LoadNumber(setarray[setupindex]);
//  BufferString[setdesclength-1] = ' ';
//  for (int i = 0; i <setdesclength; i++) {BufferString[i + setdesclength] = TDigits[i];}
//  if (myindex != setyear) {                                                           // only the year is 4 digits, else 2
//    BufferString[4] = ' ';                                                            
//    BufferString[5] = ' ';
//    if (BufferString[6] == '0') {BufferString[6] = ' ';}                             // and suppress leading 0 for 2 digit numbers too
//  }
//  BufferString[8] = '\0';                                                          // and terminate
//  printText(BufferString, 7, false);
//
//
//}  // End of Show Value

//void LoadNumber(int numtoload) {                                            // Converts number to four digit Ascii array
//  int tempnum = numtoload;
//  for (int i = 3; i >= 0; i--) {
//    TDigits[i] = (tempnum % 10) + DecToAscii;;
//    tempnum = tempnum / 10;
//  }
//}  // end of LoadNumber

//void QueueSound(int SoundFile) {                                          // place a sound to be played into sequence
//
//  if ((SoundQueuePtr == SizeQueue) || (SoundQueueCtr <= 0)) {
//    SoundQueuePtr = -1; // Dont overflow the queue
//  }
//  SoundQueuePtr++;                                                 // Increment pointer
//  SoundQueue[SoundQueuePtr] = SoundFile;                         // and store the sound chosen
//  SoundQueueCtr++;                                                // and increment # sounds in queue
//}     // end of Queue Sound File
//
//void PlaySound() {                                                // Plays appropriate Sound file
//  if (SoundQueueCtr > 0) {                                   // if nothing in the queue, just return
//    if (digitalRead(SoundBusyPin) == LOW) {                    //or if sound card busy, just return
//      return;
//    }                                                      //until idle
//    if (SoundPlayPtr == SizeQueue) {
//      SoundPlayPtr = -1; // Dont go past the queue
//    }
//    SoundPlayPtr++;                                                 // Increment pointer
//    //digitalWrite(FirstSoundPin + SoundQueue[SoundPlayPtr], LOW);            //Play the sound
//    delay(fxset);                                                   // hold to start the sound
//   // digitalWrite(FirstSoundPin + SoundQueue[SoundPlayPtr], HIGH);            //Turn off the sound
//    delay(fxset);                                                     // Ensure its set
//    SoundQueueCtr--;                                                  // and decrement sounds yet to be played
//    if (SoundQueueCtr <= 0) {
//      SoundPlayPtr = -1;
//    };                       // reset play pointer when queue is empty
//  }
//
//}     // end of PlaySound


#ifdef showoffcode

//void ShowOff() {                                             // Played at startup -- just the MX Panel Test Graphics
// // QueueSound(SoundShowOff);                                 // play Game of Thones theme as sound 
// // PlaySound();
//  scrollText("Showing Off");
//  rows();
//  columns();
//  cross();
//  checkboard();
//  bullseye();
//  bounce();
//  stripe();
//  stripe();
//  transformation1();
//  transformation2();
//  bullseye();
//  spiral();
//  delay(2000);
//  DisplayIndex = DisplayTime;                                     // force display of time after showing off display
//}                                                           // end of Show Off

void rows()                                                   // these routines are all
// Demonstrates the use of setRow()                               // from the MX library
{mx.clear();
 for (uint8_t row = 0; row < ROW_SIZE; row++)
  {
    mx.setRow(row, 0xff);
    delay(2 * DELAYTIME);
    mx.setRow(row, 0x00);
  }
}

void checkboard()
// nested rectangles spanning the entire display
{
  uint8_t chkCols[][2] = { { 0x55, 0xaa }, { 0x33, 0xcc }, { 0x0f, 0xf0 }, { 0xff, 0x00 } };
  mx.clear();
  for (uint8_t pattern = 0; pattern < sizeof(chkCols) / sizeof(chkCols[0]); pattern++)
  {
    uint8_t col = 0;
    uint8_t idx = 0;
    uint8_t rep = 1 << pattern;

    while (col < mx.getColumnCount())
    {
      for (uint8_t r = 0; r < rep; r++)
        mx.setColumn(col++, chkCols[pattern][idx]);   // use odd/even column masks
      idx++;
      if (idx > 1) idx = 0;
    }
    delay(10 * DELAYTIME);
  }
}                 // end of Checkboard

void columns()
// Demonstrates the use of setColumn()
{

  mx.clear();

  for (uint8_t col = 0; col < mx.getColumnCount(); col++)
  {
    mx.setColumn(col, 0xff);
    delay(DELAYTIME / MAX_DEVICES);
    mx.setColumn(col, 0x00);
  }
}

void cross()
// Combination of setRow() and setColumn() with user controlled
// display updates to ensure concurrent changes.
{

  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // diagonally down the display R to L
  for (uint8_t i = 0; i < ROW_SIZE; i++)
  {
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, i, 0xff);
    }
    mx.update();
    delay(DELAYTIME);
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, i, 0x00);
    }
  }

  // moving up the display on the R
  for (int8_t i = ROW_SIZE - 1; i >= 0; i--)
  {
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE - 1, 0xff);
    }
    mx.update();
    delay(DELAYTIME);
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE - 1, 0x00);
    }
  }

  // diagonally up the display L to R
  for (uint8_t i = 0; i < ROW_SIZE; i++)
  {
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE - 1 - i, 0xff);
    }
    mx.update();
    delay(DELAYTIME);
    for (uint8_t j = 0; j < MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE - 1 - i, 0x00);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void bullseye()
// Demonstrate the use of buffer based repeated patterns
// across all devices.
{

  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (uint8_t n = 0; n < 3; n++)
  {
    byte  b = 0xff;
    int   i = 0;

    while (b != 0x00)
    {
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE - 1 - i, b);
        mx.setColumn(j, COL_SIZE - 1 - i, b);
      }
      mx.update();
      delay(3 * DELAYTIME);
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE - 1 - i, 0);
        mx.setColumn(j, COL_SIZE - 1 - i, 0);
      }

      bitClear(b, i);
      bitClear(b, 7 - i);
      i++;
    }

    while (b != 0xff)
    {
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE - 1 - i, b);
        mx.setColumn(j, COL_SIZE - 1 - i, b);
      }
      mx.update();
      delay(3 * DELAYTIME);
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE - 1 - i, 0);
        mx.setColumn(j, COL_SIZE - 1 - i, 0);
      }

      i--;
      bitSet(b, i);
      bitSet(b, 7 - i);
    }
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void spiral()
// setPoint() used to draw a spiral across the whole display
{

  int  rmin = 0, rmax = ROW_SIZE - 1;
  int  cmin = 0, cmax = (COL_SIZE * MAX_DEVICES) - 1;

  mx.clear();
  while ((rmax > rmin) && (cmax > cmin))
  {
    // do row
    for (int i = cmin; i <= cmax; i++)
    {
      mx.setPoint(rmin, i, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    rmin++;

    // do column
    for (uint8_t i = rmin; i <= rmax; i++)
    {
      mx.setPoint(i, cmax, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    cmax--;

    // do row
    for (int i = cmax; i >= cmin; i--)
    {
      mx.setPoint(rmax, i, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    rmax--;

    // do column
    for (uint8_t i = rmax; i >= rmin; i--)
    {
      mx.setPoint(i, cmin, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    cmin++;
  }
}

void bounce()
// Animation of a bouncing ball
{
  const int minC = 0;
  const int maxC = mx.getColumnCount() - 1;
  const int minR = 0;
  const int maxR = ROW_SIZE - 1;

  int  nCounter = 0;

  int  r = 0, c = 2;
  int8_t dR = 1, dC = 1;  // delta row and column


  mx.clear();

  while (nCounter++ < 200)
  {
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;
    mx.setPoint(r, c, true);
    delay(DELAYTIME / 2);

    if ((r == minR) || (r == maxR))
      dR = -dR;
    if ((c == minC) || (c == maxC))
      dC = -dC;
  }
}
void stripe()
// Demonstrates animation of a diagonal stripe moving across the display
// with points plotted outside the display region ignored.
{
  const uint16_t maxCol = MAX_DEVICES*ROW_SIZE;
  const uint8_t  stripeWidth = 10;

  mx.clear();

  for (uint16_t col=0; col<maxCol + ROW_SIZE + stripeWidth; col++)
  {
    for (uint8_t row=0; row < ROW_SIZE; row++)
    {
      mx.setPoint(row, col-row, true);
      mx.setPoint(row, col-row - stripeWidth, false);
    }
    delay(DELAYTIME);
  }
}

void transformation1()
// Demonstrates the use of transform() to move bitmaps on the display
// In this case a user defined bitmap is created and animated.
{
  uint8_t arrow[COL_SIZE] =
  {
    0b00001000,
    0b00011100,
    0b00111110,
    0b01111111,
    0b00011100,
    0b00011100,
    0b00111110,
    0b00000000
  };

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TFLR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TRC,
    MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    MD_MAX72XX::TFUD,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TINV,
    MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    MD_MAX72XX::TINV
  };

  // transformation 
  
  mx.clear();

  // use the arrow bitmap
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t j=0; j<mx.getDeviceCount(); j++)
    mx.setBuffer(((j+1)*COL_SIZE)-1, COL_SIZE, arrow);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(DELAYTIME);

  // run through the transformations
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  for (uint8_t i=0; i<(sizeof(t)/sizeof(t[0])); i++)
  {
    mx.transform(t[i]);
    delay(DELAYTIME*4);
  }
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);
}

void transformation2()
// Demonstrates the use of transform() to move bitmaps on the display
// In this case font characters are loaded into the display for animation.
{
  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TINV,
    MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    MD_MAX72XX::TINV,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSD, MD_MAX72XX::TSU, MD_MAX72XX::TSD, MD_MAX72XX::TSU,
    MD_MAX72XX::TFLR, MD_MAX72XX::TFLR, MD_MAX72XX::TFUD, MD_MAX72XX::TFUD
  };}
#endif //showoffcode// 
