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

* File version : 0.0.1

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_8_20_21_12
 
* Last modified : MAR_28_20_22_21

* Change Logs : 

        1) Date : 28-03-20 Time : 22:21
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

// I/O stream
#include<iostream>

// Arrays
#include<array>

// Vectors 
#include<vector>

#include"../utils/defined.hpp"



namespace cmll
{
// Pre class declaration for recognition by the friend function
class Handler;



/* N A M E S P A C E S */

// File handling functions
namespace csv{
    Handler read(std::string filename,const char separator=',');
   

}


/* C L A S S E S */

/*
*

* Class Name : Handler

* Description : Handling the reading of dataset of various file formats, operations on the dataset etc.

* Functions : (friend)read(),columns(),rows(),get() OPerator overloading for( [], (),)

* Class version : 0.0.0
*/

class Handler
{

    private :
    
   
    /* Variables */

    // Variable to hold dataset values
    data::STORAGE  Dataset; 

   
    /* FUNCTIONS */

    /// Main Functionalities ///
    
    /*
    Function to read files (csv by default).
    File with the filename specified is opened for reading. Each row is parsed with theseparators defined.
    Binary files are not supported since they require different mechanism 

    Paramteres 
    filename - >  A valid filepath for the file to be read
   separator -> The valueseparator 

    For example in a csv file  [   1,2,3,4 ] = ',' is theseparator
    return type : Handler
    */
    friend Handler csv::read(std::string filename,const char separator);

    
   
   
    public:

    /*
    Function to insert a column in the Handler object.
    Parameters : position : Position at which to insert he column
                elements : elements of the column to insert
    return type: int
    */
    int insert(const std::size_t &position,const double &elements);
    /*
    Function to insert a value as a new column in the Handler object.
    Parameters : position : Position at which to insert he column
                element : value to be inserted in the entire new column
    return type: int
    */
    int insert(const std::size_t &position,const std::vector<double> &elements);
    

    /// Utilities ///

   /*
   Function to get number of columns currently in the Handler object (STORAGE element)
   Note : The number of columns does not change dynamically. It is only calculated when called
        : The dataset is assumed to satisfy continuity of number of element in row in the entire frame
    return type: int
   */
    int columns();

    /*
    Function to get number of rows currently in the Handler object (STORAGE element)
    Note : The number of rows does not change dynamically. It i only calculated when called
    return type: int
    */
    int rows();

    /* 
    Function to get total elements in the Handler object (STORAGE element)
    Note : size() assumes continuity of number of elements in every row (that is no missing values)
    return type: int
    */
    int size();


    /*
    Function to return the current instance of STORAGE element in the Handler object
    This doesn't effect the Handler object.
    Note :  This shall be the only method to retrieve the STORAGE element;
    return type: STORAGE
    */
    data::STORAGE get();
    
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
    Note : Negative indexing is ' NOT '  supported due to optimization reasons
    return type: Handler
    */
    Handler operator()(int,int);

    /* Functions to be implemented in version 1.0 of project */


    //Function to remove columns
    
    // Function to remove rows and columns
    /// data::STORAGE remove(std::vector<int> indexes);

    // Overloading [] operator with std::string parameter for interactive query processing
    /// Handler operator[](std::string)

    // Overloading () operator with std::string parameter for interactive query processing
    /// Handler operator()(std::string)

};

  
}


#endif