/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9 */

#ifndef PB_FUNCTIONS_PB_H_INCLUDED
#define PB_FUNCTIONS_PB_H_INCLUDED
#include "pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _ConstValueFloatFunctionConfig {
    float value;
} ConstValueFloatFunctionConfig;

typedef struct _LinearFloatFunctionConfig {
    float start;
    float end;
} LinearFloatFunctionConfig;

typedef struct _SinFloatFunctionConfig {
    float min;
    float max;
    float phase;
    float repeats;
} SinFloatFunctionConfig;

typedef struct _StepsFloatFunctionConfig {
    float num_steps;
    float diff_per_step;
    float first_step_value;
} StepsFloatFunctionConfig;

typedef struct _RepeatFloatFunctionConfig {
    float numberOfTimes;
    pb_callback_t funcToRepeat;
} RepeatFloatFunctionConfig;

typedef struct _HalfFloatFunctionConfig {
    pb_callback_t f1;
    pb_callback_t f2;
} HalfFloatFunctionConfig;

typedef struct _Comb2FloatFunctionConfig {
    pb_callback_t f1;
    float amount1;
    pb_callback_t f2;
    float amount2;
} Comb2FloatFunctionConfig;

typedef struct _FloatFunction {
    pb_callback_t const_value;
    pb_callback_t linear;
    pb_callback_t sin;
    pb_callback_t steps;
    pb_callback_t repeat;
    pb_callback_t half;
    pb_callback_t comb2;
} FloatFunction;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define ConstValueFloatFunctionConfig_init_default {0}
#define LinearFloatFunctionConfig_init_default   {0, 0}
#define SinFloatFunctionConfig_init_default      {0, 0, 0, 0}
#define StepsFloatFunctionConfig_init_default    {0, 0, 0}
#define RepeatFloatFunctionConfig_init_default   {0, {{NULL}, NULL}}
#define HalfFloatFunctionConfig_init_default     {{{NULL}, NULL}, {{NULL}, NULL}}
#define Comb2FloatFunctionConfig_init_default    {{{NULL}, NULL}, 0, {{NULL}, NULL}, 0}
#define FloatFunction_init_default               {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define ConstValueFloatFunctionConfig_init_zero  {0}
#define LinearFloatFunctionConfig_init_zero      {0, 0}
#define SinFloatFunctionConfig_init_zero         {0, 0, 0, 0}
#define StepsFloatFunctionConfig_init_zero       {0, 0, 0}
#define RepeatFloatFunctionConfig_init_zero      {0, {{NULL}, NULL}}
#define HalfFloatFunctionConfig_init_zero        {{{NULL}, NULL}, {{NULL}, NULL}}
#define Comb2FloatFunctionConfig_init_zero       {{{NULL}, NULL}, 0, {{NULL}, NULL}, 0}
#define FloatFunction_init_zero                  {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define ConstValueFloatFunctionConfig_value_tag  1
#define LinearFloatFunctionConfig_start_tag      1
#define LinearFloatFunctionConfig_end_tag        2
#define SinFloatFunctionConfig_min_tag           1
#define SinFloatFunctionConfig_max_tag           2
#define SinFloatFunctionConfig_phase_tag         3
#define SinFloatFunctionConfig_repeats_tag       4
#define StepsFloatFunctionConfig_num_steps_tag   1
#define StepsFloatFunctionConfig_diff_per_step_tag 2
#define StepsFloatFunctionConfig_first_step_value_tag 3
#define RepeatFloatFunctionConfig_numberOfTimes_tag 1
#define RepeatFloatFunctionConfig_funcToRepeat_tag 2
#define HalfFloatFunctionConfig_f1_tag           1
#define HalfFloatFunctionConfig_f2_tag           2
#define Comb2FloatFunctionConfig_f1_tag          1
#define Comb2FloatFunctionConfig_amount1_tag     2
#define Comb2FloatFunctionConfig_f2_tag          3
#define Comb2FloatFunctionConfig_amount2_tag     4
#define FloatFunction_const_value_tag            1
#define FloatFunction_linear_tag                 2
#define FloatFunction_sin_tag                    3
#define FloatFunction_steps_tag                  4
#define FloatFunction_repeat_tag                 5
#define FloatFunction_half_tag                   6
#define FloatFunction_comb2_tag                  7

/* Struct field encoding specification for nanopb */
#define ConstValueFloatFunctionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    value,             1)
#define ConstValueFloatFunctionConfig_CALLBACK NULL
#define ConstValueFloatFunctionConfig_DEFAULT NULL

#define LinearFloatFunctionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    start,             1) \
X(a, STATIC,   SINGULAR, FLOAT,    end,               2)
#define LinearFloatFunctionConfig_CALLBACK NULL
#define LinearFloatFunctionConfig_DEFAULT NULL

