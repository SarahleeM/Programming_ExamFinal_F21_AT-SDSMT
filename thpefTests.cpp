#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpef.h"
#include "ourDate.h"

const bool RUNCATCH = true;

//Main Function ========================================================================================================
int main( int argc, char **argv )
{
    Catch::Session session;
    int result;
    
    //Test case running 
    if( RUNCATCH == true )
    {
        result = session.run();
        if( result != 0 )
        {
            cout << "Test cases didnt pass." << endl;
            return result;
        } 
    }

    //Initializers =====================================================================================================
    bool tf = false; //Boolian hold value
    int i, j; //Counter values

    string fullLine;
    userData currUser;

    string inputFile;
    string tempPurFile;
    string tempPayFile;
    string tempDueFile;
    string newDate;
    ifstream input;
    ifstream tempPur;
    ifstream tempPay;
    ifstream tempDue;
    
    //Program Here =====================================================================================================
    if( argc != 5 )
    {
        cout << "Usage: thpef.exe datafile template1 template2 template3" << endl;
        cout << "       datafile --name of input data file" << endl;
        cout << "       template1 --name of purchase template file" << endl;
        cout << "       template2 --name of payment template file" << endl;
        cout << "       template3 --name of overdue template file" << endl;

        return 0;
    }

    //Setting the arguments to the appropriate strings
    inputFile = argv[1];
    tempPurFile = argv[2];
    tempPayFile = argv[3];
    tempDueFile = argv[4];

    //Opening and checking the input ===================================================================================
    tf = openInput( input, inputFile );
    if( tf == false )
    {
        cout << "Unable to open the input file: " << inputFile << endl;
        return 0;
    }

    
    
    
    //Input / Write loop ===============================================================================================
    while( getClient( input, currUser ) )
    {
        if( currDate == "" )
        {
            newDate = getDate();
            if( 0 < currUser.transaction )
            {
                writeLetter( currUser, tempPurFile, newDate );
            }
            if( currUser.transaction < 0 )
            {
                writeLetter( currUser, tempPayFile, newDate );
            }
            if( currUser.transaction == 0 )
            {
                writeLetter( currUser, tempDueFile, newDate );
            }
        }
        else
        {
            if( 0 < currUser.transaction )
            {
                writeLetter( currUser, tempPurFile, currDate );
            }
            if( currUser.transaction < 0 )
            {
                writeLetter( currUser, tempPayFile, currDate );
            }
            if( currUser.transaction == 0 )
            {
                writeLetter( currUser, tempDueFile, currDate );
            }
        }
    }

    //Closing the files ================================================================================================
    input.close();
    tempPur.close();
    tempPay.close();
    tempDue.close();

    return 0;
}

//Test cases ===========================================================================================================
TEST_CASE( "openInput - testing if the input file opens" )
{
    string data = "dataTest.txt";
    ifstream datafile;
    bool ans;

    ans = openInput( datafile, data );
    CHECK( ans == true );

    datafile.close();
}

TEST_CASE( "openInput - testing if the input file fails to open" )
{
    string data = "dataTests.txt";
    ifstream datafile;
    bool ans;

    ans = openInput( datafile, data );
    CHECK( ans == false );
}

TEST_CASE( "openOutput - testing if it opens the output files" )
{
    string output = "primeTest.txt";
    ofstream outfile; 
    bool ans;

    ans = openOutput( outfile, output );
    CHECK( ans == true );

    outfile.close();
}

TEST_CASE( "openOutput - testing if it fails to open output" )
{
    string output = "z:\\primeTests.txt";
    ofstream outfile; 
    bool ans;

    ans = openOutput( outfile, output );
    CHECK( ans == false );
}

TEST_CASE( "getDate - testing today (12/8/21)" )
{
    string time;
    
    time = getDate();

    CHECK( time == " 8 Dec, 2021" );
}

TEST_CASE ( "getClient - testing just one string" )
{
    string data = "dataTest.txt";
    ifstream datafile;
    bool ans;
    userData user;

    ans = openInput( datafile, data );
    CHECK( ans == true );

    getClient( datafile, user );
    CHECK( user.firstName == "Sarahlee" );
    CHECK( user.lastName == "Maxwell" );
    CHECK( user.street == "13805 Box Canyon" );
    CHECK( user.city == "Rapid City" );
    CHECK( user.state == "SD" );
    CHECK( user.zip == "57744" );
    CHECK( user.transaction == 20 );
    CHECK( user.balance == 10 );

    datafile.close();

}

TEST_CASE ( "getClient - testing from the datafile" )
{
    string data = "datafile1.txt";
    ifstream datafile;
    bool ans;
    userData user;

    ans = openInput( datafile, data );
    CHECK( ans == true );

    getClient( datafile, user );
    CHECK( user.firstName == "James" );
    CHECK( user.lastName == "Smith" );
    CHECK( user.street == "123 Main St" );
    CHECK( user.city == "Rapid City" );
    CHECK( user.state == "SD" );
    CHECK( user.zip == "57701" );
    CHECK( user.transaction == 89.55 );
    CHECK( user.balance == 12.5 );

    datafile.close();

}
 
TEST_CASE( "writeLetter - testing it output to a file" )
{
    userData user;
    ofstream purchase;
    bool tf;
    string purTemplate = "purchaseTemplate.txt";
    string date = " 7 Dec, 2021";
    string ans;

    user.firstName = "Sarahlee";
    writeLetter( user, purTemplate, date);

    //Manually check the file...
}
