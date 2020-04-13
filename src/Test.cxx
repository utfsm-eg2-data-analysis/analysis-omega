#include "analysisConfig.h"

int main() {
  std::cout << "PRODIR=" << proDir << std::endl;

  for (Int_t i = 0; i < 6; i++) {
    std::cout << "z" << i << " - " << edgesZ[i] << std::endl;
  }

  std::cout << "hola 123" << std::endl;
}
