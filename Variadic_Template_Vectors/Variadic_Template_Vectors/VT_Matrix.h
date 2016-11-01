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

#ifndef VT_MATRIX_H_
#define VT_MATRIX_H_

#include <array>
#include <memory>

#include "SequenceGenerator.h"
#include "VT_Vec.h"

namespace math
{
	template < size_t M, size_t N, typename DATA_TYPE = float>
	class VT_Matrix
	{
	private:

		std::array<DATA_TYPE, N*M> matrix;

		template < size_t ...seq, typename ...T >
		inline constexpr VT_Matrix(sequence<seq...> s, const VT_Vec<N, DATA_TYPE>& first, T&&... next) :
			VT_Matrix(s, next..., first[seq]...)
		{

		}

		template < size_t ...seq, typename ...T >
		constexpr VT_Matrix(sequence<seq...> s, DATA_TYPE first, T&&... next) :
			VT_Matrix(first, next...)
		{

		}

	public:

		typedef VT_Matrix < M, N, DATA_TYPE > resolved_matrix_type;

		template < typename ...T >
		constexpr VT_Matrix(const DATA_TYPE& first, T... next) :
			matrix({ first, next... })
		{

		}

		template < typename ...T >
		constexpr VT_Matrix(const VT_Vec<N, DATA_TYPE>& first, T... next) :
			VT_Matrix(typename generate_sequence<M>::Type(), first, next...)
		{

		}

		VT_Matrix() :
			matrix({ 0 })
		{

		}

		VT_Matrix(const VT_Matrix<M, N, DATA_TYPE>& other)
		{
			std::copy(other.matrix.begin(), other.matrix.end(), matrix.begin());
		}

		VT_Matrix(VT_Matrix<M, N, DATA_TYPE>&& other) :
			matrix(std::move(other.matrix))
		{

		}

		VT_Matrix<M, N, DATA_TYPE>& operator= (const resolved_matrix_type& rhs)
		{
			if (this == &rhs)
				return *this;

			std::copy(rhs.matrix, rhs.matrix + (N*M), matrix.begin());

			return *this;
		}

		resolved_matrix_type& operator= (VT_Matrix&& rhs)
		{
			if (this == &rhs)
				return *this;

			matrix = std::move(rhs.matrix);

			return *this;
		}

		DATA_TYPE operator() (const unsigned i, const unsigned j) const
		{
			return matrix[i * N + j];
		}

		DATA_TYPE& operator() (const unsigned i, const unsigned j)
		{
			return matrix[i * N + j];
		}

		static constexpr size_t NumOfRows()
		{
			return M;
		}

		static constexpr size_t NumOfColumns()
		{
			return N;
		}

		resolved_matrix_type Transpose() const
		{
			resolved_matrix_type transpose;

			for (auto i = 0; i < M; ++i)
			{
				for (auto j = 0; j < N; ++j)
				{
					transpose(j, i) = matrix[i * N + j];
				}
			}

			return transpose;
		}

		VT_Vec<N, DATA_TYPE> GetRowVector(const unsigned row) const
		{
			VT_Vec<N, DATA_TYPE> vec;

			for (auto i = 0; i < N; ++i)
				vec[i] = matrix[row * N + i];

			return vec;
		}

		VT_Vec<M, DATA_TYPE> GetColumnVector(const unsigned col) const
		{
			VT_Vec<N, DATA_TYPE> vec;

			for (auto i = 0; i < M; ++i)
				vec[i] = matrix[col + i * N];

			return vec;
		}

		DATA_TYPE Trace() const
		{
			DATA_TYPE trace = static_cast<DATA_TYPE>(0);

			for (auto i = 0; i < M; ++i)
				trace += (*this)(i, i);

			return trace;
		}

		resolved_matrix_type operator+ (const resolved_matrix_type& rhs) const
		{
			resolved_matrix_type sum;

			for (auto i = 0; i < M; ++i)
				for (auto j = 0; j < N; ++j)
					sum(i, j) = matrix[i * N + j] + rhs(i, j);

			return sum;
		}

		resolved_matrix_type operator- (const resolved_matrix_type& rhs) const
		{
			resolved_matrix_type inv_sum;

			for (auto i = 0; i < M; ++i)
				for (auto j = 0; j < N; ++j)
					inv_sum(i, j) = matrix[i * N + j] - rhs(i, j);

			return inv_sum;
		}

		resolved_matrix_type operator* (const resolved_matrix_type& rhs) const
		{
			resolved_matrix_type product;

			for (auto i = 0; i < M; ++i)
				for (auto j = 0; j < N; ++j)
					product(i, j) = GetRowVector(i) * rhs.GetColumnVector(j);

			return product;
		}

		resolved_matrix_type operator*(const DATA_TYPE& k) const
		{
			resolved_matrix_type scaled;

			for (auto i = 0; i < N*M; ++i)
				scaled.matrix[i] = matrix[i] * k;

			return scaled;
		}

		VT_Vec<N, DATA_TYPE> operator*(const VT_Vec<N, DATA_TYPE>& v)
		{
			VT_Vec<N, DATA_TYPE> Mv;

			for (auto i = 0; i < N; ++i)
				Mv[i] = GetRowVector(i) * v;

			return Mv;
		}
	};

	template < size_t M, size_t N, typename DATA_TYPE >
	inline static VT_Matrix<M, N, DATA_TYPE> operator*(const DATA_TYPE& k, const VT_Matrix<M, N, DATA_TYPE>& M)
	{
		return M * k;
	}

	template < size_t M, size_t N, typename DATA_TYPE >
	inline static VT_Vec< M, DATA_TYPE > operator*(const VT_Vec<M, DATA_TYPE>& v, const VT_Matrix<M, N, DATA_TYPE>& M)
	{
		VT_Vec<v.Dimension(), DATA_TYPE> vM;

		for (unsigned i = 0; i < v.Dimension(); ++i)
			vM[i] = v * M.GetColumnVector(i);

		return vM;
	}
}
#endif