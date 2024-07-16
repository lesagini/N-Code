#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
    data.type = tokens[0];
    if (data.type == "$GPGGA")
    {
        data.time = tokens[1];
        data.latitude = tokens[2] + tokens[3];
        data.longitude = tokens[4] + tokens[5];
        data.satellites = tokens[7];
    }
    else if (data.type == "$GPGLL")
    {
        data.latitude = tokens[1] + tokens[2];
        data.longitude = tokens[3] + tokens[4];
        data.time = tokens[5];
    }
    else if (data.type == "$GPRMC")
    {
        data.time = tokens[1];
        data.positionValidity = tokens[2];
        data.latitude = tokens[3] + tokens[4];
        data.longitude = tokens[5] + tokens[6];
        data.speed = tokens[7];
        data.course = tokens[8];
        data.date = tokens[9];
    }
    // convert the time to readable format
    data.time = convertTimeFormat(data.time);
    return data;
}

string Parser::convertTimeFormat(const string &time)
{
    // Assuming time is in hhmmss.ss format, e.g., 060800.00
    string formattedTime = time.substr(0, 2) + ":" + time.substr(2, 2) + ":" + time.substr(4, 2) + " UTC";
    return formattedTime;
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
