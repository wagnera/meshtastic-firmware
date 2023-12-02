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
#include "mesh/generated/meshtastic/remote_hardware.pb.h"
#include "configuration.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "soccer_animation.h"

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
int repeat_text = 0;

char text_trigger = 'L';
int max_index = 9; //update this when adding new text

static const char* const text_messages[] = {"This is a test", "Lunch Time!!", "Foos o'clock!", "Zito's Time!", "Thai Tuesday!",
                                            "Thai Thursday!", "Soccer Time", "Running Time", "Taco Tuesday!", "Moo goo Monday!"};
static const int text_sizes[] = {sizeof("This is a test"),sizeof("Lunch Time!!"), sizeof("Foos o'clock!"), sizeof("Zito's Time!"), sizeof("Thai Tuesday!"),
                                 sizeof("Thai Thursday!"), sizeof("Soccer Time"), sizeof("Running Time"), sizeof("Taco Tuesday!"), sizeof("Moo goo Monday!")};

// Function to convert Unix time to Central Time (CT) with DST adjustments
tm unixTimeToCT(long long unixTime) {
    time_t rawTime = (time_t)unixTime;
    struct tm *ctTimeInfo;

    // Define Central Time (CT) UTC offsets
    int ctOffsetStandard = -6; // Central Standard Time (CST) UTC offset
    int ctOffsetDST = -5;      // Central Daylight Time (CDT) UTC offset

    // Hard-coded DST transition times for the next 10 years (assuming DST starts on March 14 and ends on November 7)
    int dstTransitions[] = {
        1678608000, // March 12, 2023 - DST starts
        1699171200, // November 5, 2023 - DST ends
        1710057600, // March 10, 2024 - DST starts
        1730620800, // November 3, 2024 - DST ends
        1741507200, // March 9, 2025 - DST starts
        1762070400, // November 2, 2025 - DST ends
        1772956800, // March 8, 2026 - DST starts
        1793520000, // November 1, 2026 - DST ends
        1805011200, // March 14, 2027 - DST starts
        1825574400, // November 7, 2027 - DST ends
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
            if (repeat_text <= 0){
                current_animation = false;
            }
            else {
                repeat_text--;
                scroll_x = matrix.width();
            }
            
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

        matrix.setTextColor(matrix.Color(138, 43, 226));
        matrix.fillScreen(0);
        matrix.setCursor(1, 1);
        char time_buf [6];
        snprintf(time_buf, 6, "%02i:%02i", ctTimeInfo.tm_hour,ctTimeInfo.tm_min);
        // snprintf(time_buf, 6, "10:31");
        // LOG_DEBUG("Time string: %s\n",time_buf);
        matrix.print(time_buf);
        // matrix.print(F("10:31"));
    }
    else
    {
        matrix.setTextColor(matrix.Color(138, 43, 226));
        matrix.fillScreen(0);
        matrix.setCursor(11, 1);
        matrix.print(F(".."));
    }
    
    // matrix.print(F("10:31 AM"));

    matrix.show();
}

// void draw_image_from_array(uint16_t height, uint16_t width, uint16_t x, uint16_t y, const unsigned char* array)
// {
//   matrix.fillScreen(0);
//   for (int i =0; i < height; i++)
//   {
//     for (int j=0;j<width;j++)
//     {
//       matrix.drawPixel(x+j,y+i,matrix.Color((uint8_t)(array[j+i*width]),(uint8_t)(array[j+i*width+(height*width)]),(uint8_t)(array[j+i*width+(height*width*2)])));
//     }
//   }

//   matrix.show();
// }

// void foosball_animation()
// {
//   int index = -8;
//   for (auto bmp_img: test_gif_frame_rgb_Array)
//   {
//     // matrix.fillScreen(0);
//     // matrix.drawBitmap(index, 0, bmp_img, 8,8,  matrix.Color(255, 0, 255));
//     // matrix.show();
//     draw_image_from_array(8,8,index,0,bmp_img);
//     delay(70);
//     index++;
//   }
//   for (auto bmp_img: test_gif_frame_rgb_Array)
//   {
//     // matrix.fillScreen(0);
//     // matrix.drawBitmap(index, 0, bmp_img, 8,8,  matrix.Color(255, 0, 255));
//     // matrix.show();
//     draw_image_from_array(8,8,index,0,bmp_img);
//     delay(70);
//     index++;
//     if (index > 40)
//     {
//       break;
//     }
    
