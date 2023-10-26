#ifndef PARTICLE_H
#define PARTICLE_H

#include "unordered_map"
#include <iostream>

#include "particletype.h"
#include "resonancetype.h"

class Particle {
public:
  Particle(char *name, double px, double py, double pz);
  const char *GetName() const;
  const double GetPx() const;
  const double GetPy() const;
  const double GetPz() const;
  const double GetMass() const;
  const double GetEnergy() const;
  const double GetModuleP() const;
  const double GetInvariantMass(Particle& other_particle) const;
  void SetName(char *new_name);
  void SetP(double px,double py,double pz);
  void Print() const;
  static void AddParticleType(char *name, double mass, int charge,
                              double width);
  static void PrintAllTypes();

private:
  static const int maxNumParticleType_;
  static std::unordered_map<char *, ParticleType *> particleType_;
  static int NParticleType_;
  char *name_;
  double px_;
  double py_;
  double pz_;

  int FindParticle(char *name);
};

#endif