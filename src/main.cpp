#include "Parser.h"
#include <iostream>

int main()
{
    Parser parser;
    vector<Parser::Data> data = parser.parseFile("data/jogging_path.txt");

    for (const auto &entry : data)
    {
        cout << "Type: " << entry.type << ", Latitude: " << entry.latitude
             << ", Longitude: " << entry.longitude << ", Time: " << entry.time;
        if (entry.type == "$GPGGA")
        {
            cout << ", Number Of Satellites: " << entry.satellites;
        }
        if (entry.type == "$GPRMC")
        {
            cout << ", Position Validity: " << entry.positionValidity << ", Speed: " << entry.speed << ", Course: " << entry.course
                 << ", Date: " << entry.date;
        }
        cout << endl;
    }

    return 0;
}
