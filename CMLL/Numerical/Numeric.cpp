/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing functions for numrtical computations

*   Description : This file contains all the functions required for performing algorithms
                  such as matrix multiplication,matrix transpose addition, Inverse etc
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.1

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_50
 
* Last modified : MAR_23_20_17_03

* Change Logs : 

        1) Date : 23-03-20 Time 17:02
        Namespace array:
        Added new functions contains(),unique()
        
        2) Date : 22-03-20 Time : 14:12
        Namespace array :
        Added new functions sum(), raise_power()

        Namespace matrix:
        added new function subtract(matrix,scalar); 
        
        3) Date : 21-03-20 Time : 21:00 
        Namespace matrix :
        Added new function multiply_diagonal() (refer to function level comments for more information)

*
*/


/*
*

* Header files : For Input Output on the standard streams, vectors ,tuples etc
*
*/

#include<iostream>
#include<vector>
#include <functional> 
#include <tuple>

// Version 0.0.0
#include"Numeric.hpp"


/* Functions */

/* Functions associated with matrix namespace */

/*
*

* Function Name : multiply

* Description : Function to multiply two matrices represented as vector of vectors of int

* Parameters : m1 - > Matrix in the LHS of the equation
             : m2 - > Matrix in the RHS of the equation 

* Return : STORAGE containing the product

* Note : The brute force algorithm will be change to stressen's matrix multiplication alogithm in version 1.0

* Function Version : 0.0.0

*
*/

