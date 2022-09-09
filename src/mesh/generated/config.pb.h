/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6 */

#ifndef PB_CONFIG_PB_H_INCLUDED
#define PB_CONFIG_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _Config_DeviceConfig_Role { 
    Config_DeviceConfig_Role_CLIENT = 0, 
    Config_DeviceConfig_Role_CLIENT_MUTE = 1, 
    Config_DeviceConfig_Role_ROUTER = 2, 
    Config_DeviceConfig_Role_ROUTER_CLIENT = 3 
} Config_DeviceConfig_Role;

typedef enum _Config_PositionConfig_PositionFlags { 
    Config_PositionConfig_PositionFlags_UNSET = 0, 
    Config_PositionConfig_PositionFlags_ALTITUDE = 1, 
    Config_PositionConfig_PositionFlags_ALTITUDE_MSL = 2, 
    Config_PositionConfig_PositionFlags_GEOIDAL_SEPERATION = 4, 
    Config_PositionConfig_PositionFlags_DOP = 8, 
    Config_PositionConfig_PositionFlags_HVDOP = 16, 
    Config_PositionConfig_PositionFlags_SATINVIEW = 32, 
    Config_PositionConfig_PositionFlags_SEQ_NO = 64, 
    Config_PositionConfig_PositionFlags_TIMESTAMP = 128, 
    Config_PositionConfig_PositionFlags_HEADING = 256, 
    Config_PositionConfig_PositionFlags_SPEED = 512 
} Config_PositionConfig_PositionFlags;

typedef enum _Config_NetworkConfig_WiFiMode { 
    Config_NetworkConfig_WiFiMode_CLIENT = 0, 
    Config_NetworkConfig_WiFiMode_ACCESS_POINT = 1, 
    Config_NetworkConfig_WiFiMode_ACCESS_POINT_HIDDEN = 2 
} Config_NetworkConfig_WiFiMode;

typedef enum _Config_DisplayConfig_GpsCoordinateFormat { 
    Config_DisplayConfig_GpsCoordinateFormat_DEC = 0, 
    Config_DisplayConfig_GpsCoordinateFormat_DMS = 1, 
    Config_DisplayConfig_GpsCoordinateFormat_UTM = 2, 
    Config_DisplayConfig_GpsCoordinateFormat_MGRS = 3, 
    Config_DisplayConfig_GpsCoordinateFormat_OLC = 4, 
    Config_DisplayConfig_GpsCoordinateFormat_OSGR = 5 
} Config_DisplayConfig_GpsCoordinateFormat;

typedef enum _Config_LoRaConfig_RegionCode { 
    Config_LoRaConfig_RegionCode_UNSET = 0, 
    Config_LoRaConfig_RegionCode_US = 1, 
    Config_LoRaConfig_RegionCode_EU_433 = 2, 
    Config_LoRaConfig_RegionCode_EU_868 = 3, 
    Config_LoRaConfig_RegionCode_CN = 4, 
    Config_LoRaConfig_RegionCode_JP = 5, 
    Config_LoRaConfig_RegionCode_ANZ = 6, 
    Config_LoRaConfig_RegionCode_KR = 7, 
    Config_LoRaConfig_RegionCode_TW = 8, 
    Config_LoRaConfig_RegionCode_RU = 9, 
    Config_LoRaConfig_RegionCode_IN = 10, 
    Config_LoRaConfig_RegionCode_NZ_865 = 11, 
    Config_LoRaConfig_RegionCode_TH = 12 
} Config_LoRaConfig_RegionCode;

typedef enum _Config_LoRaConfig_ModemPreset { 
    Config_LoRaConfig_ModemPreset_LONG_FAST = 0, 
    Config_LoRaConfig_ModemPreset_LONG_SLOW = 1, 
    Config_LoRaConfig_ModemPreset_VERY_LONG_SLOW = 2, 
    Config_LoRaConfig_ModemPreset_MEDIUM_SLOW = 3, 
    Config_LoRaConfig_ModemPreset_MEDIUM_FAST = 4, 
    Config_LoRaConfig_ModemPreset_SHORT_SLOW = 5, 
    Config_LoRaConfig_ModemPreset_SHORT_FAST = 6 
} Config_LoRaConfig_ModemPreset;

