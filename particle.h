#ifndef PARTICLE_H
#define PARTICLE_H

#include "unordered_map"
#include <iostream>
#include <string>

#include "particletype.h"
#include "resonancetype.h"


class Particle {
public:
  Particle();
  Particle(std::string name, double px, double py, double pz);

  const std::string GetName() const;
  const double GetPx() const;
  const double GetPy() const;
  const double GetPz() const;
  const double GetMass() const;
  const int GetCharge() const;
  const double GetEnergy() const;
  const double GetInvariantMass(Particle& other_particle) const;

  void SetName(std::string new_name);
  void SetP(double px,double py,double pz);
  void Print() const;

  static void AddParticleType(std::string name, double mass, int charge,
                              double width = 0);
  static void PrintAllTypes();
  int Decay2Body(Particle &dau1,Particle &dau2) const;

private:
  static const int maxNumParticleType_;
  static std::unordered_map<std::string, ParticleType *> particleTypes_;
  static int NParticleType_;
  std::string name_;
  double px_;
  double py_;
  double pz_;

  const int FindParticle(std::string name) const;
  const double GetModuleP() const;

  void Boost(double bx, double by, double bz);
};

#endif