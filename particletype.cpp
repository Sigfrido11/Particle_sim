#include "particletype.h"

#include <iostream>

ParticleType::ParticleType(std::string name, double mass, int charge)
    : name_{name}, mass_{mass}, charge_{charge} {};

const std::string ParticleType::GetName() const { return name_; }

const double ParticleType::GetMass() const { return mass_; }

const int ParticleType::GetCharge() const { return charge_; }

const double ParticleType::GetWidth() const { return 0.; }

void ParticleType::Print() const {
  std::cout << name_ << " "
            << "mass: " << mass_ << " kg "
            << "charge: " << charge_ << " e" << '\n';
}