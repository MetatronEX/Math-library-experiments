
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
#ifndef QF_SIMD_POLICY_H_
#define QF_SIMD_POLICY_H_

#include "QF_Core.h"

QF_START

template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT >
class QF_SIMD_Policy;

template < template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT > typename SIMD_Policy, typename T2 >
FORCEINLINE QF_SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT> operator*(const T2& k, const SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT>& v);

template < template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT > typename SIMD_Policy >
FORCEINLINE std::ostream& operator<< (std::ostream& _out, const SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT>& v);

template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT >
class QF_SIMD_Policy : public SIMDPolicy
{
private:

	union alignas(ALIGNMENT) simd_union
	{
		SIMD_T	simd_t;
		T		t[4];
	}packed_vec;

	FORCEINLINE SIMD_T Load(const T& t)
	{
		return SIMDPolicy::Load(t);
	}

	FORCEINLINE SIMD_T Load(const T& x, const T& y, const T& z, const T& w)
	{
		return SIMDPolicy::Load(x, y, z, w);
	}

	FORCEINLINE SIMD_T Add(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Add(a, b);
	}

	FORCEINLINE SIMD_T Sub(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Sub(a, b);
	}

	FORCEINLINE SIMD_T Mul(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Mul(a, b);
	}

	FORCEINLINE SIMD_T Div(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Div(a, b);
	}

	FORCEINLINE T Dot(const SIMD_T& a, const SIMB_T& b)
	{
		return SIMDPolicy::Dot(a, b);
	}

	FORCEINLINE SIMD_T VDot(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Dot(a, b);
	}

	FORCEINLINE T VSquare(const SIMD_T& simd)
	{
		return SIMDPolicy::VSquare(simd);
	}

	FORCEINLINE SIMD_T VDotSquare(const SIMD_T& simd)
	{
		return SIMDPolicy:::VDotSquare(simd);
	}

	FORCEINLINE SIMD_T Cross(const SIMD_T& a const SIMD_T& b)
	{
		return SIMDPolicy::Cross(a, b);
	}

	FORCEINLINE T Length(const SIMD_T& simd)
	{
		return SIMDPolicy::Length(simd);
	}

	FORCEINLINE SIMD_T VLength(const SIMD_T& simd)
	{
		return SIMDPolicy::VLength(simd);
	}

	FORCEINLINE SIMD_T Normalize(const SIMD_T& simd)
	{
		return SIMDPolicy::Normalize(simd);
	}

	FORCEINLINE SIMD_T Negate(const SIMD_T& simd)
	{
		return SIMDPolicy::Negate(simd);
	}

	FORCEINLINE SIMD_T FABS(const SIMD_T& simd)
	{
		return SIMDPolicy::FABS(simd);
	}

	FORCEINLINE bool Equal(const SIMD_T& a, const SIMD_T& b)
	{
		return SIMDPolicy::Equal(a, b);
	}

	FORCEINLINE void MMTranspose(SIMD_T& v0, SIMD_T& v1, SIMD_T& v2, SIMD_T& v3)
	{
		SIMDPolicy::MMTranspose(v0, v1, v2, v3);
	}

	FORCEINLINE SIMD_T RCPPS(const SIMD_T& simd)
	{
		return SIMDPolicy::RCPPS(simd);
	}

	FORCEINLINE SIMD_T RSQRTPS(const SIMD_T& simd)
	{
		return SIMDPolicy::RSQRTPS(simd);
	}

	FORCEINLINE T RCPSS(const T& t)
	{
		return SIMDPolicy::RCPSS(t);
	}

	FORCEINLINE T RSQRTSS(const T& t)
	{
		return SIMDPolicy::RSQRTSS(t);
	}

	FORCEINLINE SIMD_T SQRTPS(const SIMD_T& simd)
	{
		return SIMDPolicy::SQRT(simd);
	}

	FORCEINLINE T SQRTSS(const T& t)
	{
		return SIMDPolicy::SQRTSS(t);
	}

	FORCEINLINE QF_SIMD_Policy(const SIMD_T& simd_t)
	{
		packed_simd.simd_t = simd_t;
	}

	FORCEINLINE QF_SIMD_Policy(SIMD_T&& simd_t)
	{
		packed_simd.simd_t = std::move(simd_t);
	}

public:

	FORCEINLINE QF_SIMD_Policy() :
		QF_SIMD_Policy(static_cast<T>(0))
	{

	}

	FORCEINLINE QF_SIMD_Policy(const T& t) :
		QF_SIMD_Policy(t,t,t,t)
	{

	}

	FORCEINLINE QF_SIMD_Policy(const T& x, const T& y, const T& z, const T& w)
	{
		pack_simd.simd_t = Load(x, y, z, w);
	}

	FORCEINLINE QF_SIMD_Policy(const QF_SIMD_Policy& other)
	{
		packed_simd.simd_t = other.packed_simd.simd_t;
	}

