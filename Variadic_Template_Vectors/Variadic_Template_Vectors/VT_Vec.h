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

#pragma once

#ifndef VARIADIC_TEMPLATE_VECTOR_H_
#define VARIADIC_TEMPLATE_VECTOR_H_

#include <array>
#include <memory>

namespace math
{
	template < size_t N, typename DATA_TYPE = float >
	class VT_Vec
	{
		std::array<DATA_TYPE, N>	vec;

	public:

		typedef DATA_TYPE	data_type;
		typedef VT_Vec < N, data_type > resolved_vector_type;

		template <typename ...T>
		explicit constexpr VT_Vec(T... n) :
			vec({ n... })
		{

		}

		VT_Vec() :
			vec({ 0 })
		{

		}

		VT_Vec(const VT_Vec& other)
		{
			std::copy(other.vec.begin(), other.vec.end(), vec.begin());
		}

		VT_Vec(VT_Vec&& other) :
			vec(std::move(other.vec))
		{

		}

		VT_Vec<N, data_type>& operator= (const VT_Vec<N, data_type>& rhs)
		{
			if (this == &rhs)
				return *this;

			std::copy(rhs.vec.begin(), rhs.vec.end(), vec.begin());

			return *this;
		}

		VT_Vec<N, data_type>& operator= (VT_Vec<N, data_type>&& rhs)
		{
			if (this == &rhs)
				return *this;

			vec = std::move(rhs.vec);

			return *this;
		}

		static constexpr size_t Dimension()
		{
			return N;
		}

		data_type& operator[] (const int i)
		{
			return vec[i];
		}

		data_type operator[] (const int i) const
		{
			return vec[i];
		}

		/// scaling operation
		VT_Vec<N, data_type> operator* (const data_type& k) const
		{
			VT_Vec<N, data_type> result;

			for (auto i = 0; i < N; ++i)
				result[i] = vec[i] * k;

			return result;
		}

		VT_Vec<N, data_type> operator/ (const data_type& k) const
		{
			VT_Vec<N, data_type> result;

			for (auto i = 0; i < N; ++i)
				result[i] = vec[i] / k;

			return result;
		}

		VT_Vec<N, data_type>& operator*= (const data_type& k)
		{
			for (auto i : vec)
				i *= k;

			return *this;
		}

		VT_Vec<N, data_type>& operator/= (const data_type& k)
		{
			for (auto i : vec)
				i /= k;

			return *this;
		}

		/// algebraic operations
		VT_Vec<N, data_type> operator+ (const VT_Vec<N, data_type>& rhs) const
		{
			VT_Vec<N, data_type> result;

			for (auto i = 0; i < N; ++i)
				result[i] = vec[i] + rhs[i];

			return result;
		}

		VT_Vec<N, data_type> operator- (const VT_Vec<N, data_type>& rhs) const
		{
			VT_Vec<N, data_type> result;

			for (auto i = 0; i < N; ++i)
				result[i] = vec[i] - rhs[i];

			return result;
		}

		VT_Vec<N, data_type>& operator+= (const VT_Vec<N, data_type>& rhs)
		{
			for (auto i = 0; i < N; ++i)
				vec[i] += rhs[i];

			return *this;
		}

		VT_Vec<N, data_type>& operator-= (const VT_Vec<N, data_type>& rhs)
		{
			for (auto i = 0; i < N; ++i)
				vec[i] -= rhs[i];

			return *this;
		}

		data_type operator* (const VT_Vec<N, data_type>& rhs) const
		{
			data_type result = static_cast<data_type>(0);

			for (auto i = 0; i < N; ++i)
				result += vec[i] * rhs[i];

			return result;
		}

		data_type Norm() const
		{
			data_type result = static_cast<data_type>(0);

			for (auto i : vec)
				result += i * i;

			return sqrt(result);
		}

		VT_Vec<N, data_type> Unit() const
		{
			return (*this / Norm());
		}

		void NormalizeThis()
		{
			(*this) /= Norm();
		}
	};

	template < size_t N, typename DATA_TYPE >
	inline static VT_Vec<N, DATA_TYPE> operator*(const DATA_TYPE& k, const VT_Vec<N, DATA_TYPE>& v)
	{
		return v*k;
	}

	template < typename DATA_TYPE >
	inline static VT_Vec<3, DATA_TYPE> operator^ (const VT_Vec<3, DATA_TYPE>& lhs, const VT_Vec<3, DATA_TYPE>& rhs)
	{
		return VT_Vec<3, DATA_TYPE>(
			lhs[1] * rhs[2] - rhs[1] * lhs[2],
			rhs[0] * lhs[2] - lhs[0] * rhs[0],
			lhs[0] * rhs[1] - rhs[0] * lhs[1]
			);
	}

	template < typename DATA_TYPE >
	inline static VT_Vec<7, DATA_TYPE> operator^(const VT_Vec<7, DATA_TYPE>& x, const VT_Vec<7, DATA_TYPE>& y)
	{
		return VT_Vec< 7, DATA_TYPE>
			(
			(x[1] * y[3] - x[3] * y[1]) + (x[2] * y[6] - x[6] * y[2]) + (x[4] * y[5] - x[5] * y[4]),
				(x[2] * y[4] - x[4] * y[2]) + (x[3] * y[0] - x[0] * y[3]) + (x[5] * y[6] - x[6] * y[5]),
				(x[3] * y[5] - x[5] * y[3]) + (x[4] * y[1] - x[1] * y[4]) + (x[6] * y[0] - x[0] * y[6]),
				(x[4] * y[6] - x[6] * y[4]) + (x[5] * y[2] - x[2] * y[5]) + (x[0] * y[1] - x[1] * y[0]),
				(x[5] * y[0] - x[0] * y[5]) + (x[6] * y[3] - x[3] * y[6]) + (x[1] * y[2] - x[2] * y[1]),
				(x[6] * y[1] - x[1] * y[6]) + (x[0] * y[4] - x[4] * y[0]) + (x[2] * y[3] - x[3] * y[2]),
				(x[0] * y[2] - x[2] * y[0]) + (x[1] * y[5] - x[5] * y[1]) + (x[3] * y[4] - x[4] * y[3])
				);
	}
}
#endif