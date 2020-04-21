

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

#include "Handler.h"


/*
	Parent name space
*/
namespace cmll
{
	/*
		Name space for data related operations, functions and classes
	*/
	namespace data
	{

		void read(Handler& obj, const std::string& filename, const char& columnSeparator, const char& rowSeparator)
		{
			/*
				This function can handle files with multitype data such as combination of string and numbers. The process is as follows


				Read first row for column names. The number of columns in first row decide the format of the rest of the file.

				1) Read each line as a string till the row separator
				2) Read each column in a line separated by the column separator
				3) If for each column the value can be converted to a number. Convert it and store it
				   If the column value cannot be converted to a number. Label Encode it and store the encode number a the position
				4) If a entire line is empty skip it
				5) If a value is missing between column delimiter for example 3,,4 or 3,4,, insert NaN at the place i.e 3,nan,4 and 3,4,nan
				6) If after every line read the number of columns is not same as the first column that contained column names throw error and erase everything read
			*/


			obj.ErrorDir = "<In function cmll::data::read()>";
			std::ifstream reader(filename);

			try
			{
				if (!reader)
				{
					throw std::runtime_error("Error : File cannot be opened. Either it doesn't exist or required permissions are not granted.");
				}

				/*
					Extracting the columns. This also determines the number of columns that are required in all future rows
				*/
				std::string firstRow, column;

				std::getline(reader, firstRow, rowSeparator);

				std::istringstream columnLine(firstRow);

				while (std::getline(columnLine, column, columnSeparator))
				{
					if (column == "")
					{
						throw std::runtime_error("Error : Column name cannot be missing. File reading discarded");
					}

					obj.Columns.emplace_back(column);
				}

				/*
					Reading rest of the file. Expecting same number of columns
				*/

				const std::vector<std::string>::size_type requiredColumns = obj.Columns.size();
				std::string row, value;
				std::size_t columnCount = 0;
				std::size_t rowCount = 1;
				double stringToNumber;
				std::vector<double> datasetRow(requiredColumns);
				std::vector<std::string>::iterator location;
				obj.Encoding.resize(requiredColumns);


				while (std::getline(reader, row, rowSeparator))
				{
					columnCount = 0;
					std::istringstream columnLine(row);

					while (std::getline(columnLine, value, columnSeparator))
					{
						/*
							If the number of columns already reached the maximum there should be, raise error
						*/
						if (columnCount == requiredColumns)
						{
							std::cerr << "Error (row : " << rowCount << " ): Column Expected were " << requiredColumns;
							throw std::runtime_error(" received more than expected");
						}


						if (value == "")
						{
							datasetRow[columnCount] = std::numeric_limits<double>::quiet_NaN();
						}

						else
						{
							/*
								Convert to number , if unsucessful label encode and store the encoded number
							*/
							try
							{
								stringToNumber = std::stod(value);

								datasetRow[columnCount] = stringToNumber;
							}
							catch (const std::invalid_argument& e)
							{
								const auto what = e.what();
								location = std::find(obj.Encoding[columnCount].begin(), obj.Encoding[columnCount].end(), value);

								if (location == obj.Encoding[columnCount].end())
								{
									obj.Encoding[columnCount].emplace_back(value);
									datasetRow[columnCount] = static_cast<double>(obj.Encoding[columnCount].size() - 1);
								}

								else
								{
									datasetRow[columnCount] = static_cast<double>(std::distance(obj.Encoding[columnCount].begin(), location));
								}
							}
						}

						++columnCount;

					}

					/*
						Skip lines that are empty
					*/
					if (columnCount == 0)
					{
						continue;
					}


					if (columnCount < requiredColumns)
					{
						std::cerr << "Error (row : " << rowCount << " ): Column Expected were " << requiredColumns;
						throw std::runtime_error(" received less than expected");
					}

					++rowCount;
					obj.Dataset.emplace_back(datasetRow);
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << obj.ErrorDir << e.what() << '\n';
				obj.clear();
			}
			reader.close();
		}

		void create(Handler& obj, const Storage& dataset, const std::vector<std::string>& columnNames)
		{
			/*
				Function fills new Handler object with values with error checking. Alternatively, Handler's constructor can be used to load values
				and column names but error checking is not supported there
			*/

			obj.ErrorDir = "<In function cmll::data::read()>";

			try
			{
				if (dataset[0].size() != columnNames.size()) throw std::length_error("Number of columns and number of column names do not match.");

				obj.Dataset = dataset;
				obj.Columns = columnNames;
				obj.Encoding.resize(columnNames.size());
			}

			catch (const std::exception& e)
			{
				std::cerr << obj.ErrorDir << e.what() << '\n';
			}

		}

		/*
			Handler class member functions
		*/
		Handler::Handler()
		{

		}

		Handler::Handler(const Storage& dataset, const std::vector<std::string> columnNames)
		{
			/*
				Constructor is useful when creating new Handler object. Alternatively cmll::data::create() can be used
			*/
			Dataset = dataset;
			Columns = columnNames;
			Encoding.resize(columnNames.size());
		}

		void Handler::clear() noexcept
		{
			/*
				Function deallocates entire memory allocated to the object's Attributes

				Note : ErrorDir is not cleared for debugging reasons
			*/

			Dataset.clear();
			Dataset.shrink_to_fit();

			Columns.clear();
			Columns.shrink_to_fit();

			Encoding.clear();
			Encoding.shrink_to_fit();
		}

		std::vector<double>::size_type Handler::columnsCount() const
		{
			/*
				Return number of columns in the Handler object
			*/
			if (Dataset.size() == 0) return 0;

			else return Dataset[0].size();
		}

		void Handler::encodingDetails() const
		{
			/*
				Function displays encoding if done.
			*/

			for (Storage::size_type col = 0; col < Encoding.size(); ++col)
			{
				/*
					If encoding was done for the column
				*/
				if (Encoding[col].size())
				{
					std::cout << "Label Encoding of column '" << Columns[col] << "'.\n";

					for (std::vector<double>::size_type value = 0; value < Encoding[col].size(); ++value)
					{
						std::cout << Encoding[col][value] << " : " << value;

						if (value < Encoding[col].size() - 1) std::cout << ", ";
					}
					std::cout << "\n\n";
				}
			}
		}

		void Handler::getEncodingDetails(std::vector<std::vector<std::string>>& result) const
		{
			/*
				Function copies the Encoding details to a external variable
			*/
			result = Encoding;
		}

		void Handler::insert(long int position, const double& value, const std::string columnName)
		{
			/*
				Function to insert a new column at spoecified position containing same specified value in all rows
			*/

			ErrorDir = "<In function cmll::Handler::insert>";
			std::size_t maxIndex = Dataset[0].size();

			try
			{
				
				// If negative indexing is done , convert to normal indexing
				if (position < 0) position = static_cast<long int>(maxIndex + position);

				if (position >= maxIndex)
				{

					std::cout << "Expected index less than " << maxIndex << ". Got " << position << ".";
					throw std::length_error("Error : Position index is out of range");
				}

				for (data::Storage::size_type row = 0; row < Dataset.size(); row++)
				{
					Dataset[row].insert(Dataset[row].begin() + position, value);
				}

				if (columnName == "")
				{
					Columns.insert(Columns.begin() + position, std::to_string(position));
				}

				else
				{
					Columns.insert(Columns.begin() + position, columnName);
				}

				//Adding the no encoded flag
				Encoding.insert(Encoding.begin() + position, { {} });

			}

			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}
		}

