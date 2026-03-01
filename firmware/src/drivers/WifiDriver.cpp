#include "WifiDriver.h"
#include <WiFi.h>

bool WifiDriver::init()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true); // Limpa o estado
    _connected = false;
    return true;
}

bool WifiDriver::connect(const char* ssid, const char* password)
{
    WiFi.begin(ssid, password);
    return true; 
}

void WifiDriver::disconnect()
{
    WiFi.disconnect(true);
    _connected = false;
}

bool WifiDriver::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

int WifiDriver::getSignalStrength() const
{
    if (isConnected()) {
        return WiFi.RSSI();
    }
    return -100; 
}