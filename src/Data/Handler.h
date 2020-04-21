

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

#include <algorithm>
#include <iostream>
#include <fstream>
#include<limits>
#include<sstream>
#include <string>


#include "../utils/Defines.h"

/*
	Parent name space
*/
namespace cmll
{
	/*
		Name space for data realted operations, functions and classes
	*/
	namespace data
	{
		// Forward declaration. See actual declaration for information
		class Handler;
		
	/**
			* Function Name :  read

			* Function Description :  Function to read from a file (non binary)

			* Parameters :

			1) obj :				Handler object that will contain the file read

									Type Expected : Handler

									Method of passing :  By reference

			2) filename  :			The name of the file to read

									Type Expected : std::string

									Method of passing :  const and by reference

			3) ColumnSeparator :	The  delimiter for values.

									Type Expected : char
									Method of passing : const by reference
			
			4) rowSeparator :		The  delimiter for rows.

									Type Expected : char
									Method of passing : const by reference

			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here

				cmll::data::Handler dataset;
				cmll::data::read(dataset,"Dataset.csv",'|',';')
			}


		*/
		void read(Handler& obj, const std::string& filename, const char& columnSeparator = ',', const char& rowSeparator = '\n');

		/**
			* Function Name :  Create

			* Function Description :  Function to create a new Handler object 

			* Parameters :

			1) obj :				Handler object that will contain the new values

									Type Expected : Handler

									Method of passing :  By reference

			2) dataset  :			The values that the new Handler object will have

									Type Expected : cmll::data::Storage

									Method of passing :  const and by reference

			3) ColumnNames :		The  Column names for each column of the new Handler obeject

									Type Expected : std::vector<std::string>

									Method of passing : const by reference


			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here

				cmll::data::Handler dataset;
				cmll::data::create(dataset,X,columns);
			}


		*/
		void create(Handler& obj, const Storage& dataset, const std::vector<std::string>& columnNames);


	/**
		* Class Name : Handler

		* Class Description : Class containing functions Data Handling , file Handling and Data Manipulation

		* Attributes :

		1) Dataset : The actual values of the object

		2) ErrorDie : Error directories for reporting location based errors

		3) Encoding : If the file read contained string values and not numeric then they will be label encoded and the encoding details are stored here

		4) Columns : The name of the Columns

		* Functions :

		1) create @friend

		2) read @freind

		3) columnCount

		4) operator << @freind

		5) encodingDetails

		6) getEncodingDetails

		7) insert

		8) memoryUsage

		9) operator[]

		10) operator()
		
		11) remove
		
		12) rowsCount

		13) show

		14) values

		*
		*/
		class Handler
		{
		protected:

			// Values
			data::Storage Dataset;
			std::string ErrorDir;

			/*
				Label Encoding details
				Each index stores details for the same column index 
			*/
			std::vector<std::vector<std::string>> Encoding;

			/*
				Friend functions :  refer to original declarations for function level comments
			*/
			friend void create(Handler& obj, const Storage& dataset, const std::vector<std::string>& columnNames);
			friend std::ostream& operator<<(std::ostream& out, const Handler& obj);
			friend void read(Handler& obj, const std::string& filename, const char& columnSeparator, const char& rowSeparator);
			
		public:


			std::vector<std::string> Columns;

		/**
		   * Constructor Name :  Handler[default]

		   * Constructor Description :  Default constructor, loads nothing

		   * Example

			   #include<Data/Handler.h>

			   int main()
			   {
				   cmll::data::Handler dataset;

				   return 0;

			   }


		   */
			Handler();

		/**
		   * Constructor Name : Handler[Parameterized]

		   * Constructor Description :  Constructor to create a new Handler object with new values and column names

		   * Parameters :

		   1) dataset :		The values that the object will have

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

		   2) columnNames :	The names of the individual columns

							Type Expected : std::vector<std::string>

							Method of passing :  constant and by reference


		   * Example

			   #include<vector>
			   #include<Data/Handler.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::data::Handler(X,columnNames);

				   return 0;

			   }


		   */
			Handler(const Storage& dataset, const std::vector<std::string> columnNames);

			/**
			* Function Name :  Clear

			* Function Description :  Function to clear the Hadler object. Which includes deallocating all memory that is taken by the object

			* Parameters :

			None

			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here

				cmll::data::Handler dataset;
				cmll::data::create(dataset,X,columns);
				dataset.clear();
			}


		*/
			void clear() noexcept;

		/**
			* Function Name :  Columns Count

			* Function Description :  Function to return number of Columns in The Hander object

			* Parameters :
				None


			* Return :	   cmll::data::Storage::size_typ - >  Number of Columns


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here

				cmll::data::Handler dataset;
				cmll::data::create(dataset,X,columns);

				std::cout<<dataset.columnsCount();
			}


		*/
			std::vector<double>::size_type columnsCount() const;

			/**
				* Function Name :  Encoding Details

				* Function Description :  Function to print information about on for what columns which values are encoded to what number

				* Parameters :
					None


				* Return :	  std::vector<double>::size_type - > Number of columns


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::create(dataset,X,columns);

					std::cout<<dataset.getEncodingDetails();
				}


		*/
			void encodingDetails() const;

			/**
				* Function Name :  Get Encoded Details

				* Function Description :  Function to return information about on for what columns which values are encoded to what number

				* Parameters :
				
				1) result	:	The vector to copy the details too

								Type Expected : std::vector<std::vector<std::string>>

								Method of passing : By reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::read(dataset,"dataset.csv");

					dataset.getEncodingDetails(details);
				}


			*/
			void getEncodingDetails(std::vector<std::vector<std::string>>& result) const;
			
