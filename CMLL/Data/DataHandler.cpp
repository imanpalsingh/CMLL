/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : Data handler for handling dataset files in format like (csv,xlxs etc)

*   Description : This File Handles the formatting of the file before running any operation
                  realted to machine learning (Preprocessing,EDA,etc). The file read is to be stored in vector of vectors. 
                  High level and low level tools are provided for performing operations on the dataset.

*
*/


/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_8_20_21_12
 
* Last modified : MAR_16_20_23_21

* Change Logs : None

*
*/


/*
*

* Header files : For Input Output on the standard streams, on the files. The declaration header,vectors,arrays.

*
*/

// Standard I/O stream
#include<iostream>
#include<stdio.h>

// File stream
#include<fstream>

// Arrays
#include<array>

// Vectors 
#include<vector>

// Datahandler declarations header (version 0.0.0)
#include"DataHandler.hpp"

// Type definitions header (version 0.0.0)
#include"../utils/defined.hpp"



/*
*

* Function Name : read

* Description : Function to read a file and store the contents in vector of vectors of double a.k.a STORAGE (See defined.hpp for typedef).

* Parameters : filename -> The filename of the file to read.
             :separator -> The delimeter that separates different observations in thefile (default = ',') 
* Return : Object of the class Handler

* Function Version : 0.0.0

* Goal of Implementations : A user defined line break delimeter ( Version 1.0)

* Note since xlxs files are binary format the cannot be opened with read(), expect a separate function for those files in version 1.0

*
*/

