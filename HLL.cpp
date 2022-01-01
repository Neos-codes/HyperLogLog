#include "HLL.h"

HLL_32::HLL_32(std::string route, unsigned char p, int seed){

  this -> p = p;
    this -> b = 32 - p;
    this -> seed = seed;
    this -> m = pow(2, p);
    this -> bucket_zeros = m;

    // Se selecciona el factor de correccion
    if(m <= 16){
      alpha = 0.673;
    }
    else if(m == 32)
      alpha = 0.697;
    else if(m == 64)
      alpha = 0.709;
    else
      alpha = 0.7213/(1 + (1.079/m));
    
    // Se define el array de tamano m
    this -> sketch_array = (char *)malloc(m * sizeof(char));
    for(int i = 0; i < m; i++)
      sketch_array[i] = 0;
    
    p_mask = 0;
    b_mask = 0;
    // Creamos una mascara para obtener la direccion "p" en el arreglo
    for(int i = 0; i != b; i++){
	b_mask += 1 << i;
    }

    // Creamos una mascara para obtener el valor v2 antes de moverlo a la derecha
    p_mask = UINT_MAX - b_mask;

    read_doc(route);

    this -> size_ = estimate();
    //std::cout << size_ << std::endl;
    
}

void HLL_32::insert(std::string key){

  // Se obtiene el valor hash
  unsigned int h_value = murmur3_32(key.c_str(), key.size(), this -> seed);
  unsigned int v1 = (h_value & p_mask) >> b;
  unsigned int v2 = h_value & b_mask;
  
  //std::cout << "direccion: " << (unsigned int)v1 << " valor: " << v2 <<std::endl; 
  
  // Encontrar la posición del primer 1
  int n_zeros = __builtin_clz(v2 << p) + 1;
  
  
  if(sketch_array[v1] == 0 && n_zeros != 0)
    bucket_zeros--;
  // Cambiar el valor de los bits en el arreglo
  if(n_zeros > sketch_array[v1]){
    sketch_array[v1] = n_zeros;
  }

}

void HLL_32::read_doc(std::string route){

  std::ifstream stream(route);
  if(!stream.is_open()){
    std::cout << "Error al abrir el archivo " << route << std::endl;
    return;
  }

  for(std::string line; std::getline(stream, line);){
    //std::cout << line;
    insert(line);

  }
}

unsigned int HLL_32::estimate(){
  double sum = 0;

    // Linear counting
    if((bucket_zeros * 100) / m > 0.7)
      return m * log((double)m/bucket_zeros);
    
    // Media Armonica
    for(int i = 0; i < m; i++){
      sum += pow(2, -sketch_array[i]);
    }
    return alpha * (double)m * m / sum;

}

unsigned int HLL_32::size(){
  return this -> size_;
}