			/**
				* Function Name :  insert

				* Function Description :  Function to insert a column with a same value in each row

				* Parameters :

				1) position	:	The position where to insert the new columns ( negative positions are allowed)

								Type Expected : long int

								Method of passing : const and by reference
				
				2) value	:	The value to insert in every row of the new column

								Type Expected : double

								Method of passing : const and by reference

				3) columnName:  The name of the new column (Should be distinct from already available columns)

								Type Expected : std::string

								Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::read(dataset,"dataset.csv");

					dataset.insert(0,12,"extra");
				}


			*/
			void insert(long int position, const double& value, const std::string columnName = "");

			/**
				* Function Name :  insert

				* Function Description :  Function to insert a column with a vector of values

				* Parameters :

				1) position	:	The position where to insert the new columns ( negative positions are allowed)

								Type Expected : long int

								Method of passing : const and by reference

				2) values	:	The values to inset (should be of same size as the other columns)

								Type Expected : double

								Method of passing : const and by reference

				3) columnName:  The name of the new column (Should be distinct from already available columns)

								Type Expected : std::string

								Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::read(dataset,"dataset.csv");

					dataset.insert(0,values,"ids");
				}


			*/
			void insert(long int position, const std::vector<double>& values, const std::string columnName = "");

			/**
				* Function Name :  Remove

				* Function Description :  Function to remove a columns with by indexes

				* Parameters :

				1) positions	:	The position where of columns to remove ( negative positions are allowed)

									Type Expected : long int

									Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::read(dataset,"dataset.csv");

					
					dataset.remove(indexes);
				}


			*/
			void remove(const std::vector<long int>& positions);
		

			/**
				* Function Name :  Memory Usage

				* Function Description :  Function to return the memory usage

				* Parameters :	 None

				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset;
					cmll::data::read(dataset,"dataset.csv");

					std::cout<<dataset.memoryUSage();
				}


			*/
			Storage::size_type memoryUsage() const;

			/**
				* Function Name :  operator ()

				* Function Description :  Function to retrieve rows and columns based on indexes

				* Parameters :

				1) Handler          :   Handler object to copy values too
										
										Type Expected : cmll::data::Handler

										Method of passing : By reference
				
				
				2) rowsIndexes		:	The row indexes to retrieve

										Type Expected : std::vector<long int>

										Method of passing : const and by reference

				3) columnIndexes	:	The column indexes to retrieve

										Type Expected : std::vector<long int>

										Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset,, sub;
					cmll::data::read(dataset,"dataset.csv");

					dataset(sub,{12,12},{13,12})
				}


			*/
			void operator()(Handler &obj,const std::vector<long int> rowsIndexes, const std::vector<long int> columnIndexes);
			

			/**
				* Function Name :  operator ()

				* Function Description :  Function to retrieve specific columns from object and copy to another

				* Parameters :


				1) Handler          :   Handler object to copy values too

										Type Expected : cmll::data::Handler

										Method of passing : By reference

				2) columnIndexes	:	The column indexes to retrieve

										Type Expected : std::vector<long int>

										Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset, sub;
					cmll::data::read(dataset,"dataset.csv");

					dataset.remove(sub,{3,4,5});
				}
			*/
			void operator()(Handler& obj, const std::vector<long int> columnIndexes);

			/**
				* Function Name :  operator ()

				* Function Description :  Function to retrieve specific columns based on column names from object and copy to anothers

				* Parameters :


				1) Handler          :   Handler object to copy values too

										Type Expected : cmll::data::Handler

										Method of passing : By reference

				2) columnNames:			The column names to retrieve

										Type Expected : std::vector<std::String>

										Method of passing : const and by reference


				* Return :	   None


				* Example

				#include<vector>
				#include<Data/Handler.h>

				int main()
				{
					//vector(y) stuff here

					cmll::data::Handler dataset, sub;
					cmll::data::read(dataset,"dataset.csv");

					dataset.remove(sub,{"id","age"}s);
				}
			*/
			void operator()(Handler& obj, const std::vector<std::string> columnNames);

			
		/**
			* Function Name :  Rows Count

			* Function Description :  Function to return number of Rows in The Hander object

			* Parameters :
				None


			* Return :	   cmll::data::Storage::size_type - >  Number of rows


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here

				cmll::data::Handler dataset;
				cmll::data::create(dataset,X,columns);

				std::cout<<dataset.rowsCount();
			}


		*/
			data::Storage::size_type rowsCount() const;
			
		/**
			* Function Name :  save

			* Function Description :  Function to write the contents of Handler object to a file (non binary)

			* Parameters :

			2) filename  :			The name of the file to save to

									Type Expected : std::string

									Method of passing :  const and by reference

			3) ColumnSeparator :	The  delimiter for values.

									Type Expected : char

									Method of passing : const by reference

			4) rowSeparator :		The  delimiter for rows.

									Type Expected : char

									Method of passing : const by reference

			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here
				cmll::data::write(dataset,"Dataset.csv",'|',';')
			}


		*/
			void save(const std::string& filename, const char& columnSeparator = ',', const char& rowSeparator = '\n');
			
		/**
			* Function Name :  save

			* Function Description :  Function to do pretty print of the object with the original values, not the label encoded ones

			* Parameters :

				None

			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here
				dataset.show();
			}


		*/
			void show() const;

		/**
			* Function Name :  values

			* Function Description :  Function to return the Dataset vector i.e the values of the Handler object as cmll::data::Storage

			* Parameters :

			1) dataset :	The values to copy to
							
							Type Expected : cmll::data::Storage

							Method of passing : By reference

			* Return :	   None


			* Example

			#include<vector>
			#include<Data/Handler.h>

			int main()
			{
				//vector(y) stuff here
				dataset.values(db);
			}


		*/
			void values(data::Storage& dataset);

			
		};
	}
}