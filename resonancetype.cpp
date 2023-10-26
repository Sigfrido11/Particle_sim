#include "resonancetype.h"

ResonanceType::ResonanceType(char *name, double mass, int charge, double width=0)
    : ParticleType(name, mass, charge){width_{width}};

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "width: " << width_ << '\n';
}

double const ResonanceType::GetWidth() const { return width_; }
