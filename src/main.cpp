#include <Arduino.h>
/**
 * This is an ESP8266 program to display the time and weather on an
 * OLED display.
 *
 * Configuration is done via serial connection.  Enter:
 *  ssid=<wifi ssid>
 *  wifipass=<wifi password>
 *  sleepTime=<seconds to sleep between measurements> (set to zero for continuous readings)
 */ 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <OLED_I2C.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include "weatherClock.h"
#include "secrets.h"

OLED myOLED(SDA, SCL);
extern uint8_t TinyFont[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

WiFiClient wifiClient;
HTTPClient http;

// These are the settings that get stored in EEPROM.  They are all in one struct which
// makes it easier to store and retrieve.
typedef struct 
  {
  unsigned int validConfig=0; 
  char ssid[SSID_SIZE] = "";
  char wifiPassword[PASSWORD_SIZE] = "";
  int sleepTime=10; //seconds to sleep between distance checks
  int gmtOffset=0;  // -5 for CDT
  double latitude=0.0;  //for weather report
  double longitude=0.0; 
  char address[ADDRESS_SIZE]=""; //static address for this device
  char netmask[ADDRESS_SIZE]=""; //netmask for static address
  } conf;

conf settings; //all settings in one struct makes it easier to store in EEPROM
boolean settingsAreValid=false;

String commandString = "";     // a String to hold incoming commands from serial
bool commandComplete = false;  // goes true when enter is pressed

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

char properURL[sizeof WEATHER_URL + sizeof WEATHER_KEY];

StaticJsonDocument<WEATHER_SIZE> jDoc; //this will hold the weather query results
char weatherBuff[WEATHER_SIZE];

void printJson(JsonObject jo, String parent)
  {
  for (JsonPair keyValue : jo) 
    {
    yield();
    if (keyValue.value().nesting()>0)
      {
      String newParent=parent+"."+keyValue.key().c_str();
      printJson(keyValue.value(),newParent);
      }
    else
      {
      Serial.print(parent+".");
      Serial.print(keyValue.key().c_str());
      Serial.print("=");
      Serial.print(keyValue.value().as<char*>());
      Serial.print(keyValue.value().as<float>());
      Serial.println(keyValue.value().nesting());
      }
    }

  }

void updateWeather()
  {
  digitalWrite(LED_BUILTIN,LOW); //turn on the LED
  Serial.print(timeClient.getFormattedTime());
  Serial.print("\t");
  Serial.println("Refreshing weather");
  connectToWiFi(); //may need to connect to the wifi

  //Fetch the weather JSON object
  if(!wifiClient.connect(WEATHER_HOST, 80)) 
    {
    Serial.println("connection failed");
    }
  else 
    {
    Serial.println("Connected to server");
    String url=String("http://")+String(WEATHER_HOST)+String(properURL);
    Serial.println("Fetching \""+url+"\""); 
    http.begin(wifiClient, url);
    int httpCode=http.GET();
    if (httpCode>0)
      {
      DeserializationError de=deserializeJson(jDoc,http.getStream());
      // ReadLoggingStream loggingStream(http.getStream(), Serial);
      // DeserializationError de=deserializeJson(jDoc, loggingStream);
      if (de.code()==de.Ok)
        {
        Serial.println("Weather refreshed.");
        JsonObject documentRoot = jDoc.as<JsonObject>();
        printJson(documentRoot,"root");
        }
      else
        {
        Serial.print("Error: ");
        Serial.println(de.code());
        }
      }
    else
      {
      Serial.println("No results available.");
      Serial.print("Code: ");
      Serial.println(httpCode);
      }
    }

  if(!wifiClient.connected())
    {
    // if the server's disconnected, stop the client:
    Serial.println("disconnected");
    wifiClient.stop();
    }  

  digitalWrite(LED_BUILTIN,HIGH); //turn off the LED
  }

void updateTime()
  {
  digitalWrite(LED_BUILTIN,LOW); //turn on the LED
  Serial.print(timeClient.getFormattedTime());
  Serial.print("\t");
  Serial.println("Refreshing time");
  connectToWiFi(); //may need to connect to the wifi
  if (settingsAreValid && WiFi.status() == WL_CONNECTED)
    {
    bool timeGood=timeClient.update();
    if (timeGood)
      timeClient.setTimeOffset(settings.gmtOffset*3600);
    else
      Serial.println("***** Unable to refresh time *****");
    }
  digitalWrite(LED_BUILTIN,HIGH); //turn off the LED
  } 

void fixup(char* rawString)
  {
  String rs=String(rawString);
  rs.replace("{latitude}",String(settings.latitude,4));
  rs.replace("{longitude}",String(settings.longitude,4));
  rs.replace("{key}",WEATHER_KEY);
  strcpy(rawString,rs.c_str());
  }

void setup() 
  {
  ESP.wdtEnable(WDTO_8S);
  pinMode(LED_BUILTIN,OUTPUT);// The blue light on the board shows WiFi activity

  Serial.begin(115200);
  Serial.setTimeout(10000);
  Serial.println();
  
  while (!Serial); // wait here for serial port to connect.

  Serial.print("Setting size is ");
  Serial.println(sizeof(settings));
  EEPROM.begin(sizeof(settings)); //fire up the eeprom section of flash
  commandString.reserve(200); // reserve 200 bytes of serial buffer space for incoming command string

  loadSettings(); //set the values from eeprom
  
  if (settingsAreValid) //Get the initial time setting
    {
    strcpy(properURL,WEATHER_URL);
    fixup(properURL);
    connectToWiFi(); //connect to the wifi
    Serial.println("updating time");
//    timeClient.begin(); //this crashes for some reason, but apparently not needed anyway
    updateTime();
    updateWeather();
    }

  boolean oledGood=myOLED.begin(SSD1306_128X64);
  if (!oledGood)
    {
    Serial.println("Problem allocating display buffer!");
    delay(100000);
    }
  myOLED.setBrightness(100);
  }
 
void showTime()
  {
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print(timeClient.getFormattedTime(),RIGHT,0);
  myOLED.update();
  }

void loop()
  {
  static unsigned long lastTime=timeClient.getEpochTime();

  ESP.wdtFeed();
  
  checkForCommand(); // Check for input in case something needs to be changed to work

  unsigned long currentTime=timeClient.getEpochTime();
  if (settingsAreValid && currentTime != lastTime)
    {
    if (currentTime%30 ==0 || timeClient.getEpochTime() < 100000)
      {
      updateTime();
      }
    lastTime=currentTime;
    showTime();

    if (currentTime%60 ==0)
      {
      updateWeather();
      }
    }
  }
  
/*
 * If not connected to wifi, connect.
 */
void connectToWiFi()
  {
  if (WiFi.status() != WL_CONNECTED)
    {
    Serial.print("Attempting to connect to WPA SSID \"");
    Serial.print(settings.ssid);
    Serial.println("\"");

//    WiFi.forceSleepWake(); //turn on the radio
//    delay(1);              //return control to let it come on
    
    WiFi.mode(WIFI_STA); //station mode, we are only a client in the wifi world
    ESP.wdtFeed(); //feed the watchdog timers. Connecting may take a while.
    WiFi.begin(settings.ssid, settings.wifiPassword);
    while (WiFi.status() != WL_CONNECTED) 
      {
      // not yet connected
      Serial.print(".");
      checkForCommand(); // Check for input in case something needs to be changed to work
      ESP.wdtFeed(); //feed the watchdog timers.
      delay(500);
      }
  
    Serial.println("Connected to network.");
    Serial.println();
    }
  }

void showSettings()
  {
  char buffer[COORDINATE_SIZE];
  Serial.print("ssid=<wifi ssid> (");
  Serial.print(settings.ssid);
  Serial.println(")");
  Serial.print("wifipass=<wifi password> (");
  Serial.print(settings.wifiPassword);
  Serial.println(")");
  Serial.print("sleeptime=<seconds to sleep between measurements> (");
  Serial.print(settings.sleepTime);
  Serial.println(")");
  Serial.print("offset=<hours from GMT to display> (");
  Serial.print(settings.gmtOffset);
  Serial.println(")");
  Serial.print("latitude=<latitude in decimal degrees> (");
  sprintf(buffer,"%2.4f",settings.latitude);
  Serial.print(buffer);
  Serial.println(")");
  Serial.print("longitude=<longitude in decimal degrees> (");
  sprintf(buffer,"%2.4f",settings.longitude);
  Serial.print(buffer);
  Serial.println(")");
  Serial.println("\n*** Use \"factorydefaults=yes\" to reset all settings ***\n");
  }

/*
 * Check for configuration input via the serial port.  Return a null string 
 * if no input is available or return the complete line otherwise.
 */
String getConfigCommand()
  {
  if (commandComplete) 
    {
    //Serial.println(commandString);
    String newCommand=commandString;

    commandString = "";
    commandComplete = false;
    return newCommand;
    }
  else return "";
  }

bool processCommand(String cmd)
  {
  const char *str=cmd.c_str();
  char *val=NULL;
  char *nme=strtok((char *)str,"=");
  if (nme!=NULL)
    val=strtok(NULL,"=");

  //Get rid of the carriage return
  if (val!=NULL && strlen(val)>0 && val[strlen(val)-1]==13)
    val[strlen(val)-1]=0; 

  if (nme==NULL || val==NULL || strlen(nme)==0 || strlen(val)==0)
    {
    showSettings();
    return false;   //not a valid command, or it's missing
    }
  else if (strcmp(nme,"ssid")==0)
    {
    strcpy(settings.ssid,val);
    saveSettings();
    }
  else if (strcmp(nme,"wifipass")==0)
    {
    strcpy(settings.wifiPassword,val);
    saveSettings();
    }
  else if (strcmp(nme,"sleeptime")==0)
    {
    settings.sleepTime=atoi(val);
    saveSettings();
    }
  else if (strcmp(nme,"offset")==0)
    {
    settings.gmtOffset=atoi(val);
    saveSettings();
    }
  else if (strcmp(nme,"latitude")==0)
    {
    settings.latitude=(double)atof(val);
    saveSettings();
    }
  else if (strcmp(nme,"longitude")==0)
    {
    settings.longitude=(double)atof(val);
    saveSettings();
    }
 else if ((strcmp(nme,"factorydefaults")==0) && (strcmp(val,"yes")==0)) //reset all eeprom settings
    {
    Serial.println("\n*********************** Resetting EEPROM Values ************************");
    initializeSettings();
    saveSettings();
    delay(2000);
    ESP.restart();
    }
  else
    {
    showSettings();
    return false; //command not found
    }
  return true;
  }

void initializeSettings()
  {
  settings.validConfig=0; 
  strcpy(settings.ssid,"");
  strcpy(settings.wifiPassword,"");
  settings.sleepTime=10;
  settings.gmtOffset=0;
  settings.latitude=0.0;
  settings.longitude=0.0;
  }

void checkForCommand()
  {
  if (Serial.available())
    {
    serialEvent();
    String cmd=getConfigCommand();
    if (cmd.length()>0)
      {
      processCommand(cmd);
      }
    }
  }
  
/*
*  Initialize the settings from eeprom and determine if they are valid
*/
void loadSettings()
  {
  EEPROM.get(0,settings);
  if (settings.validConfig==VALID_SETTINGS_FLAG)    //skip loading stuff if it's never been written
    {
    settingsAreValid=true;
    Serial.println("Loaded configuration values from EEPROM");
    }
  else
    {
    Serial.println("Skipping load from EEPROM, device not configured.");    
    settingsAreValid=false;
    }
  }

/*
 * Save the settings to EEPROM. Set the valid flag if everything is filled in.
 */
boolean saveSettings()
  {
  if (strlen(settings.ssid)>0 &&
    strlen(settings.wifiPassword)>0)
    {
    Serial.println("Settings deemed complete");
    settings.validConfig=VALID_SETTINGS_FLAG;
    settingsAreValid=true;
    }
  else
    {
    Serial.println("Settings still incomplete");
    settings.validConfig=0;
    settingsAreValid=false;
    }
    
  EEPROM.put(0,settings);
  return EEPROM.commit();
  }

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() 
  {
  while (Serial.available()) 
    {
    // get the new byte
    char inChar = (char)Serial.read();
    Serial.print(inChar);

    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it 
    if (inChar == '\n') 
      {
      commandComplete = true;
      }
    else
      {
      // add it to the inputString 
      commandString += inChar;
      }
    }
  }

