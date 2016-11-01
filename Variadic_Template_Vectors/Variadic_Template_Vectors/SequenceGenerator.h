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

#ifndef SEQUENCE_GENERATOR_H_
#define SEQUENCE_GENERATOR_H_
/*
Reference : http://mosra.cz/blog/article.php?a=21-constructing-matrix-from-column-vectors-with-c-11-variadic-template-unpacking

the folowing code uses the varaidic expansion sequence generator

template < size_t ... >					- (1)
struct sequence {};

template < size_t N, size_t ... S >		- (2)
struct generate_sequence :
generate_sequence< N - 1, N - 1, S... > {};

template < size_t ... S >				- (3)
struct generate_sequence< 0, S ... >
{
typedef sequence<S ...> Type;
};

What this code does is that it is trying to derive
a custom variadic sequence of the type
sequence< 0, ..., N - 1 >.

(1) serves as a forward declaration that is required in
(3).

(2) will be called and unpack recursively in compile time
to derive the final sequence type that the user need by
reducing the size count N by 1 ever recursion in the parameter pack.
This will end at the base case when it obtain generate_sequence<0,0,...> :

e.g Count of 5
GenSeq<5> -> GenSeq<4,4> -> GenSeq<3,3,4> -> GenSeq<2,2,3,4> -> GenSeq<1,1,2,3,4>
-> GenSeq<0,0,1,2,3,4>

Once the recursion reach the last sequence, it will delegate a call to (3) to
match that particular specialization to create and generate the final sequence.

Therefore, calling GenSeq<5> we will get the following custom sequence sequence<0,1,2,3,4>.

This sequence is used to call the index value of the vector of Dimension N thru it's operator[].
*/

//NOTE!
/*
	C++14 has provided a utility class std::integer_sequence.
	Need to update this file to accomodate that 
*/

template < size_t ... >
struct sequence
{

};

template < size_t N, size_t... S >
struct generate_sequence :
	generate_sequence< N - 1, N - 1, S... >
{

};

template < size_t ... S >
struct generate_sequence < 0, S... >
{
	typedef sequence<S...> Type;
};

#endif