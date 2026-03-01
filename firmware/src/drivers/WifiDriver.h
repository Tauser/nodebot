#pragma once

class WifiDriver
{
public:
    bool init();
    bool connect(const char* ssid, const char* password);
    void disconnect();
    bool isConnected() const;
    int getSignalStrength() const; 

private:
    bool _connected;
};