typedef enum _Config_BluetoothConfig_PairingMode { 
    Config_BluetoothConfig_PairingMode_RANDOM_PIN = 0, 
    Config_BluetoothConfig_PairingMode_FIXED_PIN = 1, 
    Config_BluetoothConfig_PairingMode_NO_PIN = 2 
} Config_BluetoothConfig_PairingMode;

/* Struct definitions */
typedef struct _Config_BluetoothConfig { 
    bool enabled;
    Config_BluetoothConfig_PairingMode mode;
    uint32_t fixed_pin;
} Config_BluetoothConfig;

typedef struct _Config_DeviceConfig { 
    Config_DeviceConfig_Role role;
    bool serial_disabled;
    bool debug_log_enabled;
} Config_DeviceConfig;

typedef struct _Config_DisplayConfig { 
    uint32_t screen_on_secs;
    Config_DisplayConfig_GpsCoordinateFormat gps_format;
    uint32_t auto_screen_carousel_secs;
    bool compass_north_top;
} Config_DisplayConfig;

typedef struct _Config_LoRaConfig { 
    int32_t tx_power;
    Config_LoRaConfig_ModemPreset modem_preset;
    uint32_t bandwidth;
    uint32_t spread_factor;
    uint32_t coding_rate;
    float frequency_offset;
    Config_LoRaConfig_RegionCode region;
    uint32_t hop_limit;
    bool tx_disabled;
    pb_size_t ignore_incoming_count;
    uint32_t ignore_incoming[3];
} Config_LoRaConfig;

typedef struct _Config_NetworkConfig { 
    bool wifi_enabled;
    Config_NetworkConfig_WiFiMode wifi_mode;
    char wifi_ssid[33];
    char wifi_psk[64];
    char ntp_server[33];
} Config_NetworkConfig;

typedef struct _Config_PositionConfig { 
    uint32_t position_broadcast_secs;
    bool position_broadcast_smart_disabled;
    bool fixed_position;
    bool gps_disabled;
    uint32_t gps_update_interval;
    uint32_t gps_attempt_time;
    uint32_t position_flags;
} Config_PositionConfig;

typedef struct _Config_PowerConfig { 
    bool is_power_saving;
    uint32_t on_battery_shutdown_after_secs;
    float adc_multiplier_override;
    uint32_t wait_bluetooth_secs;
    uint32_t mesh_sds_timeout_secs;
    uint32_t sds_secs;
    uint32_t ls_secs;
    uint32_t min_wake_secs;
} Config_PowerConfig;

typedef struct _Config { 
    pb_size_t which_payload_variant;
    union {
        Config_DeviceConfig device;
        Config_PositionConfig position;
        Config_PowerConfig power;
        Config_NetworkConfig network;
        Config_DisplayConfig display;
        Config_LoRaConfig lora;
        Config_BluetoothConfig bluetooth;
    } payload_variant;
} Config;


/* Helper constants for enums */
#define _Config_DeviceConfig_Role_MIN Config_DeviceConfig_Role_CLIENT
#define _Config_DeviceConfig_Role_MAX Config_DeviceConfig_Role_ROUTER_CLIENT
#define _Config_DeviceConfig_Role_ARRAYSIZE ((Config_DeviceConfig_Role)(Config_DeviceConfig_Role_ROUTER_CLIENT+1))

#define _Config_PositionConfig_PositionFlags_MIN Config_PositionConfig_PositionFlags_UNSET
#define _Config_PositionConfig_PositionFlags_MAX Config_PositionConfig_PositionFlags_SPEED
#define _Config_PositionConfig_PositionFlags_ARRAYSIZE ((Config_PositionConfig_PositionFlags)(Config_PositionConfig_PositionFlags_SPEED+1))

#define _Config_NetworkConfig_WiFiMode_MIN Config_NetworkConfig_WiFiMode_CLIENT
#define _Config_NetworkConfig_WiFiMode_MAX Config_NetworkConfig_WiFiMode_ACCESS_POINT_HIDDEN
#define _Config_NetworkConfig_WiFiMode_ARRAYSIZE ((Config_NetworkConfig_WiFiMode)(Config_NetworkConfig_WiFiMode_ACCESS_POINT_HIDDEN+1))

#define _Config_DisplayConfig_GpsCoordinateFormat_MIN Config_DisplayConfig_GpsCoordinateFormat_DEC
#define _Config_DisplayConfig_GpsCoordinateFormat_MAX Config_DisplayConfig_GpsCoordinateFormat_OSGR
#define _Config_DisplayConfig_GpsCoordinateFormat_ARRAYSIZE ((Config_DisplayConfig_GpsCoordinateFormat)(Config_DisplayConfig_GpsCoordinateFormat_OSGR+1))

