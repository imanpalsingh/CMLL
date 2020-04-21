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
	* Last modified : April 19, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/

#pragma once


/*
	All th includes are to be aligned in the alphabetical order
*/
#include<vector>


/*
	Parent name space : All name spaces lie under this parent name space
*/

namespace cmll
{
	/*
		data name space :  name space that contains type definitions for data structures and data related operations
	*/

	namespace data
	{
		
		/*
			For cleaner code the vector of vectors of double is used as storage
		*/
		typedef std::vector<std::vector<double>> Storage;
	}
	/*
		matrix name space :  name space that contains enums for matrix related operations such as multiply, transpose inverse etc.
	*/
	namespace matrix
	{
		
		/*
			selection of matrices

			LHS :  For LHS matrix, usually the first parameter

			RHS : For RHS matrix, usually the second parameter
		*/
		enum class selection
		{
			LHS,
			RHS
		};
	}

	/*
		Name space for array related operations 
	*/
	namespace array
	{
		/*
			Selection of axis for performing operations
		*/
		enum class axis
		{
			HORIZONTAL,
			VERTICAL
		};
	}

	/*
		Name space for linear models
	*/
	namespace linear
	{
		/*
			enum for default integer values for linear model classes
		*/
		enum class defaults
		{
			LAMBDA = 2,
			MAXIMUM_ITERATIONS = 100
		};

		/*
			Name space for default double values for linear model classes
		*/
		namespace defaultsd
		{
			constexpr double TOLERANCE = 0.0001;
		}

		/*
			Enum type for classification type for binary classifiers
		*/
		enum class ClassificationType
		{
			BINARY,
			MULTI_CLASS
		};
	}

	/*
		Name space for Bayes classifiers
	*/
	namespace bayes
	{
		/*
			Enum for defaults for Bayes classifiers
		*/
		enum class defaults
		{
			ALPHA = 1
		};
	}

	/*
		Name space for neighbor classifier and regressors
	*/
	namespace neighbors
	{
		
		/*
			enum for allowed distance metrics
		*/
		enum class distanceMetric
		{
			EUCLEDIAN,
			MANHATTAN,
			MINKOWSKI
		};

		/*
			Enum for bool value
		*/
		enum class selection
		{
			YES,
			NO
		};

		
		/*
			enum for defaults
		*/
		enum class defaults
		{
			K = 2,
			P = 2
		};
	}
}