#define SinFloatFunctionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    min,               1) \
X(a, STATIC,   SINGULAR, FLOAT,    max,               2) \
X(a, STATIC,   SINGULAR, FLOAT,    phase,             3) \
X(a, STATIC,   SINGULAR, FLOAT,    repeats,           4)
#define SinFloatFunctionConfig_CALLBACK NULL
#define SinFloatFunctionConfig_DEFAULT NULL

#define StepsFloatFunctionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    num_steps,         1) \
X(a, STATIC,   SINGULAR, FLOAT,    diff_per_step,     2) \
X(a, STATIC,   SINGULAR, FLOAT,    first_step_value,   3)
#define StepsFloatFunctionConfig_CALLBACK NULL
#define StepsFloatFunctionConfig_DEFAULT NULL

#define RepeatFloatFunctionConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    numberOfTimes,     1) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  funcToRepeat,      2)
#define RepeatFloatFunctionConfig_CALLBACK pb_default_field_callback
#define RepeatFloatFunctionConfig_DEFAULT NULL
#define RepeatFloatFunctionConfig_funcToRepeat_MSGTYPE FloatFunction

#define HalfFloatFunctionConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  f1,                1) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  f2,                2)
#define HalfFloatFunctionConfig_CALLBACK pb_default_field_callback
#define HalfFloatFunctionConfig_DEFAULT NULL
#define HalfFloatFunctionConfig_f1_MSGTYPE FloatFunction
#define HalfFloatFunctionConfig_f2_MSGTYPE FloatFunction

#define Comb2FloatFunctionConfig_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  f1,                1) \
X(a, STATIC,   SINGULAR, FLOAT,    amount1,           2) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  f2,                3) \
X(a, STATIC,   SINGULAR, FLOAT,    amount2,           4)
#define Comb2FloatFunctionConfig_CALLBACK pb_default_field_callback
#define Comb2FloatFunctionConfig_DEFAULT NULL
#define Comb2FloatFunctionConfig_f1_MSGTYPE FloatFunction
#define Comb2FloatFunctionConfig_f2_MSGTYPE FloatFunction

#define FloatFunction_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  const_value,       1) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  linear,            2) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  sin,               3) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  steps,             4) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  repeat,            5) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  half,              6) \
X(a, CALLBACK, OPTIONAL, MESSAGE,  comb2,             7)
#define FloatFunction_CALLBACK pb_default_field_callback
#define FloatFunction_DEFAULT NULL
#define FloatFunction_const_value_MSGTYPE ConstValueFloatFunctionConfig
#define FloatFunction_linear_MSGTYPE LinearFloatFunctionConfig
#define FloatFunction_sin_MSGTYPE SinFloatFunctionConfig
#define FloatFunction_steps_MSGTYPE StepsFloatFunctionConfig
#define FloatFunction_repeat_MSGTYPE RepeatFloatFunctionConfig
#define FloatFunction_half_MSGTYPE HalfFloatFunctionConfig
#define FloatFunction_comb2_MSGTYPE Comb2FloatFunctionConfig

extern const pb_msgdesc_t ConstValueFloatFunctionConfig_msg;
extern const pb_msgdesc_t LinearFloatFunctionConfig_msg;
extern const pb_msgdesc_t SinFloatFunctionConfig_msg;
extern const pb_msgdesc_t StepsFloatFunctionConfig_msg;
extern const pb_msgdesc_t RepeatFloatFunctionConfig_msg;
extern const pb_msgdesc_t HalfFloatFunctionConfig_msg;
extern const pb_msgdesc_t Comb2FloatFunctionConfig_msg;
extern const pb_msgdesc_t FloatFunction_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define ConstValueFloatFunctionConfig_fields &ConstValueFloatFunctionConfig_msg
#define LinearFloatFunctionConfig_fields &LinearFloatFunctionConfig_msg
#define SinFloatFunctionConfig_fields &SinFloatFunctionConfig_msg
#define StepsFloatFunctionConfig_fields &StepsFloatFunctionConfig_msg
#define RepeatFloatFunctionConfig_fields &RepeatFloatFunctionConfig_msg
#define HalfFloatFunctionConfig_fields &HalfFloatFunctionConfig_msg
#define Comb2FloatFunctionConfig_fields &Comb2FloatFunctionConfig_msg
#define FloatFunction_fields &FloatFunction_msg

/* Maximum encoded size of messages (where known) */
/* RepeatFloatFunctionConfig_size depends on runtime parameters */
/* HalfFloatFunctionConfig_size depends on runtime parameters */
/* Comb2FloatFunctionConfig_size depends on runtime parameters */
/* FloatFunction_size depends on runtime parameters */
#define ConstValueFloatFunctionConfig_size       5
#define FUNCTIONS_PB_H_MAX_SIZE                  SinFloatFunctionConfig_size
#define LinearFloatFunctionConfig_size           10
#define SinFloatFunctionConfig_size              20
#define StepsFloatFunctionConfig_size            15

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
