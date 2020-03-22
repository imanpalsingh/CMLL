/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declaration for call linear model classes

*   Description : This file contains classes decleration for linear models, utilities function and predict methods.
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_15_20_09_50
 
* Last modified : MAR_22_20_14_09

* Change Logs : 

1) Date : 22-03-20 Time : 14:05
  LinearRegression class (0.0.0 - > 0.0.1)
  # Linear Regression Now fully implements ELS method
  # New functions in LinearRegression RSS(),TSS(), score()

2) Date : 21-03-2020 Time : 23:03
   Function LogisticRegression::model (0.0.1 - > 0.0.2)
   # Function logistic regression now creates a lesser dimensional identity matrix (more information at function line comments)
   # Logistic regression now is even more faster than 0.0.1
   # Large Memory issue is also solved.

   ## Added a new function score()

3) Date : 20-03-2020 Time : 22:23
   Function LogisticRegression::model (0.0.0 - > 0.0.1) 
   # Function now uses matrix::inverse_diagonal() instead of matrix::diagonal for calculating inverse of diagonal matrix 'W'
   # LogisticRegression::model now is faster at fitting


*

*
*/






#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "../utils/defined.hpp"





namespace cmll{

  namespace linear
  {

/*
*

* Class Name : LinearRegression

* Description : Class for creation of Linear Regression models, Predicting values.

* Functions : model(), predict()

* Class version : 0.0.1

* Change Log : None

*
*/
class LinearRegression
{
  
    
    public : 

    // STORAGE variable to hold coefficients
    data::STORAGE Coefficients;


    /* Functions */

    /*
    Function to construct the supervised learning model for Linear Regression 
    This function can build model in only one was (currently)
     Method : ELS - > Taken from Elements of Statistical learning Book (deployed)
  
    The coefficients calculated are stored in coefficients STORAGE element

    Parameters - > Feature matrix X 
                   Prediction matrix/vector y
    return type : int -> status of model built (-1 for error)
    */
    int model(data::STORAGE,data::STORAGE);

    /* Function to use the model build to predict for X_test 
       Function uses the coeffcients build by the 'model()' to predict for new values
       Note : Building of model is required before predicting values
 
       Parameters - > STORAGE element to perform prediction on 

       return type - > STORAGE 
    */
    data::STORAGE predict(data::STORAGE);

     /* Function to calculate score for the model built
  
 
       Parameters - > y_pred - > the predicted values (STORAGE element)
                     y_test - > the actual values (STORAGE element)
                     score_type - > type of score to calculate
                                    R^2 score (linear::R_SQUARE)
                                    adjusted R^2 score(Linear::ADJUSTED_R_SQUARE)
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

* Class Name : LogisticRegression

* Description : Class for creation of Logistic Regression models, Predicting values.

* Functions : model() predict()

* Class version : 0.0.0

* Change Log : None

*
*/

class LogisticRegression
{
  
    
  protected:

     /* Function to build multiclass model.
       Note : Building of model is required before predicting values
       Parameters - > Feature matrix X 
                   Prediction matrix/vector y
       return type : int -> status of model built (-1 for error)

       NOTE : this function is still being tested and has not been deployed yet
    */

  int _multiclass_model(data::STORAGE,data::STORAGE);
  
  
  public:

  /* 
  STORAGE element to define the classes. This must be explicitly defined.
  Note :  The ordering of classes matters in this algorithm implementation
  */
  data::STORAGE Classes;

  // Activation function for logistic regression
  short Activation;

  // Max iterations to go for solution to converge
  int Maximum_iterations;

  // Alpha for some activation functions
  short Alpha;

  // Tolerance 
  double Tolerance;

  // Threshold
  double Threshold;

 // To store the calculated coefficients
  data::STORAGE Coefficients;



  // Constructor to load user defined parameters
LogisticRegression(const short &activation=SIGMOID, const int &maximum_iterations=DEFAULT_MAXIMUM_ITERATIONS, const double &threshold=DEFAULT_THRESHOLD,const double &alpha=DEFAULT_ALPHA,const double &tolerance=DEFAULT_TOLERANCE);

  /*
  Function to pass the value predicted by the linear model into a activation function (For list of activation function see namespace 'functions')
  To get a classification value, the linear model's predicted value is fed to an activation function. Then based on the given threshold the 
  classification is done
  Note :  The classifier can only perform Binary classification and the classes 'must' be labelled 0 and 1.
          The function assumes creation of model using model() before running the function. Although might still check for coefficients before applying.
  return type : int
  */
  
 int model(const data::STORAGE &X, const data::STORAGE &y);

 /*
  Function to calculate p(x1;B) based on user defined activation function
  return type : double 
  */
 double logistic_function(const double &val);

 /*
  Function predict for new feature matrix based on coefficients calculated during model creation.
  Note :  This classifier doesn't include the option to fit intercept yet.
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