		void Handler::insert(long int position, const std::vector<double>& values, const std::string columnName)
		{
			/*
				Function to insert a new column at specified position containing same specified values in rows
			*/
			ErrorDir = "<In function cmll::Handler::insert>";
			
			std::size_t maxIndex = Dataset[0].size();
			try
			{
				
				if (values.size() != Dataset.size()) throw std::length_error("Error : Number of rows are not equal.");

				//If negative indexing is done , convert to normal indexing
				if (position < 0) position = static_cast<long int>(maxIndex + position);

				if (position >= maxIndex)
				{
					std::cout << "Expected index less than " << maxIndex << ". Got " << position << ".";
					throw std::length_error("Error : Position index is out of range");
				}

				for (data::Storage::size_type row = 0; row < Dataset.size(); row++)
				{
					Dataset[row].insert(Dataset[row].begin() + position, values[row]);
				}

				if (columnName == "")
				{
					Columns.insert(Columns.begin() + position, std::to_string(position));
				}

				else
				{
					Columns.insert(Columns.begin() + position, columnName);
				}

				//Adding the no encoded flag
				Encoding.insert(Encoding.begin() + position, { {} });
			}

			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}
		}

		Storage::size_type Handler::memoryUsage() const
		{
			/*
				Discarding the space taken by Columns vector, Error Dir and Encoded vector
				Each value is a double takes sizeof(double) bytes
				So a N*N handler object will take size_of(double)*n*n bytes
			*/
			return sizeof(double) * (rowsCount() * columnsCount());
		}

