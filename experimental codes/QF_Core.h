
/*
The MIT License (MIT)
Copyright (c) 2016 Xavier RX Tan
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Core is a header file where all declarations and definitions
// are placed.

#ifndef QF_CORE_H_
#define QF_CORE_H_

// Common standard library headers.
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>

// Common STL headers.
#include <algorithm>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include <future>
//#include <promise>
#include <chrono>
#include <array>
#include <tuple>
#include <type_traits>
#include <initializer_list>
#include <numeric>
#include <functional>

#include <complex>
#include <limits>
#include <math.h>

#include <iostream>
#include <fstream>

#include <memory.h>

#ifndef STDCALL
	#define STDCALL __stdcall
#endif

#ifndef FASTCALL
	#define FASTCALL __fastcall
#endif

#if defined(__GNUC__) || defined(__clang__)
	#ifndef __forceinline 
		#define __forceinline __inline__ __attribute__( (always_inline) )
	#endif
#endif

#if defined(__GNUC__) || defined(__clang__)
	#ifndef ensure_forceinline
		#define ensure_forceinline __attrribute__((always_inline))
	#endif
#else	//	WIN32 case
	#ifndef ensure_forceinline
		#define ensure_forceinline __forceinline
	#endif
#endif

#ifndef FORCEINLINE
	#define FORCEINLINE ensure_forceinline
#endif

#ifndef STATICINLINE
	#define STATICINLINE static inline
#endif

#ifndef INLINE
	#define INLINE inline
#endif

#ifndef SAFE_DELETE
	#define SAFE_DELETE(x)	{ if(x) { delete(x); (x) = NULL; } }
#endif

#ifndef SAFE_ARRAY_DELETE
	#define SAFE_ARRAY_DELETE(x) { if(x) { delete[] (x); (x) = NULL; } }
#endif

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }
#endif

#ifndef DO_NOTHING
	#define DO_NOTHING() { (void)0; }
#endif

#ifndef UNSUED
	#define UNUSED(x) {}
#endif

#ifndef GetIID
	#define GetIID(x) __uuidof(x)
#endif

#ifndef QF_START
	#define QF_START namespace QF_SDK {
#endif

#ifndef QF_END
#define QF_END   };
#endif

#ifndef USING_QF_SDK
	#define USING_QF_SDK using namespace QF_SDK;
#endif

#ifndef QF
	#define QF QF_SDK
#endif

// primitive typedef shortcuts
typedef unsigned char		u8;
typedef char				s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;
typedef unsigned long long	u64;
typedef long long			s64;
typedef float				f32;
typedef double				f64;

typedef f64					real;
typedef u8					byte;

typedef std::array<float,3>	vec3;
typedef std::array<float,2> vec2;

QF_START

// accessor constant index
static constexpr u8  X			= 0;
static constexpr u8  Y			= 1;
static constexpr u8  Z			= 2;
static constexpr u8  W			= 3;

static constexpr u8  R			= 0;
static constexpr u8  G			= 1;
static constexpr u8  B			= 2;
static constexpr u8  A			= 3;

static constexpr u8  S			= 0;
static constexpr u8  T			= 1;
static constexpr u8  U			= 2;
static constexpr u8  V			= 3;

// Homogeneous terms
static constexpr f32 VEC		= 0.f;
static constexpr f32 PT			= 1.f;

enum class VALID_CODE { FAILED, SUCCEED };

QF_END

#endif
