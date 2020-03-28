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
#include"Neighbor/KNN.hpp"


int main()
{

  // Loading data
  auto dataset = cmll::csv::read("Dataset.csv");

  // Creating the feature matrix and vector of prediction
  auto X = dataset[cmll::list::range(0,7)].get();
  auto y = dataset[-1].get();
  
  // Creating a Knn Classifier  model
  cmll::neighbor::KnnClassifier clf;
  
  //Fitting the model
  clf.model(X,y);
  
  //Predicting
  auto y_pred = nb.predict(X);
     
  // Evaluation
  std::cout<<nb.score(y_pred,y);

  return 0;
  
}