#define _Config_LoRaConfig_RegionCode_MIN Config_LoRaConfig_RegionCode_UNSET
#define _Config_LoRaConfig_RegionCode_MAX Config_LoRaConfig_RegionCode_TH
#define _Config_LoRaConfig_RegionCode_ARRAYSIZE ((Config_LoRaConfig_RegionCode)(Config_LoRaConfig_RegionCode_TH+1))

#define _Config_LoRaConfig_ModemPreset_MIN Config_LoRaConfig_ModemPreset_LONG_FAST
#define _Config_LoRaConfig_ModemPreset_MAX Config_LoRaConfig_ModemPreset_SHORT_FAST
#define _Config_LoRaConfig_ModemPreset_ARRAYSIZE ((Config_LoRaConfig_ModemPreset)(Config_LoRaConfig_ModemPreset_SHORT_FAST+1))

#define _Config_BluetoothConfig_PairingMode_MIN Config_BluetoothConfig_PairingMode_RANDOM_PIN
#define _Config_BluetoothConfig_PairingMode_MAX Config_BluetoothConfig_PairingMode_NO_PIN
#define _Config_BluetoothConfig_PairingMode_ARRAYSIZE ((Config_BluetoothConfig_PairingMode)(Config_BluetoothConfig_PairingMode_NO_PIN+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Config_init_default                      {0, {Config_DeviceConfig_init_default}}
#define Config_DeviceConfig_init_default         {_Config_DeviceConfig_Role_MIN, 0, 0}
#define Config_PositionConfig_init_default       {0, 0, 0, 0, 0, 0, 0}
#define Config_PowerConfig_init_default          {0, 0, 0, 0, 0, 0, 0, 0}
#define Config_NetworkConfig_init_default        {0, _Config_NetworkConfig_WiFiMode_MIN, "", "", ""}
#define Config_DisplayConfig_init_default        {0, _Config_DisplayConfig_GpsCoordinateFormat_MIN, 0, 0}
#define Config_LoRaConfig_init_default           {0, _Config_LoRaConfig_ModemPreset_MIN, 0, 0, 0, 0, _Config_LoRaConfig_RegionCode_MIN, 0, 0, 0, {0, 0, 0}}
#define Config_BluetoothConfig_init_default      {0, _Config_BluetoothConfig_PairingMode_MIN, 0}
#define Config_init_zero                         {0, {Config_DeviceConfig_init_zero}}
#define Config_DeviceConfig_init_zero            {_Config_DeviceConfig_Role_MIN, 0, 0}
#define Config_PositionConfig_init_zero          {0, 0, 0, 0, 0, 0, 0}
#define Config_PowerConfig_init_zero             {0, 0, 0, 0, 0, 0, 0, 0}
#define Config_NetworkConfig_init_zero           {0, _Config_NetworkConfig_WiFiMode_MIN, "", "", ""}
#define Config_DisplayConfig_init_zero           {0, _Config_DisplayConfig_GpsCoordinateFormat_MIN, 0, 0}
#define Config_LoRaConfig_init_zero              {0, _Config_LoRaConfig_ModemPreset_MIN, 0, 0, 0, 0, _Config_LoRaConfig_RegionCode_MIN, 0, 0, 0, {0, 0, 0}}
#define Config_BluetoothConfig_init_zero         {0, _Config_BluetoothConfig_PairingMode_MIN, 0}