namespace cmll
{

data::STORAGE matrix::multiply(const data::STORAGE &m1,const data::STORAGE &m2)
{
    
    std::vector<std::vector<double> > result(m1.size(),std::vector<double>(m2[0].size(),0));
   
   
    for(int i=0;i<m1.size();i++)
    {
        for(int j=0;j<m2[0].size();j++)
        {
            
            for(int k=0;k<m1[0].size();k++)
            {
                result[i][j] +=m1[i][k] * m2[k][j];
            }
    }
    
  

}
  return result;
}

/*
*

* Function Name : multiply

* Description : Matrix multiplication of matrix and a scalar

* Parameters : m1 - > Matrix as the operand
             : m2 - > scaler 

* Return : data::STORAGE containing the product

* Function Version : 0.0.0

*
*/
 data::STORAGE matrix::multiply(const data::STORAGE &m1,const int &scalar)
 {
     data::STORAGE result;


     std::vector<double> holder;
     for(int i=0;i<m1.size();i++)
     {
        for(int j=0;j<m1[i].size();j++)
        {
            holder.emplace_back(m1[i][j]*scalar);
        }
        result.emplace_back(holder);
        holder.clear();
     }
     

     return result;
 }

/*
*

* Function Name : multiply_diagonal

* Description : Matrix multiplication of matrix and a diagonal matrix

* Parameters : m1 - > Matrix as the operand
             : m2 - > second matrix as the operand
             : which_matrix_diagonal  - > flag to represent which matrix is diagonal 0 - m1, 1 - m2

* Return : data::STORAGE containing the product

* Note : This function's idea is an external contribution of user:10251345 @stackoverflow.com

* Function Version : 0.0.0

*
*/

data::STORAGE matrix::multiply_diagonal(const data::STORAGE &m1, const data::STORAGE &m2, const bool &which_matrix_diagonal)
{
    /* The flag which_matrix_diagonal should be set to zero for implying first matrix(m1) is diagonal and 1 for implying second matrix(m2) as diagonal
    
     IMPORTANT : THE DIAGONAL MATRIX IS ASSUMED TO HAVE JUST THE DIAGONAL ELEMENTS NOT THE ZEROS WHILE PASSING

     This function is based on the diagonal property of diagonal matrices

    * The effect of pre multiplying a matrix by a diagonal matrix is 
    * that of multiplying the i-th row of matrix A by the factor ki i.e.
    * the successive rows of the original matrix are simply multiplied by successive diagonal elements of the diagonal matrix
    
    * The effect of post multiplying a matrix by a diagonal matrix is
    * is that of multiplying the i-th column of matrix A by the factor ki i.e. 
    * the successive columns of the original matrix are simply multiplied by successive diagonal elements of the diagonal matrix
   */

  //Resultant matrix
  data::STORAGE result;
  std::vector<double> temp;

  // IF m1 is diagonal matrix
  if(which_matrix_diagonal == 0)
  {
      //Pre multiplication of a matrix by a diagonal matrix property
      for(int i=0;i<m2.size();i++)
      {
          for(int j=0;j<m2[0].size();j++)
          {
            if(m2[i][j] == 0 || m1[i][0] == 0)
            {
                std::cout<<"<In function matrix::multiply_diagonal> Warning : Multiplied by zero \n";
            }
            temp.emplace_back(m2[i][j]*m1[i][0]); //refer to the 'IMPORTANT' section above for this.
          }
          result.emplace_back(temp);
          temp.clear();
      }


  }

  //if m2 is the diagonal matrix
  else if(which_matrix_diagonal == 1)
  {
    //Pre multiplication of a matrix by a diagonal matrix property
     //Pre multiplication of a matrix by a diagonal matrix property
     
      for(int i=0;i<m1.size();i++)
      {
          for(int j=0;j<m1[0].size();j++)
          {
               
                temp.emplace_back(m1[i][j]*m2[j][0]); //refer to the 'IMPORTANT' section above for this.
          }
          result.emplace_back(temp);
          temp.clear();
      }


  }

  return result;

}



/*
*

* Function Name : sum

* Description : Sum of two matrices

* Parameters : m1 - > Matrix as the operand
             : m2 - > matrix 2

* Return : data::STORAGE containing the sum

* Function Version : 0.0.0

*
*/

data::STORAGE matrix::sum(const data::STORAGE &m1,const data::STORAGE &m2)
{
     data::STORAGE result;

     std::vector<double> holder;
     for(int i=0;i<m1.size();i++)
     {
        for(int j=0;j<m1[i].size();j++)
        {
            holder.emplace_back(m1[i][j]+m2[i][j]);
        }
        result.emplace_back(holder);
        holder.clear();
     }
     

     return result;
}

/*
*

* Function Name : subtract

* Description : Subtraction of two matrices

* Parameters : m1 - > Matrix as the operand
             : m2 - > matrix 2

* Return : data::STORAGE containing the subtract

* Function Version : 0.0.0

*
*/

data::STORAGE matrix::subtract(const data::STORAGE &m1,const data::STORAGE &m2)
{
     data::STORAGE result;
     std::vector<double> holder;

     if( m1.size() == m2.size())
     {
         if(m1[0].size() == m2[0].size())
         {
     
            
            for(int i=0;i<m1.size();i++)
            {
                for(int j=0;j<m1[0].size();j++)
                {
                     holder.emplace_back(m1[i][j]-m2[i][j]);
                }
                result.emplace_back(holder);
                holder.clear();
            }
        }

        else
        {
            std::cout<<"<In function matrix::multiply> Error : Matrices are not in correct shape to be subtracted. \n";
            return result;
        }
        
     }

     else if(m1[0].size() == m2.size())
     { 
        if(m2[0].size() == 1)
        {
            for( int i=0; i < m1.size();i++)
            {
                for(int j=0;j<m1[0].size();j++)
                {
                    holder.emplace_back(m1[i][j] - m2[j][0]);
                }
                result.emplace_back(holder);
                holder.clear();
            }
        }

        else
        {
            std::cout<<"<In function matrix::multiply> Error : Matrices are not in correct shape to be subtracted. \n";
            return result;
        }
        
     }

     return result;
    
}

/*
*

* Function Name : subtract

* Description : Subtraction of a scalar from all the elements of the matrix

* Parameters : m1 - > Matrix as the operand
             : m2 - > scalar to subtract

* Return : data::STORAGE containing the subtract

* Function Version : 0.0.0

*
*/

data::STORAGE matrix::subtract(const data::STORAGE &m1,const double &m2)
{
    
    auto result = create(m1.size(),m1[0].size());
    
    // for each element in m1
    for(int i=0;i<m1.size();i++)
    {
        for(int j=0;j<m1[i].size();j++)
        {
            // subtract the scalar
            result[i][j] = m1[i][j] - m2;
        }
    }

    return result;
}


/*
*

* Function Name : transpose

* Description : transpose of a matrix

* Parameters : m1 - > Matrix as the operand

* Return : data::STORAGE containing the transpose of the parameter

* Function Version : 0.0.0

*
*/

data::STORAGE matrix::transpose(const data::STORAGE &m1)
{

  data::STORAGE result;
  std::vector<double> holder;


 //For each column
  for(int i=0; i<m1[0].size();i++)
  {
      // For each row
      for(int j=0;j<m1.size();j++)
      {
          //Checking for matrix consistency
          if(m1[0].size()!=m1[j].size())
          {
              std::cout<<"<In function matrix::transpose> Error : The passed data::STORAGE variable is not a qualified matrix. Matrix structure incorrect.\n";
              return result;
          }
          holder.emplace_back(m1[j][i]);
      }
      result.emplace_back(holder);
      holder.clear();

  }

return result;

}

/*
*

* Function Name : LU

* Description : LU decomposition of a matrix

* Parameters : m1 - > Matrix as the operand

* Return : std::tuple<data::STORAGE,data::STORAGE> contianing 0-L and 1-U matrices

* Note : This function uses Do little algorithm for LU factorization.

* Function Version : 0.0.0

*
*/


std::tuple<data::STORAGE,data::STORAGE> matrix::LU(const data::STORAGE &m1)
{
    //Defining L
    std::vector<std::vector<double> > L(m1.size(),std::vector<double>(m1.size(),0));
    
    //Defining U
    std::vector<std::vector<double> > U(m1.size(),std::vector<double>(m1.size(),0));


    // This is for only initial checking rest try block can handle
    if(m1.size()!=m1[0].size())
    {
        std::cout<<"(In function matrix::LU) Warning : Only Square Matrices can be decomposed into LU by this algorithm. Except undefined behaviour \n";
        return {L,U};
    }
    
    try
    {
        // Calculating U    
        for(int i=0; i<m1.size();i++)
        {
            for(int k=i;k<m1.size();k++)
            {
                double sum=0;
                for(int j=0;j<i;j++)
                    sum+=(L[i][j] * U[j][k]);
            
                U[i][k] = m1[i][k] - sum;

                // And U
                for(int k=i;k<m1.size();k++)
                {
                    if(i==k)
                    {
                        L[i][i]=1;
                    }
                    else
                    {
                        double sum=0;
                        for(int j=0;j<i;j++)
                        {
                            sum+=(L[k][j]*U[j][i]);
                        }

                        L[k][i] = (m1[k][i] - sum) / U[i][i];
                    }
                
                }
            }
        }
    }

     catch(const std::exception& e)
    {
        std::cout<<"(In function matrix::LU) Warning :  An exception was caught, may lead to program performing incorrectly \n";
        std::cerr << e.what() << '\n';
    }
    
    
    return {L,U};
   

}






/*
*

* Function Name : Determinant

* Description : Finding determinant of the matrix

* Parameters : LU-> std::tuple contiaing L at 0 index and U matrix at 1 ; 

* Return : det : the determinant of the matrix (double)

* Note : This function accepts LU factorization of the matrix to be passed rather than the matrix itself (refer to matrix::LU in Numeric.hpp)


* Function Version : 0.0.0

*
*/

double matrix::determinant(const std::tuple<data::STORAGE,data::STORAGE> &LU)
{
    // Extracting L and U matrices
    data::STORAGE L = std::get<0>(LU);
    data::STORAGE U = std::get<1>(LU);

    // Determinant of Triangular matices is the product of its diagonals
    // Finding determinant of L matrix
    
    double det_L=1;
    for(int i=0;i<L.size();i++)
    {
        det_L*=L[i][i];
    }

    // Finding determinant of U matrix

    double det_U=1;
    for(int i=0;i<U.size();i++)
    {
        det_U*=U[i][i];
    }

    //Finally the determinant of the matrix is the product of determinant of the L and U 
    return det_L*det_U;
  


}

/*
*

* Function Name : inverse

* Description : Finding inverseof a matrix

* Parameters : LU-> std::tuple contiaing L at 0 index and U matrix at 1 ; 

* Return : inverse_matrix : the inverse of the matrix (double)

* Note : This function accepts LU factorization of the matrix to be passed rather than the matrix itself (refer to matrix::LU in Numeric.hpp)


* Function Version : 0.0.0

*
*/




data::STORAGE matrix::inverse(const std::tuple<data::STORAGE,data::STORAGE> &LU)
{
    

  //Extracting the Lower triangular matrix 
    data::STORAGE L = std::get<0>(LU);

    // Extracting theupper triangular matrix
    data::STORAGE U = std::get<1>(LU);

    // Creating the inverse matrix
    data::STORAGE inverse_matrix;
    /* Starting the inverse process */

    /* [L]*[z] = [c] 
       [U]*[x] = [z] 
       where z is the reqired column of the inverse matrix
       and c is the column of the identity matrix
       Source : Advance engineering mathematics , LU Decomposition BS Grewal.
    */

   /* NOTE  :  Creation of Identity matrix will be added as a separate function in the matrix namespace in upcoming versions */

   // Creating an identity matrix (initialised with all zeros)
    std::vector<std::vector<double> > identity_matrix(L.size(),std::vector<double>(L.size(),0));
    
    try
    {

    // Filling the 'ones' at right position of the identity matrix
    for(int i=0; i<identity_matrix.size();i++)
    {
        identity_matrix[i][i] = 1;
    }
    // Creating an empty 'z' matrix

    std::vector<double> z(L.size());

    // Creating an empty 'x' matrix

    std::vector<double> x(L.size());


    for(int I_col=0;I_col<identity_matrix.size();I_col++)
    {

    // Implementing [L] * [z] = [c] (forward substitution)

    z[0] = identity_matrix[0][I_col] / L[0][0];
    for(int row =1; row<L.size();row++)
    {
        double divisor = 1;
        double matrix_sum = 0;
        for(int col=0;col<row;col++)
        {
        
            matrix_sum+=L[row][col]*z[col];
        }
        z[row] = (identity_matrix[row][I_col] - matrix_sum)/L[row][row];
        
    }

   
 

    // Implementing [U] * [x] = [z] (back substitution)

    x[L.size()-1] = z[z.size()-1] / U[U.size()-1][U.size()-1];
    for(int row=U.size()-2;row>=0;row--)
    {
        double divisor = 1;
        double matrix_sum = 0;
        for(int col=row+1;col<U[0].size();col++)
        {
            matrix_sum+=U[row][col]*x[col];
        }
        x[row] = (z[row] - matrix_sum)/U[row][row];
    }
    
    //adding it to the final inverse matrix
    /* IMPORTANT : At this stage the x is represented as a row matrix (but assumed to be column matrix in calculation)
    /* The final inverse_matrix will be transposed, this step is not mathematical rather a algorithm one. */

    inverse_matrix.emplace_back(x);
    }  

    // Transpose the inverse_matrix for correct mathematical representation
    inverse_matrix = matrix::transpose(inverse_matrix);

    }
    catch(const std::exception& e)
    {
        std::cout<<"(In function matrix::inverse) Warning :  An exception was caught, may lead to program performing incorrectly \n";
        std::cerr << e.what() << '\n';
    }
 
    return inverse_matrix;
    

    

}

