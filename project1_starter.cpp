#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct  Interval
{
    int start;
    int end;
};



int main()
{
    ifstream    fin;
    ofstream    fout;
    string      line;

    fin.open("Input.txt");
    if (fin.fail())
        {
        fout.open("Output.txt");
        fout << "Error: Unable to open 'Input.txt' file for reading...\n";
        fout.close();

        cout << "\nError: Unable to open 'Input.txt' file for reading...\n";
        cout << "Program ended.\n\n";

        return 0;
        }
    else
        {
        fout.open("Output.txt");
        while (getline(fin, line))
            {
            // algorithm code goes here
            }
        
        fin.close();
        fout.close();

        return 0;
        }
}
