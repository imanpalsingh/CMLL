# CMLL

![CMLL LOGO](Logo.png "Logo")


CMLL : C++'s Machine Learning Library

[![CDNJS](https://img.shields.io/github/license/imanpalsingh/CMLL?logo=CMLL)](https://github.com/imanpalsingh/CMLL/blob/master/LICENSE)
[![CDNJS](https://img.shields.io/badge/coverage-100%25-brightgreen)](#)
[![CDNJS](https://img.shields.io/badge/docs-0%25-red)](#)
[![CDNJS](https://img.shields.io/badge/CMLL-v0.1.0-blue)](#)




## Description

A Machine Learning library build using just standard C++ from scratch. CMLL uses Standard Template Library with C++17 Standards. The computational requirements are also written from roots. File Handling and manipulation tools are also included making it a fully independent library.

## Installation

### Binaries
The precompiled binary for x86 and x64 systems can be found [here](https://github.com/imanpalsingh/CMLL/tree/master/lib).
The includes are available [here](https://github.com/imanpalsingh/CMLL/tree/master/includes).<br>

### Source

The source can be found [here](https://github.com/imanpalsingh/CMLL/tree/master/src). Alternatively the repository can be pulled to load the Visual Studio project for building and debugging.<br>

## Change Logs

<small> For functional level changes, refer to source </small>

<b>Current (version 0.1.0)</b>  :

1) Added new algorithms
    1) Gaussian Naive Bayes Classifier
    2) Multinomial Naive Bayes Classifier
    3) Bernoulli Naive Bayes Classifier

2) Ridge Classifier now supports Multi class classification using One-vs-all technique

3) Added utility checks for Matrices for error handling

4) Faster algorithms, objects are passed by refernce instead of relying on return value optimizations

<b>Version 0.0.3</b>

1) Added new algorithms

    1) Ridge Regression
    2) Ridge regression
    3) KMeans clustering
    
2) Logistic Regression now converges faster using Newton Raphson's method

<b> Version 0.0.2 </b>

1) File Handler now can read file with multi type such as string and numbers. Strings are automatically label Encoded

2) Robust Exceptional Handling 

3) Added New algorithm

   1) K Nearest Neighbors Regressor
   2) K Nearest Neighbors Classifier
   
## Examples

```cpp
/*
* Creating a Ridge Classifier model in CMLL
*/
#include<iostream>
#include<vector>
#include<Linear/Linear.h> // for ridge classifier


int main()
{
    // Sample dataset
    std::vector<std::vector<double>> X = { {10,12,23,123},
                                           {13,15,43,223},
                                           {02,12,72,321},
                                           {1,2,13,402},
                                           {110,112,8,553}
                                          };
    std::vector<std::vector<double>> y = { {0},{1},{0},{1},{0} };
    
    
    //Building the model
    cmll::linear::RidgeClassifier clf;
    clf.model(X,y);
    
    // Predicting
    std::vector<std::vector<double>> yPred(X.size(),std::vector<double>(1)); // variable to store predicted values
    clf.predict(X,yPred);
    
    //Evaluating
    std::cout<<clf.score(y,yPred);
    
    return 0;
}
```

```cpp
/*
* Data loading and preprocessing
*/

#include<iostream>
#include<vector>
#include<Data/handler.h> // For file reading 
#include<utils/Preprocessing.h> // For preprocessing
#include<utils/Utils.h> // for utility checks
#include<exception>

int main()
{
    // Reading a csv file
    cmll::data::Handler Features, Labels;

    cmll::data::read(Features, "Salary_Features.csv");
    cmll::data::read(Labels, "Salary_Labels.csv");

    // Array to store their values
    std::vector<std::vector<double>> X, y;

    Features.values(X);
    Labels.values(y);

    // Clearing Features and Labels as they are no longer required
    Features.clear();
    Labels.clear();

    // Using utility checks to make sure they are safe to be used.

    //Checking if the vectors have Nan values
    if (cmll::utils::check::hasNaN(X) || cmll::utils::check::hasNaN(y))
    {
        std::cout << "Dataset has NaN values!";
        return 0;
    }

    // Checking if X and Y are in correct shapes 
    try
    {
        cmll::utils::check::Xy(X, y); //  throws invalid length if not required length 
    }

    catch (const std::length_error& e)
    {
        std::cout << e.what();
        return 0;
    }


    // Splitting X and y into train and test sets by 80% and 20% ratio
    std::vector<std::vector<double>> XTrain, XTest, yTrain, yTest;
    cmll::preprocessing::split(X, XTrain, XTest, 0.8);
    cmll::preprocessing::split(y, yTrain, yTest, 0.8);

}
```
