#include "LocationService.h"

#include <iostream>

void LocationService::AddLocation(std::string country, std::string city)
{
    // Adaugare obiecte in db:
    DatabaseConnection db;

    // Append the SQL statment
    std::string sSQL;
    sSQL.append("INSERT INTO Location(country,city) VALUES ('");
    sSQL.append(country);
    sSQL.append("', '");
    sSQL.append(city);
    sSQL.append("')");

    // Execute with sql statement
    PGresult* res = PQexec(db.GetConn(), sSQL.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("\nInsert Location record failed\n");
        PQclear(res);
        PQfinish(db.GetConn());
        return;
    }

    printf("\nInsert Location record - OK\n");

    // Clear result
    PQclear(res);

    PQfinish(db.GetConn());
}

int LocationService::GetId(std::string country, std::string city)
{
    DatabaseConnection db;
    int id = -1;
    // Will hold the number of field in employee table
    int nFields;

    // Start a transaction block
    PGresult* res = PQexec(db.GetConn(), "BEGIN");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("BEGIN command failed");
        PQclear(res);
        PQfinish(db.GetConn());
    }

    // Clear result
    PQclear(res);

    // Append the SQL statment
    std::string sSQL;
    sSQL.append("DECLARE locrec CURSOR FOR select id from location where country='");
    sSQL.append(country);
    sSQL.append("' AND city='");
    sSQL.append(city);
    sSQL.append("'");

    // Fetch rows from employee table  
    res = PQexec(db.GetConn(), sSQL.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("DECLARE CURSOR failed");
        PQclear(res);
        PQfinish(db.GetConn());
    }

    // Clear result
    PQclear(res);

    res = PQexec(db.GetConn(), "FETCH ALL in locrec");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        printf("FETCH ALL failed");
        PQclear(res);
        PQfinish(db.GetConn());
    }

    // Get the field name
    nFields = PQnfields(res);

    // Next, print out the employee record for each row
    for (int i = 0; i < PQntuples(res); i++)
    {
        for (int j = 0; j < nFields; j++)
        {
            id = atoi(PQgetvalue(res, i, j));
        }
    }

    PQclear(res);

    // Close the locrec
    res = PQexec(db.GetConn(), "CLOSE locrec");
    PQclear(res);

    // End the transaction
    res = PQexec(db.GetConn(), "END");

    // Clear result
    PQclear(res);

    PQfinish(db.GetConn());

    return id;
}

void LocationService::RemoveLocation(int id)
{
    DatabaseConnection db;

    std::string id_location = std::to_string(id);

    // Append the SQL statment
    std::string sSQL;
    sSQL.append("DELETE FROM location WHERE id=");
    sSQL.append(id_location);

    // Execute with sql statement
    PGresult* res = PQexec(db.GetConn(), sSQL.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Delete location record failed.");
        PQclear(res);
        PQfinish(db.GetConn());
    }

    printf("\nDelete Location record - OK\n");

    // Clear result
    PQclear(res);
}