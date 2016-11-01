
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
#ifndef QF_INTRINSICS_POLICY_H_
#define QF_INTRINSICS_POLICY_H_

#include "QF_Core.h"

QF_START

template <typename Derived, typename INTRINSICS, typename T>
class QF_Intrinsics_Policy
{
public:

	FORCEINLINE INTRINSICS Load(const T& t)
	{
		return static_cast<Derived*>(this)->Load(t);
	}

	FORCEINLINE INTRINSICS Load(const T& x, const T& y, const T& z, const T& w)
	{
		return static_cast<Derived*>(this)->Load(x, y, z, w);
	}

	FORCEINLINE INTRINSICS Add(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Add(a, b);
	}

	FORCEINLINE INTRINSICS Sub(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Sub(a, b);
	}

	FORCEINLINE INTRINSICS Mul(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Mul(a, b);
	}

	FORCEINLINE INTRINSICS Div(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Div(a, b);
	}

	FORCEINLINE T Dot(const INTRINSICS& a, const SIMB_T& b)
	{
		return static_cast<Derived*>(this)->Dot(a, b);
	}

	FORCEINLINE INTRINSICS VDot(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Dot(a, b);
	}

	FORCEINLINE T VSquare(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->VSquare(simd);
	}

	FORCEINLINE INTRINSICS VDotSquare(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->:VDotSquare(simd);
	}

	FORCEINLINE INTRINSICS Cross(const INTRINSICS& a const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Cross(a, b);
	}

	FORCEINLINE T Length(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->Length(simd);
	}

	FORCEINLINE INTRINSICS VLength(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->VLength(simd);
	}

	FORCEINLINE INTRINSICS Normalize(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->Normalize(simd);
	}

	FORCEINLINE INTRINSICS Negate(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->Negate(simd);
	}

	FORCEINLINE INTRINSICS FABS(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->FABS(simd);
	}

	FORCEINLINE bool Equal(const INTRINSICS& a, const INTRINSICS& b)
	{
		return static_cast<Derived*>(this)->Equal(a, b);
	}

	FORCEINLINE void MMTranspose(INTRINSICS& v0, INTRINSICS& v1, INTRINSICS& v2, INTRINSICS& v3)
	{
		static_cast<Derived*>(this)->MMTranspose(v0, v1, v2, v3);
	}

	FORCEINLINE INTRINSICS RCPPS(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->RCPPS(simd);
	}

	FORCEINLINE INTRINSICS RSQRTPS(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->RSQRTPS(simd);
	}

	FORCEINLINE T RCPSS(const T& t)
	{
		return static_cast<Derived*>(this)->RCPSS(t);
	}

	FORCEINLINE T RSQRTSS(const T& t)
	{
		return static_cast<Derived*>(this)->RSQRTSS(t);
	}

	FORCEINLINE INTRINSICS SQRTPS(const INTRINSICS& simd)
	{
		return static_cast<Derived*>(this)->SQRT(simd);
	}

	FORCEINLINE T SQRTSS(const T& t)
	{
		return static_cast<Derived*>(this)->SQRTSS(t);
	}
};

QF_END

#endif