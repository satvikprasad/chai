#pragma once

#define N_AXIS_MAX 12.f
#define N_AXIS_MIN 7.f
#define N_AXIS 10.f

#define MAX_LUAFUNC_PARAMS 8

#include <stdint.h>

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef uint32_t b32;
typedef uint8_t b8;

typedef float f32;
typedef double f64;

#define ARRAY_LENGTH(a) (sizeof((a))) / (sizeof((a)[0]))
