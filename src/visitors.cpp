#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

/**
 * @brief Finds the max visitors in the time duration.
 * 
 * This function takes a vector of visitorTimes of input time and output time
 * and calculates the max visitors in the time slot.
 * 
 * @param vector of visitorTimes with pair of input time and out time.
 * @return A pair for the time slot for max visitors .
 */

pair<string, int> findMaxVisitors(const vector<pair<string, string>>& visitorTimes) {

    map<int, int> timeVisitors;

    // Finding the visitors at every minute
    for (const auto& entry : visitorTimes) {
        string enteringTime = entry.first;
        string leavingTime = entry.second;

        // Convert to minutes
        int enterMinute = stoi(enteringTime.substr(0, 2)) * 60 + stoi(enteringTime.substr(3));
        int leaveMinute = stoi(leavingTime.substr(0, 2)) * 60 + stoi(leavingTime.substr(3));

        for (int minute = enterMinute; minute <= leaveMinute; ++minute) {
            int time =  minute;
            timeVisitors[time]++;
        }
    }

    // logic for max visitors
    int temp_time;
    int maxVisitors = 0;
    std::vector<int> numbers;
    for (const auto& entry : timeVisitors) {

        if (entry.second > maxVisitors) {
            maxVisitors = entry.second;
        }
    }

    //Generate a vector for visitor time
    for (const auto& entry : timeVisitors) {

        if (entry.second == maxVisitors) {
            temp_time = entry.first;
            numbers.push_back(temp_time);
        }
    }

    // Find maximum time
    auto max_iter = std::max_element(numbers.begin(), numbers.end());
    int max_value = *max_iter;
    std::cout << "Maximum value: " << max_value << std::endl;
    string maxxx_time = to_string(max_value / 60) + ":" + to_string(max_value % 60);

    // Find minimum time
    auto min_iter = std::min_element(numbers.begin(), numbers.end());
    int min_value = *min_iter;
    std::cout << "Minimum value: " << min_value << std::endl;
    string manimum_time = to_string(min_value / 60) + ":" + to_string(min_value % 60);

    return make_pair(manimum_time + "-" +maxxx_time , maxVisitors);
}


int main()
{

    string inputFilePath = "D:\\PerForceTest\\visitors.txt"; //Path to the text file.
    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cout << "Error: cannot  open file " << inputFilePath << endl;
        return 1;
    }

    vector<pair<string, string>> visitorTimes;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string enteringTime, leavingTime;
        getline(ss, enteringTime, ',');
        getline(ss, leavingTime, ',');

        visitorTimes.push_back(make_pair(enteringTime, leavingTime));
    }

    pair<string, int> result = findMaxVisitors(visitorTimes);

    cout << result.first << ";" << result.second << endl;

    inputFile.close();

    return 0;
}
