
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : February 15, 2020
	* Last modified : April 11, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/
#pragma once

/*
	All the includes and functions are to be aligned in the alphabetical order
*/
#include<cmath>
#include<iostream>
#include<set>

#include"../utils/Defines.h"


/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		array name space : Name space containing helpful functions for cmll::data::storage type operations
	*/
	namespace array
	{
		/**
			* Function Name :  Add

			* Function Description :  Function to add a value to all elements in the multidimensional array

			* Parameters :

			1) X :			The multidimensional vector whose elements are to be added with a value

							Type Expected : multidimensional vector

							Method of passing : By reference

			2) value :		The number to add to each element of X

							Type Expected : double

							Method of passing : const

			* Return :		None


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					cmll::array::add(X,100);

					return 0;

				}


		*/

		void add(data::Storage& X, const double value) noexcept;

		/**
			* Function Name :  Average

			* Function Description :  Function to find average of all elements of the multidimensional vector

			* Parameters :

			1) X :			The multidimensional vector whose average is to be found

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference


			* Return :		double - > average


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto average = cmll::array::average(X);

					return 0;

				}


		*/
		double average(const data::Storage& X) noexcept;

		/**
			* Function Name :  Column

			* Function Description :  Function to Extract columns from the multidimensional vector

			* Parameters :

			1) X :			The multidimensional vector to extract from

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference

			2) columns :	The columns to extract

							Type Expected : std::vector<cmll::data::Storage::size_type>

							Method of passing :constant and by reference

			3) Result :		The resultant array

							Type Expected : multidimensional vector

							Method of passing :By reference


			* Return :	 NOne

			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					std::vector<cmll::data::Storage::size_type> columns = { 1,2,4,5,6};

					cmll::array::columns(X,columns,X_new);

					return 0;

				}


		*/
		void columns(const data::Storage& X, const std::vector<data::Storage::size_type> columns, data::Storage& result) noexcept;

		/**
			* Function Name :  Contains

			* Function Description :  Function to check if the multidimensional vector contains a particular element

			* Parameters :

			1) X :			The multidimensional vector to look into

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference

			2) value :		The value to look into

							Type Expected : double

							Method of passing :constant


			* Return :		bool - >  is the value present


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto unique = cmll::array::contains(X,3);

					return 0;

				}


		*/
		bool contains(const data::Storage& X, const double value) noexcept;

		/**
			* Function Name :  Maximum

			* Function Description :  Function to find Maximum of all elements of the multidimensional vector

			* Parameters :

			1) X :			The multidimensional vector whose maximum is to be found

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference


			* Return :		double - > maximum


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto average = cmll::array::maximum(X);

					return 0;

				}


		*/
		double maximum(const data::Storage& X) noexcept;
		
		/**
			* Function Name :  Power

			* Function Description :  Function raise power of each elements in the passed vector (multidimensional)

			* Parameters :

			1) X :			The multidimensional vector whose elements are to be raised by power

							Type Expected : multidimensional vector

							Method of passing :  constant and by reference

			2) power :		The power to raise the elements of the multidimensional vector to;

							Type Expected : double

							Method of passing : const

			* Return :		None


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto  result = cmll::array::power(X,2);

					return 0;

				}


		*/
		void power(data::Storage& X, const double power) noexcept;


		/**
			* Function Name :  Ravel

			* Function Description :  Function to covert a multidimensional array to a single vector

			* Parameters :

			1) X :			The multidimensional vector to convert

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference

			3) Result :		The resultant vector

							Type Expected : one dimensional vector

							Method of passing :By reference


			* Return :	 None

			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					cmll::array::ravel(X,X_new);

					return 0;

				}


		*/
		void ravel(const data::Storage& X, std::vector<double>& result) noexcept;

		
		
		/**
			* Function Name :  Subtract

			* Function Description :  Function to subtract a value to all elements in the multidimensional array

			* Parameters :

			1) X :			The multidimensional vector whose elements are to be subtracted with a value

							Type Expected : multidimensional vector

							Method of passing : By reference

			2) value :		The number to subtract from each element of X

							Type Expected : double

							Method of passing : const

			* Return :		None


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					cmll::array::subtract(X,100);

					return 0;

				}


		*/
		void subtract(data::Storage& X, const double value) noexcept;

		

		/**
			* Function Name :  Sum

			* Function Description :  Function to find sum  of all elements of the multidimensional vector

			* Parameters :

			1) X :			The multidimensional vector whose sum is to be calculated

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference


			* Return :		double - > Sum of all elements


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto sum = cmll::array::sum(X);

					return 0;

				}


		*/
		double sum(const data::Storage& X) noexcept;

		/**
			* Function Name :  Sum

			* Function Description :  Function to find sum a elements row wise (Horizontally) or column wise (vertically)

			* Parameters :

			1) X :			The multidimensional vector whose sum is to be calculated

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference
			
			2) result  :	The resultant vector that will contain row wise or column wise sum	

							Type Expected : vector

							Method of passing : By reference
			
		    3) where :		Whether to do a horizontal or vertical addition
							
							Type Expected : cmll::array::axis

							Method of passing : const and by reference
			
			4) weight	:	Additional bias to the sum
							
							Type expected : double
							
							Method of passing const and by reference

			* Return :		None


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					cmll::array::sum(X,sum,cmll::array::axis::HORIZONTAL);

					return 0;

				}


		*/
		void sum(const data::Storage& X,std::vector<double>& result,const axis &where = axis::HORIZONTAL, const double &weight = 0) noexcept;

		/**
			* Function Name :  Unique

			* Function Description :  Function to find number of unique elements in the multidimensional vector

			* Parameters :

			1) X :			The multidimensional vector whose unique elements are to be found

							Type Expected : multidimensional vector

							Method of passing :constant and  by reference


			* Return :		cmll::data::Storage::size_type - > Number of unique values


			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					auto unique = cmll::array::unique(X);

					return 0;

				}


		*/
		data::Storage::size_type unique(const data::Storage& X) noexcept;



		/**
			* Function Name :  Unravel

			* Function Description :  Function to covert  a single vector  to a multidimensional vector 

			* Parameters :

			

			1) X :			The resultant multidimensional vector

							Type Expected :  multidimensional

							Method of passing : const and by reference
			
			2) result :		The  resultant one dimensional vector

							Type Expected : one dimensional vector

							Method of passing :by reference


			* Return :	 None

			* Example

				#include<vector>
				#include<numeric/Array.h>

				int main()
				{
					// vector creation and element adding here

					cmll::array::unravel(X,X_new);

					return 0;

				}


		*/
		void unravel(const std::vector<double>& X, data::Storage& result) noexcept;


	}
}
