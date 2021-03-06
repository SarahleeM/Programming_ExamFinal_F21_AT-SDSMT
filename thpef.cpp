#include "thpef.h"

//write functions here
 
/** ****************************************************************************
 *  @author Sarahlee Grace Maxwell
 *
 *  @par Description
 *      A boolian function that opens the input file
 *
 *  @param[in] datafile The input file to be opened 
 *  @param[in] input the string holding the input file name
 *  
 *  @returns True if the input file opens and 
 *           False if the input file fails to open
 * 
 *  @par Example
 *  @verbatim
 * ifstream inputFile;
 * string fileName = file1.txt;
 * bool tf;
 * 
    tf = openInput( inputFile, fileName );
    //True if the file opens
    //False if the file fails to open

    @endverbatim
 ******************************************************************************/ 
bool openInput( ifstream &datafile, string input )
{
    datafile.open( input );
    if( !datafile.is_open() )
    {
        return false;
    }
    return true;
}

/** ****************************************************************************
 *  @author Sarahlee Grace Maxwell
 *
 *  @par Description
 * A boolian function that opens the output file
 *
 *  @param[in] datafile The output file to be opened 
 *  @param[in] output the string holding the output file name
 *  
 *  @returns True if the output file opens and
 *           False if the output file fails to open

 *  @par Example
 *  @verbatim
 * ifstream outputFile;
 * string fileName = fileOut1.txt;
 * bool tf;
 * 
    tf = openOutput( outputFile, fileName );
    //True if the file opens
    //False if the file fails to open

    @endverbatim
 ******************************************************************************/ 
bool openOutput( ofstream &datafile, string output )
{
    datafile.open( output );
    if( !datafile.is_open() )
     {
        return false;
    }
    return true;
}

/** ****************************************************************************
 *  @author Sarahlee Grace Maxwell
 *
 *  @par Description
 *      A string function that returns the current date
 *
 *  @returns A string holding the current date in "Day, Month, Year" order
 *  
 *  @par Example
 *  @verbatim
 *  string time;
 * 
    time = getDate();
    //Time == " 4 Dec, 2021" if the date is 12/4/21
    
    @endverbatim
 ******************************************************************************/ 
string getDate()
{
    time_t myTimeT = time(NULL);
    string currTime = ctime( &myTimeT );
    string day;
    string month;
    string year;

    day = currTime.substr( 8, 2 );
    month = currTime.substr( 4, 3 );
    year = currTime.substr( 20, 4 );

    currTime = day + " " + month + ", " + year;
    
    return currTime;
}

/** ****************************************************************************
 *  @author Sarahlee Grace Maxwell
 *
 *  @par Description
 *      A boolian function that reads in data from an open ifstream and assigns
 *    the data to a structure for userData
 * 
 *  @param[in] input The input file
 *  @param[in] user The structure to hold the users data
 *
 *  @returns True if data was read in
 *           False if data was not read in
 *  
 *  @par Example
 *  @verbatim
    ifstream datafile;
    bool ans;
    userData user;

    bool = getClient( datafile, user );
    //data is read in from datafile and assigned to user

    
    @endverbatim
 ******************************************************************************/
bool getClient( ifstream &input, userData &user )
{
    string hold;
    string first, last, streetName, cityName, stateName, zipCode, transac, bal;
    double transacNum, balNum;
    
    bool tf;
    int i, j, l;
    int stringSize;

    while( getline( input, hold ) )
    {
        //Getiing the first name
        i = hold.find( "," ); //i becomes the high value
        first.assign( hold, 0, i ); //0 is the low value
        i++; 
        //Getting the last name
        j = hold.find( ",", i ); //j becomes the high value and i is the low
        l = j - i; //We take the high - low to get the str size
        last.assign( hold, i, l );
        j++;
        //Getting the street address
        i = hold.find( ",", j ); //i becomes the high value and j is the low
        l = i - j; //We take the high - low to get the str size
        streetName.assign( hold, j, l );
        i++;
        //Getting the city
        j = hold.find( ",", i ); //The pattern repeats
        l = j - i;
        cityName.assign( hold, i, l );
        j++;
        //Getting the state
        i = hold.find( ",", j );
        l = i - j;
        stateName.assign( hold, j, l );
        i++;
        //Getting the zip
        j = hold.find( ",", i );
        l = j - i;
        zipCode.assign( hold, i, l );
        j++;
        //Getting the transaction
        i = hold.find( ",", j );
        l = i - j;
        transac.assign( hold, j, l );
        i++;
        //Getting the balance
        stringSize = hold.size(); //This is the last value so we can use the end of the string as a high value
        l = stringSize - i; //Still need to get string for ballance
        bal.assign( hold, i, l );

        //Converting the transaction and ballance strings to doubles
        transacNum = stod( transac );
        balNum = stod( bal );

        //Actually assigning the strings and doubles to the userData
        user.firstName = first;
        user.lastName = last;
        user.street = streetName;
        user.city = cityName;
        user.state = stateName;
        user.zip = zipCode;
        user.transaction = transacNum;
        user.balance = balNum;

        return true;
    }
    

    return false;

}

