/*
*    

*   Author : Imanpal Singh <imanpalsingh@gmail.com>

*   Project title : CMLL C++'s Machine Learning Library

*   File title : Data handler for handling dataset files in format like (csv,xlxs etc)

*   Description : This File Handles the formatting of the file before running any operation
                  realted to machine learning (Preprocessing,EDA,etc). The file read is to be stored in vector of vectors. 
                  High level and low level tools are provided for performing operations on the dataset.

*
*/


/*
*

* Project version : 0.0.0

* File version : 0.0.1

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_8_20_21_12
 
* Last modified : APR_05_20_19_35

* Change Logs : 

        
        1) Date : 05-04-2020 Time : 19:36
        Namespace data
        # function insert is now a member of data namespace and a friend of Handler class
        # Function read now accepts mandatory column names and stores them separately.
        # Function read can now prompt for missing values in the column names row
        # Function read now reports for missing values by invalid structure of file. 
        
        Robust exceptional handling implemented

        Handler class
        # Extraction operator << is now overload for cout
        # Subscript operator [] now also accepts either column name(string) or vector of column name(vector<string>) as parameter
        
        2) Date : 04-04-2020 Time : 23:15
        #Handler and functions under file namespace are moved to a new common namespace data
        #Added a new function read_columns under the namspace data
        
        Handler class
            #Added new function create()
            #Added new function save()
            #Added new function memory_usage()
            #Negative indexing is now supported in all overloads
        

        3) Date : 28-03-20 Time : 22:21
        Handler class
            #Added new function insert ( 2 overloads)

*
*/



/*
*

* Header files : For Input Output on the standard streams, on the files. The declaration header,vectors,arrays.

*
*/



// Datahandler declarations header (version 0.0.0)
#include"DataHandler.hpp"






namespace cmll
{
    namespace data
    {
    
        Handler::Handler()
        {
        
        }

        Handler::Handler(const data::STORAGE &dataset, const std::vector<std::string> &column_names)
        {
            Dataset = dataset;
            Columns = column_names;
        }

        /*
        *

        * Function Name : read_columns

        * Description : Function to read files (csv by default).
                        File with the filename specified is opened for reading. Each row is parsed with theseparators defined.

        Paramteres :  filename - >  A valid filepath for the file to be read
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)

        * Return : num_columns -> number of columns

        * Function Version : 0.0.0

        *
        */
        std::size_t read_columns(Handler &obj,const std::string &column_line,const char &line_separator,const char &value_separator)
        {
            // Error directory 
            const std::string ERROR_DIR = "<In function[protected] Handler::__read_columns__>";
            
            // Number of columns 
            std::size_t num_columns=0;

            // String to store concatenated characters 
            std::string column = "";
            
            
            try
            {
                // If there isn't any column
                if(column_line == "") throw std::runtime_error(ERROR_DIR + "Error : Column line is empty.\nIf columns do not exit set read_columns = false.\n"); 
            
            
                // For each character in the column
                for(auto character:column_line)
                {
                    // If the character received is the value seperator or the line_seperator or the last character in the string
                    if(character==value_separator || character==line_separator)
                    {
                
                        // If no value was found (typically because of [ 1,2,,3] methods)
                        if(column == "")
                        {
                            throw std::runtime_error(ERROR_DIR + "Error : Missing value was detected while extraction column names. Column names cannot be Missing.\n");
                        }
                        
                    
                        // Append the column to the columns name vector
                        obj.Columns.push_back(column);
                        
                        
                        // Empty the string for new column datata
                        column="";

                        // updateing the number of columns
                        ++num_columns;

                        // Skip the character concatenation  of characters since delimeters are not to be used. 
                        continue;
                    }

                    // Adding characters until delimeter is reached.
                    column+=character;

                }

                
            }
            // Cathing user defined exceptions
            catch(const std::invalid_argument &e)
            {
            // rethrowing for the file::read function
                throw e;
            }

            // Appending the last column to the columns name vector
            obj.Columns.push_back(column);

            // Returning number of columns
            return ++num_columns;
        }
        
        
        