//   }

// }

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
    return 80;
}

bool LedMatrixModule::wantPacket(const meshtastic_MeshPacket *p)
{
    LOG_DEBUG("led want packet port: %i\n",p->decoded.portnum);
    // return 1;
    // return MeshService::isTextPayload(p);
    return (p->decoded.portnum == meshtastic_PortNum_TEXT_MESSAGE_APP || p->decoded.portnum == meshtastic_PortNum_REMOTE_HARDWARE_APP);
}

LedMatrixModule::LedMatrixModule()
    : SinglePortModule("LedMatrixModule", meshtastic_PortNum_TEXT_MESSAGE_APP),
      concurrency::OSThread("LedMatrixModule")
{
    /*
        Uncomment the preferences below if you want to use the module
        without having to configure it from the PythonAPI or WebUI.
    */

    if (moduleConfig.led_matrix.enabled) {
        
    } else {
        LOG_INFO("External Notification Module Disabled\n");
        disable();
    }
}

ProcessMessage LedMatrixModule::handleReceived(const meshtastic_MeshPacket &mp)
{
    if (moduleConfig.led_matrix.enabled) {
        LOG_INFO("Inside led matrix module\n");
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

        if (p.portnum == meshtastic_PortNum_TEXT_MESSAGE_APP) {
            LOG_DEBUG("Got message request from text app\n");
            LOG_INFO("Led matrix decoded msg from=0x%0x, id=0x%x, msg=%.*s\n", mp.from, mp.id, p.payload.size, p.payload.bytes);
            LOG_DEBUG("Matrix looking for %i got %i\n",text_trigger,p.payload.bytes[0]);
            if (p.payload.bytes[0] == text_trigger)
            {
                LOG_DEBUG("Got request for text message\n");
                int msg_index = p.payload.bytes[1] - 48; // 48 = 0 in ascii
                if (msg_index > max_index && msg_index >= 0)
                {
                    LOG_DEBUG("Requested message index out of range, idx: %i\n", msg_index);
                    return ProcessMessage::CONTINUE;
                }
                current_text = text_messages[msg_index];
                current_text_length = text_sizes[msg_index];
                current_color = matrix.Color(255, 0, 255);
                current_animation = true;
                repeat_text = 3;
            }
            else
            {
                LOG_DEBUG("NOT Lunchtime\n");
            }
        }
        else if (p.portnum == meshtastic_PortNum_REMOTE_HARDWARE_APP) {
            meshtastic_HardwareMessage hw_message;
            if (pb_decode_from_bytes(p.payload.bytes, p.payload.size, meshtastic_HardwareMessage_fields, &hw_message)) {
            LOG_DEBUG("Sucessfully decoded message\n");
            } else {
                LOG_ERROR("Error decoding remote button message!\n");
                return ProcessMessage::CONTINUE;
            }

            LOG_DEBUG("Got message request from physical button\n");
            LOG_DEBUG("got %i\n",(uint8_t)hw_message.gpio_value);
            LOG_DEBUG("Got request for text message\n");
            int msg_index = (uint8_t)hw_message.gpio_value - 48; // 48 = 0 in ascii
            if (msg_index > max_index || msg_index < 0)
            {
                LOG_DEBUG("Requested message index out of range, idx: %i\n", msg_index);
                return ProcessMessage::CONTINUE;
            }
            current_text = text_messages[msg_index];
            current_text_length = text_sizes[msg_index];
            current_color = matrix.Color(255, 0, 255);
            current_animation = true;
            repeat_text = 3;
        }
    } else {
        LOG_INFO("LED Matrix Module Disabled\n");
    }

    return ProcessMessage::CONTINUE; // Let others look at this message also if they want
}
