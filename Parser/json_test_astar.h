#ifndef jtastar_h
#define jtastar_h
#include <iostream>
#include <fstream>
#include <math.h>
#include "graph_json.h"
#include "../Graph/Algorithms/GreedyBFS.h"
#include "../Graph/Algorithms/Astar.h"


using namespace std;
using nlohmann::json;
void AstarTest(){
ifstream leida("./Parser/Data/airports.json");
  string total = "";
  string result;
  json aeropuertos_completo;
  json aeropuertos_grafo = json({});
  json lon_lat = json({});
  unordered_map<string,float> h;

  while ((leida >> result))
  {
    total += result;
  }

  /* cout<<total; */
  aeropuertos_completo = json::parse(total);
  /* cout<<aeropuertos_completo.dump(2); */

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


  float lon_llegada = stof((string)lon_lat["6972"]["lon"]);
  float lat_llegada = stof((string)lon_lat["6972"]["lat"]);


  for(int i = 0; i < aeropuertos_completo.size();++i){
    string actual =  aeropuertos_completo[i]["AirportID"];
    if(actual == "6972")
      h[actual] = 0;
    else{
      float lon_dest = stof((string)lon_lat[actual]["lon"]);
      float lat_dest = stof((string)lon_lat[actual]["lat"]);

      h[actual] = sqrt((lon_llegada - lon_dest) * (lon_llegada - lon_dest) + (lon_llegada - lat_dest) * (lon_llegada - lat_dest));
      
    }
    /* cout<<actual<<" "<<h[actual]<<endl; */
  }


  result = aeropuertos_grafo.dump(2);
  /* cout<<result; */

  DirectedGraph<string, float> grafito;
  graph_json<string, float> grafito_parser;
  grafito_parser.readJSON(result);
  grafito_parser.dGraphMake(grafito);


  auto a = astar(grafito,h,"4027","6972");

  for(auto &i: a){
    cout<<"{"<<i.nodo<<", "<<i.peso<<"}"<<" ";
  }

  cout << endl
    << "finished" << endl;


}
#endif
