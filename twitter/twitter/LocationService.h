#pragma once

#include <string>

#include "DatabaseConnection.h"

class LocationService
{
public:
    void AddLocation(std::string country, std::string city);
    int GetId(std::string country, std::string city);
    void RemoveLocation(int id);
};

