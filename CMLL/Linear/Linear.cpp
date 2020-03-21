/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing definition for call linear model classes

*   Description : This file contains classes definition for linear models, utilities function and predict methods.
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_50
 
* Last modified : MAR_21_20_23_35

* Change Logs : 
1) Date : 21-03-2020 Time : 23:03
   Function LogisticRegression::model (0.0.1 - > 0.0.2)
   # Function logistic regression now creates a lesser dimensional identity matrix (more information at function line comments)
   # Logistic regression now is even more faster than 0.0.1
   # Large Memory issue is also solved.

   ## Added a new function score()

2) Date : 20-03-2020 Time : 22:23
   Function LogisticRegression::model (0.0.0 - > 0.0.1) 
   # Function now uses matrix::inverse_diagonal() instead of matrix::diagonal for calculating inverse of diagonal matrix 'W'
   # LogisticRegression::model now is faster at fitting


*

*/


/* Imports */

#include<iostream>
#include<algorithm>


#include "Linear.hpp"
#include "../Numerical/Numeric.hpp"
#include "../utils/defined.hpp"



/* FUNCTIONS */




namespace cmll

{


namespace linear
{

/*
*

* Constructor Name : LinearRegression

* Description : Constructor to set parameters for model construction defined by user

* Parameters : 


* Constructor Version : 0.0.0

*
*/

LinearRegression::LinearRegression(const short &method,const bool &fit_intercept)
{
    //Setting deault method to ELS method
    Method = method;
    Fit_intercept = fit_intercept;
}

/*
*

* Function Name : Linear

* Description : Function to find coefficient matrix according to least squares method

* Parameters : X - > Feature Matrix
             : y - >  Vector of prediction

* Return : (int) 0 - > successful
                -1 - >  Error

* Function Version : 0.0.0

* Goals of Implementation  :  Expect Multithreading being used in this function in version 1.0

*
*/

int LinearRegression::model(data::STORAGE X,data::STORAGE y)
{
    /*

    The function uses two methods ISLR and ELS
    These methods are named on the basis of books they were taken from

    ELS is from Element of Statistical Learning by Trevor Hastie and more (Second Edition)
    ISLR is from Introduction to Statistical Learning by Gareth James and more

    */

   /*
   ELS Method 

   ELS method uses normalized equation as given in the book.
   Page number 12, equation number 2.6

   B_hat = (X_T*X)_(-1)*X_T*y

   */

    
    if(Method ==ELS)
    {
        
        if(Fit_intercept  == true)
        {

            
            X = matrix::subtract(X,array::average(X,array::COL));
            y = matrix::subtract(y,array::average(y,array::COL));

            
        }
        
        
        try
        {
            Coefficients = matrix::multiply(matrix::inverse(matrix::LU(matrix::multiply(matrix::transpose(X),X))),matrix::multiply(matrix::transpose(X),y));
        }

        catch(...)
        {
            return -1;
        }
    }

    /*
    ISLR method

    This method is yet to be tested then will be deployed
    Using this method currently do not cause any change
    */

    else if(Method == ISLR)
    {
        std::cout<<"<In function LinearRegression::model> Error : Method type ISLR will be added in 0.0.1 \n";

    }

    else
    {
        std::cout<<"<In function LinearRegression::model> Error : Method type unkown. Allowed = {ELS,ISLR} \n";
    }
    
    return 0;
    
}

/*
*

* Function Name : predict

* Description : Function to predict the value using Linear Regression

* Parameters : X_test - > Feature test set Matrix

* Return : result - >  Set of predicted values

* Function Version : 0.0.0

*
*/

data::STORAGE LinearRegression::predict(data::STORAGE X_test)
{
    
    data::STORAGE result;

    // Making sure that the model has been created before calling this function
    if(!Coefficients.size())
    {
        std::cout<<"<IN function LinearRegression::predict> Error : The coefficients are required to be calculated first\n";
        
    }
    
    

    else
    {
        

            /* According to ELS the y^hat (predicted) values can be found by the equation
            y_hat = X_test*coefficients
            */
           
            result =  matrix::multiply(X_test,Coefficients);
 
    
       
        

    }

    return result;
    
}



/*
*

* Constructor Name : LogisticRegression

* Description : Constructor to set parameters for model construction

* Parameters :  activation -> The activation function (see 'functions' namespace for list of available functions)
                maximum_iterations -> The maximum number of iterations to converge to a solution
                threshold -> threshold  amount to distinguish between predictions
                alpha -> alpha values being used in activation functions



* Constructor Version : 0.0.0

*
*/
LogisticRegression::LogisticRegression(const short &activation, const int &maximum_iterations, const double &threshold,const double &alpha,const double &tolerance)
{
    Activation = activation;
    Maximum_iterations = maximum_iterations;
    Tolerance = tolerance;
    Alpha = alpha;
    Threshold = threshold;
}

/*
*

* Function Name : logistic_function

* Description : Function to apply the logit function

* Parameters :  val - > the value to perform function on

* return : value after applying the logit function.

* Function Version : 0.0.0

*
*/


double LogisticRegression::logistic_function(const double &val)
{
    if(Activation == SIGMOID)
    {
        return functions::sigmoid(val);
    }

    else if(Activation == FAST_SIGMOID)
    {
        return functions::fast_sigmoid(val);
    }

    else if(Activation == SOFTPLUS)
    {
        return functions::softplus(val);
    }

    else if(Activation == SIGMOID_ALPHA)
    {
        return functions::sigmoid_alpha(val,Alpha);
    }

    else if(Activation == NAMI_MAX)
    {
        return functions::nami_max(val);
    }


    else
    {
        std::cout<<"<In function logistic_function> Error : The given activation function is illegal. Allowed are -> {SIGMOID,FAST_SIGMOID,SIGMOID_ALPHA,SOFTPLUS,NAMI_MAX}.\nDefault function will be used.\n ";
        return functions::sigmoid(val);
    }
    
    
}


/*
*

* Function Name : model

* Description : Function to build a logistic regression model

* Parameters : X - > Feature matrix
               y - > Matrix/vector of prediction

* Return : status -1 -> Error
                   0 - > Successful

* Function Version : 0.0.2

*
*/

int LogisticRegression::model(const data::STORAGE &X, const data::STORAGE &y)
{
    
    /*
    * This model fitting algorithm uses Newton-Raphson method for solving equations.
    * Ability to choose from different methods will be added is future version

    _______________________________________________________________________

     * According to Elements of statistical learning

     "To maximize the log-likelihood, we set its derivatives to zero. These score equations are"
     
                ∂ℓ(β)/∂β = E_{i=1}^{N} xi(yi − p(xi; β)) = 0
     
    "To solve the score equations (4.21), we use the Newton–Raphson algorithm, which requires the second-derivative or Hessian matrix"
    
    * A single Newton update is given by

                β^{new} = B^{old} - H^{-1}.delta

    where H is the Hessian matrix and delta is the gradient


    * "Let y denote the vector of yi values, X the N × (p + 1) matrix of xi values,
      p the vector of fitted probabilities with ith element p(xi; β^{old}) 
      and W a N ×N diagonal matrix of weights with ith diagonal element p(xi; β^{old})(1−p(xi;β^{old}))"

    * Then we have

                        delta =  X^{T}(y-p)
                        H = -X^TWX 
    
    Thus                β =  (X^{T}WX)^{−1}X^{T}Wz
    where               z = Xβ^{old} + W^{−1}(y − p) 
    */
    
    
    
    
    
    if(X.size()!=y.size())
    {
        std::cout<<"<In function LogisticRegression::model> Error :  X.size()!=y.size(). Not feasible to perform calculations.";
        return -1;
    }


    /* Intializing */
    

 

    
   // Defining Initial B as all zeros initially
    auto B = matrix::create(X[0].size(),1,0);

    
    //Defining the p matrix
    auto p = matrix::create(X.size(),1);

    
    // Defining the 1 - p matrix
    auto p_neg = matrix::create(X.size(),1);

    
    //defining the W matrix
    data::STORAGE W = matrix::create(X.size(),1);
   
    // Iteration index to keep track of iterations
    int iteration_index=0;

    
    /* 
    * Variable pre initializations to reduce time complexity
    *  Information on each variable is given at time of assignment, refer to assignment level comments 8
    */
    auto B_hat = matrix::create(X.size(),1);

    
    data::STORAGE W_inverse = matrix::create(W.size(),1);

    
    data::STORAGE y_minus_p = matrix::create(X.size(),1);

    
    data::STORAGE w_inverse_mul_y_minus_p = matrix::create(X.size(),1);

    
    data::STORAGE z = matrix::create(X.size(),1);

    
    data::STORAGE X_T = matrix::create(X[0].size(),X.size());

    
    data::STORAGE X_T_mul_W = matrix::create(X[0].size(),X.size());

   
    data::STORAGE X_T_mul_W_mul_X = matrix::create(X[0].size(),X[0].size());

    
    data::STORAGE X_T_mul_W_mul_X_inverse = matrix::create(X[0].size(),X[0].size());

    
    data::STORAGE X_T_mul_W_mul_X_inverse_mul_X_T = matrix::create(X[0].size(),X.size());
    
    
    data::STORAGE X_T_mul_W_mul_X_inverse_mul_X_T_mul_W = matrix::create(X[0].size(),X.size());

    

    
   // To store gradient
   // Note : this is not used in actual calculation. But to keep track with tolerance
   // This causes delay in computation and will be removed in future versions
    data::STORAGE grad;

    
    do
    {

    
    // helpful variable for h(x)
    B_hat = matrix::multiply(X,B);
    
    
   
    // Creating the p vector
    for(int row=0;row<p.size();row++)
    {
        p[row][0] = logistic_function(B_hat[row][0]);
    }

    
    // Creating the 1 - p vector
    for(int row=0;row<p_neg.size();row++)
    {
        p_neg[row][0] = 1 - logistic_function(B_hat[row][0]);
    }
   
    // Creating the W matrix
    for(int row=0;row<W.size();row++)
    {
         W[row][0]=p[row][0] * p_neg[row][0];
    }

    
    
    
    /*  Calculating z */

   
   // W inverse
   W_inverse = matrix::inverse_diagonal(W,1);

   // y - p 
   y_minus_p = matrix::subtract(y,p);

   // W^{-1} * (y-p)
   w_inverse_mul_y_minus_p = matrix::multiply_diagonal(W_inverse,y_minus_p,0);
   
   // z = X*B + W^{-1} * (y-p) 
   z = matrix::sum(B_hat,w_inverse_mul_y_minus_p);
   
   
   /*  Calculating B^{new} */

   //X transpose
   X_T = matrix::transpose(X);
  
   // X.T*W
   X_T_mul_W = matrix::multiply_diagonal(X_T,W,1);
  
   // X.T*W*X
   X_T_mul_W_mul_X = matrix::multiply(X_T_mul_W,X);

   // Inverse of  X.T*W*X
   X_T_mul_W_mul_X_inverse = matrix::inverse(matrix::LU(X_T_mul_W_mul_X));
  
   // Inverse of X.T*W*X * X.T
   X_T_mul_W_mul_X_inverse_mul_X_T = matrix::multiply(X_T_mul_W_mul_X_inverse,X_T);
  
   // Inverse of X.T*W*X * X.T * W
   X_T_mul_W_mul_X_inverse_mul_X_T_mul_W = matrix::multiply_diagonal(X_T_mul_W_mul_X_inverse_mul_X_T,W,1);
  
   // Inverse of X.T*W*X * X.T * W * z
   B  = matrix::multiply(X_T_mul_W_mul_X_inverse_mul_X_T_mul_W,z);

   // Note : this is not used in actual calculation. But to keep track with tolerance
  // This causes delay in computation and will be removed in future versions
 
  grad = matrix::multiply(matrix::transpose(X),matrix::subtract(y,p));
 
  //Incrementing the iteration_index;
  iteration_index++;


 
} // while the maximum number of iterations are lesser than maximumand tolerance change is not achieved
while((iteration_index<Maximum_iterations) && (std::abs(array::maximum(grad)) < Tolerance));

// Saving the final calculated coefficients
Coefficients = B;
    
}


/*
*

* Function Name : predict

* Description : Function to predict labels for new feature matrix

* Parameters : X_test - > the new feature matrix to predict values on

* Note :  This function assumes correct shape of the matrix which also includes condition of atleast aXN matrix, where a >= 2 and N is any Natural number.

* Function Version : 0.0.0

*
*/
data::STORAGE LogisticRegression::predict(const data::STORAGE &X_test)
{
    // Final predicted labels
    data::STORAGE result;

    std::vector<double> temp;

    // Making sure that the model has been created before calling this function
    if(!Coefficients.size())
    {
        std::cout<<"<IN function LinearRegression::predict> Error : The coefficients are required to be calculated first\n";
        return result;
        
    }
    

    // Multiplying by coefficient matrix
    auto XB = matrix::multiply(X_test,Coefficients);

    // For each element in XB
    for(auto el:XB)
    {
        for(auto le:el)
        {
            //find the p(xi;B)
            auto predict_prob = functions::sigmoid(le);

            
            //if is greater than threshold
            if(predict_prob > Threshold)
            {
                //Then its class 1
                temp.emplace_back(1);
                result.emplace_back(temp);
                temp.clear();
            }

            else
            {   //its class 0
                 temp.emplace_back(0);
                 result.emplace_back(temp);
                 temp.clear();
            }
        }
    }

    return result;
    
}

/*
*

* Function Name : score

* Description : Function to calculate core of the model built

* Parameters : y_pred - > the predicted values
              y_test - > the actual values

* Function Version : 0.0.0

*
*/

double LogisticRegression::score(const data::STORAGE &y_pred,const data::STORAGE &y_test)
{
    
   //Checking for equal number of observations
    if(y_pred.size()!=y_test.size())
    {
        std::cout<<"<In function LogisticRegression::score> Error : y_pred.size() ! = y_test.size().\n";
        return -1;
    }


    //Variable to hold the score
    double accuracy;

    // For each predicted and real value
    for(int i=0;i<y_pred.size();i++)
    {
        for(int j=0;j<y_pred[0].size();j++)
        {
            if(y_pred[i][j] == y_test[i][j])
            {
               //calculate number of times the model was correct
                accuracy++; 
            }
        }
    }

    //number of times the model was correct/total observations
    return (accuracy/y_pred.size());
}

}
}