namespace cmll
{

Handler csv::read(std::string filename,const char separator)
{
    
    // Object to return
    Handler object;
    
    // Object of the ifstream class to read file
    std::ifstream file_read(filename);

    // If the file is not accessible or not available
    if(!file_read)
    {
        std::cout<<"<In function csv::read> Error : Cannot open file specified.\n";
        file_read.close();
        return object;
    }
    
    // Creating variables required for the process
    double data;
    char character;
    int columns_num = 0;
    std::vector<double> data_holder;

    // Reading first row
    while(file_read>>data)
    {
        /* The format of the file is first determined.
          The number of columns in the first row determines the total columns
           to accept , if in any other row the number of columns exceed,
           an error will be raised. However expect undefined behaviour from the 
           returned object in the aforementioned case. */

        /* as specified in the goal of implementation, the line break delimeter is 
           by default '\n' in current version. Will be changed to user defined 
           delimeter by version 1.0.0 */

        // Processing the first row 
        // Reading the character ahead of the data
        
        file_read.get(character);
        
        // If the read character is theseparator of column or of line
        if((character ==separator) || (character == '\n'))
        {
            // Increment the number of rows
            columns_num++;

            // Adding the data to the temporary vector to create a row and later insert into vector of vector
            data_holder.emplace_back(data);
           
            // if the character is line break, then end of preprocessing first row.
            if(character == '\n')
            {
                break;
            }
        }

        // If the character received is unkown 
        else {
            std::cout<<"<In function csv::read> Error : An unspecified character '"<<character<<"' was received at row 1 column "<<columns_num<<" which was expected to be the delimeter '"<<separator<<"'\n";
            file_read.close();
            return object;
        }
        
    }

    // Adding the last value in the temporary  storage to the dataset
    object.Dataset.emplace_back(data_holder);

    //resetting the temporary storage
    data_holder.clear();

    // Reading rest of the rows
    
    // variable to keep track of current column
    int column=0;

    // Reading rows
    while(file_read>>data)
    {
        

        // Processing the  row 
        // Reading the character ahead of the data
        file_read.get(character);
        
        // If the read character is theseparator of column or of line
        if((character ==separator) || (character == '\n'))
        {
            // Increment the col num
            column++;
            
            // Adding the data to the temporary vector to create a row and later insert into vector of vector
            data_holder.emplace_back(data);
        

        // if the character is line break, then end of preprocessing of current row
        if(character == '\n')
        {
            // Checking if the format of the file is same as the first row i.e number of columns are same as in the first row
            if (column != columns_num)
            {
                std::cout<<"<In function file_read> Error : The csv format is not preserved in the file \n";
                std::cout<<" The Number of columns are "<<column<<". Expected were "<<columns_num <<"\n";
                file_read.close();
                return object;
            }

            // Adding the row to the final dataset
            object.Dataset.emplace_back(data_holder);

            // Clearing the temporary storage for next iteration. 
            data_holder.clear();
            column=0;

        }
        }  

        // If the character received is unkown 
        else {
            std::cout<<"<In function file_read> Error : An unspecified character '"<<character<<"' was received at row 1 column "<<columns_num<<" which was expected to be the delimeter '"<<separator<<"'\n";
            file_read.close();
            return object;
        }

        
        
    }

    // Adding the last row to the dataset. Also checking for integrity of the format.
    if(!data_holder.empty())
    object.Dataset.emplace_back(data_holder);

    //Closing the stream 
    file_read.close();
    
    
    // Returning the object (let copy constructure handle the rest)
    return object;

}


/* UTILITIES */

/*
*

* Function Name : rows

* Description : Function to Calculate number of rows. It is the number of vectors emplaced.

* Parameters : None

* Return : Number of rows in the dataset (Number of vectors inside the vector of vectors)

* Function Version : 0.0.0

*
*/

int Handler::rows()
{
    return Dataset.size();
}

/*
*

* Function Name : cols

* Description : Function to Calculate number of cols. It is the number of elements in the first vector.

* Parameters : None

* Return : Number of Cols in the dataset (umber of elements inside the each vector)

* Function Version : 0.0.0

*
*/

int Handler::columns()
{
    return Dataset[0].size();
}

/*
*

* Function Name : size()

* Description : Function to Calculate number of elements in the dataset.

* Parameters : None

* Return : Number of elements combined of all vectors.

* Function Version : 0.0.0

*
*/

int Handler::size()
{
    return rows()*columns();
}

/*
*

* Function Name : get

* Description : Function to return the data member 'Dataset'.

* Parameters : none

* Return : data::STORAGE (see DataHandler.hpp for typedef) variable

* Function Version : 0.0.0


*
*/

data::STORAGE Handler::get()
{
   return Dataset;


}


/*
*

* Function Name : operator[]

* Description : Overloading the subscript operator to allow indexing 

* Parameters : indexes - > Vector of int which contains all the indexes required

* Return : Handler object containing columns of the original dataset which are defined in the indexes parameters

* Function Version : 0.0.0

* Note negative indexing is supported since 0.0.0

*
*/

Handler Handler::operator[](std::vector<int> indexes)
{
    //Creating object to return
    Handler object;

    //Creating a temporary storage data holder
    std::vector<double> Holder;

    if(indexes.size() == 1)
    {
        std::cout<<"(In function operator[]) Error : Use 'int' instead of std::vector<int> for singular index \n";
        return object;
    }

     for(int row=0;row<Dataset.size();row++)
        {
            
        for(auto col:indexes)
            {
                // if negative indexing is provided
                if(col<0)
                    {
                    
                    //Converting to normal indexing
                    col = Dataset[0].size() + col;
                    
                    }
        
                // if the index specified is larger than number of columns in the dataset then raise an error
                if(col> Dataset[0].size()-1)
                    {
                        
                        std::cout<<"<In function operator[]> Error : Handler index out of range. Received '"<<col<<"' but expected less than '"<<Dataset[0].size()<<"'.\n";
                        return object;
                    }

                // if everything is write then add to the temporary storage
                Holder.emplace_back(Dataset[row][col]);
            }

            // Add to the object's dataset
            object.Dataset.emplace_back(Holder);

            //Clearing for next iteration
            Holder.clear();
            
        }


  return object;
}

/*
*

* Function Name : operator[]

* Description : Overloading the subscript operator to allow indexing 

* Parameters : index - > integer value of the column data to be returned 

* Return : Handler object containing column of the original dataset which is defined in the parameter

* Function Version : 0.0.0

* Note negative indexing is supported since 0.0.0

*
*/
Handler Handler::operator[](int index)
{
    //Creating object to return
    Handler object;

    //Creating a temporary storage data holder
    std::vector<double> Holder;
   
    // if negative indexing is provided
        if(index<0)
        {
            //Converting to normal indexing
            index = Dataset[0].size() + index;
        }

    // if the index specified is larger than number of columns in the dataset then raise an error
    if(index > Dataset[0].size()-1)
        {
            std::cout<<"<In function operator[]> Error : Handler index out of range. Received '"<<index<<"' but expected less than '"<<Dataset[0].size()<<"'.\n";
            return object;
        }

    // For each data item in the column
    for(auto inc = 0;inc<Dataset.size();inc++)
        {
            // Add the value to the temporary storage
            Holder.emplace_back(Dataset[inc][index]);
            object.Dataset.emplace_back(Holder);
            Holder.clear();
        }

        // Adding the row to the to be send object's Dataset
        
        // Clearing the temporary storage for next iteration.
        Holder.clear();
    

    // Returning the object
    return object;

} 
/* 
*

* Function Name : operator()

* Description : Overloading the () operator to allow row and column indexing

* Parameters : rows - > vector of int containing rows index to be extracted
               cols - > vector of int containing cols index to be extracted

* Return : Handler object containing rows and columns of the original dataset which is defined in the parameters

* Function Version : 0.0.0

* Note negative indexing is supported since 0.0.0

*
*/


Handler Handler::operator()(std::vector<int> rows,std::vector<int> cols)
{
    
    // Creating object of the class to be returned
    Handler object;
    
    // Using a temporary storage
    std::vector<double> holder;
    
    // For each row
    for(auto row:rows)
    {
        // Check for negative indexes
        if(row<0)
        {
            //Converting to normal indexing
            row = Dataset.size() + row;
        }

        // // Checking for valid index
         if(row > Dataset.size()-1)
        {
            std::cout<<"<In function operator()> Error : Handler row index out of range. Received '"<<row<<"' but expected less than '"<<Dataset.size()<<"'.\n";
            return object;
        }

        // For each column index
        for(auto col:cols)
        {
            // Check for negative indexes
            if(col<0)
            {
                //Converting to normal indexing
                col = Dataset[0].size() + col;
            }

        // // Checking for valid index
            if(col > Dataset[0].size()-1)
            {
                std::cout<<"<In function operator()> Error : Handler column index out of range. Received '"<<col<<"' but expected less than '"<<Dataset[0].size()<<"'.\n";
                return object;
            }
            holder.emplace_back(Dataset[row][col]);     
        }
        object.Dataset.emplace_back(holder);
        holder.clear();
    }

    return object;
}

/*
*

* Function Name : operator()

* Description : Overloading the () operator to allow row and column indexing

* Parameters : rows - > int containing row index to be extracted
               cols - > int containing col index to be extracted

* Return : Handler object containing row and column of the original dataset which is defined in the parameters

* Function Version : 0.0.0

* Note negative indexing is NOT supported yet due to technical reasons.

*
*/

Handler Handler::operator()(int row,int col)
{
    
    // Creating object of the class to be returned
    Handler object;
    
    // Using a temporary storage
    std::vector<double> holder;
  
    holder.emplace_back(Dataset[row][col]);     
        
    object.Dataset.emplace_back(holder);
    holder.clear();
    
    

    return object;
}


}
