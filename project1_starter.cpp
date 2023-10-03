// ============================================================================
// File: project1_starter.cpp
// ============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct  Interval
{
    int start;
    int end;
};

// Function prototypes
void                getUnavailable(string &line, vector<Interval> &unavailable);
void                getWorkingHours(string &line, int &workStart, int &workEnd);
int                 timeToMinutes(const string &time);
string              minutesToTime(int minutes);
vector<Interval>    mergeIntervals(const vector<Interval> &intervals);
vector<Interval>    availableIntervals(const vector<Interval> &merged, int workStart, int workEnd);


// ==== main ==================================================================
//
// ============================================================================

int main()
{
    ifstream            fin;
    ofstream            fout;
    string              line;
    stringstream        ss;
    int                 caseLineCount = 0;
    vector<Interval>    unavailable1;
    vector<Interval>    unavailable2;
    int                 workStart1;
    int                 workStart2;
    int                 workEnd1;
    int                 workEnd2;
    int                 meetingDuration;
    vector<Interval>    combinedUnavailable;
    vector<Interval>    mergedUnavailable;
    vector<Interval>    combinedAvailable;
    bool				first = false;

    fin.open("input.txt");
    if (fin.fail())
        {
        fout.open("output.txt");
        fout << "Error: Unable to open 'Input.txt' file for reading...\n";
        fout.close();

        cout << "\nError: Unable to open 'Input.txt' file for reading...\n";
        cout << "Program ended.\n\n";

        return 0;
        }
    else
        {
        fout.open("output.txt");

        while (getline(fin, line))
            {
            ++caseLineCount;

            // Getting the 1st person's unavailable schedule
            if (caseLineCount == 1 && line.at(0) == '[' && line.at(1) == '[')
                {
                cout << "\nDEBUG LOG: Case Line " << caseLineCount << " (Person 1 Unavailability)\n";
                getUnavailable(line, unavailable1);
                }

            // Getting the 1st person's working hours
            else if (caseLineCount == 2 && line.at(0) == '[' && line.at(1) == '\'')
                {
                cout << "\nDEBUG LOG: Case Line " << caseLineCount << " (Person 1 Working Hours)\n";
                getWorkingHours(line, workStart1, workEnd1);
                }

            // Getting the 2nd person's unavailable schedule
            else if (caseLineCount == 3 && line.at(0) == '[' && line.at(1) == '[')
                {
                cout << "\nDEBUG LOG: Case Line " << caseLineCount << " (Person 2 Unavailability)\n";
                getUnavailable(line, unavailable2);
                }

            // Getting the 2nd person's working hours
            else if (caseLineCount == 4 && line.at(0) == '[' && line.at(1) == '\'')
                {
                cout << "\nDEBUG LOG: Case Line " << caseLineCount << " (Person 2 Working Hours)\n";
                getWorkingHours(line, workStart2, workEnd2);
                }

            // Getting meeting duration
            else if (caseLineCount == 5 && isdigit(line.at(0)))
                {
                cout << "\nDEBUG LOG: Case Line " << caseLineCount << " (Meeting Duration)\n";
                ss = stringstream(line);
                ss >> meetingDuration;
                cout << "DEBUG LOG: meetingDuration = " << meetingDuration << endl;

                // Combining and merging unavailable schedules of both persons
                combinedUnavailable = unavailable1;
                combinedUnavailable.insert(combinedUnavailable.end(), unavailable2.begin(), unavailable2.end());
                sort(combinedUnavailable.begin(), combinedUnavailable.end(), [](const Interval &a, const Interval &b)
                    { return a.start < b.start; });

                for (auto &interval : combinedUnavailable)
                    {
                    interval.start = max(interval.start, max(workStart1, workStart2));
                    interval.end = min(interval.end, min(workEnd1, workEnd2));
                    }

                combinedUnavailable.erase(
                    remove_if(combinedUnavailable.begin(), combinedUnavailable.end(),
                        [&](const Interval& interval) {
                            return interval.start >= interval.end;
                        }),
                    combinedUnavailable.end());

                cout << "\nDEBUG LOG: combinedUnavailable elements\n";
                for (int index = 0; index < combinedUnavailable.size(); ++index)
                    {
                    cout << "           [" << combinedUnavailable.at(index).start
                         << ":" << combinedUnavailable.at(index).end << "]\n";
                    }

                mergedUnavailable = mergeIntervals(combinedUnavailable);

                cout << "\nDEBUG LOG: mergedUnavailable elements\n";
                for (int index = 0; index < mergedUnavailable.size(); ++index)
                    {
                    cout << "           [" << mergedUnavailable.at(index).start
                         << ":" << mergedUnavailable.at(index).end << "]\n";
                    }

                // Getting combined schedule of availability for both persons
                combinedAvailable = availableIntervals(mergedUnavailable, max(workStart1, workStart2), min(workEnd1, workEnd2));

                cout << "\nDEBUG LOG: combinedAvailable elements\n";
                for (int index = 0; index < combinedAvailable.size(); ++index)
                    {
                    cout << "           [" << combinedAvailable.at(index).start
                         << ":" << combinedAvailable.at(index).end << "]\n";
                    }
                cout << endl;

                fout << "[";
                first = true;
                for (const auto &interval : combinedAvailable)
                    {
                    if (interval.end - interval.start >= meetingDuration)
                        {
                        if (!first)
                            {
                            fout << ",";
                            }
                        fout << "['" << minutesToTime(interval.start) << "':'" << minutesToTime(interval.end) << "']";
                        first = false;
                        }
                    }
                fout << "]" << endl << endl;
                }

            // Reseting for new case
            else if (caseLineCount == 6 && line.empty())
                {
                cout << "\nDEBUG LOG: Reset for new case\n";
                line.clear();
                caseLineCount = 0;
                unavailable1.clear();
                unavailable2.clear();
                combinedUnavailable.clear();
                mergedUnavailable.clear();
                combinedAvailable.clear();
                workStart1 = 0;
                workStart2 = 0;
                workEnd1 = 0;
                workEnd2 = 0;
                meetingDuration = 0;
                }

            // Catching invalid input in input.txt file
            else
                {
                fout << "Error: Invalid input found in input.txt file...\n";
                cout << "\nError: Invalid input found in input.txt file...\n";
                cout << "Program ended.\n\n";
                return 0;
                }

            }

        fin.close();
        fout.close();
        cout << "\nProgram ended.\n\n";

        return 0;
        }

}  // end of "main"



