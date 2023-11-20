#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "particle.h"
#include "particletype.h"
#include "resonancetype.h"
#include <algorithm>
#include <cmath>

int main() {
  TFile *file = new TFile("histo.root", "RECREATE");
  gRandom->SetSeed(200769);
  Particle::AddParticleType("pion +", 0.13957, 1);
  Particle::AddParticleType("pion -", 0.13957, -1);
  Particle::AddParticleType("kaon +", 0.4937, 1);
  Particle::AddParticleType("kaon -", 0.49367, -1);
  Particle::AddParticleType("proton +", 0.93827, 1);
  Particle::AddParticleType("proton -", 0.93827, -1);
  Particle::AddParticleType("resonance", 0.89166, 0, 0.050);
  std::array<Particle, 120> EventParticles{};
  double val{0};

  TH1F *gen_particles = new TH1F("gen_particles", "gen_particles", 7, 0, 7);

  TH1F *azimuth = new TH1F("azimuth", "azimuth", 100, 0., 2 * M_PI);

  TH1F *polar_angle = new TH1F("polar_angle", "polar_angle", 100, 0., M_PI);

  TH1F *p_module = new TH1F("p_module", "p_module", 100, 0, 5);

  TH1F *p_trans = new TH1F("p_trans", "p_trans", 100, 0, 5);

  TH1F *energy = new TH1F("energy", "energy", 100, 0, 10);

  // per questi primi non serve sumw2?

  TH1F *all_inv_mass = new TH1F("all_inv_mass", "all_inv_mass", 100, 0, 10);

  all_inv_mass->Sumw2();

  TH1F *same_charge_inv_mass =
      new TH1F("same_charge_inv_mass", "same_charge_inv_mass", 100, 0, 10);

  same_charge_inv_mass->Sumw2();

  TH1F *opposite_charge_inv_mass = new TH1F(
      "opposite_charge_inv_mass", "opposite_charge_inv_mass", 100, 0, 10);
  opposite_charge_inv_mass->Sumw2();
  TH1F *pi_k_same = new TH1F("pi_k_same_charge_inv_mass",
                             "pi_k_same_charge_inv_mass", 100, 0, 10);
  pi_k_same->Sumw2();
  TH1F *pi_k_opposite = new TH1F("pi_k_opposite_charge_inv_mass",
                                 "pi_k_opposite_charge_inv_mass", 100, 0, 10);
  pi_k_opposite->Sumw2();
  TH1F *dec_inv_mass = new TH1F("dec_inv_mass", "dec_inv_mass", 100, 0, 10);
  dec_inv_mass->Sumw2();

  int star_num2{0};

  for (int i{0}; i < 1e5; i++) {
    if (star_num2 > 20) {
      std::cout << "too much resonance has been genarated" << '\n' << "\n";
    }

    star_num2 = 0;

    //std::cout << "sono nel ciclone all'iterazione " << i << '\n';

    for (int event{0}; event < 1e2; event++) {
      bool is_star{false};
      val = gRandom->Rndm();
      double phi = gRandom->Uniform(0., 2 * M_PI); // azimuth
      double theta = gRandom->Uniform(0., M_PI);   // polar angle
      double p_m = gRandom->Exp(1.);
      double px = p_m * std::cos(phi) * std::sin(theta);
      double py = p_m * std::sin(phi) * std::sin(theta);
      double pz = p_m * std::cos(theta);

      azimuth->Fill(phi);
      polar_angle->Fill(theta);
      p_module->Fill(p_m);
      p_trans->Fill(std::sqrt(std::pow(px, 2) + std::pow(py, 2)));

      Particle p;
      Particle p1;
      Particle p2;

      //std::cout << "nel ciclo all'inizio all'iterazione " << event << '\n';

      if (val < 0.4) {
        p.SetName("pion +");
        gen_particles->Fill(0.5);
      }

      else if (val < 0.8) {
        p.SetName("pion -");
        gen_particles->Fill(1.5);
      }

      else if (val < 0.85) {
        p.SetName("kaon +");
        gen_particles->Fill(2.5);
      }

      else if (val < 0.90) {
        p.SetName("kaon -");
        gen_particles->Fill(3.5);
      }

      else if (val < 0.945) {
        p.SetName("proton +");
        gen_particles->Fill(4.5);
      }

      else if (val < 0.99) {
        p.SetName("proton -");
        gen_particles->Fill(5.5);
      }

      else {
        p.SetName("resonance");
        is_star = true;
        double decadence{gRandom->Rndm()};
        p.SetP(px, py, pz);
        energy->Fill(p.GetEnergy());
        star_num2 += 2;
        if (decadence < 0.5) {
          p1.SetName("pion +");
          p2.SetName("kaon -");

        } else {
          p1.SetName("pion -");
          p2.SetName("kaon +");
        }
        int all_good{p.Decay2Body(p1, p2)};
        if (all_good != 0) {
          //std::cout << "something went wrong during decay" << '\n' << "\n";
        } else {
         // std::cout <<"qui le due decadute vanno"<< p1.GetInvariantMass(p2) <<'\n';
          dec_inv_mass->Fill(p1.GetInvariantMass(p2));
        }
      }
      if (!is_star) {
        p.SetP(px, py, pz);
        energy->Fill(p.GetEnergy());
        EventParticles[event + star_num2 / 2] = p;
      } else {

        //std::cout << "somma" << event + 1 + star_num2 / 2 << '\n';
        //std::cout<< "sono p1 e sono valido " << p1.GetCharge() << '\n';
        EventParticles[event + 1 + star_num2 / 2] = p1;
        //std::cout << "p mass deuhduhfnui" << p1.GetCharge()<< "\n";
        EventParticles[event + star_num2 / 2] = p2;
      }

      for (int compare{0}; compare < event + star_num2 / 2; compare++) {
        Particle old_particle{EventParticles[compare]};
        if (is_star) {
          //std::cout << "p mass" << p.GetCharge()<< "\n";
          //std::cout << "p1 mass" << p1.GetCharge()<< "\n";
          p = p1;
          //std::cout << "p mass" << p.GetCharge()<< "\n";
          //std::cout << "che bello sono una star" << "\n";
        }

        //std::cout << "old_particle è ben posto " << old_particle.GetMass()
         //         << '\n';
        
        //std::cout << "p è ben posto " << p.GetMass()
         //         << '\n';

        //std::cout << "inv mass " << p.GetInvariantMass(old_particle) << '\n';
        
        all_inv_mass->Fill(p.GetInvariantMass(old_particle));

        //std::cout << "nel for piccolo piccolo dopo invariant mass " << compare
         //       << "\n";

        if (p.GetCharge() == old_particle.GetCharge()) { // same charge
          same_charge_inv_mass->Fill(p.GetInvariantMass(EventParticles[event]));
          bool first_cond{p.GetName() == "pion +" &&
                          old_particle.GetName() == "kaon +"};
          bool second_cond{p.GetName() == "pion -" &&
                           old_particle.GetName() == "kaon -"};
          if (first_cond || second_cond) {
            pi_k_same->Fill(p.GetInvariantMass(old_particle));
          }
        } else { // different charge
          opposite_charge_inv_mass->Fill(
              p.GetInvariantMass(EventParticles[event]));
          bool first_cond{p.GetName() == "pion +" &&
                          old_particle.GetName() == "kaon -"};
          bool second_cond{p.GetName() == "pion -" &&
                           old_particle.GetName() == "kaon +"};
          if (first_cond || second_cond) {
            pi_k_opposite->Fill(p.GetInvariantMass(old_particle));
          }
        }
       // std::cout << "nel for piccolo piccolo alla fine sono arrivato "
         //         << compare << "\n";
      }
    }
  } 

azimuth->Write();
polar_angle->Write();
p_module->Write();
p_trans->Write();
gen_particles->Write();
energy->Write();
all_inv_mass->Write();
same_charge_inv_mass->Write();
opposite_charge_inv_mass->Write();
pi_k_same->Write();
pi_k_opposite->Write();
dec_inv_mass->Write();

azimuth->Draw();
polar_angle->Draw();
p_module->Draw();
p_trans->Draw();
gen_particles->Draw();
energy->Draw();
all_inv_mass->Draw();


/*
  for (auto &elem : Particle::particleTypes_) {
    elem.second->delete();
  }
  */
}