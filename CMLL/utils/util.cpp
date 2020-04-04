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

* Change Logs : None

*
*
*/


#include"util.hpp"

namespace cmll
{
    namespace util
    {
        /*
    *

    * Function Name : where

    * Description : Function to return a subset of original STORAGE containing a particular value in the row

    * Parameters : dataset ->  Original STORAGE element
    *              cols -> columns to look at
    *              vals -> value to look for
     

    * Return :  result - > the subset of original dataset

    * Function Version : 0.0.0

    *
    */
        data::STORAGE where(const data::STORAGE &dataset,const std::vector<int> &cols,const double &val)
        {
            // variable to store the indexes of rows that have the required values
            std::vector<int> indexes;

            data::STORAGE result;

            

            try
            {

            // for each element in all rows and given cols
            for(int row=0; row<dataset.size();row++)
            {
                for(auto col:cols)
                {
                    if(dataset[row][col] == val)
                    {
                        indexes.emplace_back(row);
                    }
                }
            }

            std::vector<double> holder;

            // Now creating the new SOTRAGE
            for(auto row:indexes)
            {
                for(auto col=0;col<dataset[row].size();col++)
                {
                    holder.emplace_back(dataset[row][col]);
                }
                result.emplace_back(holder);
                holder.clear();
            }
            }

            catch(const std::exception &e)
            {
                std::cout<<"(In function data::where) Warning : An exception was encountered \n";
                std::cerr << e.what() << '\n';
            }

            return result;

        }

     /*
        *

        * Function Name : where_index

        * Description : Function to return a index of rows of original STORAGE containing a particular value in the row

        * Parameters : dataset ->  Original STORAGE element
        *              cols -> columns to look at
        *              val -> value to look for
     

        * Return :  indexes - > the  rows containing th edesired value

        * Function Version : 0.0.0

        *
        */
        
        std::vector<int> where_index(const data::STORAGE &data,const std::vector<int> &cols,const double &val)
        {
            std::vector<int> indexes;
            // for each element in all rows and given cols
            for(int row=0; row<data.size();row++)
            {
                for(auto col:cols)
                {
                    if(data[row][col] == val)
                    {
                        indexes.emplace_back(row);
                    }
                }
            }

            return indexes;
        }

     /*
    *

    * Function Name : fetch_row

    * Description : Function to return a subset of original STORAGE with specified rows

    * Parameters : dataset ->  Original STORAGE element
    *              rows - >  rows to fetch
     

    * Return :  result - > STORAGE subset with user defined rows

    * Function Version : 0.0.0

    *
    */

        data::STORAGE fetch_row(const data::STORAGE &dataset, const std::vector<int> &rows)
        {
            
            data::STORAGE result;
            for(auto row:rows)
            {
               result.emplace_back(dataset[row]);
            }

            return result;

        }

     /*
    *

    * Function Name : split

    * Description : Function to split given STORAGE element into two subsets of given split ratio

    * Parameters : X ->  Original STORAGE element
    *              perc -> percentage taken by first subset
     

    * Return :  {train,test} - > two subsets to return

    * Function Version : 0.0.0

    *
    */

        std::tuple<data::STORAGE,data::STORAGE> split(const data::STORAGE &X,const double &perc)
        {
            data::STORAGE train,test;

            size_t total_size = X.size();

            // Calculating size of first subset
            size_t new_size = total_size*perc;
            
            // Filling new subsets
            for(int i =0; i<total_size;i++)
            {
                if(i<new_size)
                {
                train.emplace_back(X[i]);
                }
                else
                {
                 test.emplace_back(X[i]);   
                }
                
            }

            return {train,test};
            
        }
        /*
        *

        * Function Name : is_legal

        * Description : Function  to check if a STORAGE element has required size in all vectors inside it

        * Parameters : X - > STORAGE element num_of_features - > size that all vectors have to assert to

        * Return : true : if the STORAGE follows the required size, false if it doesn't

        * Function Version : 0.0.0

        *
        */

        bool is_legal(const data::STORAGE &X,const size_t &num_of_features)
        {
            for(auto row:X)
            {
                if(row.size()!=num_of_features)
                {
                    return false;
                }
            }
            return true;
        }

    }

    /* Name space for printing and buffering */
    namespace out
    {

    /*
    *

    * Function Name : print

    * Description : Function  to print a STORAGE element

    * Parameters : data -> STORAGE element to print

    * Return : NONE

    * Function Version : 0.0.0

    *
    */
    void print(const data::STORAGE &data)
    {
        if(!data.size())
        {
            std::cout<<"<In function data::out::print> Error : No values to print\n";
            return;
        }
        
        for (auto row:data)
        {
            for(auto col:row)
            {
                std::cout<<col<<" ";
            }
            std::cout<<'\n';
        }

        std::cout<<"\nNumber of rows : "<<data.size();
        std::cout<<"\nNumber of columns (if kept same in all rows) : "<<data[0].size()<<"\n";
    }
    }
}