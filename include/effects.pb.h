/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_EFFECTS_PB_H_INCLUDED
#define PB_EFFECTS_PB_H_INCLUDED
#include <pb.h>
#include "functions.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _BrightnessEffectConfig { 
    pb_callback_t mult_factor; 
} BrightnessEffectConfig;

typedef struct _HueEffectConfig { 
    pb_callback_t offset_factor; 
} HueEffectConfig;

typedef struct _RainbowEffectConfig { 
    pb_callback_t hue_start; 
    pb_callback_t hue_end; 
} RainbowEffectConfig;

typedef struct _SaturationEffectConfig { 
    pb_callback_t mult_factor; 
} SaturationEffectConfig;

typedef struct _AlternateEffectConfig { 
    uint32_t numberOfPixels; 
    bool has_hue_offset;
    FloatFunction hue_offset; 
    bool has_sat_mult;
    FloatFunction sat_mult; 
    bool has_brightness_mult;
    FloatFunction brightness_mult; 
} AlternateEffectConfig;

typedef struct _AnimationProto { 
    pb_callback_t effects; 
    uint32_t duration_ms; 
    uint32_t num_repeats; /* 0 means forever */
} AnimationProto;

typedef struct _EffectConfig { 
    uint32_t start_time; 
    uint32_t end_time; 
    pb_callback_t segments; 
    float repeat_num; 
    float repeat_start; 
    float repeat_end; 
} EffectConfig;

typedef struct _GlitterEffectConfig { 
    bool has_intensity;
    FloatFunction intensity; 
    bool has_sat_mult_factor;
    FloatFunction sat_mult_factor; 
} GlitterEffectConfig;

typedef struct _HSV { 
    float hue; 
    float sat; 
    float val; 
} HSV;

typedef struct _SegmentEffectConfig { 
    bool has_start;
    FloatFunction start; 
    bool has_end;
    FloatFunction end; 
} SegmentEffectConfig;

typedef struct _SnakeEffectConfig { 
    bool has_head;
    FloatFunction head; 
    bool has_tail_length;
    FloatFunction tail_length; 
} SnakeEffectConfig;

typedef struct _ConstColorEffectConfig { 
    bool has_color;
    HSV color; 
} ConstColorEffectConfig;

typedef struct _EffectProto { 
    bool has_effect_config;
    EffectConfig effect_config; 
    pb_callback_t const_color; 
    pb_callback_t rainbow; 
    pb_callback_t brightness; 
    pb_callback_t hue; 
    pb_callback_t saturation; 
} EffectProto;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define HSV_init_default                         {0, 0, 0}
#define ConstColorEffectConfig_init_default      {false, HSV_init_default}
#define RainbowEffectConfig_init_default         {{{NULL}, NULL}, {{NULL}, NULL}}
#define BrightnessEffectConfig_init_default      {{{NULL}, NULL}}
#define HueEffectConfig_init_default             {{{NULL}, NULL}}
#define SaturationEffectConfig_init_default      {{{NULL}, NULL}}
#define SegmentEffectConfig_init_default         {false, FloatFunction_init_default, false, FloatFunction_init_default}
#define GlitterEffectConfig_init_default         {false, FloatFunction_init_default, false, FloatFunction_init_default}
#define SnakeEffectConfig_init_default           {false, FloatFunction_init_default, false, FloatFunction_init_default}
#define AlternateEffectConfig_init_default       {0, false, FloatFunction_init_default, false, FloatFunction_init_default, false, FloatFunction_init_default}
#define EffectConfig_init_default                {0, 0, {{NULL}, NULL}, 0, 0, 0}
#define EffectProto_init_default                 {false, EffectConfig_init_default, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define AnimationProto_init_default              {{{NULL}, NULL}, 0, 0}
#define HSV_init_zero                            {0, 0, 0}
#define ConstColorEffectConfig_init_zero         {false, HSV_init_zero}
#define RainbowEffectConfig_init_zero            {{{NULL}, NULL}, {{NULL}, NULL}}
#define BrightnessEffectConfig_init_zero         {{{NULL}, NULL}}
#define HueEffectConfig_init_zero                {{{NULL}, NULL}}
#define SaturationEffectConfig_init_zero         {{{NULL}, NULL}}
#define SegmentEffectConfig_init_zero            {false, FloatFunction_init_zero, false, FloatFunction_init_zero}
#define GlitterEffectConfig_init_zero            {false, FloatFunction_init_zero, false, FloatFunction_init_zero}
#define SnakeEffectConfig_init_zero              {false, FloatFunction_init_zero, false, FloatFunction_init_zero}
#define AlternateEffectConfig_init_zero          {0, false, FloatFunction_init_zero, false, FloatFunction_init_zero, false, FloatFunction_init_zero}
#define EffectConfig_init_zero                   {0, 0, {{NULL}, NULL}, 0, 0, 0}
#define EffectProto_init_zero                    {false, EffectConfig_init_zero, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define AnimationProto_init_zero                 {{{NULL}, NULL}, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define BrightnessEffectConfig_mult_factor_tag   1
#define HueEffectConfig_offset_factor_tag        1
#define RainbowEffectConfig_hue_start_tag        1
#define RainbowEffectConfig_hue_end_tag          2
#define SaturationEffectConfig_mult_factor_tag   1
#define AlternateEffectConfig_numberOfPixels_tag 1
#define AlternateEffectConfig_hue_offset_tag     2
#define AlternateEffectConfig_sat_mult_tag       3
#define AlternateEffectConfig_brightness_mult_tag 4
#define AnimationProto_effects_tag               1
#define AnimationProto_duration_ms_tag           2
#define AnimationProto_num_repeats_tag           3
#define EffectConfig_start_time_tag              1
#define EffectConfig_end_time_tag                2
#define EffectConfig_segments_tag                3
#define EffectConfig_repeat_num_tag              4
#define EffectConfig_repeat_start_tag            5
#define EffectConfig_repeat_end_tag              6
#define GlitterEffectConfig_intensity_tag        1
#define GlitterEffectConfig_sat_mult_factor_tag  2
#define HSV_hue_tag                              1
#define HSV_sat_tag                              2
#define HSV_val_tag                              3
#define SegmentEffectConfig_start_tag            1
#define SegmentEffectConfig_end_tag              2
#define SnakeEffectConfig_head_tag               1
#define SnakeEffectConfig_tail_length_tag        2
#define ConstColorEffectConfig_color_tag         1
#define EffectProto_effect_config_tag            1
#define EffectProto_const_color_tag              2
#define EffectProto_rainbow_tag                  3
#define EffectProto_brightness_tag               4
#define EffectProto_hue_tag                      5
#define EffectProto_saturation_tag               6

