/* 
 *
 * This is a test file created for testing the modules
 
 * Author : Imanpal Singh <imanpalsingh@gmail.com>
 
 * Date Created  : FEB_9_20_11_32
 
 * Last modified : MAR_28_20_14_25
 
 * Tested version : 0.0.0
 
 * 
 */

#include<iostream>
#include"utils/defined.hpp"
#include"utils/util.hpp"
#include"Numerical/Numeric.hpp"
#include"Data/DataHandler.hpp"
#include"Linear/linear.hpp"


int main()
{

  // Loading data
  auto dataset = cmll::csv::read("Dataset.csv");

  dataset.insert(0,1);

  // Creating the feature matrix and vector of prediction
  auto X = dataset[cmll::list::range(0,8)].get();
  auto y = dataset[-1].get();
  
  // Creating a Knn Classifier  model
  cmll::linear::RidgeClassifier reg;
  
  std::cout<<"Fitting the model\n";
  //Fitting the model
  reg.model(X,y);
  
  std::cout<<"Predicting\n";
  //Predicting
  auto y_pred = reg.predict(X);

  std::cout<<"Evaluating\n";   
  // Evaluation
  std::cout<<reg.score(y_pred,y);


  return 0;
  
}
