
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : April 19, 2020
	* Last modified : April 19, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/
#pragma once

#include <iostream>

#include "../Numeric/Array.h"
#include "Defines.h"

/*
	Parent name space
*/
namespace cmll
{
	/*
		Name space for preprocessing related functions
	*/
	namespace preprocessing
	{

		/**
			   * Function Name :  Split

			   * Function Description :  Function to Split a cmll::data::Storage into 2 by some percentage

			   * Parameters :

			   1) X :			The vector to split

							    Type Expected : cmll::data::Storage

							    Method of passing :  constant and by reference

			   2) XTrain  :		The First split

							   Type Expected : cmll::data::Storage

							   Method of passing :  by reference

			   3) XTest  :	   The second split

							   Type Expected : cmll::data::Storage

							   Method of passing :  by reference

				4) splitRatio: The portion taken by XTrain

			   * Return :	   None


			   * Example

				#include<vector>
				#include<utils/Preprocessing.h>

				int main()
				{
					//vector(y) stuff here

					cmll::preprocessing::split(X,XTrain,XTest,0.75)
				}


			*/
		void split(const data::Storage& X, data::Storage& XTrain, data::Storage& XTest, const double& splitRatio = 0.7) noexcept;

		/**
			   * Function Name :  Binarizer

			   * Function Description :  Function to create a Binary output vector from a non binary vector

			   * Parameters :

			   1) X :				The vector to convert

									Type Expected : cmll::data::Storage

									Method of passing :  constant and by reference

				2) result :			The resultant vector

									Type Expected : cmll::data::Storage

									Method of passing :  by reference

				3) negativeValues : Values to assign to the negative binary values (default 0 of 0,1)
									
									Type Expected : double

									Method of passing :  const and by reference

				4) PositiveValues : Values to assign to the negative binary values (default 0 of 0,1)

									Type Expected : double

									Method of passing :  const and by reference


			   * Return :	    None


			   * Example

				#include<vector>
				#include<utils/Preprocessing.h>

				int main()
				{
					//vector(y) stuff here

					cmll::preprocessing::binarizer(X,-1,1);
				}


			*/
		void binarizer(const data::Storage& X, data::Storage& result, const double& negativeValues=0, const double& positiveValues=1) noexcept;

		/**
			   * Function Name :  BinaryFeatures

			   * Function Description :  Function to create a Binary Feature Matrix 

			   * Parameters :

			   1) X :				The Feature Matrix to convert

									Type Expected : cmll::data::Storage

									Method of passing :  constant and by reference

				2) result :			The resultant vector

									Type Expected : cmll::data::Storage

									Method of passing :  by reference

				3) negativeValues : Values to assign to the negative binary values (default 0 of 0,1)

									Type Expected : double

									Method of passing :  const and by reference

				4) PositiveValues : Values to assign to the negative binary values (default 0 of 0,1)

									Type Expected : double

									Method of passing :  const and by reference


			   * Return :	    None


			   * Example

				#include<vector>
				#include<utils/Preprocessing.h>

				int main()
				{
					//vector(y) stuff here

					cmll::preprocessing::binaryFeatures(X,-1,1);
				}


			*/
		void binaryFeatures(const data::Storage& X, data::Storage& result, const double& negativeValues = 0, const double& positiveValues = 1) noexcept;
	}
}
