/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for algorithms using Neighbor distance method

*   Description : This File includes the supervised algorithms that use Neighbor distance method
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


#include<algorithm>
#include<iostream>
#include<map>

#include"../utils/util.hpp"
#include"../Numerical/Numeric.hpp"
#include"Knn.hpp"



//Parent namespace
namespace cmll
{
    namespace neighbor
    {

        
        /*
        *

        * Constructor Name : KnnRegressor

        * Description : Constructor to set parameters for model construction

        * Parameters :  k -> The number of nearest neighbors to consider (default = 4)
                           distance_metric -> The preferred distance metric (deafault = EUCLIDEAN)
                           p - > Order for Minkowski distance_metric (default =2)

        * Constructor Version : 0.0.0

        *
        */
        KnnRegressor::KnnRegressor(const std::size_t &k, const short &distance_metric, const double &p)
        {
            K = k;
            Distance_metric = distance_metric;
            P = p;
        }
        
        
        
        
        /*
         *

         * Function Name : model

         * Description : Function to build Naive Byes model

         * Parameters : X - > Feature matrix Matrix
                      : y - > VEctor of prediction

         * Return : 0 - Successful build ; -1 - error

         * Note : The function by default assumes the structure of matrices to be in legal shapes.
         * 
         * Function Version : 0.0.0

         *
         */
        int KnnRegressor::model(const data::STORAGE &X,const data::STORAGE &y)
        {
            
            /* The Knn model function saves the Feature matrix and vector of prediction upon model creation. Contradictory name, it is actually a 
            instance based algorithm rather than a model based one
            */
            
            //Storing the feature matrix and vector of prediction
            Feature_matrix = X;
            Vector_of_prediction = y;

            return 0;
        }

        /*
         *

         * Function Name : __neighbors__

         * Description : Function to find closest K neighbors and the their label

         * Parameters : x - > Observation 

         * Return : 0 - X_y - > closest K neighbors and the their label
         
         * Note : The function by default assumes the structure of matrices to be in legal shapes.
         
         * Function Version : 0.0.0

         *
         */
        std::vector<std::pair<double,double>> KnnRegressor::__neighbors__(const std::vector<double> &x)
        {
             
            // Vector to store mapping of nearest neighors to their labels
            std::vector<std::pair<double,double> > X_y;

            // Tempeorary vector
            std::vector<double> temp;
            
            // Calculate distance from all the observations in the Feature matrix
            temp = distance_calculator(x);
                
                
            //Creating a keymap for the y
            for(std::size_t index=0;index<Vector_of_prediction.size();index++)
            {
                X_y.push_back({temp[index],Vector_of_prediction[index][0]});
            }
                
            // Sort the distances from close to far
            std::sort(X_y.begin(),X_y.end());
                
            // Resize to only required number of close distances
            X_y.resize(K);
               
            // Removing the extra allocated memory
            X_y.shrink_to_fit();

            return X_y;
        }

        /*
         *

         * Function Name : predict 
         
         * Description : Function to predict for X_test

         * Parameters : X_test- > the X_test

         * Return : STORAGE result : the predicted values
         * 
         * Function Version : 0.0.0

         *
         */
        data::STORAGE KnnRegressor::predict(const data::STORAGE &X_test)
        {
           /*
           Steps of the algorithm

           1) All the data points are loaded into memory (brute force approach currently).
           2) Distances using different distance metric (in Distance_metric) from the new test observation are calculated and stored.
           3) The distances are sorted 
           4) Based on the value of k (in K). The first k values of the sorted distances are kept. Rest are removed from the memory
           5) The mean of the y of the positions determines the predicted value
           */
           
           // Storage vector to store sorted distances
            data::STORAGE result;
           
            // Sum of the labels
            double sum;

            // X mapped to y
            std::vector<std::pair<double,double> > X_y;

            // Finding K nearest neighbors for each observation in test set
            for(std::size_t observation=0;observation<X_test.size();observation++)
            {
                X_y = __neighbors__(X_test[observation]);
            
            //Averaging
            sum = 0;

            for(auto val:X_y)
            {
                sum+=val.second;
            }

            // Storing the result
            result.push_back({sum/K});
                
            }

            return result;
        
        }


