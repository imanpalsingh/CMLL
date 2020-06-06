
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

#include "../../includes/utils/Preprocessing.h"

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
		void split(const data::Storage& X, data::Storage& XTrain, data::Storage& XTest, const double& splitRatio) noexcept
		{
			/*
				 Note :  The XTrain and XTest resizing in done in this function based on splitRatio. Thus it is not pre required.
			*/

			data::Storage::size_type originalSize = X.size();

			std::vector<double>::size_type columns = X[0].size();
			
			data::Storage::size_type newSize = static_cast<data::Storage::size_type>(originalSize * splitRatio);

			XTrain.resize(newSize, std::vector<double>(columns));
			XTest.resize(originalSize - newSize, std::vector<double>(columns));

			data::Storage::size_type innerRow = 0;

			for (data::Storage::size_type row = 0; row < originalSize; ++row)
			{
				if (row < newSize)
				{
					XTrain[row] = X[row];
				}

				else
				{
					
					XTest[innerRow++] = X[row];
				}
			}

		}

		void binarizer(const data::Storage& X, data::Storage& result, const double& negativeValues, const double& positiveValues) noexcept
		{
			/*
				Function converts the X into a binary output scenario.

				For example if X is [[0,1,2]] and negative values=-1 and positive values=1 then result is = [ [1,-1,-1], [-1,1,-1],[-1,-1,1] ]

				Note the result is resized in the function. pre-resizing is not required.
			*/
			
			result.resize(X.size(), std::vector<double>(array::unique(X),negativeValues));

			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < X[row].size(); ++col)
				{
					result[row][static_cast<data::Storage::size_type>(X[row][col])] = positiveValues;
				}
			}
		}

		void binaryFeatures(const data::Storage& X, data::Storage& result, const double& negativeValues, const double& positiveValues) noexcept
		{
			
			/*
				Function creates a binary Feature Matrix from original Feature Matrix. Helpful when using Bernoulli naive Bayes algorithm

				[[10,0,123],[0,123,123],[123,232,0]] is converted to [positioveValues,negativeValues,positiveValues] ,[negativeValues,positiveValues,positiveValues]
																	 [positiveValues,positiveValues,negativeValues]
			*/
			result.resize(X.size(), std::vector<double>(X[0].size()));

			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < X[row].size(); ++col)
				{
					result[row][row] = (X[row][col] == 0) ? negativeValues : positiveValues;
				}
			}
		}
	}
}