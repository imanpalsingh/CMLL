
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : February 8, 2020
	* Last modified : April 19, 2020

	* Change logs (.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/

#include<iostream>

#include "Knn.h"

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
		/*
			Linear Regressor class members
		*/
		
		void KnnRegressor::_calculateDistances(const data::Storage& XTest, data::Storage& distances) noexcept
		{
			/*
				For each test observation distances from all observations in Feature Matrix X are calculated by calling _distancesFromX()
			*/
			
			for (data::Storage::size_type observation = 0; observation < XTest.size(); ++observation)
			{
				_distancesFromX(XTest[observation], distances[observation]);
			}
		}

		void KnnRegressor::_distancesFromX(const std::vector<double>& x, std::vector<double>& result) noexcept
		{
			/*
				For the observation x, distance from each observation in Feature Matrix X is calculated using a distance metric function
			*/
			for (data::Storage::size_type row = 0; row < X.size(); ++row)
			{
				result[row] = DistanceCal(X[row], x, 0);
			}
		}

		void KnnRegressor::_neighborKSort(const data::Storage& distances, data::Storage& sortedKDistances) noexcept
		{
			/*
				The distances now calculated are sorted. Then first K distances are kept 
			*/
			
			std::vector<double> indexes(distances[0].size());
			for (data::Storage::size_type row = 0; row < distances.size(); ++row)
			{
				for (std::vector<double>::size_type innerRow = 0; innerRow < indexes.size(); ++innerRow)
				{
					indexes[innerRow] = static_cast<double>(innerRow);
				}


				std::stable_sort(indexes.begin(), indexes.end(), [&](double index1, double index2) {return distances[row][static_cast<std::vector<double>::size_type>(index1)] < distances[row][static_cast<std::vector<double>::size_type>(index2)]; });
				
				indexes.resize(K);

				sortedKDistances[row] = indexes;

				indexes.resize(distances[0].size());
			}
		}



		KnnRegressor::KnnRegressor(const std::size_t& k, const distanceMetric& metric, const double& p)
		{
			/*
				Constructor to load defaults values for K - the number of neighbors to consider, the distance metric and value of order p for minkowski distance metric
			*/
			K = k;
			Metric = metric;
			P = p;

			if (Metric == distanceMetric::EUCLEDIAN)
			{
				DistanceCal = functions::distance::euclidean;
			}

			else if (Metric == distanceMetric::MANHATTAN)
			{
				DistanceCal = functions::distance::manhattan;
			}

			else if (Metric == distanceMetric::MINKOWSKI)
			{
				DistanceCal = functions::distance::minkowski;
			}

		}

		void KnnRegressor::model(const data::Storage& X, const data::Storage& y) noexcept
		{
			/*
				Since this algorithm is a instance based learning, X and Y are required at time of prediction
				Note :  The X and y should be in correct order or undefined behavior may occur. Run cmll::utils::checks::.. before
			*/
			
			this->X = X;
			this->y = y;
		}

		void  KnnRegressor::predict(const data::Storage& XTest, data::Storage& result) //throws std::runtime_error
		{
			/*
				The steps followed by the function are as follows

				1) Check if X and Y are defined . If not throw std::runtime_error
				2) For every observation in the test set , find distances from each observation in X
				3) For every observation sort the distances and keep the first K distances
				4) For each observation assign  mean of the labels of the first K distances

				Note :  The XTest and result should be in correct order or undefined behavior may occur
			*/

			try
			{
				if (X.size() == 0 || y.size() == 0) throw std::runtime_error("<In function cmll::neighbors::KnnRegressor>Error :  Model is not built yet. Use model() to fit the model()");
				
				data::Storage distances(XTest.size(), std::vector<double>(X.size()));

				_calculateDistances(XTest, distances);

				data::Storage KlabelsIndexes(XTest.size(), std::vector<double>(K));

				_neighborKSort(distances, KlabelsIndexes);

				for (data::Storage::size_type row = 0; row < KlabelsIndexes.size(); ++row)
				{
					double mean = 0;
					for (std::vector<double>::size_type col = 0; col < KlabelsIndexes[row].size(); ++col)
					{
						mean += y[static_cast<data::Storage::size_type>(KlabelsIndexes[row][col])][0];
					}
					result[row][0] = mean / K;
				}
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << e.what() << '\n';
			}


		}
		double KnnRegressor::rss(const data::Storage& y_pred, const data::Storage& y_true) noexcept
		{
			/*
				This function uses the following formula for calculating RSS
				RSS = sum_of_((y_true - y_pred)^ 2)
			*/

			data::Storage difference(y_true.size(), std::vector<double>(1));


			matrix::subtraction(y_true, y_pred, difference);

			array::power(difference, 2);

			return array::sum(difference);


		}

		double KnnRegressor::score(const data::Storage& y_pred, const data::Storage& y_true) noexcept
		{
			/*
				This function uses the following formula for calculating R^square
				R^2 = 1 - RSS/TSS
			 */
			return (1 - (rss(y_pred, y_true) / (tss(y_true))));
		}

		double KnnRegressor::tss(const data::Storage& y) noexcept
		{
			/*
				This function uses the following formula for calculating TSS
				TSS = sum_of_((y_true - y_true.mean())^2)
			*/

			data::Storage difference(y.size(), std::vector<double>(1));
			data::Storage yCopy = y;


			double mean = array::average(y);
			array::subtract(yCopy, mean);
			array::power(yCopy, 2);

			return array::sum(yCopy);
		}

		/*
			Knn classifier class members
		*/

		KnnClassifier::KnnClassifier(const std::size_t& k, const distanceMetric& metric, const double& p) : KnnRegressor(k,metric,p)
		{
			/*
				Default values are passed to base class's constructor
			*/
		}

		void KnnClassifier::predict(const data::Storage& XTest, data::Storage& result) //throws std::runtime_error
		{
			/*
				The steps followed by the function are as follows

				1) Check if X and Y are defined . If not throw std::runtime_error
				2) For every observation in the test set , find distances from each observation in X
				3) For every observation sort the distances and keep the first K distances
				4) For each observation assign  mode of the labels of the first K distances

				Note :  The XTest and result should be in correct order or undefined behavior may occur
			*/

			try
			{
				if (X.size() == 0 || y.size() == 0) throw std::runtime_error("<In function cmll::neighbors::KnnRegressor>Error :  Model is not built yet. Use model() to fit the model()");

				data::Storage distances(XTest.size(), std::vector<double>(X.size()));
				data::Storage::size_type classes = array::unique(y);
				std::vector<double> occurrence;

				_calculateDistances(XTest, distances);

				data::Storage KlabelsIndexes(XTest.size(), std::vector<double>(K));

				_neighborKSort(distances, KlabelsIndexes);

				for (data::Storage::size_type row = 0; row < KlabelsIndexes.size(); ++row)
				{
					occurrence.resize(classes);
					for (std::vector<double>::size_type col = 0; col < KlabelsIndexes[row].size(); ++col)
					{
						occurrence[static_cast<std::vector<double>::size_type>(y[static_cast<data::Storage::size_type>(KlabelsIndexes[row][col])][0])]+=1;
					}
					result[row][0] = static_cast<double>(std::distance(occurrence.begin(), std::max_element(occurrence.begin(), occurrence.end())));
					occurrence.clear();
				}
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << e.what() << '\n';
			}

			
		}

		double KnnClassifier::score(const data::Storage& y_pred, const data::Storage& y) noexcept
		{

			/*
				Function uses standard indicator function for calculating accuracy.

				Note :  Y_pred and y are supposed to be in correct order of NX1.
			*/

			double count = 0;
			data::Storage::size_type observation = y.size();

			for (data::Storage::size_type value = 0; value < observation; ++value)
			{
				if (y[value][0] == y_pred[value][0]) ++count;
			}

			return static_cast<double>(count / observation);
		}

		/*
			K Means class members
		*/

		KMeans::KMeans(const std::size_t& k, const distanceMetric& metric, const double& p) : KnnClassifier(k, metric, p)
		{
			/*
				Constructor to assign defaults
				
			*/

		}
		void KMeans::_centroidUpdate(const std::vector<double>& x,const std::ptrdiff_t& centroidIndex)
		{
			/*
				Function to update the centroids

				New centroids = (last_centroid + new_observation )/2
			*/
			for (std::vector<double>::size_type row = 0; row < x.size(); ++row)
			{
				Centroids[centroidIndex][row] = ((x[row] + Centroids[centroidIndex][row]) / 2);
			}
		}

		void KMeans::_cluster(const data::Storage& X,const selection& updateCentroids)
		{
			/*	
				Assigns cluster based on the closeSt distance to the cluster
				the update_centroid when set to false , reconfigures/recalculates the cluster to create a new cluster
             
			*/
			
			std::vector<double> temp(K);
			
			for (data::Storage::size_type row = K; row < X.size(); ++row)
			{
				for (std::size_t centroid = 0; centroid < K; ++centroid)
				{
					temp[centroid] = DistanceCal(X[row], Centroids[centroid],0);
				}

				auto minIndex = std::distance(temp.begin(), std::min_element(temp.begin(), temp.end()));

				if (updateCentroids == selection::YES)
				{
					CentroidsAssigned[minIndex].emplace_back(static_cast<double>(row));
					_centroidUpdate(X[row],minIndex);
				}
				
				else
				{
					Prediction.emplace_back(static_cast<double>(minIndex));
				}
			}
		}
		
		void KMeans::_initializeCentroids(const data::Storage& centroidValue)
		{
			/*
				Initializes default Centroids that is the first K observations in X

				Note :  Be really careful if manual Centroids are to be assigned.

				Assign the Centroids in the Centroids vector and also update Centroid assigned accordingly.
				
			*/
					
			for (data::Storage::size_type row = 0; row < K; ++row)
			{
				for (std::vector<double>::size_type col = 0; col < centroidValue[row].size(); ++col)
				{
					Centroids[row][col] = centroidValue[row][col];
				}

				CentroidsAssigned[row].emplace_back(static_cast<double>(row));
			}
		}
		
		void KMeans::model(const data::Storage& X, const selection& resetCentroids)
		{
			/*
				Function created default centroids if they are not pre defined or if resetCentroids is set to yes
				
				Note : If resetCentroids is set to no. Once the Centroids are calculated they will not be re calculated if model is called on the 
				same object again. This can be useful when assigning different user defined centroids. However clustering of observations will occur
				each time
			*/
			
			if (Centroids.size() == 0 || CentroidsAssigned.size() == 0 || resetCentroids == selection::YES)
			{
				Centroids.resize(K, std::vector<double>(X[0].size()));
				CentroidsAssigned.resize(K);

				_initializeCentroids(X);
			}
			_cluster(X,selection::YES);
		}
		
		void KMeans::predict(const data::Storage& XTest, data::Storage& result, const selection& updateCentroid)
		{
			/*
				Function assigns clusters to the new observations and updates old centroids if updateCentroid is set to yes
			*/
			
			_cluster(XTest, updateCentroid);
			
			for (std::vector<double>::size_type row = 0; row < Prediction.size(); ++row)
			{
				result[row] = { Prediction[row] };
			}
		}
		
	}
}
