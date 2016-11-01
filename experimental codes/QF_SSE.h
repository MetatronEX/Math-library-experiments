
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
#ifndef QF_SSE_H_
#define QF_SSE_H_

#define M128_ALIGNMENT 16U

#include "QF_Core.h"

#include <nmmintrin.h>

#include "QF_Intrinsics_Policy.h"

QF_START

typedef __m128 sse_f;

/// http://fastcpp.blogspot.sg/2011/03/changing-sign-of-float-values-using-sse.html
static const sse_f SIGNMASK_F = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

static const sse_f ALL_ZERO_MASK_F = _mm_castsi128_ps(_mm_set1_epi32(0x00000000));

static const sse_f ALL_ONE_MASK_F = _mm_castsi128_ps(_mm_set1_epi32(0xFFFFFFFF));

class QF_SSE : public QF_Intrinsics_Policy<QF_SSE, sse_f, f32>
{
public:
	FORCEINLINE sse_f	Load(const f32& f);
	FORCEINLINE sse_f	Load(const f32& x, const f32& y, const f32& z, const f32& w);
	FORCEINLINE sse_f	Add(const sse_f& a, const sse_f& b);
	FORCEINLINE sse_f	Sub(const sse_f& a, const sse_f& b);
	FORCEINLINE sse_f	Mul(const sse_f& a, const sse_f& b);
	FORCEINLINE sse_f	Div(const sse_f& a, const sse_f& b);
	FORCEINLINE f32		Dot(const sse_f& a, const sse_f& b);
	FORCEINLINE sse_f	VDot(const sse_f& a, const sse_f& b);
	FORCEINLINE f32		VSquare(const sse_f& simd);
	FORCEINLINE sse_f	VDotSquare(const sse_f& simd);
	FORCEINLINE sse_f	Cross(const sse_f& a, const sse_f& b);
	FORCEINLINE f32		Length(const sse_f& simd);
	FORCEINLINE sse_f	VLength(const sse_f& simd);
	FORCEINLINE sse_f	Normalize(const sse_f& simd);
	FORCEINLINE sse_f	Negate(const sse_f& simd);
	FORCEINLINE sse_f	FABS(const sse_f& simd);
	FORCEINLINE bool	Equal(const sse_f& a, const sse_f& b);
	FORCEINLINE void	MMTranspose(sse_f& v0, sse_f& v1, sse_f& v2, sse_f& v3);
	FORCEINLINE sse_f	RCPPS(const sse_f& simd);
	FORCEINLINE sse_f	RSQRTPS(const sse_f& simd);
	FORCEINLINE f32		RCPSS(const f32& f32);
	FORCEINLINE f32		RSQRTSS(const f32& f32);
	FORCEINLINE sse_f	SQRTPS(const sse_f& simd);
	FORCEINLINE f32		SQRTSS(const f32& f32);
};

#include "QF_SSE.inl"

QF_END

#endif