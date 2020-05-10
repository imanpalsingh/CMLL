
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
		linear name space : Name space for linear models of regression and classification

	*/
	namespace utils
	{

		namespace check
		{


			/**
				* Function Name :  Has NaN

				* Function Description :  Function to check if a cmll::data::Storage has NaN (not a number) values

				* Parameters :

				1) X :			The vector to check into

								Type Expected : cmll::data::Storage

								Method of passing :  constant and by reference

				* Return :	    bool - > true if NaN values are present and false if there aren't


				* Example

				#include<vector>
				#include<Utils/Utils.h>

				int main()
				{
					//vector(y) stuff here

					cmll::utils::check::hasNaN(X);
				}


			*/
			bool hasNaN(const data::Storage& X) noexcept;


			/**
			* Function Name :  Xy

			* Function Description :  Function runs checks on X and y  to verify that X.size() == y.size() and X[0].size() is satisfied
										in all rows of X and same in y

			* Parameters : 

			1) X  : The feature matrix
					Type accepted : Multidimensional vector
					Method :  const and by reference

			2) y  : The vector of prediction
					Type accepted : Multidimensional vector
					Method :  const and by reference

			* Return :		None

			* Throws :

			1)	std::length_error  :  If X.size() != y.size() or if the size of every row in X is not same. Same for y.


			* Example

				#include<vector>
				#include<utils/Utils.h>

				int main()
				{
					// vector creation and element adding here

					cmll::utils::check::Xy(X,y);

					return 0;

				}


			*/
			void Xy(const data::Storage& X, const data::Storage& y); // Throws std::length_error

			/**
			* Function Name :  XTest

			* Function Description :  Function runs checks on new Test set . Ensures that XTest[0].size() == X[0].size()
										and all rows have same size in XTest.

			* Parameters :

			1) X  :		The feature matrix
						Type accepted : Multidimensional vector
						Method :  const and by reference
			2) XTest  : The test feature matrix
						Type accepted : Multidimensional vector
						Method :  const and by reference

			* Return :		None

			* Throws :

			1)	std::invalid_length   :  If XTest[0].size() != X[0].size() or if size of all rows is not equal.


			* Example

				#include<vector>
				#include<utils/Util.h>

				int main()
				{
					// vector creation and element adding here

					cmll::utils::check::XTest(XTest);

					return 0;

				}


			*/
			void XTest(const data::Storage& X, const data::Storage& XTest); // Throws std::invalid_length

			/**
			* Function Name :  CheckyTest()

			* Function Description :  Function runs checks on Test set labels or values set . Ensures that y.size() == YTest.size()

			* Parameters :

			1) y  : The vector of prediction
					Type accepted : Multidimensional vector
					Method :  const and by reference
			2) yTest  : The  test vector of prediction
					Type accepted : Multidimensional vector
					Method :  const and by reference

			* Return :		None

			* Throws :

			1)	std::invalid_length   :  If y.size() != YTest.size()


			* Example

				#include<vector>
				#include<utils/Utils.h>

				int main()
				{
					// vector creation and element adding here

					cmll::utils::check::yTest(yTest);

					return 0;

				}


			*/
			void yTest(const data::Storage& y, const data::Storage& yTest);

		}
	}

}