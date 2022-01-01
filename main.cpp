#include <iostream>
#include <unordered_map>
#include "HLL.cpp"
#include <math.h>

int main(int argc, char *argv[]){

  std::string route(argv[1]);
  std::unordered_map<std::string, int> data;
  std::ifstream file(route);
  
  // Insertar archivo en sketch
  HLL_32 hll(route, std::stoi(argv[2]), std::stoi(argv[3]));
  
  // Insertar archivo en mapa para comparar cardinalidades
  for(std::string line; std::getline(file, line);){
    data[line]++;
  }
 
  std::cout << "Cardinalidad estimada: "<< hll.size() << std::endl;
  std::cout << "Cardinalidad real: " << data.size() << std::endl;
  std::cout << "Error: " << abs((double)100 - (double)hll.size() * 100 / data.size() )<< "%" << std::endl;

  return 0;
}
