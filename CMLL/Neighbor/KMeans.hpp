/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : File containing declarations for algorithms using Neighbor distance method

*   Description : This File includes the unsupervised algorithms that use Neighbor distance method
*
*/

/*
*

* Project version : 0.0.0

* File version : 0.0.0

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : APR_04_20_10_01
 
* Last modified : APR_04_20_10_01

* Change Logs : 

*
*/


#ifndef KMEANS_HPP
#define KMEANS_HPP

#include"../utils/defined.hpp"
#include"../utils/util.hpp"
#include"../Numerical/Numeric.hpp"
#include<algorithm>
#include<cmath>
#include<vector>
#include<iostream>


// Parent namespace
namespace cmll
{
    namespace neighbor
    {

        /*
        *

        * Class Name : Kmeans

        * Description : Class for creation of clusters using unsupervised learning model K-Means clustering

        * Functions : model(), predict()

        * Class version : 0.0.0

        *
        */
        class KMeans
        {
            protected:

            /*
            Function to calculate distance between observation and centroid
            Parameters : x -> The observation
                       : centroid - > A single centoid
            return type : double
            */
            double __distance_calculate__(const std::vector<double>&,const std::vector<double>&);

            /*
            Function to update the centroid after each iteration during the model process
            Parameters : x -> The observation
                       : centroid - > A single centoid
            return type : std::vector<double>
            */
            std::vector<double> __centroid_update__(const std::vector<double>&,const std::vector<double>&);

            /*
            Function to assign data points into a cluster
            Parameters : x -> The observation
                       : update_centroid :  Whether to update the centroid (true when building the model)
            return type :void
            */
            void __cluster__(const data::STORAGE &X,const bool &update_centroid=true);
                
            public :

            //Number of clusters
            std::size_t K;

            // Value for p
            std::size_t P;

            // distance metric
            short DistanceMetric;

            // Initial centroid assmption (index number list)
            std::vector<std::size_t> InitialCentroids;

            // vector to store centroid coordinates
            data::STORAGE Centroids;
            
            // Vector to stored assigned clusters
            data::STORAGE CentroidsAssigned;

            // Predicted values
            data::STORAGE Predictions;


            /*
            Contructor to load defaults
            */
            KMeans(const std::size_t &K=DEFAULT_K, const std::size_t p=DEFAULT_P, const short &distance_metric = EUCLIDEAN);

            /*
            Function to create K clusters from the provided dataset
            Parameters : X - > the feature matrix
            */
           int model(const data::STORAGE &X);

            /*
            Function to assign new values to the clusters
            Parameters : X - > the feature matrix
                       : update_original -> true->> update the original centroids and keep learning (Learning on the fly)
                                            false->> Predict using already build clusters and do not modify them
            */
           data::STORAGE predict(const data::STORAGE &X,const bool &update_original=false);

        };

    }
}


#endif