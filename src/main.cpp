#include "Parser.h"
#include <iostream>

int main()
{
    Parser parser;
    vector<Parser::Data> data = parser.parseFile("data/jogging_path.txt");
    vector<std::string> availableNMEASentenceConfig = {"GPGGA", "GPGLL", "GPRMC"};
    int index = 0;
    for (const auto &entry : data)
    {
        ++index;
        if (find(availableNMEASentenceConfig.begin(), availableNMEASentenceConfig.end(), entry.type) != availableNMEASentenceConfig.end())
        {
            cout << index << ". NMEA Type: " << entry.type << ", Latitude: " << entry.latitude
                 << ", Longitude: " << entry.longitude << ", TimeStamp: " << entry.timestamp;
            if (entry.type == "GPGGA")
            {
                cout << ", Number Of Satellites: " << entry.satellites;
            }
            if (entry.type == "GPRMC")
            {
                cout << ", Position Validity: " << entry.positionValidity << ", Speed: " << entry.speed << " knots" << ", Heading: " << entry.course << "\370";
            }
            cout << endl;
        }
        else
        {
            cout << index << ".  Please Include Config for: " << entry.type << endl;
        }
    }

    return 0;
}
