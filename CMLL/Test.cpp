/* 
 *
 * This is a test file created for testing the modules
 
 * Author : Imanpal Singh <imanpalsingh@gmail.com>
 
 * Date Created  : FEB_9_20_11_32
 
 * Last modified : MAR_19_20_23_30
 
 * Tested version : 0.0.0
 
 * 
 */

#include<iostream>
#include"utils/defined.hpp"
#include"utils/util.hpp"
#include"Numerical/Numeric.hpp"
#include"Linear/Linear.hpp"


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
  // Creating a logistic Regression model

  cmll::linear::LogisticRegression l1;
  l1.model(X,y);

  //Creating test set
  cmll::data::STORAGE X_test = {{1,23,556,12},{67,2.88,1,12}};

  //Testting the model
  auto res =  l1.predict(X_test);
  cmll::out::print(res);



}