 /*
*

* Function Name : inverse_diagonal

* Description : Finding inverse of a diagonal matrix

* Parameters : X - >  the matrix 
            : isStructureDiagonal = If the matrix is actually represent as a diagonal matrix - 0
                                      or just a STORAGE containing the diagonal elements - 1

* Return : inverse_matrix : the inverse of the matrix (double)

* Function Version : 0.0.1

*
*/


   data::STORAGE matrix::inverse_diagonal(const data::STORAGE &X,const bool &isStructureDiagonal)
   {
        /*
        The inverse of a diagonal matrix is the diagonal elements replaced with their reciprocals
        */
       data::STORAGE inverse_matrix;
       // If the matrix is actually represented as a diagonal matrix
       if(!isStructureDiagonal)
       {
       //Assuming matrix is in correct shape
       inverse_matrix = create(X.size(),X.size(),0);

       // Computing the inverse
       for(int index=0;index<X.size();index++)
       {
           try
           {
               inverse_matrix[index][index] = 1/X[index][index];
           }
           catch(const std::exception& e)
           {
               std::cout<<"<In function matrix::inverse_diagonal> Error : ";
               std::cerr << e.what() << '\n';
           }
           
           
       }
       }
        //If it is a STORAGE element containing just the diagonal elements 
       else if(isStructureDiagonal)
       {
           inverse_matrix = create(X.size(),1);

            for(int index=0;index<X.size();index++)
       {
           try
           {
               inverse_matrix[index][0] = 1/X[index][0];
           }
           catch(const std::exception& e)
           {
               std::cout<<"<In function matrix::inverse_diagonal> Error : ";
               std::cerr << e.what() << '\n';
           }
           
           
       }

       }
       

       return inverse_matrix;
   }



/*
*

* Function Name : create

* Description : Creating a user defined size matrix with user defined default values

* Parameters : rows - > Number of rows
               cols - >  number of columns
               default_values - > default values in the newly created matrix

* Return : new_martix - > the newly created matrix

* Note :  This function is added as a supplement. Function created prior to this function
          might not be using this function's functionality. Refer to change logs in Backup for additional information on backup level changelogs
    

* Function Version : 0.0.0

*
*/
data::STORAGE matrix::create(const int &rows, const int &cols, const double &default_values)
{
    //Creating a new vector of vectors (notice it is the STORAGE , written as vector for debugging reasons)
    std::vector<std::vector<double> > new_matrix(rows,std::vector<double>(cols,default_values));
    return new_matrix;

}

/*
*

* Function Name : create_diagonal

* Description : Creating a user defined size diagonal matrix with user defined default values at diagonals

* Parameters : dimensions - > rows and cols of the diagonal matrix
               default_values - > default values in the newly created diagonal matrix at the diagonals

* Return : new_diagonal_martix - > the newly created diagonal matrix

* Note :  This function is added as a supplement. Function created prior to this function
          might not be using this function's functionality. Refer to change logs in Backup for additional information on backup level changelogs
    

* Function Version : 0.0.0

*
*/
data::STORAGE matrix::create_diagonal(const int &dimension, const double &default_values)
{
   auto new_diagonal_matrix =  create(dimension,dimension,0);

   for(int i=0;i<new_diagonal_matrix.size();i++)
   {
       new_diagonal_matrix[i][i] = default_values;
   }

   return new_diagonal_matrix;

}



/* Functions associated with list namespace */


/*
*

* Function Name : range

* Description : Create and return a vector of integers with user specified range

* Parameters : start - > the starting number of the range
               end - > the ending number of the string
               step -> Increment or decrement steps to take

* Return : result : the vector of int containing the range

* Note : This function is only a C++ replica of python's range() function. It is temporary and optimizations will be done. May be removed in future versions.


* Function Version : 0.0.0

*
*/


std::vector<int> list::range(int start,int end,int step)
{
 std::vector<int> result;

        if(start<end)
        {
        for(int i=start;i<=end;i+=step)
        result.emplace_back(i);
        }
        else
        {
            for(int i=start;i>=end;i-=step)
            result.emplace_back(i);
        }
        
        return result;
}


// Namespace for Activation functions
namespace functions
{
    /* 
    Function to pass a value to sigmoid function
    parameter : x - >  value to pass through
    return type : double
    */
    double sigmoid(const double &x)
    {
        return ( 1/(1+std::exp(-1*x)) );
    }

