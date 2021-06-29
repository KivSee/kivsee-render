/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.3 */

#ifndef PB_SEGMENTS_PB_H_INCLUDED
#define PB_SEGMENTS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _SegmentConfig {
    char name[10];
    pb_callback_t indices;
} SegmentConfig;

typedef struct _SegmentsMapConfig {
    uint32_t guid;
    uint32_t number_of_pixels;
    pb_callback_t segments;
} SegmentsMapConfig;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define SegmentConfig_init_default               {"", {{NULL}, NULL}}
#define SegmentsMapConfig_init_default           {0, 0, {{NULL}, NULL}}
#define SegmentConfig_init_zero                  {"", {{NULL}, NULL}}
#define SegmentsMapConfig_init_zero              {0, 0, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define SegmentConfig_name_tag                   1
#define SegmentConfig_indices_tag                2
#define SegmentsMapConfig_guid_tag               1
#define SegmentsMapConfig_number_of_pixels_tag   2
#define SegmentsMapConfig_segments_tag           3

/* Struct field encoding specification for nanopb */
#define SegmentConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   name,              1) \
X(a, CALLBACK, REPEATED, UINT32,   indices,           2)
#define SegmentConfig_CALLBACK pb_default_field_callback
#define SegmentConfig_DEFAULT NULL

#define SegmentsMapConfig_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FIXED32,  guid,              1) \
X(a, STATIC,   SINGULAR, UINT32,   number_of_pixels,   2) \
X(a, CALLBACK, REPEATED, MESSAGE,  segments,          3)
#define SegmentsMapConfig_CALLBACK pb_default_field_callback
#define SegmentsMapConfig_DEFAULT NULL
#define SegmentsMapConfig_segments_MSGTYPE SegmentConfig

extern const pb_msgdesc_t SegmentConfig_msg;
extern const pb_msgdesc_t SegmentsMapConfig_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define SegmentConfig_fields &SegmentConfig_msg
#define SegmentsMapConfig_fields &SegmentsMapConfig_msg

/* Maximum encoded size of messages (where known) */
/* SegmentConfig_size depends on runtime parameters */
/* SegmentsMapConfig_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif