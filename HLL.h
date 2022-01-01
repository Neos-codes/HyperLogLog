#ifndef HLL_H
#define HLL_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "murmurhash.h"

// Esta clase es para valores a lo más de 32 bits (4 bytes)
class HLL_32{

 public:
  // Metodos
  
  // Constructor
  HLL_32(std::string route, unsigned char p, int seed);
  
  // Retorna la estimacion de la cardinalidad
  unsigned int size();


 private:
  // Variables
  unsigned int seed;
  unsigned char p;
  unsigned char b;
  unsigned int m;
  unsigned int size_;
  unsigned int bucket_zeros;
  float alpha;
  unsigned int p_mask;
  unsigned int b_mask;
  char *sketch_array;

  // Método para insertar strings en HLL
  void insert(std::string key);

  // Metodo para leer un documento completo y añadirlo al sketch
  void read_doc(std::string route);
  
  // Metodo para estimar la cardinalidad
  unsigned int estimate();

 
};

#endif