	FORCEINLINE QF_SIMD_Policy(QF_SIMD_Policy&& other)
	{
		pack_simd.simd_t = std::move(other.packed_simd.simd_t);

		other.packed_simd.t = nullptr;
	}

	FORCEINLINE QF_SIMD_Policy& operator= (const QF_SIMD_Policy& rhs)
	{
		if (this == &rhs)
			return *this;

		packed_simd.simd_t = rhs.packed_simd.simd_t;

		return *this;
	}

	FORCEINLINE QF_SIMD_Policy& operator=(QF_SIMD_Policy&& rhs)
	{
		if (this == &rhs)
			return *this;

		packed_simd.simd_t = std::move(rhs.packed_simd.simd_t);
		rhs.packed_simd.t = nullptr;

		return *this;
	}

	FORCEINLINE T& operator[] (const u8 i)
	{
		return packed_simd.t[i];
	}

	FORCEINLINE T operator[] (const u8 i) const
	{
		return packed_simd.t[i];
	}

	FORCEINLINE bool operator==(const QF_SIMD_Policy& rhs) const
	{
		return Equal(packed_simd.simd_t, rhs.packed_simd.simd_t);
	}

	FORCEINLINE bool operator!=(const QF_SIMD_Policy& rhs) const
	{
		return Equal(packed_simd.simd_t, rhs.packed_simd.simd_t);
	}

	FORCEINLINE QF_SIMD_Policy operator+(const QF_SIMD_Policy& rhs) const
	{
		return Add(packed_simd.simd_t, rhs.packed_simd.sim_t);
	}

	FORCEINLINE QF_SIMD_Policy operator-(const QF_SIMD_Policy& rhs) const
	{
		return Sub(packed_simd.simd_t, rhs.packed_simd.simd_t);
	}

	FORCEINLINE T operator* (const QF_SIMD_Policy& rhs) const
	{
		return Dot(packed_simd.simd_t, rhs.packed_simd.simd_t);
	}

	FORCEINLINE QF_SIMD_Policy operator^ (const QF_SIMD_Policy& rhs) const
	{
		return Cross(packed_simd.simd_t, rhs.packed_simd.simd_t);
	}

	FORCEINLINE QF_SIMD_Policy& operator+= (const QF_SIMD_Policy& rhs)
	{
		packed_simd.simd_t = Add(packed_simd.simd_t, rhs.packed_simd.simd_t);

		return *this;
	}

	FORCEINLINE QF_SIMD_Policy& operator-= (const QF_SIMD_Policy& rhs)
	{
		packed_simd_t = Sub(packed_simd.simd_t, rhs.packed_simd.simd_t);

		return *this;
	}

	FORCEINLINE QF_SIMD_Policy operator* (const T& k) const
	{
		return Mul(packed_simd.simd_t, Load(k));
	}

	FORCEINLINE QF_SIMD_Policy operator/ (const T& k) const
	{
		return Div(packed_simd.simd_t, Load(k));
	}

	FORCEINLINE QF_SIMD_Policy operator*= (const T& k)
	{
		packed_simd.simd_t = Mul = (packed_simd.simd_t, Load(k));

		return *this;
	}

	FORCEINLINE QF_SIMD_Policy operator/= (const T& k)
	{
		packed_simd.simd_t = Div(packed_simd.simd_t, Load(k));

		return *this;
	}

	FORCEINLINE QF_SIMD_Policy operator- () const
	{
		return Negate(packed_simd.simd_t);
	}

	friend QF_SIMD_Policy operator*(const T& k, const QF_SIMD_Policy& v);
	friend std::ostream& operator<< (std::ostream& _out, const QF_SIMD_Policy& v);

	FORCEINLINE QF_SIMD_Policy Norm() const
	{
		return Normalize(packed_simd.simd_t);
	}

	FORCEINLINE void NormalizeThis()
	{
		packed_simd.simd_t = Normalize(packed_simd.simd_t);
	}
		
	FORCEINLINE T Magnitude() const
	{
		return Length(packed_simd.simd_t);
	}

	FORCEINLINE T MagnitudeSquare() const
	{
		return VSquare(packed_simd.simd_t);
	}
};

template < template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT > typename SIMD_Policy, typename T2 >
FORCEINLINE QF_SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT> operator*(const T2& k, const SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT>& v)
{
	return v*k;
}

template < template < typename SIMDPolicy, typename SIMD_T, typename T, u32 ALIGNMENT > typename SIMD_Policy >
FORCEINLINE std::ostream& operator<< (std::ostream& _out, const SIMD_Policy<SIMDPolicy, SIMD_T, T, ALIGNMENT>& v)
{
	return _out << "(" << v[X] << ", " << v[Y] << ", " << v[Z] << ", " << v[W] << ")";
}

QF_END

#endif