/* Field tags (for use in manual encoding/decoding) */
#define Config_BluetoothConfig_enabled_tag       1
#define Config_BluetoothConfig_mode_tag          2
#define Config_BluetoothConfig_fixed_pin_tag     3
#define Config_DeviceConfig_role_tag             1
#define Config_DeviceConfig_serial_disabled_tag  2
#define Config_DeviceConfig_debug_log_enabled_tag 3
#define Config_DisplayConfig_screen_on_secs_tag  1
#define Config_DisplayConfig_gps_format_tag      2
#define Config_DisplayConfig_auto_screen_carousel_secs_tag 3
#define Config_DisplayConfig_compass_north_top_tag 4
#define Config_LoRaConfig_tx_power_tag           1
#define Config_LoRaConfig_modem_preset_tag       2
#define Config_LoRaConfig_bandwidth_tag          3
#define Config_LoRaConfig_spread_factor_tag      4
#define Config_LoRaConfig_coding_rate_tag        5
#define Config_LoRaConfig_frequency_offset_tag   6
#define Config_LoRaConfig_region_tag             7
#define Config_LoRaConfig_hop_limit_tag          8
#define Config_LoRaConfig_tx_disabled_tag        9
#define Config_LoRaConfig_ignore_incoming_tag    103
#define Config_NetworkConfig_wifi_enabled_tag    1
#define Config_NetworkConfig_wifi_mode_tag       2
#define Config_NetworkConfig_wifi_ssid_tag       3
#define Config_NetworkConfig_wifi_psk_tag        4
#define Config_NetworkConfig_ntp_server_tag      5
#define Config_PositionConfig_position_broadcast_secs_tag 1
#define Config_PositionConfig_position_broadcast_smart_disabled_tag 2
#define Config_PositionConfig_fixed_position_tag 3
#define Config_PositionConfig_gps_disabled_tag   4
#define Config_PositionConfig_gps_update_interval_tag 5
#define Config_PositionConfig_gps_attempt_time_tag 6
#define Config_PositionConfig_position_flags_tag 7
#define Config_PowerConfig_is_power_saving_tag   1
#define Config_PowerConfig_on_battery_shutdown_after_secs_tag 2
#define Config_PowerConfig_adc_multiplier_override_tag 3
#define Config_PowerConfig_wait_bluetooth_secs_tag 4
#define Config_PowerConfig_mesh_sds_timeout_secs_tag 5
#define Config_PowerConfig_sds_secs_tag          6
#define Config_PowerConfig_ls_secs_tag           7
#define Config_PowerConfig_min_wake_secs_tag     8
#define Config_device_tag                        1
#define Config_position_tag                      2
#define Config_power_tag                         3
#define Config_network_tag                       4
#define Config_display_tag                       5
#define Config_lora_tag                          6
#define Config_bluetooth_tag                     7

/* Struct field encoding specification for nanopb */
#define Config_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,device,payload_variant.device),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,position,payload_variant.position),   2) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,power,payload_variant.power),   3) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,network,payload_variant.network),   4) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,display,payload_variant.display),   5) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,lora,payload_variant.lora),   6) \
X(a, STATIC,   ONEOF,    MESSAGE,  (payload_variant,bluetooth,payload_variant.bluetooth),   7)
#define Config_CALLBACK NULL
#define Config_DEFAULT NULL
#define Config_payload_variant_device_MSGTYPE Config_DeviceConfig
#define Config_payload_variant_position_MSGTYPE Config_PositionConfig
#define Config_payload_variant_power_MSGTYPE Config_PowerConfig
#define Config_payload_variant_network_MSGTYPE Config_NetworkConfig
#define Config_payload_variant_display_MSGTYPE Config_DisplayConfig
#define Config_payload_variant_lora_MSGTYPE Config_LoRaConfig
#define Config_payload_variant_bluetooth_MSGTYPE Config_BluetoothConfig

#define Config_DeviceConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    role,              1) \
X(a, STATIC,   SINGULAR, BOOL,     serial_disabled,   2) \
X(a, STATIC,   SINGULAR, BOOL,     debug_log_enabled,   3)
#define Config_DeviceConfig_CALLBACK NULL
#define Config_DeviceConfig_DEFAULT NULL

#define Config_PositionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   position_broadcast_secs,   1) \
X(a, STATIC,   SINGULAR, BOOL,     position_broadcast_smart_disabled,   2) \
X(a, STATIC,   SINGULAR, BOOL,     fixed_position,    3) \
X(a, STATIC,   SINGULAR, BOOL,     gps_disabled,      4) \
X(a, STATIC,   SINGULAR, UINT32,   gps_update_interval,   5) \
X(a, STATIC,   SINGULAR, UINT32,   gps_attempt_time,   6) \
X(a, STATIC,   SINGULAR, UINT32,   position_flags,    7)
#define Config_PositionConfig_CALLBACK NULL
#define Config_PositionConfig_DEFAULT NULL

