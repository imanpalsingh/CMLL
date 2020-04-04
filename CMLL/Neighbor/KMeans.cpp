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

* Date Created  : APR_04_20_10_07
 
* Last modified : APR_04_20_10_07

* Change Logs : 

*
*/



#include"KMeans.hpp"



//Parent namespace
namespace cmll
{
    namespace neighbor
    {

        
        /*
         *

         * Constructor Name : KMeans 
         
         * Description : Function to load user defined values 

         * Parameters : k - >  Number of clusters
         *              p - >  Value of order
         *              distance_metirc - >  Distance metric to use

         * Note : InitialCentroids define which points are to be taken as initial centroids. This process is not random.
         *        By default the first 'K' points will be considered as the centroids. to override this 
         *        Change the InitialCentroid list using the object ( obj.InitialCentroids). 
                  
         * Function Version : 0.0.0

         *
         */
        KMeans::KMeans(const std::size_t &k, const std::size_t p, const short &distance_metric)
        {
            K = k;
            P = p;
            DistanceMetric = distance_metric;
            for(std::size_t i = 0 ; i<k-1;i++)
                InitialCentroids.push_back(i);               
        }

        
        
        
        
        /*
         *

         * Function Name : model
         
         * Description : Function to create user defined clusters and assign data points to the, 

         * Parameters : X -> The feature matrix

         * Return :  0 - successfull 
                  
         * Function Version : 0.0.0

         *
         */
        int KMeans::model(const data::STORAGE &X)
        {
            
            /*
            Model is build on the assumption of that different clusters are distance seperated from each other
            
            By default the first k observations are taken as centroids. To use your own centroid selection
            Change the InitialCentroids attribute. You can use your own random function to create a random InitialCentroids.

            After setting the initial centroids
            For next observations

            Distance from both centroids are calculated
            The distance to centroid which is smaller; the point is assigned to the cluster. and cluster's new centroid is created
            using  [ from i = 0 ; to i = Features ] centrod_xi + new+xi / 2 

            */
            
            
            
            // resizing centeroids 
            Centroids.resize(K,(std::vector<double>(X[0].size())));

            // Resizing to the number of clusters to be formed
            CentroidsAssigned.resize(K);

            //Assuming centroids to be the first data points
            // Storing the centroids
            // Storing the initial assigned clusters
            
           for(std::size_t i = 0; i<K;i++)
           {
               for(std::size_t j = 0; j<X[i].size();j++)
               {
                   Centroids[i][j] = X[i][j];
                   
               }
               CentroidsAssigned[i].emplace_back(i);
           }

          // Assigning observations to clusters and updating centroids
           __cluster__(X,true);
          
        return 0;

        }

        /*
         *

         * Function Name : __distance__calculator__
         
         * Description : Function to calculate distance from a observation to the centroid

         * Parameters : x - >  the observation
         *              centroid - > the single centroid value

         * Return :  sum : the calculated value
                  
         * Function Version : 0.0.0

         *
         */

        double KMeans::__distance_calculate__(const std::vector<double> &x,const std::vector<double> &centroid)
        {
                
                double sum = 0;

                // If metric is euclidean
                if(DistanceMetric == EUCLIDEAN)
                {
                    for(int i=0;i<x.size();i++)
                    {
                        sum += std::pow( (x[i]- centroid[i]),2);
                    }
                    sum = std::sqrt(sum);
                }

                // If metric is Manhattan
                else if(DistanceMetric == MANHATTAN)
                {
                    for(int i=0;i<x.size();i++)
                    {
                        sum += std::abs(x[i]- centroid[i]);
                    }
                }

                // If metric is Minkowski
                else if(DistanceMetric ==  MINKOWSKI)
                {
                    for(int i=0;i<x.size();i++)
                    {
                        sum += std::pow( (x[i]- centroid[i]),P);
                    }
                    sum = std::pow(sum,(1/P));
                }

                else
                {
                    std::cout<<"<In funcition[protected] KMeans::__distance_euclidean__> Error : Distance metric not legal\n";
                }
             return sum;   
        }

        /*
         *

         * Function Name : __centroid_update__
         
         * Description : Function to update the centroid value

         * Parameters : x - >  the observation
         *              centroid - > the single centroid value

         * Return : new_centroid - >  The new updated centroid
                  
         * Function Version : 0.0.0

         *
         */
        std::vector<double> KMeans::__centroid_update__(const std::vector<double> &x,const std::vector<double> &centroid)
        {
            
            // New centroid
            std::vector<double> new_centroid(centroid.size());

            
            // Updating centroid (last_centroid + new_observation)/2
            for(int i=0;i<x.size();i++)
            {
                new_centroid[i] = ((x[i]  + centroid[i])/2);
            }

        return new_centroid;
        }

        /*
         *

         * Function Name : __cluster__
         
         * Description : Function to assign observations to clusters

         * Parameters : X - > Feature matrix
         *              update_centroid - whether to update centroids while assigning or not

         * Return : None
                  
         * Function Version : 0.0.0

         *
         */
        void KMeans::__cluster__(const data::STORAGE &X,const bool &update_centroid)
        {
             /*
             Assigns cluster based on the closet distance to the cluster
             the update_centroid when set to false , reconfigures/recalculates the cluster to create a new cluster
             */           
           
           std::vector<double> temp(K);

            int min_index;

           // Assigning to the centroids for rest of the observations
           for(std::size_t i=K; i<X.size();i++)
           {
               
               // For each centroid
               for(std::size_t centroid=0;centroid<K;centroid++)
               {
                  // Calculate the distances
                   temp[centroid] =  __distance_calculate__(X[i],Centroids[centroid]);
                  
               }
                
                // finding the index of minimum cluster distance
                min_index = std::distance(temp.begin(), std::min_element(temp.begin(),temp.end()));
                
                if(update_centroid)
                {
                CentroidsAssigned[min_index].emplace_back(i);
                Centroids[min_index] = __centroid_update__(Centroids[min_index],X[i]); 
                }

                else
                {
                    Predictions.push_back({(double)min_index});
                }
                
           }
        }

         /*
         *

         * Function Name : predict
         
         * Description : Function to predict which cluster new observations belong to

         * Parameters : X - > Feature matrix
         *              update_original - whether to update centroids while assigning or not (false by default)

         * Return : None
                  
         * Function Version : 0.0.0

         *
         */
         data::STORAGE KMeans::predict(const data::STORAGE &X,const bool &update_original)
         {
            
            /*
            The nearest distance to the centroid decides what centroid the new observation belongs too

            To make the model learn with new datasets. Set the update_original to true (false by default).
            this can also be used to cluster a huge dataset when all of the dataset cannot be loaded in the memory

            If the update_original is set to false, the cluster it would be assigned to will be returned and the model
            will not update centroids.
            */
            
            __cluster__(X);
             return Predictions;
         }


    }
}

