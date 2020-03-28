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

* File version : 0.0.1

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_50
 
* Last modified : MAR_28_20_18_23

* Change Logs : 
        1) Date : 28-03-20 Time : 18:22
        Added new class RidgeRegression
            # Added new function model()

        2) Date : 22-03-2020 Time : 19:56

        [Issue #1] No convergence warning 
        # Fixed : Added a convergence warning for logistic regression

        3) Date : 22-03-20 Time : 14:05
            
            LinearRegression class (0.0.0 - > 0.0.1)
            # Linear Regression Now fully implements ELS method
            # New functions in LinearRegression RSS(),TSS(), score()

        4) Date : 21-03-2020 Time : 23:03
        
        Function LogisticRegression::model (0.0.1 - > 0.0.2)
        # Function logistic regression now creates a lesser dimensional identity matrix (more information at function line comments)
        # Logistic regression now is even more faster than 0.0.1
        # Large Memory issue is also solved.

        ## Added a new function score()

        5) Date : 20-03-2020 Time : 22:23
        
        Function LogisticRegression::model (0.0.0 - > 0.0.1) 
        # Function now uses matrix::inverse_diagonal() instead of matrix::diagonal for calculating inverse of diagonal matrix 'W'
        # LogisticRegression::model now is faster at fitting


*

*/


/* Imports */

#include<iostream>
#include "Linear.hpp"
#include "../Numerical/Numeric.hpp"
#include "../utils/defined.hpp"
#include "../utils/util.hpp"



/* FUNCTIONS */




namespace cmll

{


    namespace linear
    {



        /*
        *

        * Function Name : Linear

        * Description : Function to find coefficient matrix according to least squares method

        * Parameters : X - > Feature Matrix
                    : y - >  Vector of prediction

        * Return : (int) 0 - > successful
                        -1 - >  Error

        * Function Version : 0.0.2

        * Goals of Implementation  :  Expect Multithreading being used in this function in version 1.0

        *
        */

        int LinearRegression::model(const data::STORAGE &X,const data::STORAGE &y)
        {
            /*

            The function uses method ELS
            The method is named on the basis of book it is taken from

            ELS is from Element of Statistical Learning by Trevor Hastie and more (Second Edition)
            */

            /*
            ELS Method 

            ELS method uses normalized equation as given in the book.
            Page number 12, equation number 2.6

            B_hat = (X_T*X)_(-1)*X_T*y

            */

            // Sotring the number of features
            Features = X[0].size();
            std::size_t observations = X.size();

            if(observations!=y.size())
                {
                    std::cout<<"<In function LinearRegression::model> Error :  X.size()!=y.size(). Not feasible to perform calculations.";
                    return -1;
                }

            /* Initializations */ //
            auto X_T = matrix::create(Features,observations);
            auto X_T_mul_y = matrix::create(Features,1);
            auto X_T_mul_X = matrix::create(Features,observations);
            auto X_T_mul_X_inverse  = matrix::create(Features,observations);


            try
            {
                // X transpose 
                X_T = matrix::transpose(X);

                // X^{T}*y
                X_T_mul_y = matrix::multiply(X_T,y);

                // X^{T}*X
                X_T_mul_X = matrix::multiply(X_T,X);

                // (X^{T}*X)^{-1}
                X_T_mul_X_inverse = matrix::inverse(matrix::LU(X_T_mul_X));

                // ( (X^{T}*X)^{-1})X^{T}y
                Coefficients = matrix::multiply(X_T_mul_X_inverse,X_T_mul_y);
            }

            catch(...)
            {
                return -1;
            }
                
            return 0;
            
        }

        /*
        *

        * Function Name : predict

        * Description : Function to predict the value using Linear Regression

        * Parameters : X_test - > Feature test set Matrix

        * Return : result - >  Set of predicted values

        * Function Version : 0.0.1

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

            // Making sure that the X_test has required number of features
            else if(!util::is_legal(X_test,Features))
            {
                std::cout<<"<IN function LinearRegression::predict> Error : The model was trained with "<<Features<<" features but predict received different number of features\n";
                return result;
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

        * Function Name : RSS

        * Description : Function to Calculate Residual sum of squares.

        * Parameters : y_pred - > the predicted values
                    : y_true - > The actual values

        * Return : result - >  RSS value
        * Function Version : 0.0.0

        *
        */

