
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
	* Last modified : April 16, 2020

	* Change logs (.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/

#include"Linear.h"

/*
	Parent name space : All name spaces lie under this parent name space
*/
namespace cmll
{
	/*
		linear name space : Name space for linear models of regression and classification

	*/
	namespace linear
	{
        /*
            Members of LinearRegression class
        */
        
        void LinearRegression::model(const data::Storage& X, const data::Storage& y) noexcept
        {
            /*
                This coefficient vector B_hat is calculated for which the residual sum of squares is minimum (RSS)

                To calculate B_hat normalized equation is used which is 

                                    B_hat = ( X_T * X )^{-1} * X^{T} * y

                Reference : Elements of statistical Learning  Page number 12, equation number 2.6.

                Note :  It is assumed that X and y parameters have been passed through checks (cmll::utility::checks)

            */

            
            std::vector<double>::size_type features = X[0].size(),ySize = y[0].size();
            data::Storage::size_type observations = X.size();
            

            // Initializations
            data::Storage X_t(features, std::vector<double>(observations));
            data::Storage X_t_mul_y(features, std::vector<double>(ySize));
            data::Storage X_t_mul_X(features, std::vector<double>(features));
            
            // Calculating the formula in steps
            matrix::transpose(X,X_t);
            matrix::multiplication(X_t, y,X_t_mul_y);
            matrix::multiplication(X_t, X,X_t_mul_X);

            
            /*
                Removing allocated memory since it is not required and as have to initialize more in next step
                Debatable whether this step is useful or not but since the time complexity of these is o(n) It doesn't matter.
            */
            X_t.clear();
            X_t.shrink_to_fit();

            
            // for L and U decomposition to find inverse
            data::Storage::size_type X_t_size = X_t_mul_X.size();

            
            data::Storage l(X_t_size, std::vector<double>(X_t_size));
            data::Storage u(X_t_size, std::vector<double>(X_t_size));
            
            matrix::lu(X_t_mul_X, l, u);
            matrix::inverse(l, u, X_t_mul_X);


            /*
                Again, Removing allocated memory since it is not required and as have to initialize more in next step
                Debatable whether this step is useful or not but since the time complexity of these is o(n) It doesn't matter.
            */
            l.clear();
            l.shrink_to_fit();
            u.clear();
            u.shrink_to_fit();
        
            // Final step
            Coefficients.resize(features,std::vector<double>(ySize));
            matrix::multiplication(X_t_mul_X, X_t_mul_y,Coefficients);
        }

        void LinearRegression::predict(const data::Storage &XTest, data::Storage &result) //throws std::runtime_error
        {
            /*
                 The prediction is applied using the formula

                 result = XTest*Coefficients

                 Note : it is assumed that the X_test has passed utility checks and result is already resized to hold the predicted values

                 If model is not fitted a std::runtime_error exception is thrown
            */

            try
            {
                if (!Coefficients.size()) throw std::runtime_error("Error : Model is not built. Run model() to fit the model.");

                matrix::multiplication(XTest, Coefficients,result);
            }
            catch (const std::runtime_error& e)
            {
                std::cerr << "<In function cmll::linear::Regression::predict()>" << e.what() << '\n';
                throw e;
            }

        }

        double LinearRegression::rss(const data::Storage& y_pred, const data::Storage& y_true) noexcept
        {
            /*
                This function uses the following formula for calculating RSS
                RSS = sum_of_((y_true - y_pred)^ 2)
            */
            
            data::Storage difference(y_true.size(), std::vector<double>(1));

            
            matrix::subtraction(y_true,y_pred,difference);

            array::power(difference, 2);
            
            return array::sum(difference);


        }

        double LinearRegression::score(const data::Storage& y_pred, const data::Storage& y_true) noexcept
        {
            /*
                This function uses the following formula for calculating R^square
                R^2 = 1 - RSS/TSS
             */
            return (1 - (rss(y_pred, y_true) / (tss(y_true))));
        }

        double LinearRegression::tss(const data::Storage& y) noexcept
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
            Members of Ridge Regression class
        */
        RidgeRegression::RidgeRegression(const double lambda)
        {
            /*
                If no lambda is provided the default lambda constant defined in cmll::linear::defaults::LAMBDA is used
            */
            Lambda = lambda;
        }

        void RidgeRegression::model(const data::Storage& X, const data::Storage& y) noexcept
        {
            /*

             This model is based on the linear regression (See LinearRegression::model() for information about model) with an additional penalty for the coefficients.

             The residual sum of squares for ridge regression is given by

                           RSS(lambda) = (y-XB)^{T}(y-XB) + lambdaB^{T}B

             B can be calculated using

                           B = (X^{T}X+lambdaI)^{-1}X^{T}y

             Alternatively if a linear regression model is built. THe ridge regression coefficients can be found using

                           B = B_LinearRegression/(1+lambda)

            */

            std::vector<double>::size_type features = X[0].size(), ySize = y[0].size();;
            data::Storage::size_type observations = X.size();

            data::Storage X_t(features, std::vector<double>(observations));
            data::Storage X_t_mul_X(features, std::vector<double>(features));
            data::Storage X_t_mul_y(features, std::vector<double>(ySize));
            data::Storage lamda_I(features, std::vector<double>(1, Lambda));
            data::Storage X_t_mul_X_plus_lamda_I(features, std::vector<double>(features));

            matrix::transpose(X, X_t);
            matrix::multiplication(X_t, y, X_t_mul_y);
            matrix::multiplication(X_t, X, X_t_mul_X);

            
            matrix::diagonalAddition(X_t_mul_X, lamda_I, X_t_mul_X_plus_lamda_I);
           
            /*
                Removing allocated memory since it is not required and as have to initialize more in next step
                Debatable whether this step is useful or not but since the time complexity of these is o(n) It doesn't matter.
            */
            X_t.clear();
            X_t.shrink_to_fit();
            X_t_mul_X.clear();
            X_t_mul_X.shrink_to_fit();
            lamda_I.clear();
            lamda_I.shrink_to_fit();

            data::Storage l(features, std::vector<double>(features));
            data::Storage u(features, std::vector<double>(features));

            matrix::lu(X_t_mul_X_plus_lamda_I, l, u);
            matrix::inverse(l, u, X_t_mul_X_plus_lamda_I);
            
            Coefficients.resize(features, std::vector<double>(ySize));
            matrix::multiplication(X_t_mul_X_plus_lamda_I, X_t_mul_y, Coefficients);
        }

        /*
            RidgeClassifier class members
        */

        RidgeClassifier::RidgeClassifier(const double lambda, ClassificationType method)
        {
            /*
                Initializing the penalty and the type of classification
            */
            
            Lambda = lambda;

            Method = method;

            Classes = 2;
        }

        void RidgeClassifier::_binarizer(data::Storage &yNew) noexcept
        {   
            /*
                Function converts the Y into a binary output scenario.

                For example  [0,1,2] are changed to [ [1,-1,-1], [-1,1,-1],[-1,-1,1] ]
            */
            
            for (data::Storage::size_type row = 0; row < Y.size(); ++row)
            {               
                for (std::vector<double>::size_type col = 0; col < Y[row].size(); ++col)
                {
                    yNew[row][static_cast<data::Storage::size_type>(Y[row][col])] = 1;
                }
            }
        }

        void RidgeClassifier::_encoder(const double value) noexcept
        {
            /*
                Function iterates through all elements of y. sets those elements to -1 which are equal to value
            */
            
            for (data::Storage::size_type row = 0; row < Y.size(); ++row)
            {
                for (std::vector<double>::size_type col = 0; col < Y[0].size(); ++col)
                {
                    if (Y[row][col] == value)
                    {
                        Y[row][col] = -1;
                    }
                }
            }
        }

        void RidgeClassifier::_decoder(const double value) noexcept
        {
            /*
                Function iterates through all elements of y. sets those elements to value which were set to -1
            */
            
            for (data::Storage::size_type row = 0; row < Y.size(); ++row)
            {
                for (std::vector<double>::size_type col = 0; col < Y[0].size(); ++col)
                {
                    if (Y[row][col] == -1)
                    {
                        Y[row][col] = value;
                    }
                }
            }
        }

        bool RidgeClassifier::_sign(const double value) const
        {
            /*
                Function returns 1 if value is grater than 0 else 0;
            */
            
            return (value > 0) ? 1 : 0;
        }

        void RidgeClassifier::_assingSign(data::Storage& vector) noexcept
        {
            /*
                Function uses _sign() function to assign 0 or 1 to a multidimensional vector passed
            */
			
            for (data::Storage::size_type row = 0; row < vector.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < vector[row].size(); ++col)
				{
					vector[row][col] = _sign(vector[row][col]);
				}
			}
        }

        void RidgeClassifier::_keepMaximum(const data::Storage& newVals, data::Storage& change) noexcept
        {
            /*
                Function updates maximum vector if for any index a grater value is found

                The change index stores at what iteration of function calling the change was done for particular index
            */

            static data::Storage maximum = newVals;

            for (data::Storage::size_type row = 0; row < maximum.size(); ++row)
			{
				for (std::vector<double>::size_type col = 0; col < maximum[row].size(); ++col)
				{
                    if (maximum[row][col] < newVals[row][col])
                    {
                        maximum[row][col] = newVals[row][col];
                        change[row][col]++;
                    }
				}
			}
        }
        void RidgeClassifier::model(const data::Storage& X, const data::Storage& y) noexcept
        {
            /*
                The labels are converted into -1 and 1 
                and the regression model is built. 

                For multi class setting, one vs all (one-vs-rest or ova or o.v.r) approach is followed)
            */

            Y = y;
            
            if (Method == ClassificationType::BINARY)
            {
                _encoder(0);
                RidgeRegression::model(X,Y);
                _decoder(0);
            }

            else if (Method == ClassificationType::MULTI_CLASS)
            {
                Classes = array::unique(Y);

                data::Storage yLabelled(Y.size(), std::vector<double>(Classes,-1));
               
				_binarizer(yLabelled);

				RidgeRegression::model(X, yLabelled);

            }
        }

        void RidgeClassifier::predict(const data::Storage& XTest, data::Storage& result) // throws std::runtime_error
        {
            /*
                For binary class prediction linear regression's predict method is used and then the predicted labels are assigned
                the earlier encoded numbers

                For multi class prediction from each separator model is obtained and argmax is returned.

                A std::runtime_error is thrown if the model is not built before predicting

                Xtest, result are required to be in correct shapes or undefined behavior may occur
            */

            try
            {
                if (!Coefficients.size()) throw std::runtime_error("<In function cmll::linear::RidgeClassifier::predict()>Error : Model is not built yet. Use model() to fit the model");

                if (Method == ClassificationType::BINARY)
                {
                    RidgeRegression::predict(XTest, result);
                    _decoder(0);
                    _assingSign(result);
                }

                else if (Method == ClassificationType::MULTI_CLASS)
                {
                    data::Storage CoefficientsAll = Coefficients;
                    Coefficients.clear();
                    Coefficients.shrink_to_fit();
                    Coefficients.resize(CoefficientsAll.size(), std::vector<double>(1));
                    data::Storage psudoResult(result.size(), std::vector<double>(result[0].size()));

                    for (std::size_t classType = 0; classType < CoefficientsAll[0].size(); ++classType)
                    {
                        array::columns(CoefficientsAll, { classType }, Coefficients);
                        RidgeRegression::predict(XTest, psudoResult);
                        _keepMaximum(psudoResult, result);
                    }
                }
            }

            catch (const std::runtime_error& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        double RidgeClassifier::score(const data::Storage& y_pred, const data::Storage& y) noexcept
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
            LogisticRegression Class members
        */

        LogisticRegression::LogisticRegression(const int maximumIterations, const double tolerance, ClassificationType method)
        {
            /*
                Constructor to load defaults
            */
            MaximumIterations = maximumIterations;
            Tolerance = tolerance;
            Method = method;
        }

        void LogisticRegression::_model(const data::Storage& X, const data::Storage& y) noexcept
        {
           /*
             This model fitting algorithm uses Newton-Raphson method for solving equations.
             Ability to choose from different methods will be added is future version

            _______________________________________________________________________

             According to Elements of statistical learning

             "To maximize the log-likelihood, we set its derivatives to zero. These score equations are"

                        ∂ℓ(β)/∂β = E_{i=1}^{N} xi(yi − p(xi; β)) = 0

             "To solve the score equations (4.21), we use the Newton–Raphson algorithm, which requires the second-derivative or Hessian matrix"

             A single Newton update is given by

                        β^{new} = B^{old} - H^{-1}.delta

             where H is the Hessian matrix and delta is the gradient


             "Let y denote the vector of yi values, X the N × (p + 1) matrix of xi values,
             p the vector of fitted probabilities with ith element p(xi; β^{old})
             and W a N ×N diagonal matrix of weights with ith diagonal element p(xi; β^{old})(1−p(xi;β^{old}))"

             Then we have

                                delta =  X^{T}(y-p)
                                H = -X^TWX

            Thus                β =  (X^{T}WX)^{−1}X^{T}Wz
            where               z = Xβ^{old} + W^{−1}(y − p)

            Multi label classification is not supported (yet).
            Note it is assumed that X and y are in correct order. use cmll::utility::checks::.. for checking correctness
            */

			data::Storage::size_type observations = X.size();
			std::vector<double>::size_type features = X[0].size();
            
            Coefficients.resize(features, std::vector<double>(1));
             
            data::Storage XMulCoef(observations, std::vector<double>(1)), p(observations, std::vector<double>(1)), pNeg(observations, std::vector<double>(1));
            data::Storage w(observations, std::vector<double>(1)), wInverse(observations, std::vector<double>(1));
            data::Storage yMinusp(observations, std::vector<double>(1));
            data::Storage wInverseMulyMinusp(observations, std::vector<double>(1)),z(observations, std::vector<double>(1));
            data::Storage Xt(features, std::vector<double>(observations));
            data::Storage XtMulw(features, std::vector<double>(observations));
            data::Storage XtMulwMulX(features, std::vector<double>(features));
            data::Storage XtMulwMulXMulXt(features, std::vector<double>(observations));
            data::Storage XtMulwMulXMulXtMulw(features, std::vector<double>(observations));
			data::Storage l(features,std::vector<double>(features));
            data::Storage u(features, std::vector<double>(features));
            data::Storage gradient(features,std::vector<double>(1));
            double change;

            long interationIndex = 0;

            do 
            {
                matrix::multiplication(X, Coefficients, XMulCoef);

                for (data::Storage::size_type val = 0; val < p.size(); ++val)
                {
                    p[val][0] = functions::activation::sigmoid(XMulCoef[val][0]);
                    pNeg[val][0] = 1 - p[val][0];
                    w[val][0] = p[val][0] * pNeg[val][0];
                }
                
                matrix::transpose(X, Xt);
                matrix::diagonalMultiplication(Xt, w,XtMulw,matrix::selection::RHS);
                matrix::multiplication(XtMulw, X, XtMulwMulX);

                matrix::lu(XtMulwMulX, l, u);
                matrix::inverse(l, u, XtMulwMulX);
                matrix::multiplication(XtMulwMulX, Xt, XtMulwMulXMulXt);
                matrix::diagonalMultiplication(XtMulwMulXMulXt, w, XtMulwMulXMulXtMulw,matrix::selection::RHS);

                matrix::diagonalInverse(w, wInverse);
                matrix::subtraction(y, p, yMinusp);
                matrix::diagonalMultiplication(wInverse, yMinusp, wInverseMulyMinusp,matrix::selection::LHS);
                matrix::addition(XMulCoef, wInverseMulyMinusp,z);

                matrix::multiplication(XtMulwMulXMulXtMulw, z, Coefficients);
                matrix::multiplication(Xt, yMinusp, gradient);
                change = std::abs(array::maximum(gradient));
                
                
                ++interationIndex;
                

            } while ((interationIndex < MaximumIterations) && (change < Tolerance));

            if (change <= Tolerance)
            {
                std::cerr << "<In function cmll::Linear::LogisticRegression::model> Warning : The solution did not converge at 'Maximum iterations : " << MaximumIterations << "\n";
            }

        }

        void LogisticRegression::predictProbabilities(const data::Storage& XTest, data::Storage& result) noexcept
        {
            /*
                To obtain the prediction probabilities. The Test set matrix is multiplied by the Coefficients.
                And each element of the new product matrix is passed through the activation function to get the probabilities

                Note : The model is supposed to be fit using model() an exception will not be thrown by this function
            */
            data::Storage XMulCoef(XTest.size(), std::vector<double>(1));

            matrix::multiplication(XTest, Coefficients, XMulCoef);

            for (data::Storage::size_type row = 0; row < XTest.size(); ++row)
            {
                result[row][0] = functions::activation::sigmoid(XMulCoef[row][0]);
            }
        }

        void LogisticRegression::model(const data::Storage& X, const data::Storage& y) noexcept
        {   
            /*
                The function calls the internal _model() function to build the model
            */
            
            if (Method == ClassificationType::BINARY)
            {
                _model(X, y);
            }

            else if (Method == ClassificationType::MULTI_CLASS)
            {
                std::cerr << "<In function cmll::linear::LogisticRegression> Information: Multi class classification is not supported with Newton Raphson Method \n";
            }
        }

        void LogisticRegression::predict(const data::Storage& XTest, data::Storage& result) // throws std::runtime_error
        {
            /*
                Function calls predictProbability() for calculating probabilities for each test st observations and then
                the label is assigned according to the probability
            */
            try
            {
                if (!Coefficients.size()) throw std::runtime_error("<In function cmll::linear::LogisticRegression::predict()>Error : Model is not built yet. Use model() to fit the model");

                if (Method == ClassificationType::BINARY)
                {
                    predictProbabilities(XTest, result);

                    for (data::Storage::size_type row = 0; row < XTest.size(); ++row)
                    {
                        result[row][0] = (result[row][0] >= 0.5) ? 1 : 0;
                    }
                }

                else if (Method == ClassificationType::MULTI_CLASS)
                {
					std::cerr << "<In function cmll::linear::LogisticRegression> Information: Multi class classification is not supported with Newton Raphson Method \n";
                }
            }
            catch (const std::runtime_error& e)
            {
				std::cerr << e.what() << '\n';
            }
        }

        double LogisticRegression::score(const data::Storage& y_pred, const data::Storage& y) noexcept
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

	}
}