// ==== getUnavailable ========================================================
//
// ============================================================================

void    getUnavailable(string &line, vector<Interval> &unavailable)
{
    char    prevC = line.at(0);
    char    currC = line.at(1);
    int     p1;
    int     p2;
    string  from;
    string  to;

    for (int index = 2; index < line.length(); ++index)
        {
        prevC = currC;
        currC = line.at(index);
        if (isdigit(currC) && prevC == '\'')
            {
            p1 = index;
            }
        else if (currC == ':' && prevC == '\'')
            {
            p2 = index - 2;
            from = line.substr(p1, p2 - p1 + 1);
            }
        else if (currC == ']' && prevC == '\'')
            {
            p2 = index - 2;
            to = line.substr(p1, p2 - p1 + 1);
            cout << "DEBUG LOG: from = " << from << " | to = " << to << endl;
            unavailable.push_back({timeToMinutes(from), timeToMinutes(to)});
            }
        else
            {
            //Do_nothing
            }
        }

}  // end of "getUnavailable"



// ==== getWorkingHours =======================================================
//
// ============================================================================

void    getWorkingHours(string &line, int &workStart, int &workEnd)
{
    char    prevC = line.at(0);
    char    currC = line.at(1);
    int     p1;
    int     p2;
    string  start;
    string  end;

    for (int index = 2; index < line.length(); ++index)
        {
        prevC = currC;
        currC = line.at(index);
        if (isdigit(currC) && prevC == '\'')
            {
            p1 = index;
            }
        else if (currC == ',' && prevC == '\'')
            {
            p2 = index - 2;
            start = line.substr(p1, p2 - p1 + 1);
            }
        else if (currC == ']' && prevC == '\'')
            {
            p2 = index - 2;
            end = line.substr(p1, p2 - p1 + 1);
            cout << "DEBUG LOG: workStart = " << start << " | workEnd = " << end << endl;
            workStart = timeToMinutes(start);
            workEnd = timeToMinutes(end);
            }
        else
            {
            //Do_nothing
            }
        }

}  // end of "getWorkingHours"



// ==== timeToMinutes =========================================================
//
// ============================================================================

int     timeToMinutes(const string &time)
{
    int hour;
    int min;
    int mTime;

    sscanf(time.c_str(), "%d:%d", &hour, &min);
    mTime = hour * 60 + min;

    cout << "DEBUG LOG: timeToMinutes, time = " << time
         << ", hour = " << hour << ", min = " << min
         << ", mTime = " << mTime << endl;

    return mTime;

}  // end of "timeToMinutes"



// ==== minutesToTime =========================================================
//
// ============================================================================

string  minutesToTime(int minutes)
{
    char    buffer5[5];
    char    buffer6[6];
    string  time;

    if (minutes < 600)
        {
        sprintf(buffer5, "%d:%02d", (minutes / 60), (minutes % 60));
        time = string(buffer5);
        }
    else
        {
        sprintf(buffer6, "%d:%02d", (minutes / 60), (minutes % 60));
        time = string(buffer6);
        }

    cout << "DEBUG LOG: minutesToTime, mTime = " << minutes
         << ", time = " << time << endl;

    return time;

}  // end of "minutesToTime"



// ==== mergeIntervals ========================================================
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



// ==== availableIntervals ====================================================
//
// ============================================================================

vector<Interval>    availableIntervals(const vector<Interval> &merged, int workStart, int workEnd)
{
    vector<Interval>    result;
    int                 prevEnd = workStart;

    for (const auto &interval : merged)
        {
        if (prevEnd < interval.start)
            {
            result.push_back({prevEnd, interval.start});
            }
        prevEnd = interval.end;
        }

    if (prevEnd < workEnd)
        {
        result.push_back({prevEnd, workEnd});
        }

    return result;

}  // end of "availableIntervals"
