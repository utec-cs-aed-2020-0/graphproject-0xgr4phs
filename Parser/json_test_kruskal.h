#include <iostream>
#include <fstream>
#include <math.h>
#include "graph_json.h"
#include "../Graph/Algorithms/Kruskal.h"

void KruskalTest()
{
    ifstream leida("./Data/airports.json");
    string total = "";
    string result;
    json aeropuertos_completo;
    json aeropuertos_grafo = json({});
    json lon_lat = json({});

    while ((leida >> result))
    {
        total += result;
    }

    aeropuertos_completo = json::parse(total);

    for (int i = 0; i < aeropuertos_completo.size(); ++i)
    {
        string id = aeropuertos_completo[i]["AirportID"];

        aeropuertos_grafo[id] = R"(
    { "connections" :[]
    }
    )"_json;

        string nombre = aeropuertos_completo[i]["Name"];

        aeropuertos_grafo[id]["data"] = nombre;

        string lon = aeropuertos_completo[i]["Longitude"];
        string lat = aeropuertos_completo[i]["Latitude"];

        lon_lat[id] = {{"lon", lon}, {"lat", lat}};
    }

    for (int i = 0; i < aeropuertos_completo.size(); ++i)
    {
        string id = aeropuertos_completo[i]["AirportID"];
        for (int j = 0; j < aeropuertos_completo[i]["destinations"].size(); ++j)
        {
            string dest = aeropuertos_completo[i]["destinations"][j];
            if (aeropuertos_grafo.find(dest) != aeropuertos_grafo.end())
            {
                try
                {
                    float lon_actual = stof((string)lon_lat[id]["lon"]);
                    float lat_actual = stof((string)lon_lat[id]["lat"]);
                    float lon_dest = stof((string)lon_lat[dest]["lon"]);
                    float lat_dest = stof((string)lon_lat[dest]["lat"]);
                    float distancia = sqrt((lon_actual - lon_dest) * (lon_actual - lon_dest) + (lat_actual - lat_dest) * (lat_actual - lat_dest));

                    aeropuertos_grafo[id]["connections"].push_back(
                        json::array({dest, distancia}));
                }
                catch (invalid_argument x)
                {
                    cout << lon_lat[id]["lon"] << endl;
                    cout << lon_lat[id]["lat"] << endl;
                    cout << lon_lat[dest]["lon"] << endl;
                    cout << lon_lat[dest]["lat"] << endl;
                }
            }
        }
    }

    result = aeropuertos_grafo.dump(2);

    UnDirectedGraph<string, float> grafito;
    graph_json<string, float> grafito_parser;
    grafito_parser.readJSON(result);
    grafito_parser.uGraphMake(grafito);

    kruskal(grafito).display();

    cout << endl
         << "finished" << endl;
}