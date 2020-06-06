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



/* 
	All th includes are to be aligned in the alphabetical order 
*/
#include"../../includes/Numeric/Matrix.h"

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

		void addition(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept
		{
			/*

				Addition of elements of matrixLhs and matrixRhs is stored in result;
				
				The matrixLhs and matrixRhs and result should be in the order of NXM and NXM or undefined behavior may occur.

			*/

			data::Storage::size_type row, lhsRows;
			std::vector<double>::size_type col, lhsCols;

			lhsRows = matrixLhs.size();
			lhsCols = matrixLhs[0].size();

			for (row = 0; row < lhsRows; ++row)
			{
				for (col = 0; col < lhsCols; ++col)
				{
					result[row][col] = matrixLhs[row][col] + matrixRhs[row][col];
				}
			}
		}

		void diagonalAddition(const data::Storage& matrixLhs, const data::Storage& vector, data::Storage& result) noexcept
		{
			/*
				The matrixLhs's diagonal elements are added with elements of vector to perform a diagonal matrix addition
			*/

			data::Storage::size_type row, lhsRows;
			std::vector<double>::size_type col, lhsCols;

			lhsRows = matrixLhs.size();
			lhsCols = matrixLhs[0].size();

			for (row = 0; row < lhsRows; ++row)
			{
				for (col = 0; col < lhsCols; ++col)
				{
					if (row == col)
					{
						result[row][col] = matrixLhs[row][col] + vector[row][0];
					}

					else
					{
						result[row][col] = matrixLhs[row][col];
					}
				}
			}
			
		}
		
		void diagonalMultiplication(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result, selection whichMatrixDiagonal) noexcept
		{
			/*
				One of the vectors passed is supposed to be just a column vector containing the diagonal elements

				The matrixLhs and matrixRhs should be in the order of NXP PX1 (originally as PXP)
				The result vector should be in NXP shape or undefined behavior may occur.

				Algorithm is as follows :

				This function is based on the diagonal property of diagonal matrices

				The effect of pre multiplying a matrix by a diagonal matrix is
				that of multiplying the i-th row of matrix A by the factor ki i.e.
				the successive rows of the original matrix are simply multiplied by successive diagonal elements of the diagonal matrix

				The effect of post multiplying a matrix by a diagonal matrix is
				is that of multiplying the i-th column of matrix A by the factor ki i.e.
				the successive columns of the original matrix are simply multiplied by successive diagonal elements of the diagonal matrix
			*/

			data::Storage::size_type row;
			std::vector<double>::size_type col;

			// If the matrixLhs is the diagonal matrix represented as a column vector with the diagonal elements
			if (whichMatrixDiagonal == selection::LHS)
			{
				
				data::Storage::size_type rhsRows;
				std::vector<double>::size_type rhsCols;
				
				rhsRows = matrixRhs.size();
				rhsCols = matrixRhs[0].size();

				for (row = 0; row < rhsRows; ++row)
				{
					for (col = 0; col < rhsCols; ++col)
					{
						result[row][col] = matrixRhs[row][col] * matrixLhs[row][0];
					}
				}


			}

			// If the matrixRhs is the diagonal matrix represented as a column vector with the diagonal elements
			else if (whichMatrixDiagonal == selection::RHS)
			{
				
				data::Storage::size_type lhsRows;
				std::vector<double>::size_type lhsCols;
				
				lhsRows = matrixLhs.size();
				lhsCols = matrixLhs[0].size();

				for (row = 0; row < lhsRows; ++row)
				{
					for (col = 0; col < lhsCols; ++col)
					{
						result[row][col] = matrixLhs[row][col] * matrixRhs[col][0];
					}
				}
			}

		}

		void diagonalInverse(const data::Storage& vector, data::Storage& result) noexcept
		{
			/*
			  The vector and result should be of order NX1  or undefined behavior may occur
			  
			  The inverse of a diagonal matrix is the reciprocal of its diagonal elements
			*/

			data::Storage::size_type rows = vector.size(),row;

			for (row = 0; row < rows; row++)
			{
				result[row][0] = 1 / vector[row][0];
			}

		}


		void inverse(const data::Storage& l, const data::Storage& u, data::Storage& result) noexcept
		{
			/*
				l, u and result matrices should be of same order that is NXN or undefined behavior may occur

			Inverse of a matrix is given by

			inverse(matrix) = inverse( L * U ) = U^{-1} * L^{-1}

			Which can be obtained using
			Using the equations
								[L]*[z] = [c] 
								[U]*[x] = [z] 
								
			where z is the required column of the inverse matrix
			and c is the column of the identity matrix
			Source : Advance engineering mathematics , LU Decomposition BS Grewal.
			*/
			data::Storage::size_type rows = l.size();

			
			data::Storage result_T(result[0].size(), std::vector<double>(result.size()));

			data::Storage C(rows, std::vector<double>(rows,0));
			std::vector<double> z(rows), x(rows);

			data::Storage::size_type row, colI, col;

			for (row = 0; row < rows; ++row)
			{
				C[row][row] = 1;
			}

			for (colI = 0; colI < rows; ++colI)
			{
				/* 
					Forward substitution [L]*[z] = [c] 
				*/
				z[0] = C[0][colI] / l[0][0];

				for (row = 1; row < rows; ++row)
				{
					double divisor = 1;
					double matrixSum = 0;

					for (col = 0; col < row; ++col)
					{
						matrixSum += l[row][col] * z[col];
					}

					z[row] = (C[row][colI] - matrixSum) / l[row][row];
				}

				/*
					Back substitution [U]*[x] = [z] 
				*/
				x[rows - 1] = z[rows - 1] / u[rows - 1][rows - 1];
				
				
				for (long long row = rows - 2; row>=0; --row)
				{
					double divisor = 1;
					double matrixSum = 0;
					

					for (col = row+1; col < rows; ++col)
					{
						matrixSum += u[row][col] * x[col];
					}

					
					x[row] = (z[row] - matrixSum) / u[row][row];
				}
				
				result_T[colI] = x;
			}


			/*
				The x placed inside result is represented as row vector. But was assumed to be a column vector.
				This makes the current state of the result vector to be transpose of the required inverse.
				To obtain real inverse transposing the result vector
			*/
			transpose(result_T,result);


		}

		
		void multiplication(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept
		{
			/*

				Addition of elements of matrixLhs and matrixRhs is stored in result;

				The matrixLhs and matrixRhs should be in NXP and PXM order or undefined behavior may occur.
				The result vector should be in NXM shape or undefined behavior may occur.

				Note : Algorithm used is brute force. Expect Stressen's matrix multiplication algorithm in future versions

			*/

			data::Storage::size_type row, lhsRows;
			std::vector<double>::size_type col, col_, lhsCols, rhsCols;
			
			lhsRows = matrixLhs.size();
			lhsCols = matrixLhs[0].size();
			rhsCols = matrixRhs[0].size();

			for (row = 0; row < lhsRows; ++row)
			{
				for (col = 0; col < rhsCols; ++col)
				{
					for (col_ = 0; col_ < lhsCols; ++col_)
					{

						result[row][col] += matrixLhs[row][col_] * matrixRhs[col_][col];
					}
				}
			}

		}

		void lu(const data::Storage& matrix, data::Storage& l, data::Storage& u) noexcept
		{
			/*
					The algorithm used is do little algorithm.The L (cmll::data::Storage) and U (cmll::data::Storage) are calculated
					and stored in result;

					The matrix,L,U should be in order of NXN or undefined behavior may occur.
			*/
			
			data::Storage::size_type rows = matrix.size();

			

			for (data::Storage::size_type i = 0; i < rows; i++)
			{
				for (data::Storage::size_type k = i; k < rows; k++)
				{
					double sum = 0;
					for (data::Storage::size_type j = 0; j < i; j++)
						sum += (l[i][j] * u[j][k]);

					u[i][k] = matrix[i][k] - sum;

					
					for (data::Storage::size_type k = i; k < rows; k++)
					{
						if (i == k)
						{
							l[i][i] = 1;
						}
						else
						{
							double sum = 0;
							for (data::Storage::size_type j = 0; j < i; j++)
							{
								sum += (l[k][j] * u[j][i]);
							}

							l[k][i] = (matrix[k][i] - sum) / u[i][i];
						}

					}
				}
			}

		}

		void subtraction(const data::Storage& matrixLhs, const data::Storage& matrixRhs, data::Storage& result) noexcept
		{
			/*

				Subtraction of elements of matrixLhs and matrixRhs is stored in result;

				The matrixLhs and matrixRhs and result should be in the order of NXM and NXM or undefined behavior may occur.

			*/

			data::Storage::size_type lhsRows, row;
			std::vector<double>::size_type lhsCols, col;
			
			lhsRows = matrixLhs.size();
			lhsCols = matrixLhs[0].size();

			for (row = 0; row < lhsRows; ++row)
			{
				for (col = 0; col < lhsCols; ++col)
				{
					result[row][col] = matrixLhs[row][col] - matrixRhs[row][col];
				}
			}

		}

		void transpose(const data::Storage& matrix, data::Storage& result) noexcept
		{
			/*
				Matrix is transposed and stored in result. The columns are converted into rows and vice versa

				The matrix and result should be in the order of MXN and NXM or undefined behavior may occur
			*/

			data::Storage::size_type rows, row;
			std::vector<double>::size_type cols, col;

			rows = matrix.size();
			cols = matrix[0].size();

			for (row = 0; row < rows; ++row)
			{
				for (col = 0; col < cols; ++col)
				{
					result[col][row] = matrix[row][col];
				}
			}
		}


		
		void vectorAddition(const data::Storage& matrixLhs, const data::Storage& vectorRhs, data::Storage& result) noexcept
		{
			/*
				A matrix add operation is performed on the a matrix and a column vector
				The matrix and vector should be in shapes MXN and MX1 respectively
				The result matrix should be in shape MXN or undefined behavior may occur.
			*/

			
			data::Storage::size_type lhsRows, row;
			std::vector<double>::size_type lhsCols, col;

			lhsRows = matrixLhs.size();
			lhsCols = matrixLhs[0].size();
			// Columns of vectorRHS are assumed to be 1

			for (row = 0; row < lhsRows; ++row)
			{
				for (col = 0; col < lhsCols; ++col)
				{
					result[row][col] = matrixLhs[row][col] + vectorRhs[row][0];
				}
			}

		}

		

	}
}
		