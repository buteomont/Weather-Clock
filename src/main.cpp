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
#include <pgmspace.h>
#include <NTPClient.h>
#include <OLED_I2C.h> //http://www.rinkydinkelectronics.com/library.php?id=95
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "weatherClock.h"
#include "secrets.h"
#include "weatherIcons.h"

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
IPAddress weatherAddr; //IP address of WEATHER_HOST
boolean weatherIsFetched=false;

StaticJsonDocument<WEATHER_SIZE> jDoc; //this will hold the weather query results
//DynamicJsonDocument jDoc(WEATHER_SIZE); //this will hold the weather query results
char weatherBuff[WEATHER_SIZE];
char iconBuffer[ICON_SIZE];

//Convert e.g. 130 degrees to "SE"
void windDirection(char* compass, int degrees)
  {
  yield();
  if (degrees>349 || degrees<12)
    strcpy(compass,"N");
  else if (degrees>11 && degrees<33)
    strcpy(compass,"NNE");
  else if (degrees>32 && degrees<56)
    strcpy(compass,"NE");
  else if (degrees>55 && degrees<78)
    strcpy(compass,"ENE");
  else if (degrees>77 && degrees<101)
    strcpy(compass,"E");
  else if (degrees>100 && degrees<124)
    strcpy(compass,"ESE");
  else if (degrees>123 && degrees<146)
    strcpy(compass,"SE");
  else if (degrees>145 && degrees<168)
    strcpy(compass,"SSE");
  else if (degrees>167 && degrees<192)
    strcpy(compass,"S");
  else if (degrees>191 && degrees<213)
    strcpy(compass,"SSW");
  else if (degrees>212 && degrees<237)
    strcpy(compass,"SW");
  else if (degrees>236 && degrees<259)
    strcpy(compass,"WSW");
  else if (degrees>258 && degrees<281)
    strcpy(compass,"W");
  else if (degrees>280 && degrees<304)
    strcpy(compass,"WNW");
  else if (degrees>303 && degrees<326)
    strcpy(compass,"NW");
  else if (degrees>325 && degrees<350)
    strcpy(compass,"NNW");
  else
    sprintf(compass,"%03d",degrees);
  }

void pickIcon(const char* iconCode)
  {
//  ESP.wdtFeed();
  yield(); //Let the dog eat
  if (strcmp(iconCode,"01d")==0)
    memcpy_P(iconBuffer,clearSkyDay,ICON_SIZE);
  else if (strcmp(iconCode,"02d")==0)
    memcpy_P(iconBuffer,fewCloudsDay,ICON_SIZE);
  else if (strcmp(iconCode,"03d")==0)
    memcpy_P(iconBuffer,scatteredCloudsDay,ICON_SIZE);
  else if (strcmp(iconCode,"04d")==0)
    memcpy_P(iconBuffer,brokenCloudsDay,ICON_SIZE);
  else if (strcmp(iconCode,"09d")==0)
    memcpy_P(iconBuffer,showerRainDay,ICON_SIZE);
  else if (strcmp(iconCode,"10d")==0)
    memcpy_P(iconBuffer,rainDay,ICON_SIZE);
  else if (strcmp(iconCode,"11d")==0)
    memcpy_P(iconBuffer,thunderstormDay,ICON_SIZE);
  else if (strcmp(iconCode,"13d")==0)
    memcpy_P(iconBuffer,snowDay,ICON_SIZE);
  else if (strcmp(iconCode,"50d")==0)
    memcpy_P(iconBuffer,mistDay,ICON_SIZE);
  else if (strcmp(iconCode,"01n")==0)
    memcpy_P(iconBuffer,clearSkyNight,ICON_SIZE);
  else if (strcmp(iconCode,"02n")==0)
    memcpy_P(iconBuffer,fewCloudsNight,ICON_SIZE);
  else if (strcmp(iconCode,"03n")==0)
    memcpy_P(iconBuffer,scatteredCloudsNight,ICON_SIZE);
  else if (strcmp(iconCode,"04n")==0)
    memcpy_P(iconBuffer,brokenCloudsNight,ICON_SIZE);
  else if (strcmp(iconCode,"09n")==0)
    memcpy_P(iconBuffer,showerRainNight,ICON_SIZE);
  else if (strcmp(iconCode,"10n")==0)
    memcpy_P(iconBuffer,rainNight,ICON_SIZE);
  else if (strcmp(iconCode,"11n")==0)
    memcpy_P(iconBuffer,thunderstormNight,ICON_SIZE);
  else if (strcmp(iconCode,"13n")==0)
    memcpy_P(iconBuffer,snowNight,ICON_SIZE);
  else if (strcmp(iconCode,"50n")==0)
    memcpy_P(iconBuffer,mistNight,ICON_SIZE);
  else 
    memset(iconBuffer,0,ICON_SIZE);
  }

