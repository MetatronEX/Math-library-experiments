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

#include <iostream>
#include "VT_MathFunctions.h"

using namespace math;

int main()
{
	VT_Vec<4, float> vec4D( 1.f, 2.f, 3.f, 4.f );

	std::cout << vec4D[0] << ", " << vec4D[1] << ", " << vec4D[2] << ", " << vec4D[3] << "\n";
	std::cout << vec4D.Dimension() << "\n";
	std::cout << sizeof(vec4D) << "\n";

	VT_Vec<4, float> A{ 2.f, 4.f, 8.f, 16.f }, B{ 1.f, 1.f, 1.f, 1.f };

	VT_Vec<4,float> C = A + B;

	VT_Vec<4, float> D = 2.f * C;

	std::cout << C[0] << ", " << C[1] << ", " << C[2] << ", " << C[3] << "\n";

	float&& fr = A * B;

	std::cout << fr << "\n";

	std::cout << vec4D[0] << ", " << vec4D[1] << ", " << vec4D[2] << ", " << vec4D[3] << "\n";
	std::cout << A[0] << ", " << A[1] << ", " << A[2] << ", " << A[3] << "\n";
	std::cout << B[0] << ", " << B[1] << ", " << B[2] << ", " << B[3] << "\n";
	std::cout << C[0] << ", " << C[1] << ", " << C[2] << ", " << C[3] << "\n";
	
	VT_Matrix<4, 4, float> matrix{ vec4D, A, B, C };

	std::cout << "Interrupt\n";

	std::cout << "Matrix with previous 4 vectors: " << "\n";

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << matrix(i, j) << " ";

		std::cout << "\n";
	}

	std::cout << "Identity create start.\n";

	VT_Matrix<4, 4, float> identity
	(
		VT_Vec<4, float>(1.f, 0.f, 0.f, 0.f),
		VT_Vec<4, float>(0.f, 1.f, 0.f, 0.f),
		VT_Vec<4, float>(0.f, 0.f, 1.f, 0.f),
		VT_Vec<4, float>(0.f, 0.f, 0.f, 1.f) 
	);

	std::cout << sizeof(identity) << "\n";

	std::cout << "Identity create end.\n";

	VT_Matrix<4, 4, float> product_test = identity * matrix;
	VT_Matrix<4, 4, float> addition_test = identity + matrix;
	VT_Matrix<4, 4, float> subtraction_test = matrix - identity;
	VT_Matrix<4, 4, float> scaling_test = matrix * 50.f;

	std::cout << "Multiply against identity test: " << "\n";

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << product_test(i, j) << " ";

		std::cout << "\n";
	}

	std::cout << "Addition with identity test: " << "\n";

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << addition_test(i, j) << " ";

		std::cout << "\n";
	}

	std::cout << "Subtraction with identity test: " << "\n";

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << subtraction_test(i, j) << " ";

		std::cout << "\n";
	}

	std::cout << "Scaling test: " << "\n";

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << scaling_test(i, j) << " ";

		std::cout << "\n";
	}

	std::cout << "Trace Test: " << matrix.Trace() << "\n";

	VT_Vec<4, float> v{ 4.f, 3.f, 2.f, 1.f };
	
	VT_Vec<4, float> vM = v * identity;
	VT_Vec<4, float> Mv = identity * v;

	std::cout << vM[0] << ", " << vM[1] << ", " << vM[2] << ", " << vM[3] << "\n";
	std::cout << Mv[0] << ", " << Mv[1] << ", " << Mv[2] << ", " << Mv[3] << "\n";
		
	VT_Matrix<4, 4, float> transposed = (2.f * identity).Transpose();

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
			std::cout << transposed(i, j) << " ";

		std::cout << "\n";
	}

	system("PAUSE");

	return 0;
}