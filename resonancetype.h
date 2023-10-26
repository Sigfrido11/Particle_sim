#ifndef RESONANCE_TYPE_H
#define RESONANCE_TYPE_H

#include "particle.h"
#include "particletype.h"

class ResonanceType final : public ParticleType {
public:
  virtual void Print() const override;

  const double GetWidth() const;

  ResonanceType(char *name, double mass, int charge, double width);

private:
  double const width_;
};

#endif