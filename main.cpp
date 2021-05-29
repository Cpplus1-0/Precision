#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

string parseDoubles(double flop, int precisiondex);
string parseDouble(double flop, int precisiondex);
string parseInt(int whole);
string parseFraction(double fraction, int precisiondex);
string finalCall(double flop, int precisiondex);
string ready(double flop, int precisiondex, bool click);
string readyNO(double flop, int precisiondex, bool click);

int main()
{
    //Welcome Prompt
    cout << "This program parses floating point values into strings and performs number analysis. " << endl << endl;

    //Primary Variable Input Prompt
    cout << "Enter a floating point number: ";
    double flop;
    cin >> flop;

    //Precision Input Prompt
    cout << endl << "The precision is originally set to 10 decimal places. " << endl << "It can be changed to anything between 0 to 50. " << endl << endl << "Do you want to change the precision index? (y/n): ";

    //Input Buffer Clearance
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //Buffer Clearance Assured

    char input;
    //Input Mismatch Exception Handle
    for(cin >> input; input != 'y' && input != 'n' && input != 'Y' && input != 'N'; cin >> input)
        cout << "Sorry, your input could not be validated. Please press 'y' or 'n' on your keyboard. " << endl << endl << "Do you want to set the precision index? (y/n):";

    //Precision Initialization Process
    int precision = 10;
    if(input == 89 || input == 121)
    {
        cout << "Enter the precision: ";
        //Input
        for(cin >> precision; precision < 0 || precision > 50; cin >> precision)
            cout << "Sorry, the precision you have entered is out of bounds. Please try again. " << endl << endl << "Enter a precision index between the interval [0, 50] " << endl;
    }
    //Precision Initialization Complete

    //Precision Setup Confirmation
    cout << endl << "Precision set to " << precision << endl << endl;

    //Whole
    cout << "The whole number in string format is : '" << parseInt((int) flop) << "'" << endl << endl;
    //Partial
    cout << "The fractional portion in string format is: " << parseFraction(flop - (int)flop, precision) << endl << endl;

    //Whole + Partial
    cout << "The floating point number in string format is: " << parseDouble(flop, precision) << endl << endl;

    //Final Recursive Call
    cout << "Final Recursive call double precision indexing: " << finalCall(flop, precision) << endl << endl;

    //Thank You Prompt
    cout << endl << "Thank you for using this program! " << endl;

    return 0;
}

//Call Ready Function -> Full Optimization
string ready(double flop, int precisiondex, bool click)         //Testing: 343.5667786 --> precision: 8
{
    if(precisiondex == 0)   //Complete traversal of floating point
        return "";
    else if(flop < 1.0)
    {
        //Fractional portion
        double portion = flop * 10; // .4856 * 10 = 4.856
        char fraction = (int) portion + 48;
        portion -= (int)portion;        //.856
        //Recursive Trace
        return fraction + ready(portion, precisiondex - 1, true);
    }

    char whole = ((int)flop) % 10 + 48;
    if(flop / 10 == 0)      //1st catch!!
        return "." + ready(flop / 10, precisiondex, true);

    cout << endl << endl << whole << endl << endl;

    return  whole + ready(flop / 10, precisiondex, true);
}

//Call Ready Function -> Full Optimization <---> ERASE CALL!
string readyNO(double flop, int precisiondex, bool click)
{
    if(precisiondex != 0)
    {
        if(flop == (int) flop && flop == 0)
            return "";

        return ready(flop / 10, precisiondex, true) + (char)((int) flop % 10);
    }

    double fraction = flop - ((int) flop * 10.0); //Fractional Portion
    if(fraction == 0 || precisiondex == 0)
        return ".";

    return (char)( (flop - (int)flop) * 10) + ready(fraction - ((int)fraction * 1.0), precisiondex - 1, true);
}

//Semi-Optimizization: Single Recursive Call
//Error: whole and fractional parts switch before and after the decimal point.
string finalCall(double flop, int precisiondex)
{
    //Recursive Case
    if(flop == 0 && precisiondex == 0)
        return ".";
    else if(precisiondex == 0)
        return "";
    else if((int) flop == flop && flop != 0)
    {
        char whole = (int)flop % 10 + 48;      //Rightmost Whole Digit
        cout << whole << endl;
        return whole + finalCall((int)(flop / 10), precisiondex);
    }
    else if(flop < 0)
    {
        //Extraction of fractional portion
        flop *= 10; //.456 --> 4.56
        char fraction = (int)flop + 48;

        return finalCall(flop - (int)flop, precisiondex - 1) + fraction;
    }

    return finalCall((int)flop, precisiondex) + finalCall(flop - (int) flop, precisiondex-1);
    //Base Case#2: The floating point value has reached its indicated precision

/*
    Base Case#1: The floating point value has reached its leftmost digit
    if(fraction == (int)fraction && fraction == 0)
        return "";
*/
}

//2 recursive calls: Parsing -> double TO string
string parseDouble(double flop, int precisiondex)
{
    return parseInt((int) flop) + "." + parseFraction(flop - (int) flop, precisiondex);
}

//Recursive version: portion TO string
string parseFraction(double fraction, int precisiondex)
{
/*
    Base Case#1: The floating point value has reached its leftmost digit
    if(fraction == (int)fraction && fraction == 0)
        return "";
*/
    //Recursive Case
    if(precisiondex != 0)
    {
        //Extraction of fractional portion
        fraction -= (int)fraction;
        //Temporary Characterization of Rightmost Digit for String Concatenation Compatibility
        char character = (fraction * 10 + 48);
        //Recursive Trace
        return character + parseFraction(fraction * 10, precisiondex-1);
    }
    //Base Case#2: The floating point value has reached its indicated precision
    return "";
}

//Recursive version: Parsing -> integer TO string;
string parseInt(int whole)      //time complexity: O(log n)
{
    //Base Case: All digits of the integer has been traversed.
    if(whole == 0)
        return "";

    //Temporary Characterization of Rightmost Digit for String Concatenation Compatibility
    char character = (whole % 10 + 48);

    //Recursive Case:
    return parseInt(whole / 10) + character;
}

//Loop version: Parsing -> double TO string
string parseDoubles(double flop, int precisiondex)
{
    /*
    string Flippy = "";
    for(int whole = (int) flop; whole != 0; whole /= 10)
        Flippy += (whole % 10 + 48);

    if(precisiondex == 0)
        return reverseFlip(Flippy);
    else if(precisiondex == 1)
        return reverseFlip(Flippy) + "." + to_string( (int)((flop - (int)flop) * 10.0) );

    string Floppy = "";
    for(flop -= (int)flop;  (precisiondex--) > 0; flop *= 10, flop -= (int) flop)     //values after decimal point
        Floppy += (flop * 10 + 48);
    */
    return "";
}
