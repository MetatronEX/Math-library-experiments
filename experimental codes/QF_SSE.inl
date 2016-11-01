
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
FORCEINLINE sse_f	QF_SSE::Load(const f32& f)
{
	return _mm_set_ps1(f);
}

FORCEINLINE sse_f	QF_SSE::Load(const f32& x, const f32& y, const f32& z, const f32& w)
{
	return _mm_set_ps(w, z, y, x);
}

FORCEINLINE sse_f	QF_SSE::Add(const sse_f& a, const sse_f& b)
{
	return _mm_add_ps(a, b);
}

FORCEINLINE sse_f	QF_SSE::Sub(const sse_f& a, const sse_f& b)
{
	return _mm_sub_ps(a, b);
}

FORCEINLINE sse_f	QF_SSE::Mul(const sse_f& a, const sse_f& b)
{
	return _mm_mul_ps(a, b);
}

FORCEINLINE sse_f	QF_SSE::Div(const sse_f& a, const sse_f& b)
{
	return _mm_div_ps(a, b);
}

FORCEINLINE f32		QF_SSE::Dot(const sse_f& a, const sse_f& b)
{
	/*
	Dot product example

	a = 1 2 3 0
	b = 5 6 7 0

	a * b = 5 + 12 + 21 = 38

	r0 = _mm_mul_ps(a,b)								-> 0 21 12 5
	r1 = _mm_shuffle_ps(r0,r0,_MM_SHUFFLE(1,0,3,2))		-> 21 0  5 12
	r2 = _mm_add_ps(r0,r1)								-> 21 21 17 17
	r3 = _mm_shuffle_ps(r2,r2,_MM_SHUFFLE(2,3,0,1))		-> 17 17 21 21

	result 	= _mm_add_ps(t2,t3)							-> 38 38 38 38

	N.B:  _mm_cvtss_f32 -> Copy the lower single-precision (32-bit) floating-point element of a to dst.

	N.B:

	_mm_dp_ps performance table base on architecture:

	Architecture	Latency	Throughput
	Haswell			14		-
	Ivy Bridge		12		-
	Sandy Bridge	12		-
	Westmere		11		-
	Nehalem			11		-

	Pretty obvious it's due to branching

	Operation
	DP(a[127:0], b[127:0], imm[7:0]) {
	FOR j := 0 to 3
	i := j*32
	IF imm[4+j]
	temp[i+31:i] := a[i+31:i] * b[i+31:i]
	ELSE
	temp[i+31:i] := 0
	FI
	ENDFOR

	sum[31:0] := (temp[127:96] + temp[95:64]) + (temp[63:32] + temp[31:0])

	FOR j := 0 to 3
	i := j*32
	IF imm[j]
	tmpdst[i+31:i] := sum[31:0]
	ELSE
	tmpdst[i+31:i] := 0
	FI
	ENDFOR
	RETURN tmpdst[127:0]
	}
	*/

	//const simd t0 = _mm_mul_ps(a,b);
	//const simd t1 = _mm_shuffle_ps(t0,t0, _MM_SHUFFLE(Z,W,X,Y));
	//const simd t2 = _mm_add_ps(t0,t1);
	//const simd t3 = _mm_shuffle_ps(t2,t2, _MM_SHUFFLE(X,Y,Z,W));
	//
	//return _mm_cvtss_f32(_mm_add_ps(t2,t3));

	// reference : http://hobiger.org/blog/2012/06/18/dot-product-with-sse4/
	return _mm_cvtss_f32(_mm_dp_ps(a, b, 0xf1));
}

FORCEINLINE sse_f	QF_SSE::VDot(const sse_f& a, const sse_f& b)
{
	//const simd t0 = _mm_mul_ps(a,b);
	//const simd t1 = _mm_shuffle_ps(t0,t0, _MM_SHUFFLE(Z,W,X,Y));
	//const simd t2 = _mm_add_ps(t0,t1);
	//const simd t3 = _mm_shuffle_ps(t2,t2, _MM_SHUFFLE(X,Y,Z,W));
	//
	//return _mm_add_ps(t2,t3);

	return _mm_dp_ps(a, b, 0xff);
}

FORCEINLINE f32		QF_SSE::VSquare(const sse_f& simd)
{
	return _mm_cvtss_f32(_mm_dp_ps(simd, simd, 0xf1));
}

FORCEINLINE sse_f	QF_SSE::VDotSquare(const sse_f& simd)
{
	return _mm_dp_ps(simd, simd, 0xff);
}

FORCEINLINE sse_f	QF_SSE::Cross(const sse_f& a, const sse_f& b)
{
	/*

	Cross product example
	a = 1 2 3 | 0
	b = 5 6 7 | 0

	c = a ^ b = (2*7 - 6*3, 5*3 - 1*7, 6*1 - 5*2) = ( -4, 8, -4 )

	r0 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1)) -> 0 1 3 2
	r1 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2)) -> 0 6 5 7
	r2 = _mm_mul_ps(r0,r1) -> 0 6 15 14
	r3 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2)) -> 0 2 1 3
	r4 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1)) -> 0 5 7 6
	r5 = _mm_mul_ps(r3,r4) -> 0 10 7 18
	r6 = _mm_sub_ps(r2,r5) -> 0 -4 8 -4

	*/

	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(W, X, Z, Y)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(W, Y, X, Z))),
		_mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(W, Y, X, Z)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(W, X, Z, Y)))
		);
}

FORCEINLINE f32		QF_SSE::Length(const sse_f& simd)
{
	return _mm_cvtss_f32(_mm_sqrt_ss(VDot(simd, simd)));
}

FORCEINLINE sse_f	QF_SSE::VLength(const sse_f& simd)
{
	return _mm_sqrt_ss(VDot(simd, simd));
}

FORCEINLINE sse_f	QF_SSE::Normalize(const sse_f& simd)
{
	return _mm_mul_ps(simd, _mm_rsqrt_ps(VDotSquare(simd)));
}

FORCEINLINE sse_f	QF_SSE::Negate(const sse_f& simd)
{
	return _mm_xor_ps(SIGNMASK_F, simd);
}

FORCEINLINE sse_f	QF_SSE::FABS(const sse_f& simd)
{
	return _mm_andnot_ps(SIGNMASK_F, simd);
}

FORCEINLINE bool	QF_SSE::Equal(const sse_f& a, const sse_f& b)
{
	return (_mm_test_all_ones(_mm_castps_si128(_mm_cmpeq_ps(a, b))));
}

FORCEINLINE void	QF_SSE::MMTranspose(sse_f& v0, sse_f& v1, sse_f& v2, sse_f& v3)
{
	_MM_TRANSPOSE4_PS(v0, v1, v2, v3);
}

FORCEINLINE sse_f	QF_SSE::RCPPS(const sse_f& simd)
{
	return _mm_rcp_ps(simd);
}

FORCEINLINE sse_f	QF_SSE::RSQRTPS(const sse_f& simd)
{
	return _mm_rsqrt_ps(simd);
}

FORCEINLINE f32		QF_SSE::RCPSS(const f32& t)
{
	return _mm_cvtss_f32(_mm_rcp_ss(Load(t)));
}

FORCEINLINE f32		QF_SSE::RSQRTSS(const f32& t)
{
	return _mm_cvtss_f32(_mm_rsqrt_ss(Load(t)));
}

FORCEINLINE sse_f	QF_SSE::SQRTPS(const sse_f& simd)
{
	return Mul(simd, RSQRTPS(simd));
}

FORCEINLINE f32		QF_SSE::SQRTSS(const f32& t)
{
	return t * RSQRTSS(t);
}
