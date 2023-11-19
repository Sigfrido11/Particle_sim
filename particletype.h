#ifndef PARTICLE_TYPE_H
#define PARTICLE_TYPE_H

#include <string>

class ParticleType {
public:
  const std::string GetName() const; // forse si può togliere
  const double GetMass() const;
  const int GetCharge() const;
  virtual const double GetWidth() const;
  virtual void Print() const;
  explicit ParticleType(std::string name, double mass, int charge);

private:
  std::string const name_;
  double const mass_;
  int const charge_;
};
#endif