#include <Arduino.h>

class IOHelper
{
private:
    uint8_t debounce_time = 0;
    uint8_t pinNr = 0;

    bool prellMerker = false;
    bool entprellt = false;
    unsigned long zeitmerker = 0;
    bool flankeVorher = false;

    bool flankeOn = false;
    bool toggleOn = false;
    bool blinkOn = false;
    unsigned long zeit_vorher = 0;
    bool tgl = false;
    unsigned long zeitmerkerBlink = 0;
    bool blinkOut = false;
    uint16_t blinktime = 300;

    bool out = false;

    bool toggle(bool in);
    bool FlankeP(bool in);
    bool entprellen(bool in);
    bool blink(bool in);

public:
    // Hilfe-Text
    IOHelper(/*Pin-Nr*/ uint8_t, /*Debounce-Time*/ uint8_t, /*Flankenerkennung*/ bool, /*Toggle*/ bool, /*Blink*/ bool );
    ~IOHelper();

    void poll();
    bool get();
};

///////////////////////////////
