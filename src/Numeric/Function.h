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
#include<cmath>
#include<iostream>

#include"../utils/Defines.h"

/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		functions name space : Name space containing various mathematical functions
	*/
	namespace functions
	{
		/*
			activation name space : Name space for activation functions
		*/
		namespace activation
		{


			/**
			* Function Name :  Sigmoid

			* Function Description :  Function accepts a double variable
									  The variable is fed into the sigmoid function and the resultant is returned

									  result = sigmoid(x)

			* Parameters :

			1) x :			the number to feed in the sigmoid equation [ result = sigmoid(x) ]

							Type Expected : double

							Method of passing :  constant and by reference

			* Return :		double - >result;


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto  result = cmll::functions::activation::sigmoid(0.5);

					return 0;

				}


			*/
			double sigmoid(const double& x);

			/**
			* Function Name :  Fast Sigmoid

			* Function Description :  Function accepts a double variable
									  The variable is fed into the fast sigmoid function and the resultant is returned

									  result = fastSigmoid(x);

			* Parameters :

			1) x :			the number to feed in the sigmoid equation [ result = fastSigmoid(x) ]

							Type Expected : double

							Method of passing :  constant and by reference
			*

			* Return :		double - > result


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::activation::fastSigmoid(0.5);

					return 0;

				}


			*/
			double fastSigmoid(const double& x);

			/**
			* Function Name :  Relu

			* Function Description :  Function accepts a double variable
									  The variable is fed into the fast Relu and the resultant is returned

									  result = relu(x);

			* Parameters :

			1) x :			the number to feed in the relu equation [ result = relu(x) ]

							Type Expected : double

							Method of passing :  constant and by reference
			*

			* Return :		double - > result


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::activation::relu(0.5);

					return 0;

				}


			*/
			double relu(const double& x);

			/**
			* Function Name :  Soft plus

			* Function Description :  Function accepts a double variable
									  The variable is fed into the Soft plus and the resultant is returned

									  result = softPlus(x);

			* Parameters :

			1) x :			the number to feed in the soft plus equation [ result = softPlus(x) ]

							Type Expected : double

							Method of passing :  constant and by reference
			*

			* Return :		result - > double


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::activation::softPlus(0.5);

					return 0;

				}


			*/
			double softPlus(const double& x);

		}
		/*
			Name space for functions related to Gaussian distribution
		*/
		namespace gaussian
		{
			/**
			* Function Name :  probabilityDensity

			* Function Description :  Function accepts value, mean and variance
									  The variable is fed Gaussian probability distribution function and result is stored in result

									  result = probabilityDensity(value,mean,variance,result)

			* Parameters :

			1) x :			the value to feed in the  gaussian probability distribution function [ result = probabilityDensity(value,mean,variance,result)]

							Type Expected : double

							Method of passing :  constant and by reference

			2) mean :		mean in the equation [  result = probabilityDensity(value,mean,variance,result)  ]

							Type Expected : double

							Method of passing : constant and by Reference;
			
			3) variance :	variance in the equation [  result = probabilityDensity(value,mean,variance,result)  ]

							Type Expected : double

							Method of passing : constant and by Reference;

			* Return :		double  - > result


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::gaussian::probabilityDistribution(x,mean,variance);

					return 0;

				}


			*/
			double probabilityDensity(const double& x, const double& mean, const double& variance);
		}

		/*
			Name space for distance calculation functions
		*/
		namespace distance
		{
			/**
			* Function Name :  Euclidean

			* Function Description :  Function calculates euclidean distance between two sets of point x,y


			* Parameters :

			1) x :			The first observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference
			
			2) y :			The second observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference
			*

			* Return :		result - > double


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::distance::euclidean({2,3},{4,5});

					return 0;

				}


			*/
			double euclidean(const std::vector<double>& x, const std::vector<double>& y, const double& none=0);

			/**
			* Function Name :  Manhattan

			* Function Description :  Function calculates Manhattan distance between two sets of point x,y


			* Parameters :

			1) x :			The first observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference

			2) y :			The second observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference
			*

			* Return :		result - > double


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::distance::manhattan({2,3},{4,5});

					return 0;

				}


			*/
			double manhattan(const std::vector<double>& x, const std::vector<double>& y, const double& none=0);

			/**
			* Function Name :  Minkowski

			* Function Description :  Function calculates minkowski distance between two sets of point x,y


			* Parameters :

			1) x :			The first observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference

			2) y :			The second observation

							Type Expected : std::vector<double>

							Method of passing :  constant and by reference

			3) p :			The value of order p
							
							Type Expected : double

							Method of passing :  constant and by reference
			*

			* Return :		result - > double


			* Example

				#include<vector>
				#include<numeric/Functions.h>

				int main()
				{
					// vector creation and element adding here

					auto result = cmll::functions::distance::minkowski({2,3},{4,5});

					return 0;

				}


			*/
			double minkowski(const std::vector<double>& x, const std::vector<double>& y, const double& p);
		}
	}
}