/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6 */

#ifndef PB_APPONLY_PB_H_INCLUDED
#define PB_APPONLY_PB_H_INCLUDED
#include <pb.h>
#include "channel.pb.h"
#include "config.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
/* This is the most compact possible representation for a set of channels.
 It includes only one PRIMARY channel (which must be first) and
 any SECONDARY channels.
 No DISABLED channels are included.
 This abstraction is used only on the the 'app side' of the world (ie python, javascript and android etc) to show a group of Channels as a (long) URL */
typedef struct _ChannelSet { 
    /* Channel list with settings */
    pb_size_t settings_count;
    ChannelSettings settings[8];
    /* LoRa config */
    bool has_lora_config;
    Config_LoRaConfig lora_config;
} ChannelSet;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define ChannelSet_init_default                  {0, {ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default, ChannelSettings_init_default}, false, Config_LoRaConfig_init_default}
#define ChannelSet_init_zero                     {0, {ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero, ChannelSettings_init_zero}, false, Config_LoRaConfig_init_zero}

/* Field tags (for use in manual encoding/decoding) */
#define ChannelSet_settings_tag                  1
#define ChannelSet_lora_config_tag               2

/* Struct field encoding specification for nanopb */
#define ChannelSet_FIELDLIST(X, a) \
X(a, STATIC,   REPEATED, MESSAGE,  settings,          1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  lora_config,       2)
#define ChannelSet_CALLBACK NULL
#define ChannelSet_DEFAULT NULL
#define ChannelSet_settings_MSGTYPE ChannelSettings
#define ChannelSet_lora_config_MSGTYPE Config_LoRaConfig

extern const pb_msgdesc_t ChannelSet_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define ChannelSet_fields &ChannelSet_msg

/* Maximum encoded size of messages (where known) */
#define ChannelSet_size                          573

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
