/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declaration for numeric computations

*   Description : This file declarations contains all the functions required for performing algorithms
                  such as matrix multiplication,matrix transpose, addition, Inverse etc, mathematical functions and more
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_50
 
* Last modified : MAR_20_20_23_17

* Change Logs : 
Added a new function : inverse_diagonal()

*
*/

/*
*

* Header files : For Input Output on the standard streams, vectors 
*
*/



#ifndef NUMERIC_HPP
#define NIMERIC_HPP

#include<iostream>
#include<vector>
#include<tuple>
#include<cmath>
#include"../utils/defined.hpp"


/* N A M E S P A C E S */


namespace cmll
{

// Namespace for list operations (Temporary, for more information read function header in Numeric.cpp)

namespace list
{
    /* Function for generating a std::vector<int> contianing range of numbers
       This function is a replica of python's range(). Expect this function to be deprecated in version 0.0.0
    */
    std::vector<int> range(int start,int end,int step=1);
}



// Namespace for Activation functions
namespace functions
{
    /* 
    Function to pass a value to sigmoid function
    parameter : x - >  value to pass through
    return type : double
    */
    double sigmoid(double x);

    /* 
    Function to pass a value to fast sigmoid function
    parameter : x - >  value to pass through
    return type : double
    */
    double fast_sigmoid(double x);

    /* 
    Function to pass a value to sigmoid function containing alpha
    parameter : x - >  value to pass through, value of alpha in the formula
    return type : double
    */
    double sigmoid_alpha(double x, double alpha);

     /* 
    Function to pass a value to softplus function
    parameter : x - >  value to pass through
    return type : double
    */
    double softplus(double x);

     /* 
    Function to pass a value to nami_max function
    Note : this function is experimental
    parameter : x - >  value to pass through
    return type : double
    */
    double nami_max(double x);


    data::STORAGE gradientJ(const data::STORAGE &X, const data::STORAGE &y, const short &activation);

    data::STORAGE hessian_matrix(const data::STORAGE &X,const short &activation);

}

// Namespace for Matrix operations
namespace matrix
{
    
    //Multiplying two matrices

    /*
    Function to multiply two matrices
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
                 m2 - > matrix (STORAGE assumed as matrix)
    Note :  This function may undergo a lot of algorithm type changes 
            This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : STORAGE
    */
    data::STORAGE multiply(const data::STORAGE &m1, const data::STORAGE &m2);

    /*
    Function to multiply matrix and a scalar
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
                 scalar - > number to multiply matrix with
    Note : This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : STORAGE
    */
    data::STORAGE multiply(data::STORAGE m1, int scalar);

    /*
    Function to Add two matrices
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
                 m2 - > matrix (STORAGE assumed as matrix)
    Note : This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : STORAGE
    */
    data::STORAGE sum(data::STORAGE m1, data::STORAGE m2);

    /*
    Function to Subtract two matrices
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
                 m2 - > matrix (STORAGE assumed as matrix)
    Note : This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : STORAGE
    */
    data::STORAGE subtract(data::STORAGE m1, data::STORAGE m2);

    
    /*
    Function to Find transpose of a matrix
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
    Note : This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : STORAGE
    */
    data::STORAGE transpose(data::STORAGE m);

    /*
    Function to Find LU decomposition of a matrix
    Paramters :  m1 - > matrix (STORAGE assumed as matrix)
    Note : This function assumes the legal structure of matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
           Do little algorithm is used for LU decomposition. Expect Algorithmic change in future versions.
    return type : std::tuple<STORAGE,STORAGE>
    */
    std::tuple<data::STORAGE,data::STORAGE> LU(data::STORAGE m1);

    /*
    Function to Find transpose of a matrix
    Paramters :  std::tuple<STORAGE,STORAGE> - > Tuple of LU decomposition of matrix to find determinant of.
    Note : This function assumes the legal structure of L and U matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
    return type : double
    */
    double determinant(std::tuple<data::STORAGE,data::STORAGE>);

    /*
    Function to inverse of a matrix
    Paramters :  std::tuple<STORAGE,STORAGE> - > Tuple of LU decomposition of matrix to find determinant of.
    Note : This function assumes the legal structure of L and U matrices already to boost optimization. 'MAKE SURE' matrix shapes are pre checked.
           This function uses LU decomposition of a matrix to find the inverse. Use LU() for LU decomposition.
    return type : STORAGE
    */
    data::STORAGE inverse(std::tuple<data::STORAGE,data::STORAGE>);

     /*
    Function to inverse of a diagonal matrix
    Paramters :  STORAGE element , the matrix
    return type : STORAGE
    */
    data::STORAGE inverse_diagonal(data::STORAGE);


    /*
    Function to create a user defined size matrix (STORAGE element) with default values
    Paramters :  rows - >  number of rows
                 cols - >  number of cols
                 default_values - >  default values (0 - by default)
    Note :  This function is added as a supplement. Function created prior to this function
            might not be using this function. Refer to change logs in Backup for additional information on backup level changelogs
    return type : STORAGE
    */
   data::STORAGE create(const int &rows, const int &cols, const double &default_values = 0);

    /*
    Function to create a user defined size identity matrix (STORAGE element) with also user defined diagonal values
    Paramters :  dimension - >  number of rows also the number of columns
                 default_values - >  default values to be in the diagonal (0 - by default)
    Note :  This function is added as a supplement. Function created prior to this function
            might not be using this function. Refer to change logs in Backup for additional information on backup level changelogs
    return type : STORAGE
    */
   data::STORAGE create_diagonal(const int &dimension, const double &default_values = 1);
    

}

// namespace for array related operations
namespace array 
{       
     /*
    Function to average of rows or columns
    Paramters :  X - > array (STORAGE element ) to perform averageon
                axis - > bool value 0(false) for column wise ; 1(true) for row wise
    return type : STORAGE
    */
    data::STORAGE average(const data::STORAGE &X,const bool &axis=ROW);

    /*
    Function to maximum value in a array (STORAGE element)
    Paramters :  X - > array (STORAGE element ) to look into
    return type : double
    */
   double maximum(const data::STORAGE &y);


}

}
#endif