    /* 
    Function to pass a value to fast sigmoid function
    parameter : x - >  value to pass through
    return type : double
    */

    double fast_sigmoid(const double &x)
    {
        return ( x/(1 + std::fabs(x)) );
    }

    /* 
    Function to pass a value to sigmoid function containing alpha
    parameter : x - >  value to pass through, value of alpha in the formula
    return type : double
    */
     double sigmoid_alpha(const double &x,const double &alpha)
    {
        return (0.5 * (x * alpha / ( 1 + std::fabs( x * alpha) ) ) + 0.5);
    }
    /* 
    Function to pass a value to softplus function
    parameter : x - >  value to pass through
    return type : double
    */

    double softplus(const double &x)
    {
        return (std::log(1+std::exp(x)));
    }

   /* 
    Function to pass a value to nami_max function
    Note : this function is experimental
    parameter : x - >  value to pass through
    return type : double
    */
    double nami_max(const double &x)
    {
        return (std::exp(x)/1 + softplus(x));
    }

}

// Namespace for array based operations
namespace array
{
    
    
    /*
    *

    * Function Name : average

    * Description : find average from a STORAGE element on particular axis

    * Parameters : X - > the STORAGE element
    *               axis - >  the axis to perform average on COL or ROW

    * Return : average

    * Function Version : 0.0.0

    *
    */
    data::STORAGE average(const data::STORAGE &X,const bool &axis)
    {
        double sum;
        double average;
        
        int row,col;

        // If average of columns in required
        if(axis == COL)
        {
            auto result = matrix::create(X[0].size(),1);
            for(col=0;col<X[col].size();col++)
            {
                sum=average=0;
                for(row=0;row<X.size();row++)
                {
                       sum+=X[row][col];
                }
                average = sum/row;
                result[col][0] = average;
                
            }
            return result;
        }

        // If average of rows is required
        else if(axis == ROW)
        {
            auto result = matrix::create(X.size(),1);
            for(row=0;row<X.size();row++)
            {
                 sum=average=0;
                for(col=0;col<X[row].size();col++)
                {
                       sum+=X[row][col];
                }
                average = sum/col;
                result[row][0] = average;
               
            }

            return result;
        }
        
        
    }
     /*
    *

    * Function Name : Maximum

    * Description : find maximume value from a STORAGE element

    * Parameters : X - > the STORAGE element

    * Return : average

    * Function Version : 0.0.0

    *
    */