void displayWeather(JsonObject jo)
  {
  const char* conditions=jo["current"]["weather"][0]["main"].as<char*>();
  int temperature=(int)jo["current"]["temp"].as<float>();
  int wind=(int)jo["current"]["wind_speed"].as<float>();
  const char* icon=jo["current"]["weather"][0]["icon"].as<char*>();
  int windDir=jo["current"]["wind_deg"].as<int>();
  pickIcon(icon); //goes into global iconBuffer
  char comp[4];
  windDirection(comp,windDir);
  int humidity=jo["current"]["humidity"].as<int>();
  const char* alert=jo["alerts"][0]["event"].as<char*>();


  myOLED.setFont(SmallFont);
  myOLED.drawBitmap(0,0,(uint8_t *)iconBuffer,32,32);
  myOLED.print(conditions,LEFT,34);

  myOLED.print(String(humidity)+String("%  ")+String(temperature)+String("~F"),RIGHT,24); 
  if (wind>0)
    myOLED.print(String(wind)+String(" MPH ")+String(comp),RIGHT,36);
  else
    myOLED.print(String("Wind is calm"),RIGHT,36);

  myOLED.print(String(alert),CENTER,53);
  }

void updateWeather()
  {
  digitalWrite(LED_BUILTIN,LOW); //turn on the LED
  Serial.print(timeClient.getFormattedTime());
  Serial.print("\tRefreshing weather...");
  connectToWiFi(); //may need to connect to the wifi

  //Fetch the weather JSON object
  ESP.wdtFeed();
  if(!wifiClient.connect(weatherAddr, 80))
    {
    Serial.println("connection failed");
    }
  else 
    {
    Serial.println("connected to server...");
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
        Serial.println("...done.");
        weatherIsFetched=true;
        JsonObject documentRoot = jDoc.as<JsonObject>();
//        printJson(documentRoot,"root");
        displayWeather(documentRoot);
        }
      else
        {
        Serial.print("...Error: ");
        Serial.println(de.code());
        }
      }
    else
      {
      Serial.print("...No results available.  ");
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
  Serial.print("\tRefreshing time...");
  connectToWiFi(); //may need to connect to the wifi
  if (settingsAreValid && WiFi.status() == WL_CONNECTED)
    {
    bool timeGood=timeClient.update();
    if (timeGood)
      {
      timeClient.setTimeOffset(settings.gmtOffset*3600);
      Serial.println("done.");
      }
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
//  ESP.wdtEnable(WDTO_8S);
  pinMode(LED_BUILTIN,OUTPUT);// The blue light on the board shows WiFi activity

  Serial.begin(115200);
  Serial.setTimeout(10000);
  Serial.println();
  
  while (!Serial); // wait here for serial port to connect.

  Serial.print("Setting size is ");
  Serial.println(sizeof(settings));
  EEPROM.begin(sizeof(settings)); //fire up the eeprom section of flash
  commandString.reserve(200); // reserve 200 bytes of serial buffer space for incoming command string

  boolean oledGood=myOLED.begin(SSD1306_128X64);
  if (!oledGood)
    {
    Serial.println("Problem allocating display buffer!");
    delay(100000);
    }
  myOLED.setBrightness(100);
  myOLED.rotateDisplay(true); //display is upside down in the container
  myOLED.setFont(SmallFont);
  myOLED.clrScr();

  myOLED.print("Initializing...",LEFT,0);
  myOLED.update();

  Serial.println("Loading settings");
  loadSettings(); //set the values from eeprom
  
  if (settingsAreValid) //Get the initial time setting
    {
    Serial.println("Fixing weather URL");
    strcpy(properURL,WEATHER_URL);
    fixup(properURL);
    myOLED.print("Connecting to WiFi...",LEFT,12);
    myOLED.update();
    Serial.println("Connecting to WiFi");
    connectToWiFi(); //connect to the wifi
    myOLED.print("Fetching time and",LEFT,24);
    myOLED.print("weather...",LEFT,36);
    myOLED.update();
    }
  else
    {
    myOLED.print("Settings not valid.",LEFT,26);
    myOLED.update();
    }
  }

void loop()
  {
  static unsigned long lastTime=timeClient.getEpochTime();
  ESP.wdtFeed();  
  checkForCommand(); // Check for input in case something needs to be changed to work

  unsigned long currentTime=timeClient.getEpochTime();
  if (settingsAreValid && currentTime != lastTime)
    {
    //Update the time every 12 hours, or if we just powered up
    if (currentTime%43200 ==0 || timeClient.getEpochTime() < 100000)
      {
      updateTime();
      }
    lastTime=currentTime;

    unsigned long today=timeClient.getEpochTime();
    char datebuff[32];
    sprintf(datebuff, "%02d/%02d/%04d", month(today), day(today), year(today));
    myOLED.print(String(datebuff),RIGHT,0);
    myOLED.print(timeClient.getFormattedTime(),RIGHT,12);

    //Update the weather every five minutes
    if (currentTime%300 ==0 || !weatherIsFetched)
      {
      myOLED.clrScr();
      updateWeather();
      }
    myOLED.update();
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
   
    WiFi.mode(WIFI_STA); //station mode, we are only a client in the wifi world
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

  //get the address of the weather service if not already set.
  //We have to do this here because we get a WDT reset if 
  //we try to get the weather data when using the host name
  //instead of the address.  
  if (!weatherAddr.isSet())
    {
    WiFi.hostByName(WEATHER_HOST,weatherAddr,500);
    ESP.wdtFeed();
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

