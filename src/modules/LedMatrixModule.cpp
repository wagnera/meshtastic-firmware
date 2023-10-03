/**
 * @file ExternalNotificationModule.cpp
 * @brief Implementation of the ExternalNotificationModule class.
 *
 * This file contains the implementation of the ExternalNotificationModule class, which is responsible for handling external
 * notifications such as vibration, buzzer, and LED lights. The class provides methods to turn on and off the external
 * notification outputs and to play ringtones using PWM buzzer. It also includes default configurations and a runOnce() method to
 * handle the module's behavior.
 *
 * Documentation:
 * https://meshtastic.org/docs/settings/moduleconfig/external-notification
 *
 * @author Jm Casler & Meshtastic Team
 * @date [Insert Date]
 */
#include "LedMatrixModule.h"
#include "MeshService.h"
#include "NodeDB.h"
#include "RTC.h"
#include "Router.h"
#include "configuration.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "main.h"



/*
    Documentation:
        https://meshtastic.org/docs/settings/moduleconfig/external-notification
*/




LedMatrixModule *ledMatrixModule;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 34,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

bool matrix_setup = false;
bool scroll_done = true;
bool current_animation = false;
const char *current_text;
size_t current_text_length;
uint16_t current_color;
int scroll_x;

char text_trigger = 'L';

static const char* const text_messages[] = {"This is a test", "Lunch Time!!", "Foos o'clock!", "Zito's Time!", "Thai Tuesday Time!", "Thai Thursday Time!"};
static const int text_sizes[] = {sizeof("This is a test"),sizeof("Lunch Time!!"), sizeof("Foos o'clock!"), sizeof("Zito's Time!"), sizeof("Thai Tuesday!"), sizeof("Thai Thursday!")};

// Function to convert Unix time to Central Time (CT) with DST adjustments
tm unixTimeToCT(long long unixTime) {
    time_t rawTime = (time_t)unixTime;
    struct tm *ctTimeInfo;

    // Define Central Time (CT) UTC offsets
    int ctOffsetStandard = -6; // Central Standard Time (CST) UTC offset
    int ctOffsetDST = -5;      // Central Daylight Time (CDT) UTC offset

    // Hard-coded DST transition times for the next 10 years (assuming DST starts on March 14 and ends on November 7)
    int dstTransitions[] = {
        1678846800, // March 14, 2023 - DST starts
        1700000000, // November 7, 2023 - DST ends
        1731166800, // March 12, 2024 - DST starts
        1752326000, // November 3, 2024 - DST ends
        1783492800, // March 11, 2025 - DST starts
        1804652000, // November 2, 2025 - DST ends
        1835818800, // March 10, 2026 - DST starts
        1856978000, // November 1, 2026 - DST ends
        1888144800, // March 9, 2027 - DST starts
        1909304000, // November 7, 2027 - DST ends
        // Add more years if needed
    };

    // Determine whether DST is in effect at the given Unix time
    int isDST = 0; // Default to standard time
    for (int i = 0; i < sizeof(dstTransitions) / sizeof(dstTransitions[0]); i += 2) {
        if (rawTime >= dstTransitions[i] && rawTime < dstTransitions[i + 1]) {
            isDST = 1; // DST is in effect
            break;
        }
    }

    // Adjust for the UTC offset based on DST
    int ctOffset = isDST ? ctOffsetDST : ctOffsetStandard;

    // Calculate the CT time
    rawTime += ctOffset * 3600; // Adjust for the UTC offset
    ctTimeInfo = gmtime(&rawTime); // Convert to CT time
    return *ctTimeInfo;
}

void scrollText()
{
    int text_pixel_width = current_text_length * 6;

    if (scroll_done)
    {
        LOG_DEBUG("Scrolling text setup\n");
        scroll_x = matrix.width();
        matrix.setTextColor(current_color);
        scroll_done = false;
    }
    else
    {
        matrix.fillScreen(0);
        matrix.setCursor(scroll_x, 0);
        matrix.print(F(current_text));

        if(--scroll_x < -text_pixel_width) {
            scroll_done = true;
            current_animation = false;
        }
        matrix.show();
        // delay(70);
    }
}