		void Handler::remove(const std::vector<long int>& positions)
		{
			/*
				Function to remove specified columns by index from the Handler object
			*/
			ErrorDir = "<In function cmll::Handler::remove>";
			try
			{
				for (long int pos : positions)
				{
					std::size_t maxIndex = Dataset[0].size();
					// If negative indexing is done , convert to normal indexing
					if (pos < 0) pos = static_cast<long int>(maxIndex + pos);

					if (pos >= maxIndex)
					{
						std::cout << "Expected index less than " << maxIndex << ". Got " << pos << ".";
						throw std::length_error("Error : Position index is out of range");
					}

					for (data::Storage::size_type row = 0; row < Dataset.size(); row++)
					{
						Dataset[row].erase(Dataset[row].begin() + pos);

					}

					Columns.erase(Columns.begin() + pos);

					// If encoding was done for the column, delete the information
					if (Encoding[pos].size())
					{
						Encoding[pos].clear();
						Encoding[pos].shrink_to_fit();
					}

				}
			}
			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}
		}


		std::ostream& operator<<(std::ostream& os, const Handler& obj)
		{

			if (obj.rowsCount() == 0) return os;

			// Displaying column names first
			for (auto col : obj.Columns) os << col << " ";
			os << '\n';

			// Displaying the dataset
			for (auto row : obj.Dataset)
			{
				for (auto col : row)
				{
					os << col << " ";
				}

				os << "\n";
			}

			return os;
		}

		void Handler::operator()(Handler& obj, const std::vector<long int> rowsIndexes, const std::vector<long int> columnIndexes)
		{
			/*
				The rows and column indexes given in rowsIndexes and columnIndexes are used to copy the value at those indexes into obj
			*/

			obj.Encoding.resize(columnIndexes.size());
			obj.Dataset.resize(rowsIndexes.size(), std::vector<double>(columnIndexes.size()));
			obj.Columns.resize(columnIndexes.size());

			ErrorDir = "<In function operator()>";

			// Variable to keep count of column of new object
			std::size_t countColumn, countRows = 0;
			bool isFirstRow = true;

			std::size_t numRows = rowsCount();
			std::size_t numCols = columnsCount();

			try
			{
				for (auto row : rowsIndexes)
				{
					if (row < 0)
					{
						row = static_cast<long int>(numRows + row);
					}

					if (row > numRows - 1)
					{
						std::cout << "Received '" << row << "' but expected less than '" << numRows << "'.\n";
						throw std::range_error("Error : Handler row index out of range.");

					}

					countColumn = 0;
					for (auto col : columnIndexes)
					{
						if (col < 0)
						{

							col = static_cast<long int>(numCols + col);
						}

						if (col > numCols - 1)
						{
							std::cout << "Received '" << col << "' but expected less than '" << numCols << "'.\n";
							throw std::range_error("Error : Handler column index out of range\n");
						}

						if (isFirstRow)
						{
							obj.Columns[countColumn] = Columns[col];
							if (Encoding[col].size())
							{
								obj.Encoding[countColumn] = Encoding[col];
							}

						}
						obj.Dataset[countRows][countColumn] = Dataset[row][col];
						
						++countColumn;
					}

					isFirstRow = false;
					++countRows;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}


		}

		void Handler::operator()(Handler& obj, const std::vector<long int> columnIndexes)
		{
			/*
				Copies all rows and given columns in columnIndexes into obj Handler
			*/
		
			// Variable to keep count of column of new object
			std::size_t countColumn=0;

			std::size_t numRows = rowsCount();
			std::size_t numCols = columnsCount();
			std::size_t newcols = columnIndexes.size();

			obj.Columns.resize(newcols);
			obj.Dataset.resize(Dataset.size(), std::vector<double>(newcols));
			obj.Encoding.resize(newcols);

			try
			{
				for (auto col : columnIndexes)
				{
					if (col < 0)
					{

						col = static_cast<long int>(numCols + col);
					}

					if (col > numCols - 1)
					{
						std::cout << "Received '" << col << "' but expected less than '" << numCols << "'.\n";
						throw std::range_error("Error : Handler column index out of range\n");
					}

					obj.Columns[countColumn] = Columns[col];
					if (Encoding[col].size())
					{
						obj.Encoding[countColumn] = Encoding[col];
					}

					for (data::Storage::size_type row = 0; row < numRows; ++row)
					{
						obj.Dataset[row][countColumn] = Dataset[row][col];
					}

					++countColumn;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}

		}

		void Handler::operator()(Handler& obj, const std::vector<std::string> columnNames)
		{
			/*
				Copies all rows and given columns in columnNames into obj Handler
			*/

	
			std::size_t numRows = rowsCount();
			std::size_t numCols = columnsCount();
			std::size_t newCols = columnNames.size();

			obj.Columns.resize(newCols);
			obj.Dataset.resize(Dataset.size(), std::vector<double>(newCols));
			obj.Encoding.resize(newCols);

			// Variable to keep count of column of new object
			std::size_t countColumn = 0;
			ErrorDir = "<In function Handler::operator()>";

			// Iterator to store location of column name in Columns vector
			std::vector<std::string>::iterator name;

			// variable to store the index of the column in columns vector
			std::ptrdiff_t index;

			// vector to store each column's index from the original Column vector
			std::vector<std::size_t> columnByIndex(newCols);

			try
			{
				for (std::string col : columnNames)
				{
					//finding out the column by index first
					name = std::find(Columns.begin(), Columns.end(), col);

					//if the column was not found in COlumns
					if (name == Columns.end())
					{
						throw std::invalid_argument("Error : Column name '" + col + "' was not found.");
					}

					// Else store the original index of the column
					else
					{
						index = std::distance(Columns.begin(), name);
						columnByIndex[countColumn] = index;
					}

					++countColumn;
				}

				countColumn = 0;
				for (std::size_t col : columnByIndex)
				{
					
					obj.Columns[countColumn] = Columns[col];
					if (Encoding[col].size())
					{
						obj.Encoding[countColumn] = Encoding[col];
					}
					for (std::size_t row = 0; row < numRows; ++row)
					{
						obj.Dataset[row][countColumn] = Dataset[row][col];
					}

					++countColumn;
				} 
				
			}
			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << '\n';
			}
		}

		Storage::size_type Handler::rowsCount() const
		{
			/*
				Return number of rows in the Handler object (column row excluded)
			*/
			return Dataset.size();
		}

		void Handler::save(const std::string& filename, const char& columnSeparator, const char& rowSeparator)
		{

			ErrorDir = "<in function Handler::create>";

			// Creating the file to be saved
			std::ofstream create_file(filename);

			try
			{
				if (!create_file)
				{
					throw std::exception("Error: couldn't create file.");
				}

				std::size_t numCols = Columns.size();

				//Writing column names first
				for (std::size_t col = 0; col < numCols; ++col)
				{
					create_file << Columns[col];
					if (col != numCols - 1)create_file << columnSeparator;
				}
				create_file << rowSeparator;


				// Saving each value in the format
				for (std::size_t i = 0; i < Dataset.size(); i++)
				{
					for (std::size_t j = 0; j < Dataset[i].size(); j++)
					{
						create_file << Dataset[i][j];
						if (j != Dataset[i].size() - 1) create_file << columnSeparator;
					}
					create_file << rowSeparator;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << ErrorDir << e.what() << "\n";
			}

			create_file.close();
		}

		void Handler::show() const
		{
			/*
				Function is different from overloaded extraction operator for cout. This function displaces the original values
				That were label encoded and also some additional information
			*/

			// Printing the columns first   
			std::size_t numRows = rowsCount();
			std::size_t numCols = columnsCount();

			for (std::vector<std::string>::size_type col = 0; col < numCols; ++col)
			{
				std::cout << Columns[col] << ' ';

			}
			std::cout << '\n';

			for (data::Storage::size_type row = 0; row < numRows; ++row)
			{
				for (std::vector<double>::size_type col = 0; col < numCols; ++col)
				{
					// If the column was label encoded
					if (Encoding[col].size())
					{
						// Display the original string value
						std::cout << Encoding[col][static_cast<std::vector<double>::size_type>(Dataset[row][col])] << ' ';
					}

					//If was not label encoded
					else
					{
						// Display the numerical value
						std::cout << Dataset[row][col] << ' ';
					}

				}
				std::cout << '\n';
			}

			std::cout << "\nAdditional Information : \n\n";
			encodingDetails();

			std::cout << "\nNumber of row : " << numRows << '\n';
			std::cout << "Number of columns : " << numCols << '\n';
			std::cout << "Number of elements : " << numRows * numCols << '\n';
			std::cout << "Memory usage : " << memoryUsage() << " bytes\n";
		}

		void Handler::values(data::Storage& dataset)
		{
			/*
				Function copies the Dataset vector (values) into dataset
			*/

			dataset = Dataset;
		}
	}

}