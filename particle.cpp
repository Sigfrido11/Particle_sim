#include "particle.h"
#include "unordered_map"
#include <algorithm>
#include <cmath>
#include <iostream>

int const Particle::maxNumParticleType_ = 10;
int Particle::NParticleType_ = 0;

Particle::Particle(char *name, double px = 0, double py = 0, double pz = 0)
    : name_{name}, px_{px}, py_{py}, pz_{pz} {
  auto search = particleType_.find(name);
  if (search == particleType_.end()) {
    std::cout << "Particle type not found" << '\n';
  }
}

const char *Particle::GetName() const { return name_; }

void Particle::AddParticleType(char *name, double mass, int charge,
                               double width = 0) {
  auto search = particleType_.find(name);
  if (search != particleType_.end()) {
    return;
  } else {
    ResonanceType particle{name, mass, charge, width};
    particleType_[name] = &particle;
  }
}

void Particle::PrintAllTypes() {
  std::for_each(particleType_.begin(), particleType_.end(),
                [](const auto p) { p.second->Print(); });
}

void Particle::SetName(char *new_name) {
  auto search = particleType_.find(new_name);
  if (search != particleType_.end()) {
    return;
  } else {
    name_ = new_name;
  }
}

int Particle::FindParticle(char *name) {
  return std::distance(particleType_.begin(), particleType_.find(name));
}

const double Particle::GetPx() const { return px_; }
const double Particle::GetPy() const { return py_; }
const double Particle::GetPz() const { return pz_; }

const double Particle::GetMass() const {
  auto search = particleType_.find(name_);
  return search->second->GetMass();
}

const double Particle::GetEnergy() const {
  double const m2 = std::pow(GetMass(), 2);
  double const p2 = std::pow(GetModuleP(), 2);
  return std::sqrt(m2 + p2);
}

void Particle::SetP(double px, double py, double pz) {
  px_ = px;
  py_ = py;
  pz_ = pz;
}

const double Particle::GetInvariantMass(Particle &other_particle) const {
  double const sum_e2 =
      std::pow(other_particle.GetEnergy(), 2) + std::pow(GetEnergy(), 2);
  double const sum_p2 {GetModuleP() + other_particle.GetModuleP()};
  return std::sqrt(sum_e2 - sum_p2);
}

const double Particle::GetModuleP() const {
  double const p2 =
      std::pow(px_, 2) + std::pow(py_, 2) + std::pow(pz_, 2);
  return std::sqrt(p2);
}

void Particle::Print() const {
  std::cout << FindParticle(name_) << '\n' // non so come avere indice
            << "particle type name: " << name_ << '\n'
            << "linear momentum (N/kg): (" << px_ << ", " << py_ << ", " << pz_
            << ")" << '\n';
}