/** ****************************************************************************
 *  @author Sarahlee Grace Maxwell
 *
 *  @par Description
 *      A void function that fills out a given template using given data
 * 
 *  @param[in] user The structure to hold the users data
 *  @param[in] temp The string holding the template file name
 *  @param[in] date The string holding the date
 * 
 *  
 *  
 *  @par Example
 *  @verbatim
    userData user;
    string temp = "template1.txt";
    string date = " 7 Dec, 2021";

    writeLetter( user, temp, date );
    //Fills in template1 with given data
    
    @endverbatim
 ******************************************************************************/
void writeLetter( userData user, string temp, string date )
{
    bool tf = false;
    
    ifstream purTemplate;
    ofstream output;
    string out;
    string hold;
    string asigned;
    string name;
    int i, j, l;
    int dateVal;
    int tran;
    int bal;
    string transactionVal;
    string balVal;
    ostringstream myStream;



    //Opening the input and output files =======================================
    tf = openInput( purTemplate, temp );
    if( tf == false )
    {
        cout << "Unable to open the input file: " << temp << endl;
        return;
    }
    out = user.firstName + "." + user.lastName + ".txt";
    tf = openOutput( output, out );
    if( tf == false )
    {
        cout << "Unable to open the template file: " << temp << endl;
        return;
    }

    

    //Setting the new ballance for the 2 transactions
    if( 0 < user.transaction ) 
    {
        user.balance = user.balance + user.transaction;
    }
    if( user.transaction < 0 )
    {
        user.transaction = abs( user.transaction );
        user.balance = user.balance - user.transaction;
    }

    
    
    myStream << fixed << setprecision(2);
    myStream << user.transaction;
    transactionVal = myStream.str();
    myStream.str("");
    myStream << fixed << setprecision(2);
    myStream << user.balance;
    balVal = myStream.str();
    myStream.str("");


    
    while( getline( purTemplate, hold ) )
    {
        dateVal = hold.find( "#DATE" );
        tran = hold.find( "$#TRANSACTION" );
        bal = hold.find( "$#BALANCE" );
        if( string::npos != hold.find( "#FULLNAME" ) )
        {
           name = user.firstName + " " + user.lastName;
           i = hold.find( "#FULLNAME" );
           hold.replace( i, 9, name );
           
        }
        if( string::npos != hold.find( "#ADDRESS" ) ) 
        {
           i = hold.find( "#ADDRESS" );
           hold.replace( i, 8, user.street );
        }
        if( string::npos != hold.find( "#DATE" ) )
        {
           i = hold.find( "#DATE" );
           hold.replace( i, 5, date );
        }
        if( string::npos != hold.find( "#CITY" ) )
        {
            i = hold.find( "#CITY" );
            hold.replace( i, 5, user.city );
        }
        if( string::npos != hold.find( "#STATE" ) )
        {
            i = hold.find( "#STATE" );
            hold.replace( i, 6, user.state );
        }
        if( string::npos != hold.find( "#ZIP" ) )
        {
            i = hold.find( "#ZIP" );
            hold.replace( i, 4, user.zip );
        }
        if( string::npos != hold.find( "#FIRST" ) )
        {
            i = hold.find( "#FIRST" );
            hold.replace( i, 6, user.firstName );
        }
        if( string::npos != hold.find( "#TRANSACTION" ) )
        {
            i = hold.find( "#TRANSACTION" );
            hold.replace( i, 12, transactionVal );
        }
        if( string::npos != hold.find( "#BALANCE" ) )
        {
            i = hold.find( "#BALANCE" );
            hold.replace( i, 8, balVal );
            
        }
        if( string::npos != hold.find( "#LAST" ) )
        {
            i = hold.find( "#LAST" );
            hold.replace( i, 5, user.lastName );
            
        }
        
        
        
        output << hold << endl;
        

    }     

}