        /*
        *

        * Function Name : read

        * Description : Function to read a file and store the contents in vector of vectors of double a.k.a STORAGE (See defined.hpp for typedef).

        * Parameters : filename -> The filename of the file to read.
                    : value_separator -> The delimeter that separates different observations in thefile (default = ',') 
                    : line_seperator - > The delimeter which separates lines (default '\n') 
        * Return : Object of the class Handler

        * Function Version : 0.0.0

        * Goal of Implementations : A user defined line break delimeter ( Version 1.0)

        * Note since xlxs files are binary format the cannot be opened with read(), expect a separate function for those files in version 1.0

        *
        */

        Handler read(const std::string &filename,const char &line_separator,const char &value_separator)
        {
            // Handler object to return
            Handler object;

            // Error directory
            const std::string ERROR_DIR = "<In function Handler::read>";

            // Variable to store read number
            double data;

            // variable to store next character
            char character;

            // Variable to keep count of column to read
            std::size_t column=0;

            // Temporary column holder
            std::vector<double> data_holder;

            // Total number of columns
            std::size_t num_columns;

            
            // opening the file
            std::ifstream _file(filename);
            try
            {
            
                // If not successfull
            if(!_file)
            {
                    throw std::runtime_error("Error :  Cannot access file. Either it doesn't exist or permission is required\n");

            }
            
            // Variable to sore the column names column
            std::string column_line;

            // getting the first column
            std::getline(_file,column_line,line_separator);
            
            // Extracting the column names and number o columns
            num_columns = read_columns(object,column_line,line_separator,value_separator);

            // Reading rows
            while(_file>>data)
            {
                    
                    // Processing the  row 
                    // Reading the character ahead of the data
                    _file.get(character);
                    
                    // If the read character is theseparator of column or of line
                    if((character ==value_separator) || (character == line_separator))
                    {
                        // Increment the col num
                        column++;
                        
                        // Adding the data to the temporary vector to create a row and later insert into vector of vector
                        data_holder.emplace_back(data);
                    

                    // if the character is line break, then end of preprocessing of current row
                    if(character == line_separator)
                    {
                        // Checking if the format of the file is same as the first row i.e number of columns are same as in the first row
                        if (column != num_columns)
                        {
                            
                            std::cout<<" The Number of columns are "<<column<<". Expected were "<<num_columns<<"\n";
                            throw std::length_error("Error : The csv format is not preserved in the file \n");
                        }

                        // Adding the row to the final dataset
                        object.Dataset.emplace_back(data_holder);

                        // Clearing the temporary storage for next iteration. 
                        data_holder.clear();
                        column=0;

                    }
                    }  

                    // If the character received is unkown 
                    else 
                    {
                        std::cout<<"An unspecified character '"<<character<<"' was received at row 1 column " << num_columns << " which was expected to be the delimeter '"<<value_separator<<"'\n";
                        throw std::invalid_argument("Error : Bad shape\n");
                    }

                }

                // Adding the last row to the dataset. Also checking for integrity of the format.
                if(!data_holder.empty())
                object.Dataset.emplace_back(data_holder);

                //Closing the stream 
                _file.close();
            }

            // Catiching all the exceptions
            catch(const std::invalid_argument &e)
            {
                std::cerr<<ERROR_DIR<<e.what();
                _file.close();
                
            }

            catch(const std::length_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what();
                _file.close();
            }

            catch(const std::runtime_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what();
                _file.close();
            }
            catch(const std::exception &e)
            {
                std::cerr<<ERROR_DIR<<e.what();
                _file.close();
            }
                
                
            // Returning the object (let copy constructure handle the rest)
            return object;

        }
        
