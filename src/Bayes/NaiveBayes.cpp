
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

#include "../../includes/Bayes/NaiveBayes.h"

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
		/*
			Gaussian Naive Bayes class members
		*/

		double GaussainNaiveBayes::_mean(const std::vector<double>& x) noexcept
		{
			/*
				Function iterates through the vcetor x, sums all the elements and returns the ratio with number of elements in x
			*/
			
			double sum = 0;
			
			for (double value : x)
			{
				sum += value;
			}

			return (sum / x.size());
		}

		double GaussainNaiveBayes::_variance(const std::vector<double>& x,const double mean) noexcept
		{
			/*
				Function iterates through all elements of x , adds the square of difference between the value and the mean. Returns the ratio with number of elements in x
			*/
			
			double sum = 0;

			for (double value : x)
			{
				sum += std::pow((value - mean), 2);
			}

			return (sum / x.size());
		}

		void GaussainNaiveBayes::probabilityDensity(const std::vector<double>& x, std::vector<double>& probDen) noexcept
		{
			/*
				For each value in x, the Gaussian probability distribution function is called and value is stored in probDen
			*/
			
			for (data::Storage::size_type classType = 0; classType < Mean.size(); ++classType)
			{
				for (std::vector<double>::size_type feature = 0; feature < x.size(); ++feature)
				{
					probDen[classType] *= functions::gaussian::probabilityDensity(x[classType], Mean[classType][feature], Variance[classType][feature]);
				}

			}
		}

		void GaussainNaiveBayes::model(const data::Storage& X, const data::Storage& y) noexcept
		{
			
			/*
				The function uses the Bayes theorem for calculating p(y,X);
								    __
				P(y|x1,...xn) ~ p(y)||P(xi|y)

				where p(xi|y) is calculated using

				P(xi|y) =            1               |   (xi - mean)^2  |
							      --------  * exp    |    ------------  |
							      ______             |     2*variance   |
							    _/2*pi*variance


				The distribution is assumed to be Gaussian.

				Note it is assumed that X and y are in correct order. use cmll::utility::checks::.. for checking correctness

			*/

			std::vector<double>::size_type features = X[0].size();
			data::Storage::size_type observations = X.size();
			data::Storage::size_type classes = array::unique(y);
			std::vector<data::Storage> splitByClass(classes);
			Mean.resize(classes, std::vector<double>(features));
			Variance.resize(classes, std::vector<double>(features));
			ClassProbability.resize(classes);
			std::vector<double> occurrence(classes);

			for (data::Storage::size_type observation = 0; observation < observations; ++observation)
			{
				splitByClass[static_cast<data::Storage::size_type>(y[observation][0])].emplace_back(X[observation]);
				occurrence[static_cast<data::Storage::size_type>(y[observation][0])]+=1;
				ClassProbability[static_cast<data::Storage::size_type>(y[observation][0])] = occurrence[static_cast<data::Storage::size_type>(y[observation][0])] / observations;
			}

			for (data::Storage::size_type classType = 0; classType < classes; ++classType)
			{
				data::Storage mat(splitByClass[classType][0].size(), std::vector<double>(splitByClass[classType].size()));
				matrix::transpose(splitByClass[classType],mat);

				for (data::Storage::size_type val = 0; val < mat.size(); ++val)
				{
					Mean[classType][val] = _mean(mat[val]);
					Variance[classType][val] = _variance(mat[val], Mean[classType][val]);
				}
			}
		}

		void GaussainNaiveBayes::predict(const data::Storage& XTest, data::Storage& result) // throws std::runtime_error
		{
			
			/*
											   __
				For prediction y = argmax( p(y)||P(xi|y))  is done. 

				Note :  XTest and result are required to be in correct shape 
			*/

			try
			{
				if (Mean.size() == 0 || Variance.size() == 0) throw std::runtime_error("<In function cmll::bayes::GaussianNaiveBayes::predict()>Error : Model is not built. Use model() to fit the model");

				std::vector<double> probDen(Mean.size(), 1);
				std::vector<double> pY(ClassProbability.size());

				for (data::Storage::size_type observation = 0; observation < XTest.size(); ++observation)
				{
					probabilityDensity(XTest[observation], probDen);

					double maximum = 0;

					for (std::vector<double>::size_type op = 0; op < probDen.size(); ++op)
					{
						pY[op] = probDen[op] * ClassProbability[op];
					}

					for (std::vector<double>::size_type op = 0; op < pY.size(); ++op)
					{
						if (pY[op] > maximum) maximum = static_cast<double>(op);
					}

					result[observation][0] = maximum;
				}
			}
			catch (const std::runtime_error &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		
		double GaussainNaiveBayes::score(const data::Storage& y_pred, const data::Storage& y) noexcept
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
			Members of Multinomial Naive Bayes class
		*/

		MultinomialNaiveBayes::MultinomialNaiveBayes(const double alpha)
		{
			/*
				Loading value for smoothing
			*/
			Alpha = alpha;
		}
		
		void MultinomialNaiveBayes::model(const data::Storage& X, const data::Storage& y) noexcept
		{
			/*
				The parameters is estimated by a smoothed version of maximum likelihood, i.e. relative frequency counting:

				FeatureProbability = Nyi + alpha / Ny + alpha*n

				where Nyi is the number of times feature  appears in a sample of class  in the training set , and Ny is the total count of all features for class .

				The smoothing priors alpha > 0 accounts for features not present in the learning samples and prevents zero probabilities in further computations

				Source : Scikit-learn Multinomial Naive Bayes documentation

				Note  :  The X and y should be in correct shapes . run cmll::util::checks::.. functions to verify
			*/
			
			data::Storage::size_type observations = X.size();
			std::vector<double>::size_type features = X[0].size();
			data::Storage::size_type classes = array::unique(y);
			std::vector<data::Storage> splitByClass(classes);
			ClassProbability.resize(classes);
			std::vector<double> occurrence(classes);
			data::Storage count(classes,std::vector<double>(features));
			std::vector<double> countAll(classes);
			FeatureProbability.resize(classes, std::vector<double>(features));

			for (data::Storage::size_type observation = 0; observation < observations; ++observation)
			{
				splitByClass[static_cast<data::Storage::size_type>(y[observation][0])].emplace_back(X[observation]);
				occurrence[static_cast<data::Storage::size_type>(y[observation][0])] += 1;
				ClassProbability[static_cast<data::Storage::size_type>(y[observation][0])] = std::log(occurrence[static_cast<data::Storage::size_type>(y[observation][0])] / observations);
			}

			for (data::Storage::size_type classType = 0; classType < classes; ++classType)
			{

				array::sum(splitByClass[classType], count[classType], array::axis::VERTICAL,Alpha);
			}

			array::sum(count, countAll, array::axis::HORIZONTAL);
			for (data::Storage::size_type classType = 0; classType < classes; ++classType)
			{
				for (std::vector<double>::size_type feature = 0; feature < count[classType].size(); ++feature)
				{
					FeatureProbability[classType][feature] = std::log(count[classType][feature] / countAll[classType]);
				}
			}

		}
		void MultinomialNaiveBayes::logProbabilities(const data::Storage& XTest, data::Storage& result) noexcept
		{
			/*
				The Xtest and FeatureProbability are multiplied to obtain the probabilities which are then added to class probabilities
				Note : This function does not throw an exception if the model is not fit first. Model is required to be built before 
				calling this function

				The Xtest and result vectors are also supposed to be in correct shape 
			*/
			data::Storage FeatureProbabilityt(FeatureProbability[0].size(), std::vector<double>(FeatureProbability.size()));
			matrix::transpose(FeatureProbability, FeatureProbabilityt);
			matrix::multiplication(XTest, FeatureProbabilityt,result);

			for (data::Storage::size_type row = 0; row < result.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < result[row].size(); ++col)
				{
					result[row][col] += ClassProbability[col];
				}
			}
		}

		void MultinomialNaiveBayes::predict(const data::Storage& XTest, data::Storage& result)
		{
			/*
				The logProbabilities function is called and the argmax is returned as the final prediction.

				Note the XTest and result should be in correct order
			*/
			
			try
			{
				if(FeatureProbability.size() == 0 || ClassProbability.size() == 0) throw std::runtime_error("<In function cmll::bayes::MultinomialNaiveBayes::predict()>Error : Model is not built. Use model() to fit the model");
				
				data::Storage probs(XTest.size(), std::vector<double>(FeatureProbability.size()));
				logProbabilities(XTest, probs);

				for (data::Storage::size_type prob = 0; prob < probs.size(); ++prob)
				{
					result[prob][0] = static_cast<double>(std::distance(probs[prob].begin(), std::max_element(probs[prob].begin(), probs[prob].end())));
				}
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << e.what() << '\n';
			}

		}

		double MultinomialNaiveBayes::score(const data::Storage& y_pred, const data::Storage& y) noexcept
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
			Bernoulli Naive Bayes class members
		*/
		BernoulliNaiveBayes::BernoulliNaiveBayes(const double alpha)
		{
			/*
				Loading value for smoothing
			*/
			Alpha = alpha;
		}


		void BernoulliNaiveBayes::model(const data::Storage& X, const data::Storage& y) noexcept
		{
			/*
				In the multivariate Bernoulli event model, features are independent booleans (binary variables) describing inputs.
				There for this model requires samples to be represented as binary-valued feature vectors.

				The decision rule for Bernoulli is based on 
				
				P(xi|y) = P(i|y)xi + (1 - P(i|y))(1 - xi)

				The X and y are required to be in correct shape. check using cmll::utils::check
			*/
			data::Storage::size_type observations = X.size();
			std::vector<double>::size_type features = X[0].size();
			data::Storage::size_type classes = array::unique(y);
			std::vector<data::Storage> splitByClass(classes);
			ClassProbability.resize(classes);
			std::vector<double> occurrence(classes);
			data::Storage count(classes, std::vector<double>(features));
			std::vector<double> countAll(classes);
			FeatureProbability.resize(classes, std::vector<double>(features));

			for (data::Storage::size_type observation = 0; observation < observations; ++observation)
			{
				splitByClass[static_cast<data::Storage::size_type>(y[observation][0])].emplace_back(X[observation]);
				occurrence[static_cast<data::Storage::size_type>(y[observation][0])] += 1;
				ClassProbability[static_cast<data::Storage::size_type>(y[observation][0])] = std::log(occurrence[static_cast<data::Storage::size_type>(y[observation][0])] / observations);
			}

			for (data::Storage::size_type classType = 0; classType < classes; ++classType)
			{

				array::sum(splitByClass[classType], count[classType], array::axis::VERTICAL, Alpha);
			}

			double smoothing = 2 * Alpha;

			for (data::Storage::size_type observation = 0; observation < observations; ++observation)
			{
				countAll[static_cast<data::Storage::size_type>(y[observation][0])] = occurrence[static_cast<data::Storage::size_type>(y[observation][0])] + smoothing;
			}

			for (data::Storage::size_type classType = 0; classType < classes; ++classType)
			{
				for (std::vector<double>::size_type feature = 0; feature < count[classType].size(); ++feature)
				{
					FeatureProbability[classType][feature] = count[classType][feature] / countAll[classType];
				}
			}
		}

		void BernoulliNaiveBayes::logProbabilities(const data::Storage& XTest, data::Storage& result) noexcept
		{
			/*	
				Probabilities for the test set are calculated using the earlier calculated Feature probabilities and class probabilities
			*/

			data::Storage FeatureProbabilityLog(FeatureProbability.size(), std::vector<double>(FeatureProbability[0].size()));
			data::Storage FeatureProbabilityLogt(FeatureProbabilityLog[0].size(), std::vector<double>(FeatureProbabilityLog.size()));
			data::Storage product(XTest.size(), std::vector<double>(FeatureProbability.size()));
			data::Storage productabs(XTest.size(), std::vector<double>(FeatureProbability.size()));

			for (data::Storage::size_type row = 0; row < FeatureProbability.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < FeatureProbability[row].size(); ++col)
				{
					FeatureProbabilityLog[row][col] = std::log(FeatureProbability[row][col]);
				}
			}

			matrix::transpose(FeatureProbabilityLog, FeatureProbabilityLogt);
			matrix::multiplication(XTest, FeatureProbabilityLogt, product);

			for (data::Storage::size_type row = 0; row < FeatureProbabilityLog.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < FeatureProbabilityLog[row].size(); ++col)
				{
					FeatureProbabilityLog[row][col] = std::log(1 - FeatureProbability[row][col]);
				}
			}

			matrix::transpose(FeatureProbabilityLog,FeatureProbabilityLogt);
		    data::Storage XTestabs(XTest.size(), std::vector<double>(XTest[0].size()));

			for (data::Storage::size_type row = 0; row < XTest.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < XTest[row].size(); ++col)
				{
					XTestabs[row][col] = std::abs(XTest[row][col] - 1);
				}
			}
			matrix::multiplication(XTestabs, FeatureProbabilityLogt, productabs);

			matrix::addition(product, productabs,result);

			for (data::Storage::size_type row = 0; row < result.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < result[row].size(); ++col)
				{
					result[row][col] += ClassProbability[col];
				}
			}
		}
		void BernoulliNaiveBayes::predict(const data::Storage& XTest, data::Storage& result)
		{
			/*
				The logProbabilities function is called and the argmax is returned as the final prediction.

				Note the XTest and result should be in correct order
			*/

			try
			{
				if (FeatureProbability.size() == 0 || ClassProbability.size() == 0) throw std::runtime_error("<In function cmll::bayes::MultinomialNaiveBayes::predict()>Error : Model is not built. Use model() to fit the model");

				data::Storage probs(XTest.size(), std::vector<double>(FeatureProbability.size()));
				logProbabilities(XTest, probs);

				for (data::Storage::size_type prob = 0; prob < probs.size(); ++prob)
				{
					result[prob][0] = static_cast<double>(std::distance(probs[prob].begin(), std::max_element(probs[prob].begin(), probs[prob].end())));
				}
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << e.what() << '\n';
			}

		}
	}

}

