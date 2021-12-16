#include <ArduinoIoTCloud.h>https://github.com/romanvillarrord/FitPal
#include <Arduino_ConnectionHandler.h>
const char THING_ID[]           = "f4bcf355-5b3d-40e8-af16-b3cdfcaf6673";
const char DEVICE_LOGIN_NAME[]  = "5c90a600-41bf-4226-959c-d11dd8447717";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onEffectiverepsChange();
void onEffectiveornotChange();
void onMvwifiChange();

int effectivereps;
bool effectiveornot;
int mvwifi;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(effectivereps, READWRITE, ON_CHANGE, onEffectiverepsChange);
  ArduinoCloud.addProperty(effectiveornot, READWRITE, ON_CHANGE, onEffectiveornotChange);
  ArduinoCloud.addProperty(mvwifi, READWRITE, ON_CHANGE, onMvwifiChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
