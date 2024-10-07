#include "SignalLed.h"

SignalLed::SignalLed(const uint8_t ledPinAnode, const uint8_t ledPinCathode)
  : _ledPinAnode(ledPinAnode), _ledPinCathode(ledPinCathode) {}

void SignalLed::init() const {
  pinMode(_ledPinAnode, OUTPUT);
  pinMode(_ledPinCathode, OUTPUT);
}

void SignalLed::setSignalLedRed() const {
  digitalWrite(_ledPinAnode, HIGH);
  digitalWrite(_ledPinCathode, LOW);
}

void SignalLed::setSignalLedGreen() const {
  digitalWrite(_ledPinAnode, LOW);
  digitalWrite(_ledPinCathode, HIGH);
}

void SignalLed::setSignalLedOff() const {
  digitalWrite(_ledPinAnode, LOW);
  digitalWrite(_ledPinCathode, LOW);
}