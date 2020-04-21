
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : March 24, 2020
	* Last modified : April 16, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/
#pragma once
/*
	All the includes and functions are to be aligned in the alphabetical order Classes are aligned on basis of inheritance
*/
#include <algorithm>
#include <iostream>

#include "../Numeric/Array.h"
#include "../Utils/Defines.h"
#include "../Numeric/Function.h"
#include "../Numeric/Matrix.h"





/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		Bayes name space : Name space for models that use Bayes theorem 

	*/
	namespace bayes
	{
		/**
		* Class Name : GaussianNaiveBayes

		* Class Description : Class containing functions required for building a Gaussian Naive Bayes model

		* Attributes :

		1) ClassProbability : probability for each class

		2) Mean : The mean of the X

		3) Variance  : Variance of the X

		* Functions :

		1) _mean

		2) _variance

		3) model

		4) predict

		5) predictProbability

		6) score

		*
		*/
		class GaussainNaiveBayes
		{
		protected:

		/**
		   * Function Name :  Mean

		   * Function Description :  Function to find mean of a vector

		   * Parameters :

		   1) x :		   The vector to find mean of

						   Type Expected : std::vector<double>

						   Method of passing : const and by reference

		   * Return :	   double -> mean


		   * Example

			This function is internal and protected


		*/
			double _mean(const std::vector<double>& x) noexcept;
		
		/**
		   * Function Name :  Variance

		   * Function Description :  Function to find Variance of a vector

		   * Parameters :

		   1) x :		   The vector to find variance of

						   Type Expected : std::vector<double>

						   Method of passing : const and  by reference
			
		   2) mean :	   The mean of the vector

						   Type Expected : std::vector<double>

						   Method of passing : const and  by reference

		   * Return :		double -> variance

		   * Example

			This function is internal and protected


		*/
			double _variance(const std::vector<double>& x,const double mean) noexcept;
			
		public:
			
			std::vector<double> ClassProbability;
			data::Storage Mean;
			data::Storage Variance;

		  /**
		   * Function Name :  model

		   * Function Description :  Function to built a Gaussian Naive Bayes  model using Feature Matrix X and vector of prediction y.

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
			   #include<bayes/NaiveBayes.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::bayes::GaussianNaiveBayes clf;

				   clf.model(X,y);

				   return 0;

			   }


		   */
			void model(const data::Storage& X, const data::Storage& y) noexcept;

			/**
			* Function Name :  predict

			* Function Description :  Function to predict using Gaussian Naive Bayes model built by model()

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
				#include<bayes/NaiveBayes.h>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::GaussianNaiveBayes clf;

					clf.model(X,y);

					clf.predict(XTest,result);

					return 0;

				}


			*/
			void predict(const data::Storage& XTest, data::Storage& result); // throws std::runtime_error

			/**
		   * Function Name :  Probability Density function

		   * Function Description :  Function to calculate the probability density for Gaussian distribution

		   * Parameters :

		   1) x :		   The vector to perform the function on

						   Type Expected : std::vector<double>

						   Method of passing : const and  by reference

		   2) probDen :	   The resultant vector

						   Type Expected : std::vector<double>

						   Method of passing :  By reference

		   * Return :		None


		   * Example

			   #include<vector>
			   #include<bayes/NaiveBayes.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::bayes::GaussianNaiveBayes clf;

				   clf.model(X,y)

				   clf.probabilityDensity(x,result);

				   return 0;

			   }


		   */
			void probabilityDensity(const std::vector<double>& x, std::vector<double>& probDen) noexcept;

			/**
			* Function Name :  score

			* Function Description :  Function to calculate accuracy of the Gaussian Naive Bayes model built

			* Parameters :

			1) yPred:		The predicted values by the model

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			2) y:	        The actual values

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference


			* Return :		Score calculated


			* Example

				#include<vector>
				#include<bayes/NaiveBayes.h>
				#include<iostream>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::GaussianNaiveBayes clf;

					clf.model(X,y);

					clf.predict(XTest,y_pred);

					std::cout<<clf.score(yPred,y);

					return 0;

				}


			*/
			double score(const data::Storage& X_test, const data::Storage& y_true) noexcept;
			
		};

		/**
		* Class Name : Multinomial Naive Bayes

		* Class Description : Class containing functions required for building a Multinomial Naive Bayes model

		* Attributes :

		1) Alpha : The smoothing parameter

		2) ClassProbability : Probability for each class

		3) FeatureProbability : Probability for each feature

		* Functions :

		1) model

		2) logProbabilities

		3) predict

		4) score

		*
		*/
		class MultinomialNaiveBayes
		{
		public:

			double Alpha;
			std::vector<double> ClassProbability;
			data::Storage FeatureProbability;

		/**
		   * Constructor Name : MultinomialNaiveBayes[Parameterized]

		   * Constructor Description :  Constructor to load value of alpha

		   * Parameters :

		   1) Alpha			The smoothing

							Type Expected : double

							Method of passing :  constant


		   * Example

			   #include<vector>
			   #include<bayes/NaiveBayes.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::bayes::MultinomialNaiveBayes clf(1.0);

				   return 0;

			   }


		   */
			MultinomialNaiveBayes(const double alpha = static_cast<double>(defaults::ALPHA));

		/**
		   * Function Name :  model

		   * Function Description :  Function to built a Multinomial Naive Bayes  model using Feature Matrix X and vector of prediction y.

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
			   #include<bayes/NaiveBayes.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::bayes::MultinomialNaiveBayes clf;

				   clf.model(X,y);

				   return 0;

			   }


		   */
			void model(const data::Storage& X, const data::Storage& y) noexcept;

			/**
			* Function Name :  log Probabilities

			* Function Description :  Function to calculate the log of probabilities for Xtest

			* Parameters :

			1) XTest :		The test set feature matrix

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			2) result :		The probabilities

							Type Expected : cmll::data::Storage

							Method of passing :  by reference

			* Return :		None

			* Example

				#include<vector>
				#include<bayes/NaiveBayes.h>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::MultinomialNaiveBayes clf;

					clf.model(X,y);

					clf.logProbabilities(XTest,result);

					return 0;

				}


			*/
			void logProbabilities(const data::Storage& XTest, data::Storage& result) noexcept;

			/**
			* Function Name :  predict

			* Function Description :  Function to predict using Multinomial Naive Bayes model built by model()

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
				#include<bayes/NaiveBayes.h>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::MultinomialNaiveBayes clf;

					clf.model(X,y);

					clf.predict(XTest,result);

					return 0;

				}


			*/
			void predict(const data::Storage& XTest, data::Storage& result); //throws std::runtime_error

			/**
			* Function Name :  score

			* Function Description :  Function to calculate accuracy of the Multinomial Naive Bayes model built

			* Parameters :

			1) yPred:		The predicted values by the model

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			2) y:	        The actual values

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference


			* Return :		Score calculated


			* Example

				#include<vector>
				#include<bayes/NaiveBayes.h>
				#include<iostream>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::MultinomialNaiveBayes clf;

					clf.model(X,y);

					clf.predict(XTest,y_pred);

					std::cout<<clf.score(yPred,y);

					return 0;

				}


			*/
			double score(const data::Storage& X_test, const data::Storage& y_true) noexcept;

		};

		/**
		* Class Name :  Bernoulli Naive Bayes

		* Class Description : Class containing functions required for building a  Bernoulli Naive Bayes model

		* Attributes :

		1) Alpha : The smoothing parameter @inhertied

		2) ClassProbability : Probability for each class @inherited

		3) FeatureProbability : Probability for each feature @ingerited

		* Functions :

		1) model @overriden

		2) logProbabilities @iverriden

		3) predict @overriden

		4) score @inherited

		*
		*/
		class BernoulliNaiveBayes : public MultinomialNaiveBayes
		{
		public:

		/**
		   * Constructor Name : BernoulliNaiveBayes[Parameterized]

		   * Constructor Description :  Constructor to load value of Alpha

		   * Parameters :

		   1) Alpha		The smoothing

							Type Expected : double

							Method of passing :  constant


		   * Example

			   #include<vector>
			   #include<bayes/NaiveBayes.h>
			   #include<iostream>

			   int main()
			   {

				   cmll::bayes::BernoulliNaiveBayes clf(1.0);

				   return 0;

			   }


		   */
			BernoulliNaiveBayes(const double alpha = static_cast<double>(defaults::ALPHA));
			
		/**
		   * Function Name :  model

		   * Function Description :  Function to built a Bernoulli Naive Bayes  model using Feature Matrix X and vector of prediction y.

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
			   #include<bayes/NaiveBayes.h>

			   int main()
			   {
				   // vector creation and element adding here

				   cmll::bayes::BernoulliNaiveBayes clf;

				   clf.model(X,y);

				   return 0;

			   }


		   */
			void model(const data::Storage& X, const data::Storage& y) noexcept;

			/**
			* Function Name :  log Probabilities

			* Function Description :  Function to calculate the log of probabilities for Xtest

			* Parameters :

			1) XTest :		The test set feature matrix

							Type Expected : cmll::data::Storage

							Method of passing :  constant and by reference

			2) result :		The probabilities

							Type Expected : cmll::data::Storage

							Method of passing :  by reference

			* Return :		None

			* Example

				#include<vector>
				#include<bayes/NaiveBayes.h>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::BernoulliNaiveBayes clf;

					clf.model(X,y);

					clf.logProbabilities(XTest,result);

					return 0;

				}


			*/
			void logProbabilities(const data::Storage& XTest, data::Storage& result) noexcept;

			/**
			* Function Name :  predict

			* Function Description :  Function to predict using Bernoulli Naive Bayes model built by model()

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
				#include<bayes/NaiveBayes.h>

				int main()
				{
					// vector creation and element adding here

					cmll::bayes::BernoullilNaiveBayes clf;

					clf.model(X,y);

					clf.predict(XTest,result);

					return 0;

				}


			*/
			void predict(const data::Storage& XTest, data::Storage& result);
		};

	}
}


