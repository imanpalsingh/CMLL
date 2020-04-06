/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : Data handler for handling dataset files in format like (csv,xlxs etc)

*   Description : This File includes the declarations of the class and class members, member funtions.
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.3

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_8_20_21_12
 
* Last modified : APR_06_20_14_33

* Change Logs : 

        
        1) Date : 06-04-2020 Time : 14:33
        Namespace data
        # Added new function read_all
        # Multi type file, categorical data now can be loaded using read_all which will automatically label encode non numeric data and assign Nan to missing values
        
        Handler class
        # Added new attribute Encoded to store the Label encoding
        # function clear now also clears the Encoded attribute

        2) Date : 05-04-2020 Time : 19:36
        Namespace data
        # function insert is now a member of data namespace and a friend of Handler class
        # Function read now accepts mandatory column names and stores them separately.
        # Function read can now prompt for missing values in the column names row
        # Function read now prompts for missing values by invalid structure of file. 
        
        Robust exceptional handling implemented

        Handler class
        # Extraction operator << is now overload for cout
        # Subscript operator [] now also accepts either column name(string) or vector of column name(vector<string>) as parameter
        
        3) Date : 04-04-2020 Time : 23:15
        #Handler and functions under file namespace are moved to a new common namespace data
        #Added a new function read_columns under the namspace data
        
        Handler class
            #Added new function create()
            #Added new function save()
            #Added new function memory_usage()
            #Negative indexing is now supported in all overloads
        

        4) Date : 28-03-20 Time : 22:21
        Handler class
            #Added new function insert ( 2 overloads)

*
*/


/*
*

* Header files : For Input Output on the standard streams, Vectors,Arrays.

*
*/


#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP


#include<algorithm>
#include<array>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<limits>
#include<stdexcept>
#include<stdio.h>
#include<string>
#include<vector>
#include<sstream>
#include<stdio.h>


#include"../utils/defined.hpp"
#include"../utils/util.hpp"




namespace cmll
{


namespace data
{   
    // Pre class declaration for recognition by the friend function
    class Handler;

    /*
    Function to read files (csv by default).
    File with the filename specified is opened for reading. Each row is parsed with theseparators defined.
    Binary files are not supported since they require different mechanism 

    Paramteres :  filename - >  A valid filepath for the file to be read
                line_separator -> The seperator which separates rows (default '\n')
                value_Separator - > Th eseparator which separates cols (default ',' - csv)

    For example in a csv file  [   1,2,3,4 ] = ',' is theseparator

    NOTE : Except for the Column names row all other rows should only contain , int,float or double types
    return type : Handler
    */
    Handler read(const std::string &filename,const char &line_separator='\n',const char &value_separator=',');

    /*
    Function to read files (csv by default).
    File with the filename specified is opened for reading. Each row is parsed with theseparators defined.
    Binary files are not supported since they require different mechanism 

    Paramteres :  filename - >  A valid filepath for the file to be read
                line_separator -> The seperator which separates rows (default '\n')
                value_Separator - > Th eseparator which separates cols (default ',' - csv)

    For example in a csv file  [   1,2,3,4 ] = ',' is theseparator
    Note :  This function can handle different datatypes. Except for the First row (column names) all other rows are automatically labelled encoded from 0 to unique values;

    return type : Handler
    */
    Handler read_all(const std::string &filename,const char &line_separator='\n',const char &value_separator=',');

    /*
    Function to read columns (csv by default).
    This function is automatically called after reading the first line of the file read by file::read()

    Paramteres : obj -> The handler object to write into
                column_line : THe first line read by file::read()
                line_separator -> The seperator which separates rows (default '\n')
                value_Separator - > Th eseparator which separates cols (default ',' - csv)
    return type : std::size_t
    */
    std::size_t read_columns(Handler &obj,const std::string &column_line,const char &line_separator='\n',const char &value_separator=',');


    /*
    Function to create a new Handler object with STORAGE element and column names
    Parameters :  dataset : The values to store
                column_names : The column names 
    return type: void
    */
    Handler create(const STORAGE &dataset,const std::vector<std::string> &column_names);

    /* C L A S S E S */

    /*
    *

    * Class Name : Handler

    * Description : Handling the reading of dataset of various file formats, operations on the dataset etc.

    * Functions : (friend)read,(friend)read_columns(),insert(),create(),save(),memory_usage(),columns(),rows(),get() OPerator overloading for( [], (),<<),

    * Class version : 0.0.0
    */

    class Handler
    {

        protected :

        // Variable to hold dataset values
        STORAGE  Dataset; 

        // Variable to hold the Error directories
        std::string ERROR_DIR;

        // vector to store label encoded strings
        std::vector<std::vector<std::string>> Encoded;



        /* FUNCTIONS */

        /// Main Functionalities ///
        
        /*
        Function to read files (csv by default).
        File with the filename specified is opened for reading. Each row is parsed with theseparators defined.
        Binary files are not supported since they require different mechanism 

        Paramteres :  filename - >  A valid filepath for the file to be read
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)

        For example in a csv file  [   1,2,3,4 ] = ',' is theseparator

        NOTE : Except for the Column names row all other rows should only contain , int,float or double types
        return type : Handler
        */
        friend Handler read(const std::string &filename,const char &line_separator,const char &value_separator);

        
        /*
        Function to read columns (csv by default).
        This function is automatically called after reading the first line of the file read by file::read()

        Paramteres : obj -> The handler object to write into
                    column_line : THe first line read by file::read()
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)
        return type : std::size_t
        */
        friend std::size_t read_columns(Handler &obj,const std::string &column_line,const char &line_separator,const char &value_separator);

