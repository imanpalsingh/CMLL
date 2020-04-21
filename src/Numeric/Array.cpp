
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

#include"Array.h"

/*
	Parent name space : All name spaces lie under this parent names pace
*/
namespace cmll
{

	/*
		array name space : Name space containing helpful functions for cmll::data::storage type operations
	*/
	namespace array
	{
		void add(data::Storage& X, const double value) noexcept
		{
			/*
				Function iterates through elements and adds the number and stores the new number
			*/
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					X[row][col] += value;
				}
			}
		}

		double average(const data::Storage& X) noexcept
		{
			
			/*
				Function iterates through the elements, adds the sum , counts the number of elements and return their ratio
			*/
			
			double sum = 0;
			data::Storage::size_type elementCount = 0;

			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					sum += X[row][col]; ++elementCount;
				}
			}

			return (sum / elementCount);
		}

		void columns(const data::Storage& X, const std::vector<data::Storage::size_type> columns, data::Storage& result) noexcept
		{
			
			/*
				Function iterates through elements picks up only elements that have second column index as specified in columns vector
				The result vector is supposed to be in correct shape.
			*/
		
			std::vector<double>::size_type columnIndex;
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				columnIndex = 0;
				for (data::Storage::size_type col : columns)
				{
					result[row][columnIndex++] = X[row][col];
				}
			}
		}

		bool contains(const data::Storage& X, const double value) noexcept
		{
			/*
				Function iterates over the multi dimensional vector and returns true if element is found else false
			*/
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					if (X[row][col] == value)
					{
						return true;
					}
				}
			}

			return false;
		}

		double maximum(const data::Storage& X) noexcept
		{
			/*
				Function iterates over all elements. Assumes first element to be the maximum and then updates if larger 
				numbers are found.
			*/
			
			
			double maximum = X[0][0];
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					if (X[row][col] > maximum)	maximum = X[row][col];
				}
			}

			return maximum;
		}

		void power(data::Storage& X, const double power) noexcept
		{
			/*
				Function iterates over each elements, finds the required power and stores the new number.
			*/
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					X[row][col] = std::pow(X[row][col], power);
				}
			}

		}

		void ravel(const data::Storage& X, std::vector<double>& result) noexcept
		{
			/*
				Function iterates over each element in X and adds it to result
			*/
			data::Storage::size_type resultCol = 0; 
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					result[resultCol++] = X[row][col];
				}
			}
		}

		void subtract(data::Storage& X, const double value) noexcept
		{
			/*
				Function iterates through elements and subtracts the number and stores the new number
			*/

			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					X[row][col] -= value;
				}
			}
		}

		double sum(const data::Storage& X) noexcept
		{
			/*
				Function finds sum of all elements in the vector by iterating through them
			*/
			
			double sumOfAllElements = 0;

			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				for (data::Storage::size_type col = 0; col < X[row].size(); ++col)
				{
					sumOfAllElements += X[row][col];
				}
			}

			return sumOfAllElements;
		}

		void sum(const data::Storage& X, std::vector<double>& result, const axis& where, const double& weight) noexcept
		{
			
			/*
				Based on the where parameter the elements are either added row wise or column wise
			*/
			double sum;
			
			if (where == axis::HORIZONTAL)
			{
				for (data::Storage::size_type row = 0; row < X.size(); ++row)
				{
					sum = 0;
					for (std::vector<double>::size_type col = 0; col < X[row].size(); ++col)
					{
						sum += X[row][col];
					}

					result[row] = sum + weight;
				}
			}

			else if (where == axis::VERTICAL)
			{
				for (std::vector<double>::size_type col = 0; col < X[0].size(); ++col)
				{
					sum = 0;
					for (data::Storage::size_type row = 0; row < X.size(); ++row)
					{
						sum += X[row][col];
					}

					result[col] = sum + weight;
				}

			}
		}

		data::Storage::size_type unique(const data::Storage& X) noexcept
		{
			/*
				Algorithm iterates over the elements in X, adds them to a set. The set contains only one instance of the value
				The size of the set is returned.
			*/
			
			std::set<double> unique;
			
			for (auto row : X)
			{
				for (auto col : row)
				{
					unique.insert(col);
				}
			}

			return unique.size();
		}

		void unravel(const std::vector<double>& X, data::Storage& result) noexcept
		{
			/*
				Each element in x is converted to a vector and then assigned into result
			*/
			
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				result[row] = { X[row] };
			}
		}
	}
}