/* Struct field encoding specification for nanopb */
#define HSV_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    hue,               1) \
X(a, STATIC,   SINGULAR, FLOAT,    sat,               2) \
X(a, STATIC,   SINGULAR, FLOAT,    val,               3)
#define HSV_CALLBACK NULL
#define HSV_DEFAULT NULL

#define ConstColorEffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  color,             1)
#define ConstColorEffectConfig_CALLBACK NULL
#define ConstColorEffectConfig_DEFAULT NULL
#define ConstColorEffectConfig_color_MSGTYPE HSV

#define RainbowEffectConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  hue_start,         1) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  hue_end,           2)
#define RainbowEffectConfig_CALLBACK pb_default_field_callback
#define RainbowEffectConfig_DEFAULT NULL
#define RainbowEffectConfig_hue_start_MSGTYPE FloatFunction
#define RainbowEffectConfig_hue_end_MSGTYPE FloatFunction

#define BrightnessEffectConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  mult_factor,       1)
#define BrightnessEffectConfig_CALLBACK pb_default_field_callback
#define BrightnessEffectConfig_DEFAULT NULL
#define BrightnessEffectConfig_mult_factor_MSGTYPE FloatFunction

#define HueEffectConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  offset_factor,     1)
#define HueEffectConfig_CALLBACK pb_default_field_callback
#define HueEffectConfig_DEFAULT NULL
#define HueEffectConfig_offset_factor_MSGTYPE FloatFunction

#define SaturationEffectConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  mult_factor,       1)
#define SaturationEffectConfig_CALLBACK pb_default_field_callback
#define SaturationEffectConfig_DEFAULT NULL
#define SaturationEffectConfig_mult_factor_MSGTYPE FloatFunction

#define SegmentEffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  start,             1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  end,               2)
#define SegmentEffectConfig_CALLBACK NULL
#define SegmentEffectConfig_DEFAULT NULL
#define SegmentEffectConfig_start_MSGTYPE FloatFunction
#define SegmentEffectConfig_end_MSGTYPE FloatFunction

#define GlitterEffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  intensity,         1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  sat_mult_factor,   2)
#define GlitterEffectConfig_CALLBACK NULL
#define GlitterEffectConfig_DEFAULT NULL
#define GlitterEffectConfig_intensity_MSGTYPE FloatFunction
#define GlitterEffectConfig_sat_mult_factor_MSGTYPE FloatFunction

#define SnakeEffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  head,              1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  tail_length,       2)
#define SnakeEffectConfig_CALLBACK NULL
#define SnakeEffectConfig_DEFAULT NULL
#define SnakeEffectConfig_head_MSGTYPE FloatFunction
#define SnakeEffectConfig_tail_length_MSGTYPE FloatFunction

