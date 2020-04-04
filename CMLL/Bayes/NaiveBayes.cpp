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

* Date Created  : MAR_24_20_11_04
 
* Last modified : MAR_24_20_11_05

* Change Logs : None

*
*/

#include"NaiveBayes.hpp"



//Parent namespace
namespace cmll
{

   //Namespace for algorithms using bayes rule
    namespace bayes
    {
        
        /*
         *

         * Function Name : model

         * Description : Function to build Naive Byes model

         * Parameters : X - > Feature matrix Matrix
                      : y - > VEctor of prediction

         * Return : 0 - Successful build ; -1 - error

         * Note : The function by default assumes the distribution of the feature matrix to be Gaussian. More distributions will be added in future versions

         * Function Version : 0.0.0

         *
         */
        int NaiveBayes::model(const data::STORAGE &X, const data::STORAGE &y)
        {
            /*
            The function uses the bayes theorem for calculating p(y,X);
                                __
            P(y|x1,...xn) ~ p(y)||P(xi|y)

            where p(xi|y) is calculated using

            P(xi|y) =            1               |   (xi - mean)^2  |
                              --------      * exp|    ------------  |
                               ______            |     2*variance   |
                             _/2*pi*variance
            
            
            The distribution is assumed to be Gaussian. More options will be available in future versions.

            */

           // Checking for size consistency 
           if(X.size()!=y.size())
            {
               std::cout<<"<In function LogisticRegression::score> Error : X.size() ! = y.size().\n";
               return -1;
            }

            //Calculating number of Features
            std::size_t features = X[0].size();

            // Gathering unique targets
            auto classes = array::unique(y);

            // Calculating number of unique targets
            std::size_t classes_num = classes.size();

            // vector of STORAGE to store subset of original data based on targets
            std::vector<data::STORAGE> split(classes_num);

            // Resizing the Mean according to number of features
            Mean.resize(classes.size(),std::vector<double>(features));

            // Resizing the Variance according to number of features
            Variance.resize(classes.size(),std::vector<double>(features));

            // Resizing the Variance according to number of classes
            Class_probability.resize(classes_num);

            // Vector to store number of occurrence of classes
            std::vector<double> occurrence(classes_num,0);

            
            for(int i=0;i<X.size();i++)
            {
                 // Seperating based on classes
                 split[y[i][0]].emplace_back(X[i]);

                 // Incrementing the occurrence of the class
                 occurrence[y[i][0]] +=1;

                 // updating the class probability 
                 Class_probability[y[i][0]] = occurrence[y[i][0]]/X.size();
            }

          // Calculating the mean and the variance of independent features
           for(std::size_t class_type=0; class_type<split.size();class_type++)
           {
              // Transposing to directly obtain the column for faster processing 
              auto mat = matrix::transpose(split[class_type]);

                  // For each column
                   for(std::size_t j=0;j<mat.size();j++)
                   {
                      Mean[class_type][j]= __mean__(mat[j]);
                      Variance[class_type][j] = __variance__(mat[j], Mean[class_type][j]);

                   }
                   
           }

           
        }

         /*
         *

         * Function Name : __mean__

         * Description : Function to find mean of a vector

         * Parameters : X - > Vector to find mean of

         * Return : double : The mean
         * 
         * Function Version : 0.0.0

         *
         */
         double  NaiveBayes::__mean__(const std::vector<double> &X)
         {
             /* The function accepts the vector to be a column of which is mean is to be find */
             
             double _sum= 0;
             for(std::size_t i=0; i<X.size();i++)
             {
                _sum+=X[i]; 
             }

             return (_sum/X.size());
             
        }

         /*
         *

         * Function Name : __variance__

         * Description : Function to find variance of a vector

         * Parameters : X - > Vector to find mean of

         * Return : double : variance
         * 
         * Function Version : 0.0.0

         *
         */
         double  NaiveBayes::__variance__(const std::vector<double> &X,const double &mean)
         {
             
             /* The function accepts the vector to be a column of which is variance is to be find */
             double _sum= 0;
             for(std::size_t i=0; i<X.size();i++)
             {
                _sum += std::pow((X[i] - mean),2);
             }

             return (_sum/X.size());
             
        }
        /*
         *

         * Function Name : calculate_probability

         * Description : Function to calculate P(xi|y) using Gaussian probability density function

         * Parameters : X - > Vector as a independent column

         * Return : std::vector<double> : The probability of each class P(xi|y) where y are the different classes
         * 
         * Function Version : 0.0.0

         *
         */ 

         std::vector<double> NaiveBayes::calculate_probability(const std::vector<double> &x)
         {
            
            // Creating space for storing probability for each class
            std::vector<double> product(Mean.size(),1);
            
            // For each class 
            for(std::size_t class_type=0;class_type<Mean.size();class_type++)
            {
               // Calculate probability
               for(std::size_t feature=0;feature<x.size();feature++)
               {
                  product[class_type]*=functions::Gaussian_density(x[class_type],Mean[class_type][feature],Variance[class_type][feature]);
               }
             
            } 
           
            return product;                                 
         }

         /*
         *

         * Function Name : predict

         * Description : Use the model built to predict for new observations

         * Parameters : X - > X_test set feature matrix

         * Return : STORAGE : the predicted values
         * 
         * Function Version : 0.0.0

         *
         */ 


        data::STORAGE NaiveBayes::predict(const data::STORAGE &X)
        {
           
           // the final predicted values to be stored in
           data::STORAGE result;
           
           //  P(y) for each observation
           std::vector<double> res(Class_probability.size());
           // Checking for size consistency 

            // Calculating probability for each observation in ( p(x1|y)
           for(std::size_t observation=0;observation<X.size();observation++)
           {
              auto prob = calculate_probability(X[observation]);
             
              
           double max = 0;

           //P(xi|y)*p(y)
           for(std::size_t i=0;i<prob.size();i++)
           {
                res[i] = prob[i]*Class_probability[i];
                
           }

            //                 __
            // y = argmax( p(y)||P(xi|y)) 
            for(int j=0;j<res.size();j++)
               {
                  if(res[j] > max) max = j;
               }
   
            
          result.push_back({max});

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
      double NaiveBayes::score(const data::STORAGE &y_pred,const data::STORAGE &y_true)
      {
    
         //Checking for equal number of observations
         if(y_pred.size()!=y_true.size())
         {
            std::cout<<"<In function NaiveBayes::score> Error : y_pred.size() ! = y_true.size().\n";
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