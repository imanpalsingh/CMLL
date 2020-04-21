# CMLL
![CMLL LOGO](Logo.png "Logo")


CMLL : C++'s Machine Learning Library

## Description

A Machine Learning library build using just standard C++ from scratch. CMLL uses Standard Template Library with C++17 Standards. The computational requirements are also written from roots. File Handling and manipulation tools are also included making it a fully independent library.

## Installation

### Binaries
The precompiled binary for x86 and x64 systems can be found [here](https://github.com/imanpalsingh/CMLL/tree/master/lib).
The includes are available [here](https://github.com/imanpalsingh/CMLL/tree/master/includes).<br>
For information regarding linking and including refer to the [documentation](#).

### Source

The source can be found [here](https://github.com/imanpalsingh/CMLL/tree/master/src). Alternatively the repository can be pulled to load the Visual Studio project for building and debugging.<br>
More information on bulding from source and debugging can be found in the [documentation](#)

## Change Logs

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
