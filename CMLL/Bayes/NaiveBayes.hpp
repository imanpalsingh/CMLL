/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for algorithms using Bayes algorithm

*   Description : This File includes the classifiers that use Bayes algorithm
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_24_20_11_04
 
* Last modified : MAR_26_20_19_43

* Change Logs : 

*
*/


#ifndef NB_HPP
#define NB_HPP

#include "../utils/defined.hpp"


// Global namespace
namespace cmll
{
    
    // Namespace for algorithms using bayes theorem
    namespace bayes
    {
        
        /*
        *

        * Class Name : NaiveBayes

        * Description : Class for creation of Naive Bayes model , prediction using naive bayes model

        * Functions : model() predict()

        * Class version : 0.0.1

        *
        */
        class NaiveBayes
        {
            protected:

            /*
            Special Helper function for calculation of mean from a vector
            Parameters :  X - > vector to find mean of
            return type : double
            */
            double __mean__(const std::vector<double> &X);
            /*
            Special Helper function for calculation of variance from a vector
            Parameters :  X - > vector to find variance of
            return type : double
            */
            double __variance__(const std::vector<double> &X,const double &mean);
            
            public :

            // calculated mean
            data::STORAGE Mean;

            // calculated variance
            data::STORAGE Variance;

            // Class probability
            std::vector<double> Class_probability;


            /*
            Function to create a Naive Bayes model.
            Note : Currently the function assumes the distributions to be Gaussian.
            Expected Binomial and multinomial distribution in future version 
            Parameters : X -> Feature matrix
                         y - > Vector of prediction
            return type : int
            */
            int model(const data::STORAGE &X,const data::STORAGE &y);

            /*
            Function to predict using a Naive Bayes model built already.
            Note : Currently the function assumes the distributions to be Gaussian.
            Expected Binomial and multinomial distribution in future version 
            Parameters : X ->Test Feature matrix
            return type : STORAGE
            */
            data::STORAGE predict(const data::STORAGE &X);

            /*
            Function to find the probability of independent features using the probability density 
            Note : Currently the function assumes the distributions to be Gaussian.
            Expected Binomial and multinomial distribution in future version 
            Parameters : X ->Test Feature matrix column (x^{T})
            return type : std::vector<double>
            */            
            std::vector<double> calculate_probability(const std::vector<double> &x);

            /*
             Function to calculate score of the model built
             Note :  This function uses standard Indicator function.
             return type : double
            */
            double score(const data::STORAGE &y_pred,const data::STORAGE &y_true);
        };
    }
}

#endif