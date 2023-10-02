// ============================================================================
// File: project1_starter.cpp
// ============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
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
            stringstream        ss(line);
            string              from;
            string              to;
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
            bool                first = false;

            // Getting the 1st person's unavailable schedule
            while (ss >> from >> to)
                {
                unavailable1.push_back({
                    timeToMinutes(from.substr(2, from.size() - 3)),
                    timeToMinutes(to.substr(1, to.size() - 3))
                    });
                }

            // Getting the 1st person's working hours
            getline(fin, line);
            ss = stringstream(line);
            ss >> from >> to;
            workStart1 = timeToMinutes(from.substr(1, from.size() - 2));
            workEnd1 = timeToMinutes(to.substr(1, to.size() - 2));

            // Getting the 2nd person's unavailable schedule
            getline(fin, line);
            ss = stringstream(line);
            while (ss >> from >> to)
                {
                unavailable2.push_back({
                    timeToMinutes(from.substr(2, from.size() - 3)),
                    timeToMinutes(to.substr(1, to.size() - 3))
                    });
                }

            // Getting the 2nd person's working hours
            getline(fin, line);
            ss = stringstream(line);
            ss >> from >> to;
            workStart2 = timeToMinutes(from.substr(1, from.size() - 2));
            workEnd2 = timeToMinutes(to.substr(1, to.size() - 2));

            // Getting meeting duration
            getline(fin, line);
            ss = stringstream(line);
            ss >> meetingDuration;

            // Combining and merging unavailable schedules of both persons
            combinedUnavailable = unavailable1;
            combinedUnavailable.insert(combinedUnavailable.end(),
                                       unavailable2.begin(),
                                       unavailable2.end());
            sort(combinedUnavailable.begin(), combinedUnavailable.end(),
                 [](const Interval &a, const Interval &b) {
                 return a.start < b.start; });
            mergedUnavailable = mergeIntervals(combinedUnavailable);

            // Getting combined schedule of availability for both persons
            combinedAvailable = availableIntervals(mergedUnavailable,
                                                   max(workStart1, workStart2),
                                                   min(workEnd1, workEnd2));

            fout << "[";
            cout << "[";
            first = true;
            for (const auto &interval : combinedAvailable)
                {
                if (interval.end - interval.start >= meetingDuration)
                    {
                    if (!first)
                        {
                        fout << ", ";
                        cout << ", ";
                        }
                    fout << "['" << minutesToTime(interval.start) << "', '"
                         << minutesToTime(interval.end) << "']";
                    cout << "['" << minutesToTime(interval.start) << "', '"
                         << minutesToTime(interval.end) << "']";
                    first = false;
                    }
                }
            fout << "]" << endl;
            cout << "]" << endl;
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

vector<Interval>    availableIntervals(const vector<Interval> &merged,
                                       int workStart, int workEnd)
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
