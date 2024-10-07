#ifndef SIGNALLED_H
#define SIGNALLED_H

#include "Arduino.h"

class SignalLed {
    public:
      SignalLed(uint8_t ledPinAnode, uint8_t ledPinCathode);
      void init() const;
      void setSignalLedRed() const;
      void setSignalLedGreen() const;
      void setSignalLedOff() const;

    private:
       const uint8_t _ledPinAnode;
       const uint8_t _ledPinCathode;
};

#endif //SIGNALLED_H
