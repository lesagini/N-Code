#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Parser
{
public:
    struct Data
    {
        string type;
        string time;
        string timestamp;
        string positionValidity;
        string latitude;
        string longitude;
        string gpsQuality;
        string satellites;
        string hdop;
        string altitude;
        string undulation;
        string speed;
        string course;
        string date;
        string checkSum;
    };

    Parser();
    vector<Data> parseFile(const string &filePath);
    Data parseSentence(const string &sentence);
    vector<string> split(const string &s, char delimiter);
    string convertToDegreesMinutesSeconds(const string &coordinate, const string &direction);
    string convertDateTimeFormat(const string &time, const string &date);
    map<string, string> parseKeyValuePairs(const vector<string> &tokens);
public:
    bool isTxtFile(const string &filePath);
};

#endif