void displayTime()
{
    // Account for central timezone
    uint32_t current_unix_time = getValidTime(RTCQualityFromNet);
    if (current_unix_time != 0)
    {
        tm ctTimeInfo = unixTimeToCT(current_unix_time);

        matrix.setTextColor(current_color);
        matrix.fillScreen(0);
        matrix.setCursor(1, 1);
        char time_buf [6];
        snprintf(time_buf, 6, "%02i:%02i", ctTimeInfo.tm_hour,ctTimeInfo.tm_min);
        // LOG_DEBUG("Time string: %s\n",time_buf);
        matrix.print(F(time_buf));
        // matrix.print(F("10:31"));
    }
    else
    {
        matrix.setTextColor(matrix.Color(255, 0, 255));
        matrix.fillScreen(0);
        matrix.setCursor(11, 1);
        matrix.print(F(".."));
    }
    
    // matrix.print(F("10:31 AM"));

    matrix.show();
}

int32_t LedMatrixModule::runOnce()
{
    // if (!moduleConfig.led_matrix.enabled) {
    //     return INT32_MAX; // we don't need this thread here...
    // } else {
        
    //     return 25;
    // }
    if (!matrix_setup)
    {
        matrix.begin();
        matrix.setTextWrap(false);
        matrix.setBrightness(50);
        // matrix.setTextColor(colors[0]);
    }
    if(current_animation)
    {
        scrollText();
    }
    else
    {
        displayTime();
    }
    return 100;
}

bool LedMatrixModule::wantPacket(const meshtastic_MeshPacket *p)
{
    LOG_DEBUG("led want packet port: %i\n",p->decoded.portnum);
    // return 1;
    return MeshService::isTextPayload(p);
}

LedMatrixModule::LedMatrixModule()
    : SinglePortModule("LedMatrixModule", meshtastic_PortNum_TEXT_MESSAGE_APP),
      concurrency::OSThread("LedMatrixModule")
{
    /*
        Uncomment the preferences below if you want to use the module
        without having to configure it from the PythonAPI or WebUI.
    */

    // moduleConfig.external_notification.alert_message = true;
    // moduleConfig.external_notification.alert_message_buzzer = true;
    // moduleConfig.external_notification.alert_message_vibra = true;

    // moduleConfig.external_notification.active = true;
    // moduleConfig.external_notification.alert_bell = 1;
    // moduleConfig.external_notification.output_ms = 1000;
    // moduleConfig.external_notification.output = 4; // RAK4631 IO4
    // moduleConfig.external_notification.output_buzzer = 10; // RAK4631 IO6
    // moduleConfig.external_notification.output_vibra = 28; // RAK4631 IO7
    // moduleConfig.external_notification.nag_timeout = 300;

    if (moduleConfig.external_notification.enabled) {
        
    } else {
        LOG_INFO("External Notification Module Disabled\n");
        disable();
    }
}

ProcessMessage LedMatrixModule::handleReceived(const meshtastic_MeshPacket &mp)
{
    if (moduleConfig.external_notification.enabled) {
        LOG_INFO("Inside led matrix module");
        auto &p = mp.decoded;
        // scrollText("Lunch Time", sizeof("Lunch Time"), matrix.Color(0, 0, 255));
        // current_animation = true;
        // current_text = "Lunch Time";
        // current_text_length = sizeof("Lunch Time");
        // current_text = (const char *)p.payload.bytes;
        // memcpy(current_text, (const char *)p.payload.bytes, p.payload.size);
        // current_text_length = p.payload.size;
        // current_color = matrix.Color(0, 0, 255);
        // LOG_DEBUG("Led matrix decoded msg: msg=%.*s\n", mp.decoded.payload.bytes);
        LOG_INFO("Led matrix decoded msg from=0x%0x, id=0x%x, msg=%.*s\n", mp.from, mp.id, p.payload.size, p.payload.bytes);
        LOG_DEBUG("Matrix looking for %i got %i\n",text_trigger,p.payload.bytes[0]);
        if (p.payload.bytes[0] == text_trigger)
        {
            LOG_DEBUG("Got request for text message\n");
            int msg_index = p.payload.bytes[1] - 97;
            current_text = text_messages[msg_index];
            current_text_length = text_sizes[msg_index];
            current_color = matrix.Color(255, 0, 255);
            current_animation = true;
        }
        else
        {
            LOG_DEBUG("NOT Lunchtime\n");
        }
    } else {
        LOG_INFO("LED Matrix Module Disabled\n");
    }

    return ProcessMessage::CONTINUE; // Let others look at this message also if they want
}
