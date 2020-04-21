
/*

	* Project title : CMLL :  C++'s Machine Learning Library

	* Project Author : Imanpal Singh <Imanpalsingh@gmail.com>

	* Project creation date : February 8, 2020

	* Project description : A modern C++ Machine Learning library that uses the STL for easier creation and deployment of Machine Learning models
*/

/*

	* Project version 0.1.0
	* File version 0.1.0
	* Date created : February 15, 2020
	* Last modified : April 16, 2020

	* Change logs (0.1.0)

			None

	Note :  For earlier change logs of version before the current one, refer to backups folder
*/
#pragma once


/*
	All the includes and functions are to be aligned in the alphabetical order Classes are aligned on basis of inheritance
*/
#include<algorithm>
#include<iostream>

#include"../numeric/Array.h"
#include"../utils/Defines.h"
#include"../numeric/Function.h"
#include"../numeric/Matrix.h"



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
       /**
        * Class Name : LinearRegression

        * Class Description : Class containing functions required for building a linear regression model

        * Attributes :

	    1) Coefficients : The variable holding calculated coefficients
						   Type : cmll::data::Storage

        * Functions : 
        
        1) model 
        
        2) predict

        3) rss

        4) score

        5) tss
         
        *
        */
        class LinearRegression
        {


        public:

            // Storage variable to hold coefficients
            data::Storage Coefficients;


            /* Functions */

           /**
            * Function Name :  model

            * Function Description :  Function to built a linear regression model using Feature Matrix X and vector of prediction y.

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LinearRegression l1;

                    l1.model(X,y);

                    return 0;

                }


            */
            void model(const data::Storage& X, const data::Storage& y) noexcept;

           /**
            * Function Name :  predict

            * Function Description :  Function to predict using linear regression model built by model()

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LinearRegression l1;

                    l1.model(X,y);

                    l1.predict(XTest,result);

                    return 0;

                }


            */
            void predict(const data::Storage& XTest, data::Storage& result); //throws std::runtime_error

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
               #include<linear/Linear.h>
               #include<iostream>

               int main()
               {
                   // vector creation and element adding here

                   cmll::linear::LinearRegression l1;

                   l1.model(X,y);

                   l1.predict(XTest,y_pred);

                   std::cout<<l1.rss(yPred,y);

                   return 0;

               }


           */
            double rss(const data::Storage& y_pred, const data::Storage& y_true) noexcept;

           /**
            * Function Name :  score

            * Function Description :  Function to calculate R^2 score of the linear Regression model built

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
                #include<linear/Linear.h>
                #include<iostream>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LinearRegression l1;

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
               #include<linear/Linear.h>
               #include<iostream>

               int main()
               {
                   // vector creation and element adding here

                   cmll::linear::LinearRegression l1;

                   std::cout<<l1.tss(y);

                   return 0;

               }


           */
            double tss(const data::Storage& y) noexcept;

        };

        /**
        * Class Name : RidgeRegression

        * Class Description : Class containing functions required for building a Ridge regression model

        * Attributes :

        1) Lambda :  The value of Lambda penalty

        * Functions :

        1) model - @overriden

        2) predict - @inherited

		3) rss - @inherited

		4) tss - @inherited

        5) score - @inherited

        */
        class RidgeRegression : public LinearRegression
        {
        public:

            // Penalty 
            double Lambda;

           /**
           * Constructor Name : RidgeRegression[Parameterized]

           * Constructor Description :  Constructor to load value of lambda 

           * Parameters :

           1) lambda		    The penalty 

                            Type Expected : double

                            Method of passing :  constant


           * Example

               #include<vector>
               #include<linear/Linear.h>
               #include<iostream>

               int main()
               {

                   cmll::linear::RidgeRegression r1(10);

                   return 0;

               }


           */
            RidgeRegression(const double lambda = static_cast<double>(defaults::LAMBDA));

            /**
            * Function Name :  model

            * Function Description :  Function to built a ridge regression model using Feature Matrix X and vector of prediction y.

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::RidgeRegression l1;

                    l1.model(X,y);

                    return 0;

                }


            */
            void model(const data::Storage& X, const data::Storage& y) noexcept;

        };

        /**
        * Class Name : RidgeRegression

        * Class Description : Class containing functions required for building a Ridge regression model

        * Attributes :

        1) Classes : Number of distinct classes

        2) Lambda :  The value of Lambda penalty @inherited

        3) Method : Either binary classification for Multi class

        4) Y : The vector of prediction

        * Functions :

        1) _assignSign @protected

        2) _binarizer   @protected
        
        3) _decoder @protected

        4) _encoder @protected

        5) _keepMaximum @protected

        6) _sign @protected

        7) model - @overriden and called

        8) predict - @overriden and called
		
        9) rss - @privateScoped

		10) tss - @privateScoped

        11) score - @overrriden

        

        */
        class RidgeClassifier : public RidgeRegression
        {
        protected:
            
			/*
                In a classification setting, rss and tss are not required
            */
            using RidgeRegression::rss;
			using RidgeRegression::tss;

            /**
            * Function Name : Assign sign

            * Function Description :  Function that assigns 0 to values less than and equal to zero and one to others

            * Parameters :

            1) X:			vector whose value are to be assigned

                            Type Expected : multidimensional vetor

                            Method of passing :  By reference

            * Return :		None


            * Example

               This function is internal and protected ;


            */
            void _assingSign(data::Storage& X) noexcept;

            /**
            * Function Name : Binarizer

            * Function Description :  Function to encode create a multi output regression scenario with labels either -1 or 1

            * Parameters :

            1) yNew :			The new Y, encoded

                                Type Expected : multidimensional vector

                                Method of passing :  reference

            * Return :		None


            * Example

               This function is internal and protected ;


            */
            void _binarizer(data::Storage& yNew) noexcept;

            /**
            * Function Name : Decoder

            * Function Description :  Function to set the values earlier set to -1 to value

            * Parameters :

            1) value :			The value to place instead of -1

                                Type Expected : double

                                Method of passing :  constant

            * Return :		None


            * Example

               This function is internal and protected ;


            */
            void _decoder(const double value) noexcept;


            /**
            * Function Name : Encoder

            * Function Description :  Function to encode specific labels to -1 and rest to 1

            * Parameters :

            1) value :			The value to encode to -1

                                Type Expected : double

                                Method of passing :  constant 

            * Return :		None


            * Example

               This function is internal and protected ;


            */
            void _encoder(const double value) noexcept;

            /**
           * Function Name : Keep maximum

           * Function Description :  Function receives same vector multiple times and keeps the maximum value for each index
                                     The changes per index per iteration are saved in Changes.

           * Parameters :

           1) newVals  :    Vector to check for changes in

                            Type Expected : multidimensional vector

                            Method of passing : Const and by reference

           2) Change  :     The changes vector stores what index last update was done for every index

                            Type Expected : multidimensional vector

                            Method of passing : By reference

           * Return :		None


           * Example

              This function is internal and protected ;


           */
            void _keepMaximum(const data::Storage& newVals, data::Storage& Change) noexcept;
            
            
            /**
            * Function Name : sign

            * Function Description :  Function that returns 0 if the value is less than  or equal to 0 and 1 id value is grater than 0;

            * Parameters :

            1) value :			value to check

                                Type Expected : double

                                Method of passing :  constant

            * Return :		    bool - >  0 or 1


            * Example

               This function is internal and protected ;


            */
            bool _sign(const double value) const;


        public:

			// Number of classes
			data::Storage::size_type Classes;

            // Hold the classification type
            ClassificationType Method;

            // The vector of prediction is required
            data::Storage Y;

            

           /**
           * Constructor Name : RidgeClassifier[Parameterized]

           * Constructor Description :  Constructor to load value of lambda and type of classification (binary, multi-class)

           * Parameters :

           1) lambda		The penalty

                            Type Expected : double

                            Method of passing :  constant
           
           2) method        The classification type ( cmll::linear::ClassificationType::BINARY or cmll::linear::ClassificationType::MULTI_CLASS    

							Type Expected : cmll::linear::ClassificationType

							Method of passing :  value

           * Example

               #include<vector>
               #include<linear/Linear.h>
               #include<iostream>

               int main()
               {

                   cmll::linear::RidgeClasifier r1(10,cmll::linear::classificationType::MULTI_CLASS);

                   return 0;

               }


           */
            RidgeClassifier(const double lambda = static_cast<double>(defaults::LAMBDA), ClassificationType method = ClassificationType::BINARY);

            /**
            * Function Name :  model

            * Function Description :  Function to built a ridge classifier model using Feature Matrix X and vector of prediction y.

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::RidgeClassifier l1;

                    l1.model(X,y);

                    return 0;

                }


            */
            void model(const data::Storage& X, const data::Storage& y) noexcept;

            /**
            * Function Name :  predict

            * Function Description :  Function to predict using RidgeClassifier model built by model()

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::RidgeClassifier l1;

                    l1.model(X,y);

                    l1.predict(XTest,result);

                    return 0;

                }


            */
            void predict(const data::Storage& XTest, data::Storage& result); // throws std::runtime_error

            /**
            * Function Name :  score

            * Function Description :  Function to calculate accuracy of the RidgeClassifier model built

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
                #include<linear/Linear.h>
                #include<iostream>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::RidgeClassifier l1;

                    l1.model(X,y);

                    l1.predict(XTest,y_pred);

                    std::cout<<l1.score(yPred,y);

                    return 0;

                }


            */
            double score(const data::Storage& y_pred, const data::Storage& y) noexcept;
        };

        /**
        * Class Name : LogisticRegression

        * Class Description : Class containing functions required for building a Logistic regression model

        * Attributes :

        1) Coefficients : The Coefficient vector

        2) MaximumItertions : The maximum iterations to run the convergence loop for

        3) Method :  Classification type binary or multi class

        4) Tolerance : The tolerance

        * Functions :

        1) _model -  @protected

        2) model

        3) predict

        4) predictProbabilities

        5) score 
        */
        class LogisticRegression
        {

        protected:
            /**
            * Function Name :  model (internal)

            * Function Description :  The model (public) function calls this internal function to build the model

            * Parameters :

            1) X :			The feature matrix

                            Type Expected : cmll::data::Storage

                            Method of passing :  constant and by reference

            2) y :		    Vector of prediction

                            Type Expected : cmll::data::Storage

                            Method of passing :  constant and by reference

            * Return :		None


            * Example
                This function is internal and protected ;

            */
            void _model(const data::Storage& X, const data::Storage& y) noexcept;
            
        public:

            data::Storage Coefficients;
            int MaximumIterations;
            ClassificationType Method;
            double Tolerance;

           /**
           * Constructor Name : LogisticRegression[Parameterized]

           * Constructor Description :  Constructor to load value of MaximumIterations, Tolerance and type of classification (binary, multi-class)

           * Parameters :

           1) maximumIterations :   Maximum iterations to wait for solution to converge

                                    Type Expected : int

                                    Method of passing :  constant
		   
           2) Tolerance :           The tolerance factor that decides the convergence of solution

									Type Expected : double

									Method of passing :  constant

           
           3) method        The classification type ( cmll::linear::ClassificationType::BINARY or cmll::linear::ClassificationType::MULTI_CLASS

                            Type Expected : cmll::linear::ClassificationType

                            Method of passing :  value

           * Example

               #include<vector>
               #include<linear/Linear.h>
               #include<iostream>

               int main()
               {

                   cmll::linear::LogisticRegresiion r1(300,0.004,cmll::linear::classificationType::MULTI_CLASS);

                   return 0;

               }


           */
            LogisticRegression(const int maximumIterations = static_cast<int>(defaults::MAXIMUM_ITERATIONS), const double tolerance = defaultsd::TOLERANCE, ClassificationType method = ClassificationType::BINARY);

            /**
            * Function Name :  model

            * Function Description :  Function to built a Logistic Regression model using Feature Matrix X and vector of prediction y.

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LogisticRegression l1;

                    l1.model(X,y);

                    return 0;

                }


            */
            void model(const data::Storage& X, const data::Storage& y) noexcept;

            /**
            * Function Name :  predict

            * Function Description :  Function to predict using Logistic regression model built by model()

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
                #include<linear/Linear.h>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LogisticRegression l1;

                    l1.model(X,y);

                    l1.predict(XTest,result);

                    return 0;

                }


            */
            void predict(const data::Storage& XTest, data::Storage& result); //throws std::runtime_error

            /**
            * Function Name :  predict probabilities

            * Function Description :  Function returns the predicted probabilities for each observation in the test set

            * Parameters :

            1) XTest :		The test set feature matrix

                            Type Expected : cmll::data::Storage

                            Method of passing :  constant and by reference

            2) result :		The predicted probability values

                            Type Expected : cmll::data::Storage

                            Method of passing :  by reference

            * Return :		None

            * Example

            #include<vector>
            #include<iostream>
            #include<Linear/Linear.h>
            int main()
            {
                // Vectors here

                cmll::linear::LogisticRegression l1;

                l1.model(X,y);
                l1.predictProbabilities(XTest,yPredProba);

                return 0;
            }
                

            */
            void predictProbabilities(const data::Storage& XTest, data::Storage& result) noexcept;

            /**
            * Function Name :  score

            * Function Description :  Function to calculate accuracy of the Logistic Regression model built

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
                #include<linear/Linear.h>
                #include<iostream>

                int main()
                {
                    // vector creation and element adding here

                    cmll::linear::LogisticRegression l1;

                    l1.model(X,y);

                    l1.predict(XTest,y_pred);

                    std::cout<<l1.score(yPred,y);

                    return 0;

                }


            */
            double score(const data::Storage& X_test, const data::Storage& y_true) noexcept;

        };
	}
}