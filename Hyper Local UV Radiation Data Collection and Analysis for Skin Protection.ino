#include <SparkFun_VEML6075_Arduino_Library.h>

VEML6075 uv;

#define BLYNK_PRINT 
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

double rawUva, rawUvb, Uva, Uvb, micro, milli, low_percent, high_percent, lowpercenttype1, lowpercenttype2, lowpercenttype3, lowpercenttype4, lowpercenttype5, lowpercenttype6, highpercenttype1, highpercenttype2, highpercenttype3, highpercenttype4, highpercenttype5, highpercenttype6, UvIndex;
double fitzmintype1 = 15000;
double fitzmintype2 = 25000;
double fitzmintype3 = 30000;
double fitzmintype4 = 40000;
double fitzmintype5 = 60000;
double fitzmintype6 = 90000;
double fitzmaxtype1 = 30000;
double fitzmaxtype2 = 40000;
double fitzmaxtype3 = 50000;
double fitzmaxtype4 = 60000;
double fitzmaxtype5 = 90000;
double fitzmaxtype6 = 150000;
String fitztype1 = "";
String fitztype2 = "";
String fitztype3 = "";
String fitztype4 = "";
String fitztype5 = "";
String fitztype6 = ""; 

BlynkTimer timer;

void sendSensor()
{
  double rawUva = uv.rawUva(); 
  double rawUvb = uv.rawUvb(); 
  double Uva = uv.uva(); 
  double Uvb = uv.uvb();
  double UvIndex = uv.index();
  lowpercenttype1 = minmedcalc(Uvb, fitzmintype1);
  highpercenttype1 = maxmedcalc(Uvb, fitzmaxtype1);
  lowpercenttype2 = minmedcalc(Uvb, fitzmintype2);
  highpercenttype2 = maxmedcalc(Uvb, fitzmaxtype2);
  lowpercenttype3 = minmedcalc(Uvb, fitzmintype3);
  highpercenttype3 = maxmedcalc(Uvb, fitzmaxtype3);
  lowpercenttype4 = minmedcalc(Uvb, fitzmintype4);
  highpercenttype4 = maxmedcalc(Uvb, fitzmaxtype4);
  lowpercenttype5 = minmedcalc(Uvb, fitzmintype5);
  highpercenttype5 = maxmedcalc(Uvb, fitzmaxtype5);
  lowpercenttype6 = minmedcalc(Uvb, fitzmintype6);
  highpercenttype6 = maxmedcalc(Uvb, fitzmaxtype6); 
  String fitztype1 = "Fitzpatrik Type 1 Vulnerability Percentages: " + String(highpercenttype1) + "% - " + String(lowpercenttype1) + "%";
  String fitztype2 = "Fitzpatrik Type 2 Vulnerability Percentages: " + String(highpercenttype2) + "% - " + String(lowpercenttype2) + "%";
  String fitztype3 = "Fitzpatrik Type 3 Vulnerability Percentages: " + String(highpercenttype3) + "% - " + String(lowpercenttype3) + "%";
  String fitztype4 = "Fitzpatrik Type 4 Vulnerability Percentages: " + String(highpercenttype4) + "% - " + String(lowpercenttype4) + "%";
  String fitztype5 = "Fitzpatrik Type 5 Vulnerability Percentages: " + String(highpercenttype5) + "% - " + String(lowpercenttype5) + "%";
  String fitztype6 = "Fitzpatrik Type 6 Vulnerability Percentages: " + String(highpercenttype6) + "% - " + String(lowpercenttype6) + "%"; 
  Blynk.virtualWrite(V0, rawUva);
  Blynk.virtualWrite(V1, rawUvb);
  Blynk.virtualWrite(V2, Uva);
  Blynk.virtualWrite(V3, Uvb);
  Blynk.virtualWrite(V4, fitztype1);
  Blynk.virtualWrite(V5, fitztype2);
  Blynk.virtualWrite(V6, fitztype3);
  Blynk.virtualWrite(V7, fitztype4);
  Blynk.virtualWrite(V8, fitztype5);
  Blynk.virtualWrite(V9, fitztype6);
  Blynk.virtualWrite(V10, UvIndex);

}

void setup() {

  Serial.begin(9600);
  Wire.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  if (!uv.begin())
  {
    Serial.println("Unable to communicate with VEML6075.");
    while (1);
  }

  timer.setInterval(1000L, sendSensor);

}

void loop() {

  Blynk.run();
  timer.run();

}

double microtomilli(double micro) {

milli = micro * 1000;

return milli;

}

double minmedcalc(double input_Uvb, double min_med) {

  low_percent = (input_Uvb / min_med) * 100;

  return low_percent;

}

double maxmedcalc(double input_Uvb, double max_med) {

  high_percent = (input_Uvb / max_med) * 100;

  return high_percent;

}



