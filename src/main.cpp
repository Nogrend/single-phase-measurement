#include <Arduino.h>
#include <SDM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SignalLed.h>
#include <../login.h>

SDM sdm(Serial, SDM_UART_BAUD, NOT_A_PIN, SERIAL_8N1, false);

WiFiClient espClient;
PubSubClient client(espClient);

constexpr int LED_PIN_ANODE = 15;
constexpr int LED_PIN_CATHODE = 16;
SignalLed signalLed(LED_PIN_ANODE, LED_PIN_CATHODE);

void setup_wifi() {
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        signalLed.setSignalLedRed();
        delay(250);
        signalLed.setSignalLedOff();
    }
}

void reconnect() {
    while (!client.connected()) {
        if (!client.connect(deviceId, mqttUsername, mqttPassword)) {
            delay(2500);
            signalLed.setSignalLedRed();
            delay(2500);
            signalLed.setSignalLedOff();
        }
    }
}

void setup() {
    signalLed.init();
    signalLed.setSignalLedRed();

    sdm.begin();
    setup_wifi();
    client.setServer(mqttServer, mqttPort);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    signalLed.setSignalLedGreen();

    const float voltage = sdm.readVal(SDM_PHASE_1_VOLTAGE);
    const float current = sdm.readVal(SDM_PHASE_1_CURRENT);
    const float power = sdm.readVal(SDM_PHASE_1_POWER);
    const float apparentPower = sdm.readVal(SDM_PHASE_1_APPARENT_POWER);
    const float reactivePower = sdm.readVal(SDM_PHASE_1_REACTIVE_POWER);
    const float powerFactor = sdm.readVal(SDM_PHASE_1_POWER_FACTOR);
    const float angle = sdm.readVal(SDM_PHASE_1_ANGLE);
    const float frequency = sdm.readVal(SDM_FREQUENCY);
    const float importActiveEnergy = sdm.readVal(SDM_IMPORT_ACTIVE_ENERGY);
    const float exportActiveEnergy = sdm.readVal(SDM_EXPORT_ACTIVE_ENERGY);
    const float importReactiveEnergy = sdm.readVal(SDM_IMPORT_REACTIVE_ENERGY);
    const float exportReactiveEnergy = sdm.readVal(SDM_EXPORT_REACTIVE_ENERGY);

    char dataPayload[200];
    sprintf(dataPayload, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",
            voltage, current, power, apparentPower, reactivePower, powerFactor, angle,
            frequency, importActiveEnergy, exportActiveEnergy, importReactiveEnergy, exportReactiveEnergy);

    client.publish(mqttTopic, dataPayload);

    signalLed.setSignalLedOff();
    delay(10000);
}
