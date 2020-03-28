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
 
* Last modified : MAR_26_20_19_42

* Change Logs : 

    1) Date : 26-03-20 Time : 19:41
       # Added a new namespace math
       # Added constexpr PI to math
    
    2) Date : 23-03-2020 Time : 17:00
        # All the helper functions now have been moved to utils.cpp
    
    3) Date: 22-03-2020 Time : 15:15
       # Removed unnecessary flags



*
*/


#ifndef DEFINED_HPP
#define DEFINED_HPP


/* Imports */
#include<vector>


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

    
}

// Namespace for Neighbor related models
namespace neighbor
{
    
    // Default number of neighbors
    const std::size_t DEFAULT_K = 4;

    // Default order (p)
    const double DEFAULT_P = 2;
    
    /* Flags defining the selection of the distance metric */
    const short EUCLIDEAN = 0;
    const short MANHATTAN = 1;
    const short MINKOWSKI = 2;

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

    // Value for default iterations (maximum)
    const int DEFAULT_MAXIMUM_ITERATIONS = 100;

    // Value for default tolerance
    const double DEFAULT_TOLERANCE = 0.0001;

    // default value for lambda (penalty)
    const double DEFAULT_LAMBDA = 1;


}
// Namespace for different math related constants
namespace math
{
    constexpr double PI  =3.141592653589793238463;
}

namespace array
{
    //Flag to represent selection of column for an array
    const bool COL = false; // or 1 ... inf

    // Flag to represent selection of row for an array
    const bool ROW  = true; // or 0
}


}
#endif