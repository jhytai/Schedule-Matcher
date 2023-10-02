// ============================================================================
// File: project1_starter.cpp
// ============================================================================

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

// Function prototypes
int                 timeToMinutes(const string &time);
string              minutesToTime(int minutes);
vector<Interval>    mergeIntervals(const vector<Interval> &intervals);
vector<Interval>    availableIntervals(const vector<Interval> &merged,
                                       int workStart, int workEnd);


// ==== main ==================================================================
//
// ============================================================================

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

}  // end of "main"



// ==== timeToMinutes =========================================================
//
// ============================================================================

int     timeToMinutes(const string &time)
{
    int hour;
    int min;

    sscanf(time.c_str(), "%d:%d", &hour, &min);

    return (hour * 60 + min);

}  // end of "timeToMinutes"



// ==== minutesToTime =========================================================
//
// ============================================================================

string  minutesToTime(int minutes)
{
    char    buffer[6];

    sprintf(buffer, "%02d:%02d", (minutes / 60), (minutes % 60));

    return string(buffer);

}  // end of "minutesToTime"



// ==== mergeIntervals =========================================================
//
// ============================================================================

vector<Interval>    mergeIntervals(const vector<Interval> &intervals)
{
    int                 start;
    int                 end;
    vector<Interval>    result;

    if (intervals.empty())
        {
        return {};
        }
    else
        {
        start = intervals[0].start;
        end = intervals[0].end;

        for (const auto &interval : intervals)
            {
            if (interval.start <= end)
                {
                end = max(end, interval.end);
                }
            else
                {
                result.push_back({start, end});
                start = interval.start;
                end = interval.end;
                }
            }

        result.push_back({start, end});

        return result;
        }

}  // end of "mergeIntervals"
