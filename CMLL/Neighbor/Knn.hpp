/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for algorithms using Neighbor distance method

*   Description : This File includes the classifiers that use Neighbor distance method
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : MAR_27_20_18_14
 
* Last modified : MAR_28_20_15_25

* Change Logs : 

*
*/


#ifndef NEIGHBOR_HPP
#define NEIGHBOR_HPP


#include "../utils/defined.hpp"


//Parent namespace
namespace cmll
{
    namespace neighbor
    {
        /*
        *

        * Class Name : KnnRegressor

        * Description : Class for creation of Knn model for regression and also prediction using the model.

        * Functions : model(),predict(), __neighbors__(), distance_calculate(), TSS(), RSS(), score()

        * Class version : 0.0.0

        *
        */

       class KnnRegressor
       {
           
           protected:
            /*
            Function to find K nearest neighbors
            Note : Function uses Eucleadian distance currently
            Parameters : x - > observation
            return type : std::vector<std::pair<double,double>>
           */
           std::vector<std::pair<double,double>> __neighbors__(const std::vector<double> &x);
           
           
           
           public:

           // Constructor to load defaults
           KnnRegressor(const std::size_t &k=DEFAULT_K, const short &distance_metric=EUCLIDEAN, const double &p = DEFAULT_P);

            // Storing variables
           data::STORAGE Feature_matrix;
           data::STORAGE Vector_of_prediction;

           // Distance metric selection
           short Distance_metric;

           // Order value
           double P;

           // Number of neighbors to consider (K)
           std::size_t K;

            /*
            Function to create a KNN model.
            Note : The function only stores The feature matrix and vector of prediction.
            Parameters : X -> Feature matrix
                         y - > Vector of prediction
            return type : int
           */
           int model(const data::STORAGE &X, const data::STORAGE &y);

           /*
            Function to predict using KNN technique
            Parameters : X_test - > Test feature matrix
            return type : STORAGE
           */
           data::STORAGE predict(const data::STORAGE &X_test);
            
            /*
             Function to calculate distances from observations in Feature matrix to a new observation matrix
             Parameters : x - > The new observation
             return type : std::vector<double>
            */
           std::vector<double> distance_calculator(const std::vector<double> &x);

           /* Function to calculate score for the model built
              Parameters - > y_pred - > the predicted values (STORAGE element)
                           y_test - > the actual values (STORAGE element)
            return type : double
            */
            double score(const data::STORAGE &y_pred,const data::STORAGE &y_true);

            /* Function to calculate RSS (Residual sum of squares) for the model built
  
 
            Parameters - > y_pred - > the predicted values (STORAGE element)
                             y_test - > the actual values (STORAGE element)
            return type : double
            */
            double RSS(const data::STORAGE &y_pred,const data::STORAGE &y_true);
   
            /* Function to calculate TSS (Total sum of squres) for the model built
                    Parameters - > y_pred - > the predicted values (STORAGE element)
                             y_test - > the actual values (STORAGE element)
            return type : double
            */
            double TSS(const data::STORAGE &y_true);

        };

        /*
        *

        * Class Name : KnnClassifier

        * Description : Class for creation of Knn model for classification and also prediction using the model.

        * Functions : model() [inherited], predict()[overriden], __neighbors__()[inherited], distance_calculate()[inherited], TSS()[forbidden], RSS()[forbidden], score()[overriden]

        * Class version : 0.0.0

        *
        */

        class KnnClassifier : public KnnRegressor
        {
                
                private:
                // Forbidding the use of RSS and TSS in a classification setting
                using KnnRegressor::RSS;
                using KnnRegressor::TSS;

                public:

                /*
                Function to predict using KNN technique
                Parameters : X_test - > Test feature matrix
                return type : STORAGE
                */
                data::STORAGE predict(const data::STORAGE &X_test);

               /*
               Function to calculate score of the model built
               Note :  This function uses standard Indicator function.
               return type : double
               */
               double score(const data::STORAGE &X_test,const data::STORAGE &y_true);
                
        };
    }
}

#endif