        /*
         *

         * Function Name : distance_calculator
         
         * Description : Function to calculate  distances from observations in Feature matrix to a new observation 

         * Parameters : X -> the new observation

         * Return : result : The distances calculated.
                  
         * Function Version : 0.0.0

         *
         */
        std::vector<double> KnnRegressor::distance_calculator(const std::vector<double> &x)
        {
            
            // Variable to store square of the difference between points added upto all featres
            double sum;

            // Vector to store all the distances from the test 
            std::vector<double> distance_unsorted;

            // For each observation (row) in Feature matrix
            for(std::size_t observation=0;observation<Feature_matrix.size();observation++)
            {
                 // Resetting sum for next iteration
                 sum = 0;
                 // Checking for selected metric

                 // If metric is euclidean
                 if(Distance_metric == EUCLIDEAN)
                 {
                 
                        //Setting the sum = 0 fr next observation(row)
                        

                        // For each row
                        for(std::size_t feature=0;feature<Feature_matrix[observation].size();feature++)
                        {
                            //Calculating the sum of square of differences
                            sum += std::pow( (Feature_matrix[observation][feature] - x[feature]),2);
                    
                        }
                        sum = std::sqrt(sum);
                       
                 }
                 
                 // If metric is Manhattan
                 else if(Distance_metric == MANHATTAN)
                 {
                     
                     for(std::size_t feature=0;feature<Feature_matrix[observation].size();feature++)
                        {
                            //Calculating the sum of square of differences
                            sum += std::abs( (Feature_matrix[observation][feature] - x[feature]));
                    
                        }
                        
                 }

                 // If metric is Minkowski
                 else if(Distance_metric == MINKOWSKI)
                 {
                     // For each row
                        for(std::size_t feature=0;feature<Feature_matrix[observation].size();feature++)
                        {
                            //Calculating the sum of square of differences
                            sum += std::pow( (Feature_matrix[observation][feature] - x[feature]),P);
                    
                        }
                        sum = std::pow(sum,(1/P));
                    
                 }

                // Storing the distances calculated
                distance_unsorted.emplace_back(sum);
            }

            return distance_unsorted;

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

        double KnnRegressor::RSS(const data::STORAGE &y_pred,const data::STORAGE &y_true)
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

        double KnnRegressor::TSS(const data::STORAGE &y_true)
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
        double KnnRegressor::score(const data::STORAGE &y_pred,const data::STORAGE &y_true)
        {
    
            /*
            * This function uses the following formula for calculating R^square
            *  R^2 = 1 - RSS/TSS
            * 
            */

            auto RS = 1 - (RSS(y_pred,y_true)/(TSS(y_true)));
            return RS;

        }





        /* KNN CLASSIFIER */
        /*
         *

         * Function Name : predict 
         
         * Description : Function to predict for X_test

         * Parameters : X_test- > the X_test

         * Return : STORAGE result : the predicted values
         * 
         * Function Version : 0.0.0

         *
         */
        data::STORAGE KnnClassifier::predict(const data::STORAGE &X_test)
        {
           
            /*
           Steps of the algorithm

           1) All the data points are loaded into memory (brute force approach currently).
           2) Distances using different distance metric (in Distance_metric) from the new test observation are calculated and stored.
           3) The distances are sorted 
           4) Based on the value of k (in K). The first k values of the sorted distances are kept. Rest are removed from the memory
           5) The mode of the y of the positions determines the predicted value
           */
           
            // Storage vector to store sorted distances
            data::STORAGE result;
           
            // Sum of the labels
            double sum;

            // Store the single result;
            double res;

            // X mapped to y
            std::vector<std::pair<double,double> > X_y;

            // Finding K nearest neighbors for each observation in test set
            for(std::size_t observation=0;observation<X_test.size();observation++)
            {
                X_y = __neighbors__(X_test[observation]);
            
            // Finding mode
            
            
            //List to hold number of occurrences
            std::vector<int> occurrences(array::unique(Vector_of_prediction).size());

            for(auto val:X_y)
            {
                // Counting the number of labels occuring
                occurrences[val.second]+=1;
            }

            // Storing the result
            res = std::distance(occurrences.begin(), std::max_element(occurrences.begin(), occurrences.end()));
            result.push_back({res});
                
            }

            return result;
        
        }
      /*
      *

      * Function Name : score

      * Description : Function to calculate score of the model built

      * Parameters : y_pred - > the predicted values
                     y_test - > the actual values

      * Function Version : 0.0.0

      *
      */
      double KnnClassifier::score(const data::STORAGE &y_pred,const data::STORAGE &y_true)
      {
    
         //Checking for equal number of observations
         if(y_pred.size()!=y_true.size())
         {
            std::cout<<"<In function KnnClassifier::score> Error : y_pred.size() ! = y_true.size().\n";
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

        
    }
}