#define AlternateEffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   numberOfPixels,    1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  hue_offset,        2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  sat_mult,          3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  brightness_mult,   4)
#define AlternateEffectConfig_CALLBACK NULL
#define AlternateEffectConfig_DEFAULT NULL
#define AlternateEffectConfig_hue_offset_MSGTYPE FloatFunction
#define AlternateEffectConfig_sat_mult_MSGTYPE FloatFunction
#define AlternateEffectConfig_brightness_mult_MSGTYPE FloatFunction

#define EffectConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   start_time,        1) \
X(a, STATIC,   SINGULAR, UINT32,   end_time,          2) \
X(a, CALLBACK, SINGULAR, STRING,   segments,          3) \
X(a, STATIC,   SINGULAR, FLOAT,    repeat_num,        4) \
X(a, STATIC,   SINGULAR, FLOAT,    repeat_start,      5) \
X(a, STATIC,   SINGULAR, FLOAT,    repeat_end,        6)
#define EffectConfig_CALLBACK pb_default_field_callback
#define EffectConfig_DEFAULT NULL

#define EffectProto_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  effect_config,     1) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  const_color,       2) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  rainbow,           3) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  brightness,        4) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  hue,               5) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  saturation,        6)
#define EffectProto_CALLBACK pb_default_field_callback
#define EffectProto_DEFAULT NULL
#define EffectProto_effect_config_MSGTYPE EffectConfig
#define EffectProto_const_color_MSGTYPE ConstColorEffectConfig
#define EffectProto_rainbow_MSGTYPE RainbowEffectConfig
#define EffectProto_brightness_MSGTYPE BrightnessEffectConfig
#define EffectProto_hue_MSGTYPE HueEffectConfig
#define EffectProto_saturation_MSGTYPE SaturationEffectConfig

#define AnimationProto_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  effects,           1) \
X(a, STATIC,   SINGULAR, UINT32,   duration_ms,       2) \
X(a, STATIC,   SINGULAR, UINT32,   num_repeats,       3)
#define AnimationProto_CALLBACK pb_default_field_callback
#define AnimationProto_DEFAULT NULL
#define AnimationProto_effects_MSGTYPE EffectProto

extern const pb_msgdesc_t HSV_msg;
extern const pb_msgdesc_t ConstColorEffectConfig_msg;
extern const pb_msgdesc_t RainbowEffectConfig_msg;
extern const pb_msgdesc_t BrightnessEffectConfig_msg;
extern const pb_msgdesc_t HueEffectConfig_msg;
extern const pb_msgdesc_t SaturationEffectConfig_msg;
extern const pb_msgdesc_t SegmentEffectConfig_msg;
extern const pb_msgdesc_t GlitterEffectConfig_msg;
extern const pb_msgdesc_t SnakeEffectConfig_msg;
extern const pb_msgdesc_t AlternateEffectConfig_msg;
extern const pb_msgdesc_t EffectConfig_msg;
extern const pb_msgdesc_t EffectProto_msg;
extern const pb_msgdesc_t AnimationProto_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define HSV_fields &HSV_msg
#define ConstColorEffectConfig_fields &ConstColorEffectConfig_msg
#define RainbowEffectConfig_fields &RainbowEffectConfig_msg
#define BrightnessEffectConfig_fields &BrightnessEffectConfig_msg
#define HueEffectConfig_fields &HueEffectConfig_msg
#define SaturationEffectConfig_fields &SaturationEffectConfig_msg
#define SegmentEffectConfig_fields &SegmentEffectConfig_msg
#define GlitterEffectConfig_fields &GlitterEffectConfig_msg
#define SnakeEffectConfig_fields &SnakeEffectConfig_msg
#define AlternateEffectConfig_fields &AlternateEffectConfig_msg
#define EffectConfig_fields &EffectConfig_msg
#define EffectProto_fields &EffectProto_msg
#define AnimationProto_fields &AnimationProto_msg

/* Maximum encoded size of messages (where known) */
/* RainbowEffectConfig_size depends on runtime parameters */
/* BrightnessEffectConfig_size depends on runtime parameters */
/* HueEffectConfig_size depends on runtime parameters */
/* SaturationEffectConfig_size depends on runtime parameters */
/* EffectConfig_size depends on runtime parameters */
/* EffectProto_size depends on runtime parameters */
/* AnimationProto_size depends on runtime parameters */
#define ConstColorEffectConfig_size              17
#define HSV_size                                 15
#if defined(FloatFunction_size) && defined(FloatFunction_size)
#define GlitterEffectConfig_size                 (12 + FloatFunction_size + FloatFunction_size)
#define SegmentEffectConfig_size                 (12 + FloatFunction_size + FloatFunction_size)
#define SnakeEffectConfig_size                   (12 + FloatFunction_size + FloatFunction_size)
#endif
#if defined(FloatFunction_size) && defined(FloatFunction_size) && defined(FloatFunction_size)
#define AlternateEffectConfig_size               (24 + FloatFunction_size + FloatFunction_size + FloatFunction_size)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
