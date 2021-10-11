#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

///////////////////////////////////////////////
// Get date portion of a utc timestamp
// e.g. 2018-12-09T14:19:00+00:00 -> 2018-12-09
///////////////////////////////////////////////
string getDate (string utcTimestamp) {
    if (utcTimestamp.size() < 10)
        return "INVALID";
    return utcTimestamp.substr(0, 10);
}

/////////////////////////////////////////////////////////////////////
// Parse arg "input" into the following args "cookie" and "timestamp"
// Arguments:
// a) "input": formatted as "[cookie],[timestamp]"
// b) "cookie": any value, passed as reference and will be altered
// c) "timestamp": any value, passed as reference and will be altered
// Returns true if input is properly parsed; false otherwise
/////////////////////////////////////////////////////////////////////
bool parseCookieTimestamp(string input, string &cookie, string &timestamp) {
    if (input.size() == 0) return false;
    int i = 0;
    //traverse to index of ',' (split between cookie key and timestamp)
    while (input[i] != ',') {
        i++;
        if (i == input.size())
            return false;
    }
    cookie = input.substr(0, i);
    timestamp = input.substr(i + 1, input.size() - i - 1);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////
// Return the most active cookies for a specified date given arguments:
// a) cookie_data: list of strings with cookie and timestamp
// b) target_date: a date string formatted as yyyy-mm-dd
// Define the most active cookies as the ones seen in the log the most times during
// a given day.
//////////////////////////////////////////////////////////////////////////////////////
vector<string> getMostActiveCookies(vector<string> cookie_data, string target_date) {
    vector<string> most_active_cookies;
    unordered_map<string, int> cookie_occurences;

    //find occurence of all cookies with timestamp date matching target_date
    for (int i = 0; i < cookie_data.size(); i++) {
        string cookie_data_entry = cookie_data[i];
        string cookie, timestamp;
        if(parseCookieTimestamp(cookie_data_entry, cookie, timestamp)) {
            string date = getDate(timestamp);
            if (date == target_date)
                cookie_occurences[cookie]++;
        }
    }

    //find max occurence of a cookie
    int max_occurence = 0;
    for (auto i : cookie_occurences)
        max_occurence = max(max_occurence, i.second);

    //return all cookies with same max occurence
    for (auto i : cookie_occurences)
        if (max_occurence == i.second)   
            most_active_cookies.push_back(i.first);
    return most_active_cookies;
}

// argc is number of words entered into the CLI
// char** argv is array of arguments(string) passed in
// argv[0] holds name of executable
int main(int argc, char* argv[]) {
    /* Read CLI arguments and perform error checking*/
    if (argc < 4) {
        cout << "Invalid number of arguments!" << endl;
        exit(1);
    }

    if (strcmp(argv[2], "-d")) {
        cout << "Invalid option passed!" << endl;
        exit(1);
    }
    
    string target_date = argv[3];
    string inputfile_name = argv[1];

    ifstream cookie_log;
    cookie_log.open(inputfile_name);

    if (cookie_log.is_open()) {
        //skip the first line
        string skip;
        getline(cookie_log, skip);

        //store each line of cookie_log file into a vector
        vector<string> cookie_data;
        while (cookie_log) {
            string cookie_log_line, cookie, timestamp;
            getline(cookie_log, cookie_log_line);
            cookie_data.push_back(cookie_log_line);
        }

        //compute and print the most active cookies
        vector<string> most_active_cookies = getMostActiveCookies(cookie_data, target_date);
        for (string cookie : most_active_cookies)
            cout << cookie << endl;
    }
    else {
        cout << "Failed to open passed in file" << endl;
        exit(1);
    }
}