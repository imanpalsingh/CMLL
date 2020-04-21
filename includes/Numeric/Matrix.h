/*

	* Project title : CMLL :  C++'s Machine Learning Library 
	
	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>
	
	* Project creation date : February 8, 2020
	
	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : February 8, 2020
	* Last modified : April 10, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/

#pragma once


/* 
	All the includes are to be aligned in the alphabetical order 
*/
#include<iostream>
#include"../utils/Defines.h"

/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		matrix name space :  name space that contains functions for matrix related operations such as multiply, transpose inverse etc.
	*/
	namespace matrix
	{


		/**
		* Function Name :  Matrix Addition

		* Function Description :  Function accepts three multidimensional vectors.
								  A matrix Add operation is performed on first two parameters and the result is stored in the third parameter.

								  result = matrixLhs + matrixRhs

		* Parameters :

		1) matrixLhs :  Left hand matrix of equation [ result = matrixLhs + matrixRhs ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) matrixRhs :  Right hand matrix of equation [ result = LHS + RHS ]

						Type Expected : Multidimensional vector 

						Method of passing : constant and by reference

		3) result :		result of the equation [ result = LHS + RHS]

						Type Expected : Multidimensional vector 

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::addition(lhs,rhs,result);

				return 0;

			}


		*/
		void addition(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept;

		/**
		* Function Name :  Matrix Diagonal Addition

		* Function Description :  Function accepts three multidimensional vectors.
								  The second vector is supposed to be a column vector with diagonal elements as its elements
								  THe diagonal elements are added to the diagonal elements of the matrixLhs

								  result = matrixLhs + matrixRhs

		* Parameters :

		1) matrixLhs :  Left hand matrix of equation [ result = matrixLhs + matrixRhs ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) vector :		The diagonal matrix containing only the diagonal elements
						
						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference


		3) result :		result of the equation [ result = LHS + RHS]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::diagonalAddition(lhs,rhs,result);

				return 0;

			}


		*/
		void diagonalAddition(const data::Storage& matrixLhs, const data::Storage& vector, data::Storage& result) noexcept;
		/**
		* Function Name :  Matrix diagonal multiplication

		* Function Description :  Function accepts three multidimensional vectors.

								  A matrix multiplication operation is performed on first two parameters and the result is stored in the third parameter.
								  One of the two matrices is just a column vector of diagonal elements instead of an entire matrix.

								  result = matrixLhs * matrixRhs

		* Parameters :

		1) matrixLhs :			Left hand matrix of equation [ result = matrixLhs * matrixRhs ]

								Type Expected : Multidimensional vector

								Method of passing :  constant and by reference

		2) matrixRhs :			Right hand matrix of equation [ result = LHS * RHS ]

								Type Expected : Multidimensional vector 

								Method of passing : constant and by reference

		3) result :				result of the equation [ result = LHS * RHS]

								Type Expected : Multidimensional vector

								Method of passing : Reference;

		4) whichMatrixDiagonal : enum of matrix::selection to specify which of the matrices passed is an diagonal matrix

								 Type expected : cmll::matrix::selection enum
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				 /// create some vectors add some values

				cmll::matrix::diagonalMultiplication(lhs,rhs,result,cmll::matrix::selection::LHS);

				return 0;

			}


		*/
		void diagonalMultiplication(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result, selection whichMatrixDiagonal) noexcept;

		/**
		* Function Name :  Diagonal Matrix inverse

		* Function Description :  Function accepts two multidimensional vectors
								  The first vector is a column vector that contains diagonal elements of the diagonal matrix

								  result = inverse(vector);

		* Parameters :

		1) vector :		Column vector containing the diagonal elements of the diagonal matrix [ result = inverse(vector) ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) result :		result of the equation [ result = inverse(vector) ]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::diagonalInverse(vector,result);

				return 0;

			}


		*/
		void diagonalInverse(const data::Storage& vector, data::Storage& result) noexcept;

		/**
		* Function Name :  Matrix inverse

		* Function Description :  Function accepts three multidimensional vectors.
								  The l and u are evaluated to calculate the inverse of the matrix

								  result = inverse(l,u);

		* Parameters :

		1) l :			l decomposition of the matrix to find inversion of [ result = inverse(l,u) ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) u :			u decomposition of the matrix to find inversion of [ result = inverse(l,u) ]

						Type Expected : Multidimensional vector

						Method of passing : constant and by reference

		3) result :		result of the equation [ result = inverse(l,u) ]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::inverse(l,u,result);

				return 0;

			}


		*/
		void inverse(const data::Storage& l, const data::Storage& u, data::Storage& result) noexcept;
		
		
		
		/**
		* Function Name :  Matrix multiplication

		* Function Description :  Function accepts three multidimensional vectors.
								  A matrix multiplication operation is performed on first two parameters and the result is stored in the third parameter.

								  result = matrixLhs * matrixRhs

		* Parameters :

		1) matrixLhs :  Left hand matrix of equation [ result = matrixLhs * matrixRhs ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) matrixRhs :  Right hand matrix of equation [ result = LHS * RHS ]

						Type Expected : Multidimensional vector

						Method of passing : constant and by reference

		3) result :		result of the equation [ result = LHS * RHS]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::multiplication(lhs,rhs,result);

				return 0;

			}


		*/
		void multiplication(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept;

		/**
		* Function Name :  L U decomposition of a matrix

		* Function Description :  Function accepts three multidimensional vectors matrix, l and u.

								  A square matrix is decomposed into a L and a U matrix using do little algorithm

								  l,u = Lu(matrix)

		* Parameters :

		1) matrix :		Matrix of equation [ l,u = Lu(matrix) ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) l :			l of equation [ l,u = Lu(matrix) ]

						Type Expected : Multi dimensional vector

						Method of passing : by reference
		
		3) u :			u of equation [ l,u = Lu(matrix) ]

						Type Expected : Multi dimensional vector

						Method of passing : by reference
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::lu(matrix,l,u)

				return 0;

			}
		*/
		void lu(const data::Storage& matrix, data::Storage& l, data::Storage& u) noexcept;

		/**
		* Function Name :  Matrix subtraction

		* Function Description :  Function accepts three multidimensional vectors.

								 A matrix subtract operation is performed on first two parameters and the result is stored in the third parameter.

								 result = matrixLhs - matrixRhs

		* Parameters :

		1) matrixLhs :  Left hand matrix of equation [ result = matrixLhs - matrixRhs ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) matrixRhs :  Right hand column matrix of equation [ result = LHS - RHS ]

						Type Expected : Multidimensional vector

						Method of passing : constant and by reference

		3) result :		result of the equation [ result = LHS - RHS]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector definition and element adding here

				cmll::matrix::subtraction(lhs,rhs,result);

				return 0;

			}


		*/
		void subtraction(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept;

		/**
		* Function Name :  Matrix transpose

		* Function Description :  Function accepts two multidimensional vectors.

								  A matrix transpose operation is performed on first parameter and the result is stored in the second parameter.

								  result = transpose(matrix)

		* Parameters :

		1) matrix:		Original matrix of equation [ result = transpose(matrix) ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) result :		result of the equation [ result = transpose(matrix) ]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector definition and element adding here

				cmll::matrix::transpose(matrix,result)

				return 0;

			}


		*/
		void transpose(const data::Storage& matrix, data::Storage& result) noexcept;


		/**
		* Function Name :  Matrix Addition with a vector

		* Function Description :  Function accepts three multidimensional vectors.
								 
								 A matrix Add operation is performed on first two parameters and the result is stored in the third parameter.
								 The second parameter is assumed to be a column vector instead of a matrix
								 
								 result = matrixLhs + matrixRhs

		* Parameters :

		1) matrixLhs :  Left hand matrix of equation [ result = matrixLhs + matrixRhs ]

						Type Expected : Multidimensional vector

						Method of passing :  constant and by reference

		2) matrixRhs :  Right hand column matrix of equation [ result = LHS + RHS ]

						Type Expected : Multidimensional vector

						Method of passing : constant and by reference

		3) result :		result of the equation [ result = LHS + RHS]

						Type Expected : Multidimensional vector

						Method of passing : Reference;
		*

		* Return :		None


		* Example

			#include<vector>
			#include<numeric/Matrix.h>

			int main()
			{
				// vector creation and element adding here

				cmll::matrix::addition(lhs,rhs,result);

				return 0;

			}


		*/
		void vectorAddition(const data::Storage& matrixLhs, const data::Storage& vectorRhs, data::Storage& result) noexcept;

	}
}