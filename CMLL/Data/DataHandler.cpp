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

* File version : 0.0.3

* The contents of the program are distributed with versions numbers. If a particular function or content fails to execute, replace it with previous version from the backup folder.

* Date Created  : FEB_8_20_21_12
 
* Last modified : APR_06_20_14_33

* Change Logs : 

 
        1) Date : 06-04-2020 Time : 14:33 [ VERSION 0.0.1]
        Namespace data
        # Added new function read_all
        # Multi type file, categorical data now can be loaded using read_all which will automatically label encode non numeric data and assign Nan to missing values
        
        Handler class
        # Added new attribute Encoded to store the Label encoding
        # function clear now also clears the Encoded attribute

        2) Date : 05-04-2020 Time : 19:36
        Namespace data
        # function insert is now a member of data namespace and a friend of Handler class
        # Function read now accepts mandatory column names and stores them separately.
        # Function read can now prompt for missing values in the column names row
        # Function read now prompts for missing values by invalid structure of file. 
        
        Robust exceptional handling implemented

        Handler class
        # Extraction operator << is now overload for cout
        # Subscript operator [] now also accepts either column name(string) or vector of column name(vector<string>) as parameter
        
        3) Date : 04-04-2020 Time : 23:15
        #Handler and functions under file namespace are moved to a new common namespace data
        #Added a new function read_columns under the namspace data
        
        Handler class
            #Added new function create()
            #Added new function save()
            #Added new function memory_usage()
            #Negative indexing is now supported in all overloads
        

        4) Date : 28-03-20 Time : 22:21
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
    
        
        /*
        *

        * Constructor Name : Handler

        * Description : Default constrctor defined

        * Paramteres :  None

        * Constructor Version : 0.0.0

        *
        */
        Handler::Handler()
        {
        
        }

        /*
        *

        * Constructor Name : Handler

        * Description : constructor to load defaults

        * Paramteres :  dataset -> THe vector of vectors (STORAGE)
                        column_names - > Name of columns in order

        * Constructor Version : 0.0.0

        *
        */
        Handler::Handler(const STORAGE &dataset, const std::vector<std::string> &column_names)
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

        * Function Version : 0.0.1
        
        * NOTE : Except for the Column names row all other rows should only contain , int,float or double types
        * since xlxs files are binary format the cannot be opened with read(), expect a separate function for those files in version 1.0

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
                    throw std::runtime_error("Error :  Cannot access file. Either it doesn't exist or permission is required");

            }
            
            // Variable to sore the column names column
            std::string column_line;

            // getting the first column
            std::getline(_file,column_line,line_separator);
            
            // Extracting the column names and number o columns
            num_columns = read_columns(object,column_line,line_separator,value_separator);

            //Since it was read() the Encoding is supposed to be empty but to maintain continuity
            object.Encoded.resize(num_columns);

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
                            
                            std::cout<<"The Number of columns are "<<column<<". Expected were "<<num_columns<<"\n";
                            throw std::length_error("Error : The csv format is not preserved in the file.");
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
                        throw std::invalid_argument("Error : Bad shape.");
                    }

            }

                // Adding the last row to the dataset. Also checking for integrity of the format.
                if(!data_holder.empty())
                object.Dataset.emplace_back(data_holder);

                if(column!=0) throw std::runtime_error("Error : File was not read completely due to unkown error.If file contains categorical data use read_all()");
            }

            // Catiching all the exceptions
            catch(const std::invalid_argument &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
                
                
            }

            catch(const std::length_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
                
            }

            catch(const std::runtime_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
               
            }
            catch(const std::bad_alloc &e)
            {
                std::cerr<<ERROR_DIR<<"Error : Cannot allocated memory.\n";
                object.clear();
            }
            catch(const std::exception &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
              
            }

            _file.close();  
                
            // Returning the object (let copy constructure handle the rest)
            return object;

        }

        /*
        *

        * Function Name : read_all

        * Description : Function to read a file and store the contents in vector of vectors of double a.k.a STORAGE (See defined.hpp for typedef).

        * Parameters : filename -> The filename of the file to read.
                    : value_separator -> The delimeter that separates different observations in thefile (default = ',') 
                    : line_seperator - > The delimeter which separates lines (default '\n') 
        * Return : Object of the class Handler

        * Function Version : 0.0.0
        
        * NOTE : This function can handle non binary type values. Expect this function to be slower than read due to extra overhead
        *        Do not use this function if your file contains only numerical values except for in the column names row.
        * since xlxs files are binary format the cannot be opened with read(), expect a separate function for those files in version 1.0

        *
        */
        Handler read_all(const std::string &filename,const char &line_separator,const char &value_separator)
        {
            /*
            This function is useful when the file to load has values in different formats

            The working of the function is at follows

            1) Read the column line using read_columns function
            2) Read each line at a time (line ends at line_separator)
            3) split the line based on value separator to get new strings and for each string
            4) if the new formed string can be converted into a integer then store the converted integer.
               else store the string in a labeled vector (The label vector's index defines what label is the string mapped to)
            5) Keep reading, do not store already stored string in the labelled vector
            6) Fill the string spaces with the assigned label
            7) If a row has lesser number of columns or/and missing values automatically assign NaN to get equal number of columns as in first row (column names row)
            8) However, if number of columns exceed the number of columns in first row (column name row) throw a length error

            Note : This function can handle missing/Nan/Null values in contrast to read function. However this function may be slow depending upon how many categorical values are present.
            */
            
            // Handler object to return
            Handler object;

            // Error directory
            const std::string ERROR_DIR = "<In function Handler::read_all>";

            // Number of columns
            std::size_t num_columns;

            //Location to string in the encoded vector 
            std::vector<std::string>::iterator locate;

            // Temporary column holder
            std::vector<double> data_holder;

            
            // opening the file
            std::ifstream _file(filename);

            // Variable to keep count of column to read
            std::size_t column=0;
            
            try
            {
                if(!_file) throw std::runtime_error("Error :  Cannot access file. Either it doesn't exist or permission is required");

                // Variable to sore the column names column
                std::string column_line;

                // getting the first column
                std::getline(_file,column_line,line_separator);
                
                // Extracting the column names and number of columns
                num_columns = read_columns(object,column_line,line_separator,value_separator);

                // Resizing the encoded vector according to the number of columns
                object.Encoded.resize(num_columns);
            
                // storing single character
                std::string line;

                // Storing the string to number converion
                double converted_number;

                // iterator for location indexing
                std::vector<std::string>::iterator location;

                // storing single value
                std::string value; 

                // Reading rest of the file line by line
                while(std::getline(_file,line,line_separator))
                {   
                    
                    column = 0;
                    //converting to string stream
                    std::istringstream line_stream(line);

                    // For each value (seperated by value_separator)
                    while(std::getline(line_stream,value,value_separator))
                    {
                        
                        // If it is a missing value
                        if(value=="")
                        {
                            //Assign Nan to it
                            data_holder.emplace_back(std::numeric_limits<double>::quiet_NaN());
                        }
                        
                        // if its not a missing value
                        else
                        {
                            try
                            {   // Trying to convert the string to number
                                converted_number = std::stod(value);

                                // If possible (or expection would have been thrown by now (std::invalid_argument) or (std::length_error)) save the number
                                data_holder.emplace_back(converted_number);
                            }
                            catch(const std::invalid_argument e)
                            {
                                /* If the string couldn't be converted to a number, label encode it and save the encoded number
                                 If the string already saved, discard the string and save the encoded number with the string
                                 */
                                
                                // Checking if the string is already encoded 
                                location = std::find(object.Encoded[column].begin(),object.Encoded[column].end(),value);

                                // If not already encoded , encode it at assign it the encoded value
                                if(location == object.Encoded[column].end())
                                {
                                    object.Encoded[column].emplace_back(value);
                                    data_holder.emplace_back(object.Encoded[column].size()-1);
                                }

                                // If is already encoed
                                else
                                {
                                    // Store already assigned label to it (i.e its index)
                                    data_holder.emplace_back(std::distance(object.Encoded[column].begin(),location));
                                }
                                
                            }
                            catch(const std::length_error &e)
                            {
                                throw std::length_error(e.what());                        
                            }
                        }
                        column++;

                        
                    }
                    // If the number of columns is lesser than what it is supposed to be. Fill them with NaN value;
                    if(column < num_columns)
                    {
                       while(column != num_columns)
                       {    
                            data_holder.emplace_back(std::numeric_limits<double>::quiet_NaN());
                            column++;
                       }
                    }

                    // If the number of columns exceed then what it is supposed to be. Terminate the process
                    if(column != num_columns)
                        {
                            std::cout<<"The Number of columns are "<<column<<". Expected were "<<num_columns<<"\n";
                            throw std::length_error("Error : The csv format is not preserved in the file.");
                        }
                        

                    
                    object.Dataset.emplace_back(data_holder);
                    data_holder.clear();

                }
                    
               
            }
            
            
            catch(const std::runtime_error &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
            }

            catch(const std::invalid_argument &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
            }

            catch(const std::length_error &e)
            {
                 std::cerr<<ERROR_DIR<<e.what()<<'\n';
                 object.clear();
            }

            catch(const std::out_of_range& e)
            {
                 std::cerr<<ERROR_DIR<<e.what()<<'\n'; 
                 object.clear();  
            }

            catch(const std::bad_alloc &e)
            {
                std::cerr<<ERROR_DIR<<"Error : Cannot allocated memory.\n";
                object.clear();
            }
            catch(const std::exception &e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
                object.clear();
            }
            
            _file.close();

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

        Handler create(const STORAGE &dataset, const std::vector<std::string> &column_names)
        {
            
            Handler object;

            // Error directory
            const std::string ERROR_DIR = "<In function Handler::read>";

            //Number of columns
            std::size_t cols = column_names.size();

            //Resizing the encoded
            object.Encoded.resize(cols);

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
                object.clear();
            }
            
            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error occurred\n";
                object.clear();
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
            //Error dir
            ERROR_DIR = "<In function Handler::insert>";
            
            //Number of columns
            std::size_t max_index = Dataset[0].size();

            try
            {
               //If negative indexing is done , convert to normal indexing
               if(position < 0 ) position = max_index + position;
               
               // If index is out of range
               if(position >= max_index) 
               {
                   //throw exception
                   std::cout<<"Expected index less than "<<max_index<<". Got "<<position<<".";
                   throw std::length_error("Error : Position index is out of range");
               }

               // For each row add the column values
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
               
               //Adding the no encoded flag
               Encoded.insert(Encoded.begin()+position,{{}});
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
            //Error directory
            ERROR_DIR = "<In function Handler::insert>";

            // Number of columns
            std::size_t max_index = Dataset[0].size();
            
            
            try
            {  //If negative indexing is done , convert to normal indexing
               if(position < 0 ) position = max_index + position;
               
               // If index out of range
               if(position >= max_index) 
               {
                   // throw exception
                   std::cout<<"Expected index less than "<<max_index<<". Got "<<position<<".";
                   throw std::length_error("Error : Position index is out of range");
               }

               // for each row 
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

               //Adding the no encoded flag
               Encoded.insert(Encoded.begin()+position,{{}});

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
        
        * Function Version : 0.0.1

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

            // Deleting any label encoding (if done)
            Encoded.clear();

            //Shrinking to remove allocated memory
            Encoded.shrink_to_fit();
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

        * Return : STORAGE (see DataHandler.hpp for typedef) variable

        * Function Version : 0.0.0


        *
        */

        STORAGE Handler::get() const
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
            // Discarding the space taken by Columns vector and Encoded vector
            // Each value is a double takes size_of(double) bytes
            // So a N*N handler object will take size_of(double)*n*n bytes
            return (sizeof(double)*rows()*columns());

        }

        /*
        *

        * Function Name : show

        * Description :  Function to do a pretty print of the Handler object along with additional information such as label encoded values

        * Parameters : None

        * Return : None

        * Function Version : 0.0.0

        * Note this function convers doubles to string for pretty print. Expect this function to be slow on larger datasets. using std::cout is recommended
        *
        */
        void Handler::show()
        {
            

            ERROR_DIR = "<In function Handler::show>";
            try
            {
                // Dataset size
                const std::size_t num_rows = Dataset.size();

                if(!num_rows) throw std::invalid_argument("Error : Empty Handler Object.");

                // Columns
                const std::size_t num_cols = Dataset[0].size();
                
                
                //Vector to hold size the elements would take on input
                std::vector<int> Maximum_width_column(Dataset[0].size());

                // Width of the output buffer
                std::size_t width;

                std::size_t row,col;


                // Initially assuming the column names to be the maximum width required
                for(col=0;col<num_cols;col++)
                {
                    Maximum_width_column[col] = Columns[col].length();
                }
                
                
                //Finding largest width for each column

                // For each row 
                for(row=0;row<num_rows;row++)
                {
                    //For each column
                    for(col=0;col<num_cols;col++)
                    {
                        //If the column was labelled encoded
                        if(Encoded[col].size())
                        {
                            //Calculate the width of the original string on the row
                            width = Encoded[col][Dataset[row][col]].length();
                        }
                        // If the column wasn't label encoded
                        else
                        {
                        //Calculate the width the number takes
                        width = std::to_string(Dataset[row][col]).length();
                        }
                    
                        // If the width is greater than  previously stored
                        if( width > Maximum_width_column[col])
                        {
                            //Update it
                            Maximum_width_column[col] = width;
                        }
                    }
                }
                
                // Drawing th first line of ----'s   
                for(col=0;col<num_cols;col++)
                {
                std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill('-')<<'-'<<" + ";
                }

                std::cout<<'\n';


                // Printing the columns first   
                for(col=0;col<num_cols;col++)
                {
                    std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill(' ')<<Columns[col]<<" | ";

                }
                std::cout<<'\n';


                // Drawing ___'s right after column names to distinguish them
                for(col=0;col<num_cols;col++)
                {
                std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill('_')<<'_'<<" + ";
                }
                std::cout<<'\n';


                // For each row in the dataset
                for(row=0;row<num_rows;row++)
                {
                    // For each column
                    for(col=0;col<num_cols;col++)
                    {
                            // If the column was label encoded
                            if(Encoded[col].size())
                            {
                                // Display the original string value
                                std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill(' ')<<Encoded[col][Dataset[row][col]]<<" | ";
                            }

                            //If was not label encoded
                            else
                            {   
                                // Display the numerical value
                                std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill(' ')<<Dataset[row][col]<<" | ";
                            }
                            
                    }
                    std::cout<<'\n';
                    
                    // After every row add extra ----'s for formatting
                    for(col=0;col<num_cols;col++)
                    {
                        std::cout<<std::right<<std::setw(Maximum_width_column[col])<<std::setfill('-')<<'-'<<" + ";
                    }
                    std::cout<<'\n';

                }

                //Displaying additional information
                std::cout<<"\nAdditional Information : \n\n";
                encoded_details();

                std::cout<<"\nNumber of row : "<<num_rows<<'\n';
                std::cout<<"Number of columns : "<<num_cols<<'\n';
                std::cout<<"Number of elements : "<<num_rows*num_cols<<'\n';
                std::cout<<"Memory usage : "<<memory_usage()<<" bytes\n";
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            
            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<'\n';
            }
            

        }

        /*
        *

        * Function Name :encoded_details

        * Description :  Function to show details of column encoding that was done while reading the file using read_all()

        * Parameters : None

        * Return : None

        * Function Version : 0.0.0
        *
        */
        void Handler::encoded_details()
        {
            
            //if no encoding was done
            if(!Encoded.size())
            {
                std::cout<<"No encoding was done.\n";
                return;
            }
            
            
            //Displaying the label encoding that occurred
            for(int i=0;i<Encoded.size();i++)
            {
                
                if(Encoded[i].size())
                {
                    std::cout<<"Label Encoding of column '"<<Columns[i]<<"'.\n";
                    for(int j=0;j<Encoded[i].size();j++)
                    {
                        std::cout<<Encoded[i][j]<<" : "<<j;
                        if(j<Encoded[i].size()-1) std::cout<<", ";
                    }
                    std::cout<<"\n\n";
                }
    
            
            }
        }

        /*
        *

        * Function Name :get_encoded_details

        * Description :  Function to return the Encoded vector

        * Parameters : None

        * Return : Encoded : The vector of vector of strings containing the encoded strings which enoded values as the index

        * Function Version : 0.0.0
        *
        */
        std::vector<std::vector<std::string>> Handler::get_encoded_details() const
        {
            
            //If no encoding took place
            if(!Encoded.size())
            {
                std::cout<<"<In function Handler::get_encoded_details>Warning : No encoding was done.Returned vector is empty.\n";
            }

            return Encoded;
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

            object.Encoded.resize(indexes.size());
            
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
                            if(row == 0) 
                            {
                                object.Columns.emplace_back(Columns[col]);
                                
                                //Updating encoding if defined.
                                if(Encoded[col].size())
                                {
                                    object.Encoded[col] = Encoded[col];
                                } 
                            }
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

            object.Encoded.resize(1);

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
                
                //Updating encoding if defined.
                if(Encoded[index].size())
                {
                   object.Encoded[0] = Encoded[index];
                } 
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

           //Creating space for Encoding
           object.Encoded.resize(1);

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
               if(Encoded[index].size())
                {
                   object.Encoded[0] = Encoded[index];
                } 
               

           }

           catch(const std::invalid_argument &e)
           {
               std::cerr<<ERROR_DIR << e.what() << '\n';
               object.clear();
               
           }

           catch(const std::exception &e)
           {
               std::cerr<<ERROR_DIR<<e.what()<<": Unkown Error occurred.\n";
               object.clear();
               
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

           //Resizing the encoding vector
           object.Encoded.resize(columns.size());

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
                      
                        //Copying the encoding (if present)
                       if(Encoded[index].size())
                       {
                           object.Encoded[index] = Encoded[index];
                       }
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
               object.clear();
               
           }

           catch(const std::exception &e)
           {
               std::cerr<<ERROR_DIR<<e.what()<<": Unkown Error occurred.\n";
               object.clear();
               
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

            //Creating space for Encoding
            object.Encoded.resize(cols.size());

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

                            
                            
                        }

                        if(row==0)
                        {
                            object.Columns.emplace_back(Columns[col]);
                            if(Encoded[col].size())
                            {
                                object.Encoded[col] = Encoded[col];
                            }
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
                object.clear();
            }
            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error.\n";
                object.clear();
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
        *
        */

        Handler Handler::operator()(int row,int col)
        {
            
            // Creating object of the class to be returned
            Handler object;

            //Creating space for Encoding
            object.Encoded.resize(1);
            
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
                
                object.Columns.emplace_back(Columns[col]);

                
                if(Encoded[col].size())
                {
                    object.Encoded[0] = Encoded[col];
                }
                   
                object.Dataset.emplace_back(holder);
                holder.clear();
            }

            catch(const std::range_error& e)
            {
                std::cerr<<ERROR_DIR<<e.what()<<"\n";
                object.clear();
            }

            catch(const std::exception& e)
            {
                std::cerr<<ERROR_DIR<< e.what() <<"Unkown Error.\n";
                object.clear();
            }

            return object;
        }

        /*
        *

        * Function Name : operator=

        * Description : Overloading the = operator to allow assignment 

        * Parameters : object : Handler object

        * Return : Handler object 

        * Function Version : 0.0.0

        *
        *

       Handler &Handler::operator=(const Handler &object)
       {
            Dataset = object.Dataset;
            Columns = object.Columns;
            Encoded = object.Encoded;

            return *this;
       }
        */

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
                for(auto col:obj.Columns) std::cout<<col<<" ";
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
