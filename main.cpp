#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "particle.h"
#include "particletype.h"
#include "resonancetype.h"
#include <algorithm>
#include <cmath>

#include <iterator>

int main() {
  TFile *file = new TFile("histo.root", "RECREATE");
  gRandom->SetSeed(200769);
  Particle::AddParticleType("pion +", 0.13957, 1);
  Particle::AddParticleType("pion -", 0.13957, -1);
  Particle::AddParticleType("kaon +", 0.49367, 1);
  Particle::AddParticleType("kaon -", 0.49367, -1);
  Particle::AddParticleType("proton +", 0.93827, 1);
  Particle::AddParticleType("proton -", 0.93827, -1);
  Particle::AddParticleType("resonance", 0.89166, 0, 0.050);
  std::array<Particle, 120> EventParticles{};
  

  TH1F *gen_particles = new TH1F("gen_particles", "gen_particles", 7, 0, 7);

  TH1F *azimuth = new TH1F("azimuth", "azimuth", 1000, 0., 2 * M_PI);

  TH1F *polar_angle = new TH1F("polar_angle", "polar_angle", 1000, 0., M_PI);

  TH1F *p_module = new TH1F("p_module", "p_module", 1000, 0, 5);

  TH1F *p_trans = new TH1F("p_trans", "p_trans", 1000, 0, 5);

  TH1F *energy = new TH1F("energy", "energy", 1000, 0, 6);

  // per questi primi non serve sumw2?

  TH1F *all_inv_mass = new TH1F("all_inv_mass", "all_inv_mass", 1000, 0, 6);

  all_inv_mass->Sumw2();

  TH1F *same_charge_inv_mass =
      new TH1F("same_charge_inv_mass", "same_charge_inv_mass", 1000, 0, 6);

  same_charge_inv_mass->Sumw2();

  TH1F *opposite_charge_inv_mass = new TH1F(
      "opposite_charge_inv_mass", "opposite_charge_inv_mass", 1000, 0, 6);
  opposite_charge_inv_mass->Sumw2();
  TH1F *pi_k_same = new TH1F("pi_k_same_charge_inv_mass",
                             "pi_k_same_charge_inv_mass", 1000, 0, 6);
  pi_k_same->Sumw2();
  TH1F *pi_k_opposite = new TH1F("pi_k_opposite_charge_inv_mass",
                                 "pi_k_opposite_charge_inv_mass", 1000, 0, 6);
  pi_k_opposite->Sumw2();
  TH1F *dec_inv_mass = new TH1F("dec_inv_mass", "dec_inv_mass", 1000, 0, 6);
  dec_inv_mass->Sumw2();

  int star_num2{0};

  for (int i{0}; i < 1e5; i++) {
    if (star_num2 > 20) {
      std::cout << "too much k* has been genarate" << '\n';
    }

    star_num2 = 0;

      for (int event{0}; event < 1e2; event++) {
      bool is_star{false};
      double val = gRandom->Rndm();
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

      if (val <= 0.4) {
        p.SetName("pion +");
        gen_particles->Fill(0.5);
      }

      else if (val <= 0.8) {
        p.SetName("pion -");
        gen_particles->Fill(1.5);
      }

      else if (val <= 0.85) {
        p.SetName("kaon +");
        gen_particles->Fill(2.5);
      }

      else if (val <= 0.90) {
        p.SetName("kaon -");
        gen_particles->Fill(3.5);
      }

      else if (val <= 0.945) {
        p.SetName("proton +");
        gen_particles->Fill(4.5);
      }

      else if (val <= 0.99) {
        p.SetName("proton -");
        gen_particles->Fill(5.5);
      }

      else {
        p.SetName("resonance");
        gen_particles->Fill(6.5);
        is_star = true;
        double decad{gRandom->Rndm()};
        p.SetP(px, py, pz);
        energy->Fill(p.GetEnergy());
        star_num2 += 2;
        if (decad <= 0.5) {
          p1.SetName("pion +");
          p2.SetName("kaon -");

        } else {
          p1.SetName("pion -");
          p2.SetName("kaon +");
        }
        int all_good{p.Decay2Body(p1, p2)};
        if (all_good != 0) {
          std::cout << "something went wrong during decay" << '\n' << "\n";
        } else {
           dec_inv_mass->Fill(p1.GetInvariantMass(p2));
        }
      }
      if (!is_star) {
        p.SetP(px, py, pz);
        energy->Fill(p.GetEnergy());
        EventParticles[event + star_num2 / 2] = p;
      } else {
        EventParticles[event + 1 + star_num2 / 2] = p1;
        EventParticles[event + star_num2 / 2] = p2;
      }

      for (int compare{0}; compare < event + star_num2 / 2; compare++) {
        Particle old_particle{EventParticles[compare]};
        if (is_star) {
        p = p1;
        }
        all_inv_mass->Fill(p.GetInvariantMass(old_particle));
        if (p.GetCharge() == old_particle.GetCharge()) { // same charge
          same_charge_inv_mass->Fill(p.GetInvariantMass(old_particle));
          bool first_cond{p.GetName() == "pion +" &&
                          old_particle.GetName() == "kaon +"};
          bool second_cond{p.GetName() == "pion -" &&
                           old_particle.GetName() == "kaon -"};
          if (first_cond || second_cond) {
            pi_k_same->Fill(p.GetInvariantMass(old_particle));
          }
        } else { // different charge
          opposite_charge_inv_mass->Fill(
              p.GetInvariantMass(old_particle));
          bool first_cond{p.GetName() == "pion +" &&
                          old_particle.GetName() == "kaon -"};
          bool second_cond{p.GetName() == "pion -" &&
                           old_particle.GetName() == "kaon +"};
          if (first_cond || second_cond) {
            pi_k_opposite->Fill(p.GetInvariantMass(old_particle));
          }
        }
      }
    }
   /* auto pos= std::find(EventParticles.begin(), EventParticles.end(), 0);
    int distance = std::distance(EventParticles.end(), EventParticles.begin());
    if(distance <= 100 ){
      std::cout<<"l'array ha dei buchi" << "\n";
    }
    std::fill(EventParticles.begin(), EventParticles.end(),0);
    */
   //devi farlo funzionare per maggiore sicurezza
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
dec_inv_mass->Draw();


  TCanvas *c[12];
  for (int i{}; i < 14; i++) {
    c[i] = new TCanvas("c" + i, "histo", 200, 10, 600, 400);
  }
  c[0]->cd(0);
  gen_particles->Draw("HEP");
  c[0]->Print("gen_particles.pdf");
  c[0]->Print("gen_particles.C");
  c[0]->Print("gen_particles.root");
  c[1]->cd(0);
  all_inv_mass->Draw("HEP");
  c[6]->Print("invariant_mass_all.pdf");
  c[6]->Print("invariant_mass_all.C");
  c[6]->Print("invariant_mass_all.root");
  c[7]->cd(0);
  same_charge_inv_mass->Draw("HEP");
  c[7]->Print("invariant_mass_same_charge.pdf");
  c[7]->Print("invariant_mass_same_charge.C");
  c[7]->Print("invariant_mass_same_charge.root");
  c[8]->cd(0);
  opposite_charge_inv_mass->Draw("HEP");
  c[8]->Print("invariant_mass_opposite_charge.pdf");
  c[8]->Print("invariant_mass_opposite_charge.C");
  c[8]->Print("invariant_mass_opposite_charge.root");
  c[9]->cd(0);
  pi_k_same->Draw("HEP");
  c[9]->Print("invariant_mass_pi_k_same_charge.pdf");
  c[9]->Print("invariant_mass_pi_k_same_charge.C");
  c[9]->Print("invariant_mass_pi_k_same_charge.root");
  c[10]->cd(0);
  pi_k_opposite->Draw("HEP");
  c[10]->Print("invariant_mass_pi_k_opposite_charge.pdf");
  c[10]->Print("invariant_mass_pi_k_opposite_charge.C");
  c[10]->Print("invariant_mass_pi_k_opposite_charge.root");
  c[11]->cd(0);
  dec_inv_mass->Draw("HEP");
  c[11]->Print("invariant_mass_decay_product.pdf");
  c[11]->Print("invariant_mass_decay_product.C");
  c[11]->Print("invariant_mass_decay_product.root");
  c[12]->cd(0);



/*
  for (auto &elem : Particle::particleTypes_) {
    elem.second->delete();
  }
  */
}