/* 
 *
 * This is a test file created for testing the modules
 
 * Author : Imanpal Singh <imanpalsingh@gmail.com>
 
 * Date Created  : FEB_9_20_11_32
 
 * Last modified : MAR_26_20_21_30
 
 * Tested version : 0.0.0
 
 * 
 */

#include<iostream>
#include"utils/defined.hpp"
#include"utils/util.hpp"
#include"Numerical/Numeric.hpp"
#include"Linear/Linear.hpp"
#include"Bayes/NaiveBayes.hpp"
#include"Data/DataHandler.hpp"


int main()
{

  //Defining data

    cmll::data::STORAGE X = { {199,14.31,123,13.33},
                            {199,12,2,12},
                            {1,23,556,12},
                            {67,1.1,2.88,121},
                            {123,122,1,34},
                            {12,344,12,12},
                            {23,23,22,12}};
     cmll::data::STORAGE y = { {0},
                            {1},
                            {0},
                            {0},
                            {1},
                            {0},
                            {1}};
  
  // Creating a Naive Bayes Gaussian model
  cmll::bayes::NaiveBayes nb;

  //Fitting the model
   nb.model(X,y);
   std::cout<<"Done modelling\n";

   //Predicting
   auto y_pred = nb.predict(X);
   std::cout<<"Done predicting\n";

   //Evaluating
   std::cout<<nb.score(y_pred,y);
  



}