        double LinearRegression::RSS(const data::STORAGE &y_pred,const data::STORAGE &y_true)
        {
            /*
            * This funcion uses the following formula for calculating RSS
            * 
            * RSS = sum_of_((y_true - y_pred)^ 2)
            */
            
            // Variable to store RSS
            double RSS = 0;
            
            // Distributed process of calculating RSS

            auto RSS_mat = matrix::subtract(y_true,y_pred);
            auto RSS_SQUARE_arr = array::raise_power(RSS_mat,2);
            RSS = array::sum(RSS_SQUARE_arr);

            return RSS;

        }

        /*
        *

        * Function Name : TSS

        * Description : Function to Calculate Total sum of squares.

        * Parameters : y_pred - > the predicted values
                    : y_true - > The actual values

        * Return : result - >  TSS value

        * Function Version : 0.0.0

        *
        */

        double LinearRegression::TSS(const data::STORAGE &y_true)
        {
            /*
            * This funcion uses the following formula for calculating TSS
            * 
            *  TSS = sum_of_((y_true - y_true.mean())^2)
            */

            // Variable to store RSS
            double TSS = 0;
            
            // Distributed process of calculating RSS

            auto TSS_mat = matrix::subtract(y_true,array::average(y_true,array::COL));
            auto TSS_SQUARE_mat = array::raise_power(TSS_mat,2);
            TSS  = array::sum(TSS_SQUARE_mat);

            return TSS;

        }


        /*
        *

        * Function Name : score

        * Description : Function to find score (R^2 score)

        * Parameters : y_pred - > the predicted values
                    : y_true - > The actual values

        * Return : result - >  score val

        * Function Version : 0.0.0

        *
        */
        double LinearRegression::score(const data::STORAGE &y_pred,const data::STORAGE &y_true)
        {
            
            /*
            * This function uses the following formula for calculating R^square
            * R^2 = 1 - RSS/TSS
            * 
            */

            auto RS = 1 - (RSS(y_pred,y_true)/(TSS(y_true)));
            return RS;

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

        * Function Version : 0.0.3

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
            
            
            
            
            // Storing number of features
            Features = X[0].size();
            std::size_t observations = X.size();

            if(observations!=y.size())
            {
                std::cout<<"<In function LogisticRegression::model> Error :  X.size()!=y.size(). Not feasible to perform calculations.";
                return -1;
            }


            /* Intializing */
            
            // Defining Initial B as all zeros initially
            auto B = matrix::create(Features,1,0);

            
            //Defining the p matrix
            auto p = matrix::create(observations,1);

            
            // Defining the 1 - p matrix
            auto p_neg = matrix::create(observations,1);

            
            //defining the W matrix
            data::STORAGE W = matrix::create(observations,1);
        
            // Iteration index to keep track of iterations
            int iteration_index=0;

            
            /* 
            * Variable pre initializations to reduce time complexity
            *  Information on each variable is given at time of assignment, refer to assignment level comments 8
            */
            auto B_hat = matrix::create(observations,1);

            
            data::STORAGE W_inverse = matrix::create(observations,1);

            
            data::STORAGE y_minus_p = matrix::create(observations,1);

            
            data::STORAGE w_inverse_mul_y_minus_p = matrix::create(observations,1);

            
            data::STORAGE z = matrix::create(observations,1);

            
            data::STORAGE X_T = matrix::create(Features,observations);

            
            data::STORAGE X_T_mul_W = matrix::create(Features,observations);

        
            data::STORAGE X_T_mul_W_mul_X = matrix::create(Features,Features);

            
            data::STORAGE X_T_mul_W_mul_X_inverse = matrix::create(Features,Features);

            
            data::STORAGE X_T_mul_W_mul_X_inverse_mul_X_T = matrix::create(Features,observations);
            
            
            data::STORAGE X_T_mul_W_mul_X_inverse_mul_X_T_mul_W = matrix::create(Features,observations);

            

            
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

            // Checking if solution actually converged   [as reported in issue #1]
            if(std::abs(array::maximum(grad)) <= Tolerance)
            {
                std::cout<<"<In function LogisticRegression::model> Warning : The solution did not converge at 'Maximum_iterations : "<<Maximum_iterations<<"\n";
            }

            // Saving the final calculated coefficients
            Coefficients = B;
            
        }


