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

#include"Data/DataHandler.hpp"
#include"Neighbor/KMeans.hpp"
#include"Neighbor/Knn.hpp"
#include"Numerical/Numeric.hpp"
#include"Linear/Linear.hpp"


int main()
{

  // Loading data
  auto dataset = cmll::csv::read("Salary.csv");

  auto X = dataset[{3,4,5}].get();
  auto y = dataset[-1].get();
  
  // Creating a KMeans model
  cmll::linear::LinearRegression k;
  k.model(X,y);

  auto y_pred = k.predict(X);
  std::cout<<k.score(y,y_pred);

  return 0;
  
}
