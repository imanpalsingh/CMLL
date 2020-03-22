/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for extra helpful functions

*   Description : This File includes the typedefs, extra helpful functions
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_28
 
* Last modified : MAR_22_20_16_28

* Change Logs : 

* 1) Date: 22-03-2020 Time : 15:15
       
       # Removed unnecessary flags



*
*/


#ifndef DEFINED_HPP
#define DEFINED_HPP


/* Imports */
#include<vector>
#include<tuple>

/* N A M E S P A C E S */


namespace cmll
{


// Namespace for data and dataset related functions and typedefs
namespace data
{
    /*
    typedef for std::vector<std::vector<double> >
    This is recommended replacement for using CML 
    */
    typedef std::vector<std::vector<double> > STORAGE;

    /*
    Function to return columns having the required value
    Parameters : dataset - >  dataset to look into
                 cols -> columns to look into
                 val - >  value to look for
    
    return type : STORAGE
    */

    STORAGE where(const STORAGE &dataset,const std::vector<int> &cols, const double &val);

    /*
    Function to return indexes of columns having the required value
    Parameters : dataset - >  dataset to look into
                 cols -> columns to look into
                 val - >  value to look for
    return type : std::vector<int>
    */
    std::vector<int> where_index(const STORAGE &data,const std::vector<int> &cols,const double &val);
    
    /*
    Function to return rows defined by index
    Parameters : dataset - >  dataset to look into
                 rows - > indexes of rows to fetch
    return type : STORAGE
    */
    STORAGE fetch_row(const STORAGE &dataset,const std::vector<int> &rows);

    /*
    Function to return two subsets (partition) of STORAGE based on a percentage defined
    Parameters : X - >  dataset to perform split on
                 perc - > percentage of rows first subset gets
    return type std::tuple<STORAGE,STORAGE>
    */
    std::tuple<STORAGE,STORAGE> split(const STORAGE &X,const double &perc = 0.7);
}

// Namespace for different flags of Linear Models
namespace linear
{
    
    /* LOGISTIC REGRESSION */

    // Flag to reperesent selection of SIGMOID function
    const short SIGMOID=2;

    // Flag to represent selection of FAST SIGMOID function
    const short FAST_SIGMOID=3;
    
    // Flag to represent selection of SOFTMAX function
    const short SOFTPLUS=4;

    // Flag to represent selection of SIGMOID_ALPHA function
   const short SIGMOID_ALPHA = 8;
    
    // Flag to represent selection of NAMI_MAX function
    const short NAMI_MAX = 9;

    // Value to define default the threshold value
    const double DEFAULT_THRESHOLD = 0.5;

    // Value for default alpha
    const double DEFAULT_ALPHA  = 0.01;

    // Value for defualt iterations (maximum)
    const int DEFAULT_MAXIMUM_ITERATIONS = 100;

    // Value for default tolerance
    const double DEFAULT_TOLERANCE = 0.0001;


}

namespace array
{
    //Flag to represent selection of column for an array
    const bool COL = false; // or 1 ... inf

    // Flag to represent selection of row for an array
    const bool ROW  = true; // or 0
}

namespace out
{
    
    /*
    Function to perform a pretty print of a STORAGE element along with number of rows and columns
    Parameters :  data - >  STORAGE element to print
    return type : void
    */
    void print(const data::STORAGE &data);

}
}
#endif