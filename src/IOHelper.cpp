#include "IOHelper.h"

IOHelper::IOHelper(/*Pin-Nr*/ uint8_t pin, /*Debounce-Time*/ uint8_t time, /*Flankenerkennung*/ bool flanke, /*Toggle*/ bool toggle, /*Blink*/ bool blink)
{
    pinMode(pin, INPUT_PULLUP);
    debounce_time = time;
    pinNr = pin;
    flankeOn = flanke;
    toggleOn = toggle;
    blinkOn = blink;
}

IOHelper::~IOHelper()
{
}

void IOHelper::poll()
{
    // Entprellen
    if (debounce_time)
    {
        out = entprellen(digitalRead(pinNr));
    }

    // Flankenerkennung
    if (flankeOn)
    {
        out = FlankeP(out);
    }

    // Toggle
    if (toggleOn)
    {
        out = toggle(out);
    }

        // Blink
    if (blinkOn)
    {
        out = blink(out);
    }
}

bool IOHelper::get()
{
    return out;
}

bool IOHelper::toggle(bool in)
{
    if (in)
        tgl = !tgl;
    return tgl;
}

bool IOHelper::FlankeP(bool in)
{
    bool flankeAusgang = false;
    if (in > flankeVorher)
    {
        flankeAusgang = true;
        // Serial.println(".");
    }
    flankeVorher = in;
    return flankeAusgang;
}

bool IOHelper::entprellen(bool in)
{
    if (millis() - zeitmerker > debounce_time)
    {
        if (prellMerker == in)
        {
            entprellt = in;
            // Serial.println(".");
        }
        zeitmerker = millis();
    }
    prellMerker = in;
    return entprellt;
}

bool IOHelper::blink(bool in)
{
    if (in)
    {
        if (millis() - zeitmerkerBlink > blinktime)
        {
            blinkOut = !blinkOut;
            zeitmerkerBlink = millis();
        }
    }
    else
        blinkOut = false;

    return blinkOut;
}