    double maximum(const data::STORAGE &X)
    {
        double max = 0;
        for(auto row:X)
        {
            for(auto col:row)
            {
                if(col > max) max = col;    
            }
        }

        return max;
    }
    
    /*
    *

    * Function Name : sum

    * Description : find the sum of the elements in the STORAGE

    * Parameters : X - > the STORAGE element

    * Return : sum

    * Function Version : 0.0.0

    *
    */
    double sum(const data::STORAGE &X)
    {
        double sum = 0;
        for(auto row:X)
        {
            for(auto col:row)
            {
                sum+=col;
            }
        }

        return sum;
    }

   /*
    *

    * Function Name : raise_power

    * Description : raise the exponent power of each value in the STORAGE

    * Parameters : X - > the STORAGE element
    *            : pow - > the exponent power to raise

    * Return : result (STORAGE) the array with power raised of each value inside it.

    * Function Version : 0.0.0

    *
    */

   data::STORAGE raise_power(const data::STORAGE &X,const double pow)
   {
       
       auto result = matrix::create(X.size(),X[0].size());
       
       for(int i=0;i<X.size();i++)
       {
           for(int j=0;j<X[i].size();j++)
           {
            result[i][j] = std::pow(X[i][j],pow);
           }
       }

       return result;
   }

   /*

    * Function Name : contains

    * Description : find if an array contains a particular value

    * Parameters : X - > the STORAGE element
    *            : value - >  The value to look for
    * 
    * Return : result -> true  - >  if it contains , false - > if is doesn't

    * Function Version : 0.0.0

    *
    */

   bool contains(const data::STORAGE &X, const double value)
   {
       
       
       // For each element in the array
       for(auto col:X)
       {
           for(auto element:col)
           {
               // If the element is equal to the value
                if(element == value)
                {
                    return true;
                }

           }
       }
       //if the element was not found
       return false;
   }

    /*

    * Function Name : unique

    * Description :find unique values in an array

    * Parameters : X - > the STORAGE element
    * 
    * Return : result -> unique values in an array

    * Function Version : 0.0.0

    *
    */

   data::STORAGE unique(const data::STORAGE &X)
   {
       data::STORAGE result;

       for(auto row:X)
       {
           for(auto element:row)
           {
               if(!contains(result,element))
               {
                   result.push_back({element});
               }
           }
       }

       return result;
     
   }





}


}