        /*
        Function to read files (csv by default).
        File with the filename specified is opened for reading. Each row is parsed with theseparators defined.
        Binary files are not supported since they require different mechanism 

        Paramteres :  filename - >  A valid filepath for the file to be read
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)

        For example in a csv file  [   1,2,3,4 ] = ',' is theseparator
        Note :  This function can handle different datatypes. Except for the First row (column names) all other rows are automatically labelled encoded from 0 to unique values;

        return type : Handler
        */
        friend Handler read_all(const std::string &filename,const char &line_separator,const char &value_separator);


        /* Overloading the extraction operator */
        friend std::ostream& operator<<(std::ostream& out,const Handler &obj);

    
    
        public:

        // Variable to store column names
        std::vector<std::string> Columns;

        
        /* Constructor to load defaults */
        Handler();
        Handler(const STORAGE &dataset, const std::vector<std::string> &column_names);

        /*
        Function to insert a column in the Handler object.
        Parameters : position : Position at which to insert he column
                    elements : elements of the column to insert
                    column_name : Name of the new column (default = "" the position will be set as the column name)
        return type: None
        */
        void insert(std::size_t position,const double &elements, const std::string &column_name = "");
        /*
        Function to insert a value as a new column in the Handler object.
        Parameters : position : Position at which to insert he column
                    element : value to be inserted in the entire new column
                    column_name : Name of the new column (default = "" the position will be set as the column name)
        return type: None
        */
        void insert(std::size_t position,const std::vector<double> &elements,const std::string &column_name = "");
        
        /*
        Function to create a new Handler object with STORAGE element and column names
        Parameters :  dataset : The values to store
                    column_names : The column names 
        return type: void
        */
        friend Handler create(const STORAGE &dataset,const std::vector<std::string> &column_names);

        /*
        Function to save the Handler object to a file
        Parameters  filename - >  A valid filepath for the file to be written
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)
        return type: void
        */
        void save(const std::string &filename,const char &line_separator='\n',const char &value_separator=',');

        
        /*
        Function to clear the entire Handler object. Removing the dynamic memory allocated
        Parameters : None
        return type: void
        */
        void clear();

        
        
        /// Utilities ///

        /*
        Function to do a pretty print of the Handler object along with additional information such as label encoded values 
        Parameters : None
        return type: None
        */
        void show();

        /*
        Function to show what labels are assigned to what strings
        Parameters : None
        return type: None
        */
        void encoded_details();

        /*
        Function to return the vector containing the encoding details
        Parameters : None
        return type: std::vector<std::vector<std::string>>
        */
        std::vector<std::vector<std::string>> get_encoded_details() const;

        /*
        Function to get number of columns currently in the Handler object (STORAGE element)
        Note : The number of columns does not change dynamically. It is only calculated when called
            : The dataset is assumed to satisfy continuity of number of element in row in the entire frame
        return type: int
        */
        int columns() const;

        /*
        Function to get number of rows currently in the Handler object (STORAGE element)
        Note : The number of rows does not change dynamically. It i only calculated when called
        return type: int
        */
        int rows() const;

        /* 
        Function to get total elements in the Handler object (STORAGE element)
        Note : size() assumes continuity of number of elements in every row (that is no missing values)
        return type: int
        */
        int size()const;

        /* 
        Function to calculate total memory being used by the Handler object in Bytes
        Note : function assumes continuity of number of elements in every row (that is no missing values)
        return type: int
        */
        int memory_usage() const;

        /*
        Function to return the current instance of STORAGE element in the Handler object
        This doesn't effect the Handler object.
        Note :  This shall be the only method to retrieve the STORAGE element;
        return type: STORAGE
        */
        STORAGE get()const;
        
        /// Operator Overloads ///

    
        /*
        Overloaded subscript '[]' operator for fetching of particular columns from the original Handler object
        Parameter indexes - >  indexes of columns to return.
        Note : Negative indexing is also supported since version 0.0.0 

        For example HANDLER_OBJECT[{-1,-2}] will return Handler object with last and second last column
        return type: Handler
        */
        Handler operator[](std::vector<int> indexes);

        /*
        Overloaded subscript '[]' operator for fetching of particular column from the original Handler object
        Parameter indexes - >  indexes of column to return.
        Note : Negative indexing is also supported since version 0.0.0 

        For example HANDLER_OBJECT[-1] will return Handler object with last column
        return type: Handler
        */
        Handler operator[](int index);

        /*
        Overloaded call operator '[]'  for fetching of column based on column name
        Parameters string : name of the column
        return type: Handler
        */
        Handler operator[](const std::string);

        /*
        Overloaded call operator '[]'  for fetching of columns based on columns name
        Parameters vector<string> : name of the columns
        return type: Handler
        */
        Handler operator[](const std::vector<std::string>);


        /*
        Overloaded call operator '()'  for fetching of rows and columns defined in the indexes
        Parameters 1st - > rows index to fetch
                2nd - > cols index to fetch;
        Note : Negative indexing is supported since version 0.0.0
        return type: Handler
        */

        Handler operator()(std::vector<int>,std::vector<int>);

        
        /*
        Overloaded call operator '()'  for fetching of row and column defined in the indexes
        Parameters 1st - > row index to fetch
                2nd - > col index to fetch;
        Note : Negative indexing is supported
        return type: Handler
        */
        Handler operator()(int,int);

        /*
        Overloaded assignment operator for copying of values
        Parameters : The object to copy
        return : COpy of the parameter
        */
        //Handler &operator=(const Handler&);

        
        /* Functions to be implemented in version 1.0 of project */


        //Function to remove columns
        
        // Function to remove rows and columns
        /// STORAGE remove(std::vector<int> indexes);

        // Overloading () operator with std::string parameter for interactive query processing
        /// Handler operator()(std::string)

    };
}
  
}


#endif