#define Config_PowerConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     is_power_saving,   1) \
X(a, STATIC,   SINGULAR, UINT32,   on_battery_shutdown_after_secs,   2) \
X(a, STATIC,   SINGULAR, FLOAT,    adc_multiplier_override,   3) \
X(a, STATIC,   SINGULAR, UINT32,   wait_bluetooth_secs,   4) \
X(a, STATIC,   SINGULAR, UINT32,   mesh_sds_timeout_secs,   5) \
X(a, STATIC,   SINGULAR, UINT32,   sds_secs,          6) \
X(a, STATIC,   SINGULAR, UINT32,   ls_secs,           7) \
X(a, STATIC,   SINGULAR, UINT32,   min_wake_secs,     8)
#define Config_PowerConfig_CALLBACK NULL
#define Config_PowerConfig_DEFAULT NULL

#define Config_NetworkConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     wifi_enabled,      1) \
X(a, STATIC,   SINGULAR, UENUM,    wifi_mode,         2) \
X(a, STATIC,   SINGULAR, STRING,   wifi_ssid,         3) \
X(a, STATIC,   SINGULAR, STRING,   wifi_psk,          4) \
X(a, STATIC,   SINGULAR, STRING,   ntp_server,        5)
#define Config_NetworkConfig_CALLBACK NULL
#define Config_NetworkConfig_DEFAULT NULL

#define Config_DisplayConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   screen_on_secs,    1) \
X(a, STATIC,   SINGULAR, UENUM,    gps_format,        2) \
X(a, STATIC,   SINGULAR, UINT32,   auto_screen_carousel_secs,   3) \
X(a, STATIC,   SINGULAR, BOOL,     compass_north_top,   4)
#define Config_DisplayConfig_CALLBACK NULL
#define Config_DisplayConfig_DEFAULT NULL

#define Config_LoRaConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    tx_power,          1) \
X(a, STATIC,   SINGULAR, UENUM,    modem_preset,      2) \
X(a, STATIC,   SINGULAR, UINT32,   bandwidth,         3) \
X(a, STATIC,   SINGULAR, UINT32,   spread_factor,     4) \
X(a, STATIC,   SINGULAR, UINT32,   coding_rate,       5) \
X(a, STATIC,   SINGULAR, FLOAT,    frequency_offset,   6) \
X(a, STATIC,   SINGULAR, UENUM,    region,            7) \
X(a, STATIC,   SINGULAR, UINT32,   hop_limit,         8) \
X(a, STATIC,   SINGULAR, BOOL,     tx_disabled,       9) \
X(a, STATIC,   REPEATED, UINT32,   ignore_incoming, 103)
#define Config_LoRaConfig_CALLBACK NULL
#define Config_LoRaConfig_DEFAULT NULL

#define Config_BluetoothConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     enabled,           1) \
X(a, STATIC,   SINGULAR, UENUM,    mode,              2) \
X(a, STATIC,   SINGULAR, UINT32,   fixed_pin,         3)
#define Config_BluetoothConfig_CALLBACK NULL
#define Config_BluetoothConfig_DEFAULT NULL

extern const pb_msgdesc_t Config_msg;
extern const pb_msgdesc_t Config_DeviceConfig_msg;
extern const pb_msgdesc_t Config_PositionConfig_msg;
extern const pb_msgdesc_t Config_PowerConfig_msg;
extern const pb_msgdesc_t Config_NetworkConfig_msg;
extern const pb_msgdesc_t Config_DisplayConfig_msg;
extern const pb_msgdesc_t Config_LoRaConfig_msg;
extern const pb_msgdesc_t Config_BluetoothConfig_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Config_fields &Config_msg
#define Config_DeviceConfig_fields &Config_DeviceConfig_msg
#define Config_PositionConfig_fields &Config_PositionConfig_msg
#define Config_PowerConfig_fields &Config_PowerConfig_msg
#define Config_NetworkConfig_fields &Config_NetworkConfig_msg
#define Config_DisplayConfig_fields &Config_DisplayConfig_msg
#define Config_LoRaConfig_fields &Config_LoRaConfig_msg
#define Config_BluetoothConfig_fields &Config_BluetoothConfig_msg

/* Maximum encoded size of messages (where known) */
#define Config_BluetoothConfig_size              10
#define Config_DeviceConfig_size                 6
#define Config_DisplayConfig_size                16
#define Config_LoRaConfig_size                   67
#define Config_NetworkConfig_size                137
#define Config_PositionConfig_size               30
#define Config_PowerConfig_size                  43
#define Config_size                              140

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