        /*
        *

        * Function Name : create

        * Description : Function to create a new Handler object with STORAGE element and column names

        * Parameters :  dataset : The values to store
                        column_names : The column names 

        * Return  : void
        * Function Version : 0.0.0

        *
        */

        Handler create(const data::STORAGE &dataset, const std::vector<std::string> &column_names)
        {
            
            Handler object;

            // Error directory
            const std::string ERROR_DIR = "<In function Handler::read>";

            //Number of columns
            std::size_t cols = column_names.size();

            try
            {
                // Column names are mandatory
                if(cols == 0) throw std::length_error("Column names are required.");

                // Column names should be equal to number of columns in the entire dataset
                if(!util::is_legal(dataset,cols)) throw std::length_error("The dataset format isn't correct. call cmll::util::is_legal to verify.");

                object.Dataset = dataset;
                object.Columns = column_names;
            }
            
            // Exceptions
            catch(const std::length_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            
            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error occurred\n";
            }
            


            return object;
        }


        /*
        *

        * Function Name : insert

        * Description : Function to insert a column in the Handler object.

        * Parameters :  position -> Position at which to insert he column
                        elements -> elements of the column to insert

        * Return : None

        * Function Version : 0.0.0

        *
        */
        void Handler::insert(std::size_t position,const std::vector<double> &elements,const std::string &column_name)
        {
            ERROR_DIR = "<In function Handler::insert>";
            std::size_t max_index = Dataset[0].size();

            try
            {
               if(position < 0 ) position = max_index + position;
               
               if(position >= max_index) 
               {
                   std::cout<<"Expected index less than "<<max_index<<". Got "<<position<<".";
                   throw std::length_error("Error : Position index is out of range");
               }

               for(int row=0;row<Dataset.size();row++)
               {
                    Dataset[row].insert(Dataset[row].begin()+position,elements[row]);
               }

               //Updating the column vector
               if(column_name == "")
               {
                   Columns.insert(Columns.begin()+position,std::to_string(position));
               }

               else
               {
                   Columns.insert(Columns.begin()+position,column_name);
               }
               
               
            }

            catch(const std::length_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
 
        }

        /*
        *

        * Function Name : insert

        * Description : Function to insert a value as a new column in the Handler object.

        * Parameters :  position : Position at which to insert he column
                        element : value to be inserted in the entire new column

        * Return : None

        * Function Version : 0.0.0

        *
        */

        void Handler::insert(std::size_t position,const double &element,const std::string &column_name)
        {
            ERROR_DIR = "<In function Handler::insert>";
            std::size_t max_index = Dataset[0].size();
            
            
            try
            {
               if(position < 0 ) position = max_index + position;
               
               if(position >= max_index) 
               {
                   std::cout<<"Expected index less than "<<max_index<<". Got "<<position<<".";
                   throw std::length_error("Error : Position index is out of range");
               }
               for(int row=0;row<Dataset.size();row++)
               {
                    Dataset[row].insert(Dataset[row].begin()+position,element);
               }
                
               //Updating the column vector
               if(column_name == "")
               {
                   Columns.insert(Columns.begin()+position,std::to_string(position));
               }

               else
               {
                   Columns.insert(Columns.begin()+position,column_name);
               }

            }

            catch(const std::length_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        

        /*
        *

        * Function Name : create

        * Description : Function to save the Handler object to a file

        * Parameters  filename - >  A valid filepath for the file to be written
                    line_separator -> The seperator which separates rows (default '\n')
                    value_Separator - > Th eseparator which separates cols (default ',' - csv)

        * Return  : void
        * Function Version : 0.0.0

        *
        */

        void Handler::save(const std::string &filename,const char &line_separator,const char &value_separator)
        {
            // Defining error path
            ERROR_DIR = "<in function Handler::create>";
            
            // Creating the file to be saved
            std::ofstream create_file(filename);
            try
            {
            // If not successful;
            if(!create_file)
            {
                throw std::exception();
            }
            
            // Getting number of columns
            std::size_t num_of_cols = Columns.size();

            //Writing column names first
            for(std::size_t col=0;col<num_of_cols;col++)
            {
                create_file<<Columns[col];
                if(col!=num_of_cols-1)create_file<<value_separator;
            }
            create_file<<line_separator;


            // Saving each value in the format
            for(std::size_t i =0;i<Dataset.size();i++)
            {
                    for(std::size_t j = 0; j<Dataset[i].size();j++)
                    {
                        create_file<<Dataset[i][j];
                        if(j != Dataset[i].size()-1) create_file<<value_separator;
                    }
                    create_file<<line_separator;
            }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << "Unkwon error.\n";
            }

            create_file.close();
            
        }

        /*
        *

        * Function Name : clear

        * Description : Function to clear the entire Handler object. Removing the dynamic memory allocated

        * Parameters : None
        * Return  : void
        * Function Version : 0.0.0

        *
        */

        void Handler::clear()
        {
            
            // Deleting Dataset
            Dataset.clear();

            // Shrinking to remove allocated memory
            Dataset.shrink_to_fit();

            // Deleting column names
            Columns.clear();

            // Shrinking to remove allocated memory
            Columns.shrink_to_fit();
        }

        /* UTILITIES */

        /*
        *

        * Function Name : rows

        * Description : Function to Calculate number of rows. It is the number of vectors emplaced.

        * Parameters : None

        * Return : Number of rows in the dataset (Number of vectors inside the vector of vectors)

        * Function Version : 0.0.0

        *
        */

        int Handler::rows() const
        {
           
            
            return Dataset.size();
        }

        /*
        *

        * Function Name : cols

        * Description : Function to Calculate number of cols. It is the number of elements in the first vector.

        * Parameters : None

        * Return : Number of Cols in the dataset (umber of elements inside the each vector)

        * Function Version : 0.0.0

        *
        */

        int Handler::columns() const
        {
            if(rows() ==0)
                return 0;
            
            return Dataset[0].size();
        }

        /*
        *

        * Function Name : size()

        * Description : Function to Calculate number of elements in the dataset.

        * Parameters : None

        * Return : Number of elements combined of all vectors.

        * Function Version : 0.0.0

        *
        */

        int Handler::size() const
        {
            return rows()*columns();
        }

        /*
        *

        * Function Name : get

        * Description : Function to return the data member 'Dataset'.

        * Parameters : none

        * Return : data::STORAGE (see DataHandler.hpp for typedef) variable

        * Function Version : 0.0.0


        *
        */

        data::STORAGE Handler::get() const
        {
        return Dataset;


        }

        /*
        *

        * Function Name : memory_usage

        * Description : Function to return the memory used by Dataset(STORAGE).

        * Parameters : none

        * Return : memory usage

        * Function Version : 0.0.0


        *
        */

        int Handler::memory_usage() const
        {
            // Discarding the space taken by Columns vector
            // Each value is a double takes size_of(double) bytes
            // So a N*N handler object will take size_of(double)*n*n bytes
            return (sizeof(double)*rows()*columns());

        }

        /*
        *

        * Function Name : operator[]

        * Description : Overloading the subscript operator to allow indexing 

        * Parameters : indexes - > Vector of int which contains all the indexes required

        * Return : Handler object containing columns of the original dataset which are defined in the indexes parameters

        * Function Version : 0.0.0

        * Note negative indexing is supported since 0.0.0

        *
        */

        Handler Handler::operator[](std::vector<int> indexes)
        {
            //Creating object to return
            Handler object;
            
            //Error_DIR
            ERROR_DIR = "<In function operator[]>";

            // Extraction of number of rows and columns
            std::size_t num_rows = Dataset.size();
            std::size_t num_cols = Dataset[0].size();

            //Creating a temporary storage data holder
            std::vector<double> Holder;

            try
            {

                for(std::size_t row=0;row<num_rows;row++)
                {
                        
                    for(auto col:indexes)
                    {
                            // if negative indexing is provided
                            if(col<0)
                            {
                                
                                //Converting to normal indexing
                                col = num_cols + col;
                                
                            }
                    
                            // if the index specified is larger than number of columns in the dataset then raise an error
                            if(col> num_cols-1)
                            {
                                std::cout<<"Received '"<<col<<"' but expected less than '"<<num_cols<<"'.\n";   
                                throw std::out_of_range(ERROR_DIR + "Error : Handler index out of range");
                                   
                            }

                            // if everything is write then add to the temporary storage
                            Holder.emplace_back(Dataset[row][col]);
                            
                            // Updating the new objects column vector
                            if(row == 0) object.Columns.emplace_back(Columns[col]);
                    }

                        // Add to the object's dataset
                        object.Dataset.emplace_back(Holder);

                        //Clearing for next iteration
                        Holder.clear();
                    
                }
            }

            catch(const std::out_of_range &e)
            {
                std::cout<<ERROR_DIR<<e.what()<<'\n';
            }

            catch(const std::exception &e)
            {
                std::cout<<ERROR_DIR<<e.what()<<'\n';
            }

            return object;
        }

        /*
        *

        * Function Name : operator[]

        * Description : Overloading the subscript operator to allow indexing 

        * Parameters : index - > integer value of the column data to be returned 

        * Return : Handler object containing column of the original dataset which is defined in the parameter

        * Function Version : 0.0.0

        * Note negative indexing is supported since 0.0.0

        */
        
        Handler Handler::operator[](int index)
        {
            //Creating object to return
            Handler object;

            //Error_DIR
            ERROR_DIR = "<In function operator[]>";

            // Extraction of number of rows and columns
            std::size_t num_rows = Dataset.size();
            std::size_t num_cols = Dataset[0].size();

            //Creating a temporary storage data holder
            std::vector<double> Holder;

            try
            {
                // if negative indexing is provided
                if(index<0)
                {
                    //Converting to normal indexing
                    index = num_cols + index;
                }

                // if the index specified is larger than number of columns in the dataset then raise an error
                if(index > num_cols-1)
                {
                    std::cout<<"Received '"<<index<<"' but expected less than '"<<num_cols<<"'.\n";
                    throw std::range_error("Error : Handler index out of range");
                }

                // For each data item in the column
                for(std::size_t inc = 0;inc<num_rows;inc++)
                {
                    // Add the value to the temporary storage
                    Holder.emplace_back(Dataset[inc][index]);
                    object.Dataset.emplace_back(Holder);
                    Holder.clear();
                }


                
                object.Columns.emplace_back(Columns[index]);   
                // Clearing the temporary storage for next iteration.
                Holder.clear();
            }
            

            // Checking exceptions
            catch(const std::range_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<"\n";
            }

            catch(const std::exception& e)
            {
                std::cerr << e.what() <<"Unkown Error\n";
            }
            // Returning the object
            return object;

        }
        /*
        *

        * Function Name : operator[]

        * Description : Overloading the subscript operator to allow indexing by column name

        * Parameters : column - > column name (must be defined in Columns vector)

        * Return : Handler object containing column of the original dataset which is defined in the parameter

        * Function Version : 0.0.0

        *
        */
       Handler Handler::operator[](const std::string column) 
       {
           
           //The object to return
           Handler object;

           // Error directory
           ERROR_DIR = "<In function Handler::operator[]>";

           //Creating a temporary storage data holder
           std::vector<double> holder;

           // Iterator to store location of column name in Columns vector
           std::vector<std::string>::iterator name;

           // variable to store the index of the column in columns vector
           std:: ptrdiff_t index;

           // Extraction of number of rows and columns
           std::size_t num_rows = Dataset.size();


           try
           {
                //finding out the column by index first
                name = std::find(Columns.begin(),Columns.end(),column);
                
                //if the column was not found in COlumns
                if(name == Columns.end())
                {
                    
                    throw std::invalid_argument("Error : Column name '" + column + "' was not found.");
                }

                // Else store the original index of the column
                else
                {
                    index = std::distance(Columns.begin(),name);
                    object.Columns.emplace_back(Columns[index]);

                }
                
               // Storing the column
               for(std::size_t row=0;row<num_rows;row++)
               {
                  
                   holder.emplace_back(Dataset[row][index]);

                   object.Dataset.emplace_back(holder);
                   holder.clear();
               }
               

           }

           catch(const std::invalid_argument &e)
           {
               std::cerr<<ERROR_DIR << e.what() << '\n';
               
           }

           catch(const std::exception &e)
           {
               std::cerr<<ERROR_DIR<<e.what()<<": Unkown Error occurred.\n";
               
           } 

           
           return object;

       }
        /*
        *

        * Function Name : operator[]

        * Description : Overloading the subscript operator to allow indexing by column names

        * Parameters : columns - > column names (must be defined in Columns vector)

        * Return : Handler object containing columns of the original dataset which are defined in the parameter

        * Function Version : 0.0.0

        *
        */
       Handler Handler::operator[](const std::vector<std::string> columns) 
       {
           
           //The object to return
           Handler object;

           // Error directory
           ERROR_DIR = "<In function Handler::operator[]>";

           //Creating a temporary storage data holder
           std::vector<double> holder;

           // Iterator to store location of column name in Columns vector
           std::vector<std::string>::iterator name;

           // variable to store the index of the column in columns vector
           std:: ptrdiff_t index;

           // vector to store each columns's index from the original Column vector
           std::vector<std::size_t> column_by_index;

           // Extraction of number of rows and columns
           std::size_t num_rows = Dataset.size();


           try
           {
               // For each column
               for(std::string col:columns)
               {    
                   //finding out the column by index first
                   name = std::find(Columns.begin(),Columns.end(),col);
                   
                   //if the column was not found in COlumns
                   if(name == Columns.end())
                   {
                        throw std::invalid_argument("Error : Column name '" + col + "' was not found.");
                   }
                    
                   // Else store the original index of the column
                   else
                   {   
                       index = std::distance(Columns.begin(),name);
                       column_by_index.emplace_back(index);
                       object.Columns.emplace_back(Columns[index]);
                   }
               }

               // Storing the column
               for(std::size_t row=0;row<num_rows;row++)
               {
                  
                   for(std::size_t col:column_by_index)
                   {
                        holder.emplace_back(Dataset[row][col]);
                   }

                   object.Dataset.emplace_back(holder);
                   holder.clear();
               }
               

           }

           catch(const std::invalid_argument &e)
           {
               std::cerr<<ERROR_DIR << e.what() << '\n';
               
           }

           catch(const std::exception &e)
           {
               std::cerr<<ERROR_DIR<<e.what()<<": Unkown Error occurred.\n";
               
           } 

           
           return object;

       }

        /* 
        *

        * Function Name : operator()

        * Description : Overloading the () operator to allow row and column indexing

        * Parameters : rows - > vector of int containing rows index to be extracted
                    cols - > vector of int containing cols index to be extracted

        * Return : Handler object containing rows and columns of the original dataset which is defined in the parameters

        * Function Version : 0.0.0

        * Note negative indexing is supported since 0.0.0

        *
        */


        Handler Handler::operator()(std::vector<int> rows,std::vector<int> cols)
        {
            
            // Creating object of the class to be returned
            Handler object;

            //Error dir
            ERROR_DIR = "<In function operator()>";
            
            // Using a temporary storage
            std::vector<double> holder;

            // Extraction of number of rows and columns
            std::size_t num_rows = Dataset.size();
            std::size_t num_cols = Dataset[0].size();


            try
            {
                // For each row
                for(auto row:rows)
                {
                    // Check for negative indexes
                    if(row<0)
                    {
                        //Converting to normal indexing
                        row = num_rows + row;
                    }

                    // Checking for valid index
                    if(row > num_rows-1)
                    {
                        std::cout<<"Received '"<<row<<"' but expected less than '"<<num_rows<<"'.\n";
                        throw std::range_error("Error : Handler row index out of range.");
                        return object;
                    }

                    // For each column index
                    for(auto col:cols)
                    {
                        // Check for negative indexes
                        if(col<0)
                        {
                            //Converting to normal indexing
                            col = num_cols + col;
                        }

                        // Checking for valid index
                        if(col > num_cols-1)
                        {
                            std::cout<<"Received '"<<col<<"' but expected less than '"<<num_cols<<"'.\n";
                            throw std::range_error("Error : Handler column index out of range\n");
                            return object;
                        }
                        holder.emplace_back(Dataset[row][col]);     
                    }
                    object.Dataset.emplace_back(holder);
                    holder.clear();
                }
            }


            catch(const std::range_error& e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error.\n";
            }

            return object;
        }

        /*
        *

        * Function Name : operator()

        * Description : Overloading the () operator to allow row and column indexing

        * Parameters : rows - > int containing row index to be extracted
                    cols - > int containing col index to be extracted

        * Return : Handler object containing row and column of the original dataset which is defined in the parameters

        * Function Version : 0.0.0

        * Note negative indexing is NOT supported yet due to technical reasons.

        *
        */

        Handler Handler::operator()(int row,int col)
        {
            
            // Creating object of the class to be returned
            Handler object;
            
            // Using a temporary storage
            std::vector<double> holder;

            //Error dir
            ERROR_DIR = "<In function operator()>";

            // Extraction of number of rows and columns
            std::size_t num_rows = Dataset.size();
            std::size_t num_cols = Dataset[0].size();

            try
            {
              
            
                // Check for negative indexes
                if(row<0)
                {
                    //Converting to normal indexing
                    row = num_rows + row;
                }

                // Checking for valid index
                if(row > num_rows-1)
                {
                    std::cout<<"Received '"<<row<<"' but expected less than '"<<num_rows<<"'.\n";
                    throw std::range_error("Error : Handler row index out of range.");
                }

                if(col<0)
                {
                    //Converting to normal indexing
                    col = num_cols + col;
                }

                // Checking for valid index
                if(col > num_cols-1)
                {
                    std::cout<<"Received '"<<col<<"' but expected less than '"<<num_cols<<"'.\n";
                    throw std::range_error("Error : Handler row index out of range.");
                    
                }

                holder.emplace_back(Dataset[row][col]);     
                    
                object.Dataset.emplace_back(holder);
                holder.clear();
            }

            catch(const std::range_error& e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<"\n";
            }

            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error.\n";
            }

            return object;
        }

        /* Overloading the extraction operator */
        std::ostream& operator<<(std::ostream& os, const Handler &obj)
        {
            
            try
            {
                //Extracting number of cols and rows of Dataset vector
                const std::size_t cols = obj.columns();
                const std::size_t rows = obj.rows();
                const std::size_t size = obj.size();
                const std::size_t memory = obj.memory_usage();

                // Displaying column names first
                for(auto col:obj.Columns) std::cout<<col<<' ';
                std::cout<<'\n';

                // Displaying the dataset
                for(auto row:obj.Dataset)
                {
                    for(auto col:row)
                    {
                        os<<col<< " ";
                    }

                    os<<"\n";
                 }

                // Extra details about handler object
                os<<"\nNumber of row : "<<rows<<'\n';
                os<<"Number of columns : "<<cols<<'\n';
                os<<"Number of elements : "<<size<<'\n';
                os<<"Memory usage : "<<memory<<" bytes\n";
            }

            catch(const std::exception &e)
            {
                std::cerr<<e.what()<<"Unkown Error\n";
            }

            return os;
        }
    }


}