        /*
        *

        * Function Name : predict

        * Description : Function to predict labels for new feature matrix

        * Parameters : X_test - > the new feature matrix to predict values on

        * Note :  This function assumes correct shape of the matrix which also includes condition of atleast aXN matrix, where a >= 2 and N is any Natural number.

        * Function Version : 0.0.1

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
                std::cout<<"<IN function LogisticRegression::predict> Error : The coefficients are required to be calculated first\n";
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

        double LogisticRegression::score(const data::STORAGE &y_pred,const data::STORAGE &y_true)
        {
            
        //Checking for equal number of observations
            if(y_pred.size()!=y_true.size())
            {
                std::cout<<"<In function LogisticRegression::score> Error : y_pred.size() ! = y_true.size().\n";
                return -1;
            }


            //Variable to hold the score
            double accuracy;

            // For each predicted and real value
            for(int i=0;i<y_pred.size();i++)
            {
                for(int j=0;j<y_pred[0].size();j++)
                {
                    if(y_pred[i][j] == y_true[i][j])
                    {
                    //calculate number of times the model was correct
                        accuracy++; 
                    }
                }
            }

            //number of times the model was correct/total observations
            return (accuracy/y_pred.size());
        }

        /*
        *

        * Constructor Name : predict

        * Description : Constructor to load the defaults

        * Parameters : lambda : the value of lambda (default 1)

        * Constructor Version : 0.0.0

        *
        */
        RidgeRegression::RidgeRegression(const double &lambda)
        {
            Lambda = lambda;
        }

        /*
        *

        * Function Name : model

        * Description : Function to find coefficient matrix 

        * Parameters : X - > Feature Matrix
                    : y - >  Vector of prediction

        * Return : (int) 0 - > successful
                        -1 - >  Error

        * Function Version : 0.0.2

        * Goals of Implementation  :  Expect Multithreading being used in this function in version 1.0

        *
        */
        int RidgeRegression::model(const data::STORAGE &X,const data::STORAGE &y)
        {
            
            /*
            * This model is based on the linear regression (See LinearRegression::model() for information about model) with an additional penalty for the coefficients.
            * 
            * The residual sum of squares for ridge regression is given by
            *               
            *               RSS(λ) = (y-Xβ)^{T}(y-Xβ) + λβ^{T}β
            * 
            * β can be calculated using
            * 
            *               β = (X^{T}X+λI)^{-1}X^{T}y
            * 
            * Alternatively if a linear regression model is built. THe ridge regression coefficients can be found using 
            *                   
            *               β = β_LinearRegression/(1+λ) 
            */        

            // Sotring the number of features   
            Features = X[0].size();
            std::size_t observations = X.size();
            if(observations!=y.size())
                {
                    std::cout<<"<In function LinearRegression::model> Error :  X.size()!=y.size(). Not feasible to perform calculations.";
                    return -1;
                }

            /* Initializations */ //
            auto X_T = matrix::create(Features,observations);
            auto X_T_mul_X = matrix::create(Features,observations);
            auto X_T_mul_y = matrix::create(Features,1);
            auto lambda_I = matrix::create_diagonal(Features,Lambda);
            auto X_T_mul_X_plus_lambda_I = matrix::create_diagonal(Features);
            auto X_T_mul_X_plus_lambda_I_inverse = matrix::create_diagonal(Features);

            try
            {
                // X transpose 
                X_T = matrix::transpose(X);

                // X^{T}*y
                X_T_mul_y = matrix::multiply(X_T,y);

                // X^{T}*X
                X_T_mul_X = matrix::multiply(X_T,X);

                // (X^{T}*X) + λI
                X_T_mul_X_plus_lambda_I = matrix::sum(X_T_mul_X,lambda_I);

                // ( (X^{T}*X) + λI )^{-1}
                X_T_mul_X_plus_lambda_I_inverse = matrix::inverse(matrix::LU(X_T_mul_X_plus_lambda_I));

                // β = ( (X^{T}*X) + λI )^{-1} * (X^{T}*y)
                Coefficients = matrix::multiply(X_T_mul_X_plus_lambda_I_inverse,X_T_mul_y);
            }

            catch(...)
            {
                return -1;
            }

        }





}
}
