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

#include"Function.h"

/*
	Parent name space : All names paces lie under this parent name space
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
			double sigmoid(const double& x)
			{
				/*
					Sigmoid function is defined as 1/1+e^{-1}
				*/

				return (1 / (1 + std::exp(-x)));

			}

			double fastSigmoid(const double& x) 
			{
				/*
					Fast sigmoid function is defined as  x/1+|x|
				*/

				return (x / (1 + std::abs(x)));

			}

			double relu(const double& x) 
			{
				/*
					relu function is max(0,x)
				*/
				return ((x > 0) ? x : 0);
			}

			double softPlus(const double& x) 
			{
				/*
					softplus is given by  log(1 + e^{x})
				*/

				return (std::log(1 + std::exp(x)));
			}
		}
		
		/*
			Name space for functions related to Gaussian distribution
		*/
		namespace gaussian
		{
			double probabilityDensity(const double& x, const double& mean, const double& variance)
			{
				/*
					The Gaussian probability distribution function is given by
					
					g(x) = 1/(2*pi*variance) * e ^ { -1/2 * ( x - u )^2/variance }
				*/

				double e = std::exp((-1 * std::pow(x - mean, 2)) / (2 * variance));

				return (e * (1 / (std::sqrt(2 * 3.141592653589793238463 * variance))));
			}
		}

		/*
			Name space for distance calculation functions
		*/
		namespace distance
		{
			double euclidean(const std::vector<double>& x, const std::vector<double>& y, const double &none)
			{
				/*
					Euclidean distance  is given by sqrt( ( (x[i]-y[i])^2) )

					The x and y should be of same size
				*/
				double sum = 0;
				for (std::vector<double>::size_type di = 0; di < x.size(); ++di)
				{
					sum += std::pow((x[di] - y[di]), 2);
				}

				return std::sqrt(sum);
			}

			double manhattan(const std::vector<double>& x, const std::vector<double>& y, const double &none)
			{
				double sum = 0;
				for (std::vector<double>::size_type di = 0; di < x.size(); ++di)
				{
					sum += std::abs(x[di] - y[di]);
				}

				return sum;
			}

			double minkowski(const std::vector<double>& x, const std::vector<double>& y,const double &p)
			{
				double sum = 0;
				for (std::vector<double>::size_type di = 0; di < x.size(); ++di)
				{
					sum += std::pow((x[di] - y[di]), p);
				}

				return std::pow(sum, (1 / p));
			}
		}
	}
}