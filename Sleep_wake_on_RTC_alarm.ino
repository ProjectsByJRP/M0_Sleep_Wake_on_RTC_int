#include <RTCZero.h>

RTCZero zerortc;

// Set how often alarm goes off here
const byte alarmSeconds = 30;
const byte alarmMinutes = 0;
const byte alarmHours = 0;


volatile bool alarmFlag = false; // Start awake

void setup()
{
  Serial.begin(9600);
  delay(3000); // Wait for console
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  zerortc.begin(); // Set up clocks and such
  
  resetAlarm();  // Set alarm
  zerortc.attachInterrupt(alarmMatch); // Set up a handler for the alarm
}

void loop()
{
  if (alarmFlag == true) {
        alarmFlag = false;  // Clear flag
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Alarm went off - I'm awake!");
      }
  resetAlarm();  // Reset alarm before returning to sleep
  Serial.println("Alarm set, going to sleep now.");
  digitalWrite(LED_BUILTIN, LOW);
  zerortc.standbyMode();    // Sleep until next alarm match
}



void alarmMatch(void)
{
  alarmFlag = true; // Set flag
}

void resetAlarm(void) {
  byte seconds = 0;
  byte minutes = 0;
  byte hours = 0;
  byte day = 1;
  byte month = 1;
  byte year = 1;
  
  zerortc.setTime(hours, minutes, seconds);
  zerortc.setDate(day, month, year);

  zerortc.setAlarmTime(alarmHours, alarmMinutes, alarmSeconds);
  zerortc.enableAlarm(zerortc.MATCH_HHMMSS);
}
