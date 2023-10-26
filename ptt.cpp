#include "particletype.cpp"

int main() {
  char b[3] = {'s', 't', 'e'};
  ParticleType a{b, 23, 24};
  a.Print();
}