#ifndef PARTICLE_TYPE_H
#define PARTICLE_TYPE_H


class ParticleType {
public:
  const char GetName() const; //forse si può togliere
  const double GetMass() const;
  const int GetCharge() const;
  virtual void Print() const;
  explicit ParticleType(char *name, double mass, int charge);

private:
  const char *const name_;
  double const mass_;
  int const charge_;
};
#endif