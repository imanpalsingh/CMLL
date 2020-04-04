/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for utility functions

*   Description : This File includes the utility functions
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_28
 
* Last modified : MAR_23_20_16_28

* Change Logs : 

*
*
*/


#ifndef UTIL_HPP
#define UTIL_HPP


#include<tuple>
#include "defined.hpp"
#include<vector>
#include"../Numerical/Numeric.hpp"
#include<iostream>

namespace cmll
{
    namespace util
    {
        /*
    Function to return columns having the required value
    Parameters : dataset - >  dataset to look into
                 cols -> columns to look into
                 val - >  value to look for
    
    return type : STORAGE
    */

    data::STORAGE where(const data::STORAGE &dataset,const std::vector<int> &cols, const double &val);

    /*
    Function to return indexes of columns having the required value
    Parameters : dataset - >  dataset to look into
                 cols -> columns to look into
                 val - >  value to look for
    return type : std::vector<int>
    */
    std::vector<int> where_index(const data::STORAGE &data,const std::vector<int> &cols,const double &val);
    
    /*
    Function to return rows defined by index
    Parameters : dataset - >  dataset to look into
                 rows - > indexes of rows to fetch
    return type : STORAGE
    */
    data::STORAGE fetch_row(const data::STORAGE &dataset,const std::vector<int> &rows);

    /*
    Function to return two subsets (partition) of STORAGE based on a percentage defined
    Parameters : X - >  dataset to perform split on
                 perc - > percentage of rows first subset gets
    return type std::tuple<STORAGE,STORAGE>
    */
    std::tuple<data::STORAGE,data::STORAGE> split(const data::STORAGE &X,const double &perc = 0.7);

    /*
    Function to check if a given STORAGE element has the required number of features
    Parameters : X - >  STORAGE element, size - > size to follow
    return type : bool
    */

    bool is_legal(const data::STORAGE &X,const size_t &size);
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