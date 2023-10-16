#include "KeypadModule.h"
#include "MeshService.h"
#include "NodeDB.h"
#include "RTC.h"
#include "Router.h"
#include "configuration.h"
#include "main.h"
#include "keypad/Key.h"
#include "keypad/Keypad.h"
#include "keypad/Keypad_I2C.h"

#define I2CADDR 0x38 // Set the Address of the PCF8574

const byte ROWS = 4; // Set the number of Rows
const byte COLS = 4; // Set the number of Columns

// Set the Key at Use (4x4)
char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// define active Pin (4x4)
byte rowPins [ROWS] = {0, 1, 2, 3}; // Connect to Keyboard Row Pin
byte colPins [COLS] = {4, 5, 6, 7}; // Connect to Pin column of keypad.

// makeKeymap (keys): Define Keymap
// rowPins:Set Pin to Keyboard Row
// colPins: Set Pin Column of Keypad
// ROWS: Set Number of Rows.
// COLS: Set the number of Columns
// I2CADDR: Set the Address for i2C
// PCF8574: Set the number IC
Keypad_I2C keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574, &Wire1);

bool keypad_setup = false;

#define WATCH_INTERVAL_MSEC (30 * 1000)

KeypadModule::KeypadModule()
    : ProtobufModule("remotehardware", meshtastic_PortNum_REMOTE_HARDWARE_APP, &meshtastic_HardwareMessage_msg),
      concurrency::OSThread("RemoteHardwareModule")
{
}

bool KeypadModule::handleReceivedProtobuf(const meshtastic_MeshPacket &req, meshtastic_HardwareMessage *pptr)
{
    if (moduleConfig.remote_hardware.enabled) {
        auto p = *pptr;
        LOG_INFO("Received RemoteHardware type=%d\n", p.type);
    }

    return false;
}

int32_t KeypadModule::runOnce()
{
    if (true) { // replace with moduleConfig.remote_hardware.enabled
        // Wire.begin(38,39); // Call the connection Wire
        keypad.begin(makeKeymap (keys)); // Call the connection
    }
    if (true) {
        uint32_t now = millis();

        if (now - lastWatchMsec >= WATCH_INTERVAL_MSEC) {
            char key = keypad.getKey();
            if (key != NO_KEY)
            {
                LOG_INFO("Broadcasting keypad pressed %c!\n", key);

                // Something changed!  Tell the world with a broadcast message
                meshtastic_HardwareMessage r =  {meshtastic_HardwareMessage_Type_GPIOS_CHANGED, 0, (uint64_t)key};//meshtastic_HardwareMessage_init_default;
                // LOG_DEBUG("keypad gpio_value1: %u\n",(uint8_t)r.gpio_mask);
                r.type = meshtastic_HardwareMessage_Type_GPIOS_CHANGED;
                // r.gpio_mask = (uint64_t)key;
                r.gpio_value = (uint64_t)key;
                // LOG_DEBUG("keypad gpio_value2: %u\n",(uint8_t)r.gpio_mask);
                meshtastic_MeshPacket *p = allocDataProtobuf(r);
                service.sendToMesh(p);
            }
            
        }
    } else {
        // No longer watching anything - stop using CPU
        return disable();
    }

    return 50; // Poll our GPIOs every 200ms (FIXME, make adjustable via protobuf arg)
}
