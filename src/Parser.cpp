#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

Parser::Parser() {}

vector<Parser::Data> Parser::parseFile(const string &filePath)
{
    vector<Data> data;
    ifstream file(filePath);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty() || line[0] != '$')
                continue;
            Data parsedData = parseSentence(line);
            data.push_back(parsedData);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << filePath << endl;
    }

    return data;
}

Parser::Data Parser::parseSentence(const string &sentence)
{
    Data data;
    vector<string> tokens = split(sentence, ',');
    string latitudeRef = "";
    string longitudeRef = "";

    data.type = tokens[0].substr(1, -1);

    if (data.type == "GPGGA")
    {
        data.time = tokens[1];
        data.latitude = tokens[2];
        latitudeRef = tokens[3];
        data.longitude = tokens[4];
        longitudeRef = tokens[5];
        data.satellites = tokens[7];
    }
    else if (data.type == "GPGLL")
    {
        data.latitude = tokens[1];
        latitudeRef = tokens[2];
        data.longitude = tokens[3];
        longitudeRef = tokens[4];
        data.time = tokens[5];
    }
    else if (data.type == "GPRMC")
    {
        data.time = tokens[1];
        data.positionValidity = tokens[2];
        data.latitude = tokens[3];
        data.longitude = tokens[5];
        latitudeRef = tokens[4];
        longitudeRef = tokens[6];
        data.speed = tokens[7];
        data.course = tokens[8];
        data.date = tokens[9];
    }
    else
    {
        return data;
    }
    // convert the time to readable format
    data.timestamp = convertDateTimeFormat(data.time, data.date);
    data.latitude = convertToDegreesMinutesSeconds(data.latitude, latitudeRef);
    data.longitude = convertToDegreesMinutesSeconds(data.longitude, longitudeRef);
    return data;
}

string Parser::convertToDegreesMinutesSeconds(const string &coordinate, const string &direction)
{
    double coord = stod(coordinate);
    int degrees = static_cast<int>(coord / 100);
    double minutes = coord - degrees * 100;
    double seconds = (minutes - static_cast<int>(minutes)) * 60.0;
    minutes = static_cast<int>(minutes);

    stringstream ss;
    ss << degrees << "\370" << minutes << "'" << fixed << setprecision(2) << seconds << " \"" << direction;

    return ss.str();
}

string Parser::convertDateTimeFormat(const string &time, const string &date)
{

    stringstream ss;
    tm tm = {};
    string formattedTime = time.substr(0, 2) + ":" + time.substr(2, 2) + ":" + time.substr(4, 2) + " UTC";

    // Parse time (HHMMSS)
    tm.tm_hour = std::stoi(time.substr(0, 2));
    tm.tm_min = std::stoi(time.substr(2, 2));
    tm.tm_sec = std::stoi(time.substr(4, 2));
    char buffer[30];

    if (!date.empty())
    {
        // Parse date (DDMMYY)
        tm.tm_mday = std::stoi(date.substr(0, 2));
        tm.tm_mon = std::stoi(date.substr(2, 2)) - 1;
        tm.tm_year = std::stoi("20" + date.substr(4, 2)) - 1900;
        time_t t = mktime(&tm);
        std::tm gmtm;
        #ifdef _WIN32
        gmtime_s(&gmtm, &t);  // Windows
        #else
        gmtime_r(&t, &gmtm);  // Unix-like
        #endif

        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S UTC", &gmtm);
        return string(buffer);
    }
    time_t t = mktime(&tm);
    std::tm gmtm;
    #ifdef _WIN32
    gmtime_s(&gmtm, &t);  // Windows
    #else
    gmtime_r(&t, &gmtm);  // Unix-like
    #endif

    strftime(buffer, sizeof(buffer), "%H:%M:%S UTC", &gmtm);
    return string(buffer);
}

vector<string> Parser::split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
