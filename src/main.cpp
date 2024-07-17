#include "Parser.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    Parser parser;
    string filePath = "data/jogging_path.txt";

    if (argc == 2)
    {
        filePath = argv[1];

        // Validate if the provided file path ends with ".txt"
        if (!parser.isTxtFile(filePath))
        {
            cerr << "Error: Provided file is not a valid .txt file." << endl;
            return 1;
        }
    }
    else if (argc > 2)
    {
        cerr << "Usage: " << argv[0] << " [<file_path>]" << endl;
        return 1;
    }

    // Check if the default file exists and is a valid .txt file
    if (!fs::exists(filePath))
    {
        cerr << "Error: Default file 'jogging_nmea.txt' not found." << endl;
        return 1;
    }
    else if (!parser.isTxtFile(filePath))
    {
        cerr << "Error: Default file 'jogging_nmea.txt' is not a valid .txt file." << endl;
        return 1;
    }

    vector<Parser::Data> data = parser.parseFile(filePath);
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
