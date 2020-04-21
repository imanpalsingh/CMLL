
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

#include"Utils.h"

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

			bool hasNaN(const data::Storage& X) noexcept
			{
				/*
					Function iterates over all elements and checks if any value is NaN
				*/
				
				for (std::vector<double> row : X)
				{
					for (double  value:row)
					{
						if (std::isnan(value)) return true;
					}
				}

				return false;
			}



			void Xy(const data::Storage& X, const data::Storage& y) // Throws std::invalid_length
			{

				const std::string ErrorDir = "<In function cmll::utils::check::Xy>";
				/*
					The checks performed are

					1) X.size() == y.size()
					2) X[0].size() == X[n].size() where n is  = 1 to X.size()-1
					3) y[0].size() == 1
					4) y[0].size() == y[n].size() where n is = 1 to y.size()-1
				*/

				try
				{
					/*
						Validating X
					*/
					data::Storage::size_type rows = X.size(), row;

					if (rows == 0) throw std::length_error("Error : Feature matrix X is empty.");

					std::vector<double>::size_type cols = X[0].size();

					if (cols == 0) throw std::length_error("Error : Feature matrix X is not in correct shape.");

					for (row = 0; row < rows; ++row)
					{
						if (X[row].size() != cols) throw std::length_error("Error : Feature matrix X is not a qualified matrix.");
					}

					/*
						Validating y
					*/
					rows = y.size();

					if (rows == 0) throw std::length_error("Error : Vector of prediction y is empty.");

					cols = y[0].size();

					if (cols == 0) throw std::length_error("Error : Vector of prediction y is not in correct shape.");

					for (row = 0; row < rows; ++row)
					{
						if (y[row].size() != cols)  throw std::length_error("Error :  Vector of prediction y is not a qualified matrix.");
					}

					/*
						Validating X.size() == y.size()
					*/
					if (rows != X.size())  throw std::length_error("Error :  X.size() != y.size() ");

				}
				catch (const std::length_error& e)
				{
					std::cerr << ErrorDir << e.what() << '\n';
					throw e;
				}
			}

			void XTest(const data::Storage& X, const data::Storage& XTest) // Throws std::invalid_length
			{
				
				const std::string ErrorDir = "<In function cmll::utils::check::XTest>";
				/*
					The checks performed in the function

					1) X[0].size() == XTest[0].size()
					2) XTest[0].size() == XTest[n].size() where n = 1 to XTest.size() - 1

					Note :  No test is performed on X, it is assumed to be already tested using cmll::utils::check::Xy();
				*/

				try
				{
					/*
						Validating XTest
					*/
					data::Storage::size_type rows = XTest.size(), row;

					if (rows == 0) throw std::length_error("Error : Feature matrix XTest is empty.");

					std::vector<double>::size_type cols = XTest[0].size();

					if (cols == 0) throw std::length_error("Error : Feature matrix XTest is not in correct shape.");

					for (row = 0; row < rows; ++row)
					{
						if (XTest[row].size() != cols) throw std::length_error("Error : Feature matrix X is not a qualified matrix.");
					}

					if (cols != X[0].size()) throw std::length_error("Error : Number of features are not equal in X and X test");

				}
				catch (const std::length_error& e)
				{
					std::cerr << ErrorDir << e.what() << '\n';
					throw e;
				}
			}

			void yTest(const data::Storage& y, const data::Storage& yTest) // Throws std::invalid_length
			{
				const std::string ErrorDir = "<In function cmll::utils::check::yTest>";

				/*
					The checks performed in the function

					1) y.size()  == yTest.size()
					2) y[0].size() == yTest[0].size
					3) y[0].size() == yTest[n].size()  for n = 1 to yTest.size()-1

					Note :  No test is performed on y, it is assumed to be already tested using cmll::utils::check::Xy();
				*/

				try
				{
					/*
						Validating XTest
					*/
					data::Storage::size_type rows = yTest.size(), row;

					if (rows == 0) throw std::length_error("Error : y_test is empty.");

					std::vector<double>::size_type cols = yTest[0].size();

					if (cols == 0 || cols > 1) throw std::length_error("Error : y_test is not in correct shape.");

					for (row = 0; row < rows; ++row)
					{
						if (cols == 0 || cols > 1) throw std::length_error("Error : y_test is not in correct shape.");
					}

					if (rows != y.size()) throw std::length_error("Error : Number of rows are not equal in y and  yTest");

				}
				catch (const std::length_error& e)
				{
					std::cerr << ErrorDir << e.what() << '\n';
					throw e;
				}
			}
		}
	}
}