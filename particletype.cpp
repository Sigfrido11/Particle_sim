#include "particletype.h"
#include <iostream>

ParticleType::ParticleType(char *name, double mass, int charge)
    : name_{name}, mass_{mass}, charge_{charge} {};
const char ParticleType::GetName() const { return *name_; }
const double ParticleType::GetMass() const { return mass_; }
const int ParticleType::GetCharge() const { return charge_; }
void ParticleType::Print() const {
  std::cout << *name_ << " "
            << "mass: " << mass_ << " kg "
            << "charge: " << charge_ << " e" << '\n';
}
