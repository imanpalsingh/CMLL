
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : March 27, 2020
	* Last modified : April 19, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/
#pragma once

#include <algorithm>
#include <functional>
#include <iostream>

#include "../utils/Defines.h"
#include "../Numeric/Function.h"
#include "../Numeric/Matrix.h"
#include "../Numeric/Array.h"

/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		neighbors name space : For algorithms using neighbors approach
	*/

	namespace neighbors
	{

	/**
		* Class Name : KnnRegressor

		* Class Description : Class containing functions required for building a Knn regression model

		* Attributes :

		1) K : - Neighbors to consider

		2) Metric : The distance metric

		3) P : Order

		4) X : Feature Matrix

		5) y : Vector of prediction

		* Functions :

		1) _calculateDistances

		2) _distancesFromX

		3) _neighborKSort

		4) model

		5) predict

		6) rss

		7) score

		8) tss

		*
		*/
		class KnnRegressor
		{
		protected:

			distanceMetric Metric;

			/**
			   * Function Name :  Calculate Distance

			   * Function Description :  Function to Calculate distances of each observation of Xtest to each observation in X

			   * Parameters :

			   1) XTest :		The test set feature matrix

							   Type Expected : cmll::data::Storage

							   Method of passing :  constant and by reference

			   2) result :		The predicted values

							   Type Expected : cmll::data::Storage

							   Method of passing :  by reference

			   * Return :	   None


			   * Example

				This function is internal and protected


			*/
			void _calculateDistances(const data::Storage& Xtest, data::Storage& result) noexcept;
			
		/**
		   * Function Name :  Neighbor K Sort

		   * Function Description :  Function to Sort the calculated distances and Keep only first K distances

		   * Parameters :

		   1) distances	:		The calculated distances

								Type Expected : cmll::data::Storage

								Method of passing : const and by reference

		   2) sortedKDistances :	   The distance of the point from  each observation X

									   Type Expected : cmll::data::Storage

									   Method of passing : By reference

		   * Return :	   None


		   * Example

			This function is internal and protected


		*/
			void _neighborKSort(const data::Storage& distances, data::Storage& sortedKDistances) noexcept;

		/**
		   * Function Name :  Distances From X

		   * Function Description :  Function to distances of a new set of points from the Feature matrix

		   * Parameters :

		   1) x :		   The new set of points

						   Type Expected : std::vector<double>

						   Method of passing : const and by reference
		
		   2) result :	   The distance of the point from  each observation X 

						   Type Expected : std::vector<double>

						   Method of passing : By reference

		   * Return :	   None


		   * Example

			This function is internal and protected


		*/
			void _distancesFromX(const std::vector<double>& x, std::vector<double>& result) noexcept;

		public:

			data::Storage X, y;
			std::size_t K;
			double P;
			


			std::function<double(const std::vector<double>&, const std::vector < double>&,const double&)> DistanceCal;

		/**
		   * Constructor Name : KnnRegressor[Parameterized]

		   * Constructor Description :  Constructor to load values

		   * Parameters :

		   1) K				Number of nearest neighbors to consider

							Type Expected : double

							Method of passing :  constant and by reference

		   2) metric		Distance metric

							Type expected distanceMetrix

							Method of passing : const and by reference

		   3) p			    The value p for order

							Type Expected : double

							Method of passing :  constant and by reference
		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::neighbors::KnnRegressor r1(4,cmll::neighbors::distanceMetric::EUCLEDIAN);

				   return 0;

			   }


		   */
			KnnRegressor(const std::size_t& k = static_cast<std::size_t>(defaults::K), const distanceMetric& metric = distanceMetric::EUCLEDIAN, const double &p = static_cast<double>(defaults::P));

			/**
			* Function Name :  model

			* Function Description :  Function to built a Knn regression model using Feature Matrix X and vector of prediction y.

			* Parameters :

			1) X :			The feature matrix

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			2) y :		    Vector of prediction

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			* Return :		None


			* Example

				#include<vector>
				#include<Neighbors/Knn.h>

				int main()
				{
					// vector creation and element adding here

					cmll::neighbors::KnnRegressor l1;

					l1.model(X,y);

					return 0;

				}


			*/
			void model(const data::Storage& X, const data::Storage& y) noexcept;

		/**
		   * Function Name :  predict

		   * Function Description :  Function to predict using Knn regression model built by model()

		   * Parameters :

		   1) XTest :		The test set feature matrix

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference

		   2) result :		The predicted values

						   Type Expected : cmll::data::Storage

						   Method of passing :  by reference

		   * Return :		None

		   * Throws    :  std::runtime_error : If the coefficient vector is empty

		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KnnRegressor r1;

				   l1.model(X,y);

				   l1.predict(XTest,result);

				   return 0;

			   }


		   */
			void predict(const data::Storage& XTest, data::Storage& result); // throws std::runtime_error

		/**
		   * Function Name :  RSS

		   * Function Description :  Function to calculate Residual Sum of Squares of the model

		   * Parameters :

		   1) yPred:		The predicted values by the model

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference

		   2) y:	        The actual values

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference


		   * Return :		Residual sum of squares calculated


		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KnnRegressor r1;
				   
				   l1.model(X,y);

				   l1.predict(XTest,y_pred);

				   std::cout<<l1.rss(yPred,y);

				   return 0;

			   }


		   */
			double rss(const data::Storage& y_pred, const data::Storage& y_true) noexcept;

		/**
		   * Function Name :  score

		   * Function Description :  Function to calculate R^2 score of the Knn Regression model built

		   * Parameters :

		   1) yPred:		The predicted values by the model

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference

		   2) y:	        The actual values

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference


		   * Return :		R^2 score calculated


		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KnnRegressor r1;

				   l1.model(X,y);

				   auto yPred = l1.predict(XTest);

				   std::cout<<l1.score(yPred,y);

				   return 0;

			   }


		   */
			double score(const data::Storage& y_pred, const data::Storage& y_true) noexcept;

		/**
		  * Function Name :  TSS

		  * Function Description :  Function to calculate Total Sum of Squares of the model

		  * Parameters :

		  1) y:	        The actual values

						  Type Expected : cmll::data::Storage

						  Method of passing :  constant and by reference


		  * Return :		Total sum of squares calculated


		  * Example

			  #include<vector>
			  #include<Neighbors/Knn.h>
			  #include<iostream>

			  int main()
			  {
				  // vector creation and element adding here

				  cmll::neighbors::KnnRegressor r1;

				  std::cout<<l1.tss(y);

				  return 0;

			  }


		  */
			double tss(const data::Storage& y) noexcept;

		};
		/**
		* Class Name : KnnClassifier

		* Class Description : Class containing functions required for building a Knn Classifier model

		* Attributes :

		1) K : - Neighbors to consider @inherited

		2) Metric : The distance metric @inherited

		3) P : Order @inherited

		4) X : Feature Matrix @inherited

		5) y : Vector of prediction @inherited

		* Functions :

		1) _calculateDistances @inherited

		2) _distancesFromX @inherited

		3) _neighborKSort @inherited

		4) model @inherited

		5) predict @overriden

		6) rss @protectedScoped

		7) score @overriden

		8) tss @protectedScoped

		*
		*/
		class KnnClassifier : public KnnRegressor
		{
		protected:
			
			/*
				In a classification setting, rss and tss are not required
			*/

			using KnnRegressor::rss;
			using KnnRegressor::tss;

		public:

		/**
		   * Constructor Name : KnnClassifierr[Parameterized]

		   * Constructor Description :  Constructor to load values

		   * Parameters :

		   1) K				Number of nearest neighbors to consider

							Type Expected : double

							Method of passing :  constant and by reference
			
			2) metric		Distance metric

							Type expected distanceMetrix

							Method of passing : const and by reference

			3) p			The value p for order
							
							Type Expected : double

							Method of passing :  constant and by reference



		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::neighbors::KnnClassifier r1(4,cmll::neighbors::distanceMetric::EUCLEDIAN);

				   return 0;

			   }


		   */
			KnnClassifier(const std::size_t& k = static_cast<std::size_t>(defaults::K), const distanceMetric& metric = distanceMetric::EUCLEDIAN, const double& p = static_cast<double>(defaults::P));

			
		/**
		   * Function Name :  predict

		   * Function Description :  Function to predict using Knn classifier model built by model()

		   * Parameters :

		   1) XTest :		The test set feature matrix

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference

		   2) result :		The predicted values

						   Type Expected : cmll::data::Storage

						   Method of passing :  by reference

		   * Return :		None

		   * Throws    :  std::runtime_error : If the coefficient vector is empty

		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KnnClassifier r1;

				   l1.model(X,y);

				   l1.predict(XTest,result);

				   return 0;

			   }


		   */
			void predict(const data::Storage& XTest, data::Storage& result); // throws std::runtime_error
		
		/**
		   * Function Name :  score

		   * Function Description :  Function to calculate Accuracy of  model built

		   * Parameters :

		   1) yPred:		The predicted values by the model

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference

		   2) y:	        The actual values

						   Type Expected : cmll::data::Storage

						   Method of passing :  constant and by reference


		   * Return :		Accuracy calculated


		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KnnClassifier r1;

				   l1.model(X,y);

				   auto yPred = l1.predict(XTest);

				   std::cout<<l1.score(yPred,y);

				   return 0;

			   }


		   */
			double score(const data::Storage& y_pred, const data::Storage& y_true) noexcept;
		};

	/**
		* Class Name : K Means

		* Class Description : Class containing functions required for implementing K Means Clustering

		* Attributes :

		1) K : - Neighbors to consider @inherited

		2) Metric : The distance metric @inherited

		3) P : Order @inherited

		4) X : Feature Matrix @inherited

		5) y : Vector of prediction @ProtectedScoped

		* Functions :

		1) _calculateDistances @inherited

		2) _centroidUpdate

		3) _cluster

		4) _distancesFromX @inherited

		5) _initializeCentroids

		6) _neighborKSort @inherited

		7) model @overriden

		8) predict @overriden

		9) rss @protectedScoped

		10) score @inherited

		11) tss @protectedScoped

		*
		*/
		class KMeans : public KnnClassifier
		{
		protected:
			/*
				Vector of prediction is not required in an unsupervised learning setting
			*/
			using KnnClassifier::y;
			
		/**
		   * Function Name :  Centroid update

		   * Function Description :  Function to update the centroids after new assignment of cluster

		   * Parameters :

		   1) x :				    The new set of points

								    Type Expected : std::vector<double>

									Method of passing : const and by reference

		   2) centroidIndex :	    The index of the Centroid to update

									Type Expected : std::ptrdiff_t

									Method of passing : const and By reference

		   * Return :	   None


		   * Example

			This function is internal and protected


		*/
			void _centroidUpdate(const std::vector<double>& x, const std::ptrdiff_t& centroidIndex);

		/**
		   * Function Name :  cluster

		   * Function Description :  Function to assign a set ob observations to different clusters

		   * Parameters :

		   1) X :				    The new set of observations

									Type Expected : cmll::data::Storage

									Method of passing : const and by reference

		   2) updateCentroids :	    if the new assignment of cluster should update the centroids (yes during model building process)

									Type Expected : cmll::neighbors::selection

									Method of passing : const and By reference

		   * Return :	   None


		   * Example

			This function is internal and protected


		*/
			void _cluster(const data::Storage&,const selection& updateCentroids);

		/**
			   * Function Name :  initializeCentroids

			   * Function Description :  Function to initialize initial centroids

			   * Parameters :

			   1) centroidValues :		The centroid values to set as initial

										Type Expected : cmll::data::Storage

										Method of passing : const and by reference

			   * Return :	   None


			   * Example

				This function is internal and protected


			*/
			void _initializeCentroids(const data::Storage& centroidValues);
			
			
		public:
			
			// Centroid numbering
			data::Storage Centroids;

			// Clusters the observations are assigned to
			data::Storage CentroidsAssigned;

			// Clusters the observations of XTest (in predict()) are assigned to
			std::vector<double> Prediction;


		/**
		   * Constructor Name : KMEansr[Parameterized]

		   * Constructor Description :  Constructor to load values

		   * Parameters :

		   1) K				Number of nearest neighbors to consider

							Type Expected : double

							Method of passing :  constant and by reference

			2) metric		Distance metric

							Type expected distanceMetrix

							Method of passing : const and by reference

			3) p			The value p for order

							Type Expected : double

							Method of passing :  constant and by reference



		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::neighbors::KMeans r1(4,cmll::neighbors::distanceMetric::EUCLEDIAN);

				   return 0;

			   }


		   */
			KMeans(const std::size_t& k = static_cast<std::size_t>(defaults::K), const distanceMetric& metric = distanceMetric::EUCLEDIAN, const double& p = static_cast<double>(defaults::P));

		/**
			* Function Name :  model

			* Function Description :  Function to built clusters and assign the data points to K clusters

			* Parameters :

			1) X :				The feature matrix

								Type Expected : cmll::data::Storage

								Method of passing :  constant and by reference

			2) resetCentroids:  If set to 'yes' The default centroids will be set every time model is called
								If set to no once centroids are assigned only clustering will take place

								Type Expected : cmll::neighbors::selection

								Method of passing : const and By reference


			* Return :		None


			* Example

				#include<vector>
				#include<Neighbors/Knn.h>

				int main()
				{
					// vector creation and element adding here

					cmll::neighbors::KMeans l1;

					l1.model(X);

					return 0;

				}


			*/
			void model(const data::Storage& X,const selection& resetCentroids = selection::YES);

		/**
		   * Function Name :  predict

		   * Function Description :  Function to assign clusters to new observations

		   * Parameters :

		   1) XTest :			The test set feature matrix

								Type Expected : cmll::data::Storage

								Method of passing :  constant and by reference

		   2) result :			The predicted values

								Type Expected : cmll::data::Storage

								Method of passing :  by reference

		   3) updateCentroid :  Whether to update the original centroid values ( select yes for batch learning, no for regular prediction)

								Type Expected : cmll::neighbors::selection

								Method of passing : const and By reference

		   * Return :		None

		   * Throws    :  std::runtime_error : If the Centroid vectors are empty vector is empty

		   * Example

			   #include<vector>
			   #include<Neighbors/Knn.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::neighbors::KMeans r1;

				   l1.model(X,y);

				   l1.predict(XTest,result);

				   return 0;

			   }


		   */
			void predict(const data::Storage& XTest, data::Storage& result, const selection& updateCentroid = selection::NO);
		};
	}
}