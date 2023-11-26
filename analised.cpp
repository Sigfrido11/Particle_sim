#include <iostream>

void analyse() {

  TFile *file = new TFile("histo.root");
  TH1F *gen_particles = (TH1F *)file->Get("gen_particles");
  TH1F *azimuth = (TH1F *)file->Get("azimuth");
  TH1F *polar_angle = (TH1F *)file->Get("polar_angle");
  TH1F *p_module = (TH1F *)file->Get("p_module");
  TH1F *p_trans = (TH1F *)file->Get("p_trans");
  TH1F *energy = (TH1F *)file->Get("energy");
  TH1F *all_inv_mass = (TH1F *)file->Get("all_inv_mass");
  TH1F *same_charge_inv_mass = (TH1F *)file->Get("same_charge_inv_mass");
  TH1F *opposite_charge_inv_mass =
      (TH1F *)file->Get("opposite_charge_inv_mass");
  TH1F *pi_k_same = (TH1F *)file->Get("pi_k_same_charge_inv_mass");
  TH1F *pi_k_opposite = (TH1F *)file->Get("pi_k_opposite_charge_inv_mass");
  TH1F *dec_inv_mass = (TH1F *)file->Get("dec_inv_mass");

  all_inv_mass->Sumw2();
  same_charge_inv_mass->Sumw2();
  opposite_charge_inv_mass->Sumw2();
  pi_k_same->Sumw2();
  pi_k_opposite->Sumw2();
  dec_inv_mass->Sumw2();

  if (gen_particles->GetEntries() == 1e7) {
    std::cout << "entries in gen particles histo: ok" << '\n';
  } else {
    std::cout << "entries in gen particles histo: unexpected value" << '\n';
  }
  if (azimuth->GetEntries() == 1e7) {
    std::cout << "entries in azimuth histo: ok" << '\n';
  } else {
    std::cout << "entries in azimuth histo: unexpected value" << '\n';
  }
  if (polar_angle->GetEntries() == 1e7) {
    std::cout << "entries in polar angle histo: ok" << '\n';
  } else {
    std::cout << "entries in polar angle histo: unexpected value" << '\n';
  }
  if (p_module->GetEntries() == 1e7) {
    std::cout << "entries in p module histo: ok" << '\n';
  } else {
    std::cout << "entries in p module histo: unexpected value" << '\n';
  }
  if (p_trans->GetEntries() == 1e7) {
    std::cout << "entries in p trans histo: ok" << '\n';
  } else {
    std::cout << "entries in p trans histo: unexpected value" << '\n';
  }
  if (energy->GetEntries() == 1e7) {
    std::cout << "entries in energy histo: ok" << '\n';
  } else {
    std::cout << "entries in energy histo: unexpected value" << '\n';
  }
  if (all_inv_mass->GetEntries() < 1e5 * 60 * 119 &&
      all_inv_mass->GetEntries() > 1e5 * 40 * 79) {
    std::cout << "entries in gen particles histo: ok" << '\n';
  } else {
    std::cout << "entries in gen particles histo: unexpected value" << '\n';
  }
  if (same_charge_inv_mass->GetEntries() < 1e5 * 40 * 119 &&
      same_charge_inv_mass->GetEntries() > 1e5 * 30 * 79) {
    std::cout << "entries in same charge inv mass histo: ok" << '\n';
  } else {
    std::cout << "entries in same charge inv mass histo: unexpected value"
              << '\n';
  }
  if (opposite_charge_inv_mass->GetEntries() < 1e5 * 40 * 119 &&
      opposite_charge_inv_mass->GetEntries() > 1e5 * 30 * 79) {
    std::cout << "entries in opposite charge inv mass histo: ok" << '\n';
  } else {
    std::cout << "entries in opposite charge inv mass histo: unexpected value"
              << '\n';
  }
  if (pi_k_same->GetEntries() < 1e5 * 30 * 119 &&
      pi_k_same->GetEntries() > 1e5 * 20 * 79) {
    std::cout << "entries in pi k same histo: ok" << '\n';
  } else {
    std::cout << "entries in pi k same histo: unexpected value" << '\n';
  }
  if (pi_k_opposite->GetEntries() < 1e5 * 30 * 119 &&
      pi_k_opposite->GetEntries() > 1e5 * 20 * 79) {
    std::cout << "entries in pi k opposite histo: ok" << '\n';
  } else {
    std::cout << "entries in pi k opposite histo: unexpected value" << '\n';
  }
  if (dec_inv_mass->GetEntries() < 1e6 && dec_inv_mass->GetEntries() > 1e4) {
    std::cout << "entries in dec inv mass histo: ok" << '\n';
  } else {
    std::cout << "entries in dec inv mass histo: unexpected value" << '\n';
  }

  if (gen_particles->GetBinContent(1) - gen_particles->GetBinError(1) <=
          gen_particles->GetEntries() * 0.4 &&
      gen_particles->GetBinContent(1) + gen_particles->GetBinError(1) >=
          gen_particles->GetEntries() * 0.4) {
    std::cout << "n pi+: ok" << '\n';
  } else {
    std::cout << "n pi+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(2) - gen_particles->GetBinError(2) <=
          gen_particles->GetEntries() * 0.4 &&
      gen_particles->GetBinContent(2) + gen_particles->GetBinError(2) >=
          gen_particles->GetEntries() * 0.4) {
    std::cout << "n pi-: ok" << '\n';
  } else {
    std::cout << "n pi-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(3) - gen_particles->GetBinError(3) <=
          gen_particles->GetEntries() * 0.05 &&
      gen_particles->GetBinContent(3) + gen_particles->GetBinError(3) >=
          gen_particles->GetEntries() * 0.05) {
    std::cout << "n k+: ok" << '\n';
  } else {
    std::cout << "n k+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(4) - gen_particles->GetBinError(4) <=
          gen_particles->GetEntries() * 0.05 &&
      gen_particles->GetBinContent(4) + gen_particles->GetBinError(4) >=
          gen_particles->GetEntries() * 0.05) {
    std::cout << "n k-: ok" << '\n';
  } else {
    std::cout << "n k-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(5) - gen_particles->GetBinError(5) <=
          gen_particles->GetEntries() * 0.045 &&
      gen_particles->GetBinContent(5) + gen_particles->GetBinError(5) >=
          gen_particles->GetEntries() * 0.045) {
    std::cout << "n p+: ok" << '\n';
  } else {
    std::cout << "n p+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(6) - gen_particles->GetBinError(6) <=
          gen_particles->GetEntries() * 0.045 &&
      gen_particles->GetBinContent(6) + gen_particles->GetBinError(6) >=
          gen_particles->GetEntries() * 0.045) {
    std::cout << "n p-: ok" << '\n';
  } else {
    std::cout << "n p-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(7) - gen_particles->GetBinError(7) <=
          gen_particles->GetEntries() * 0.01 &&
      gen_particles->GetBinContent(7) + gen_particles->GetBinError(7) >=
          gen_particles->GetEntries() * 0.01) {
    std::cout << "n k*: ok" << '\n';
  } else {
    std::cout << "n k*: unexpected" << '\n';
  }

  TF1 *f1 = new TF1("f1", "[0]", 0, 10);
  azimuth->Fit(f1);
  std::cout << "azimuth: uniform fit parameter: " << f1->GetParameter(0)
            << "+/-" << f1->GetParError(0) << '\n';
  std::cout << "ChiSquare/NDF; " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';
  polar_angle->Fit(f1);
  std::cout << "polar angle: uniform fit parameter: " << f1->GetParameter(0)
            << "+/-" << f1->GetParError(0) << '\n';
  std::cout << "ChiSquare/NDF " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';

  f1 = new TF1("f2", "expo(0)", 0, 1);
  p_module->Fit(f1);
  if ((f1->GetParameter(1) - 1) / f1->GetParError(1) < 2 &&
      (f1->GetParameter(1) - 1)/ f1->GetParError(1)>-2) {
      std::cout << "p module distrution is as expexted" << '\n';
    }
  else {
    std::cout << "unexpexted results for p module distriution" << '\n';
  }
  std::cout << "p module: expo fit parameter: " << f1->GetParameter(1) << "+/-"
            << f1->GetParError(1) << '\n';
  std::cout << "ChiSquare/NDF " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';

  /*
  11)Considerando gli istogrammi di massa invariante:
  1) tutte le particelle, combinazioni con carica di segno opposto
  2) tutte le particelle, combinazioni con carica di segno concorde
  3) quello in cui si combinano solo pioni e kaoni di segno opposto,
  4) quello in cui si combinano solo pioni e kaoni di segno concorde.
  5) quello contenente solo i decadimenti della K*
  si sottragga dall’ 1) il 2) e dal 3) il 4). Negli istogrammi esito della
  sottrazione, si osserva un picco in corrispondenza della massa della risonanza
  K*? È consistente con il segnale dell’istogramma 5)? n.b., per una corretta
  valutazione delle incertezze sui contenuti dei bin negli istogrammi esito di
  tali differenze, è necessario che per gli istogrammi “operandi” sia stato
  invocato il metodo Sumw2() in fase di creazione nel programma di generazione.
  Infine, dagli istogrammi esito della sottrazione estrarre la massa e la
  larghezza della K* adattando la distribuzione ottenuta dalla differenza a una
  distribuzione gaussiana (media della gaussiana = massa K*, sigma gaussiana =
  larghezza K*, definite esplicitamente un TF1 e stampate a schermo sullo
  standard output il valore dei parametri, il X2 /NDF e la probabilità del fit)
  */
  TH1F *diff = new TH1F(*opposite_charge_inv_mass);
  diff->Add(same_charge_inv_mass, -1.);
  TH1F *diff_p_k = new TH1F(*pi_k_opposite);
  diff->Add(pi_k_same, -1);
  opposite_charge_inv_mass->GetMaximumBin();
  diff_p_k->GetMaximumBin();
  dec_inv_mass->GetMaximumBin();
  f1 = new TF1("f3", "gaus(0)", 0, 10);
  opposite_charge_inv_mass->Fit(f1);
  std::cout << "from difference opposite and same charge inv mass: " << '\n'
            << "k* mass: " << f1->GetParameter(1) << "+/-" << f1->GetParError(1)
            << '\n'
            << f1->GetParameter(1) << "+/-" << f1->GetParError(1) << '\n'
            << "k* width: " << f1->GetParameter(2) << "+/-"
            << f1->GetParError(2) << '\n';
  std::cout << "ChiSquare/NDF " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';
  pi_k_opposite->Fit(f1);
  std::cout
      << "from difference opposite and same charge pions and kaons inv mass: "
      << '\n'
      << "k* mass: " << f1->GetParameter(1) << "+/-" << f1->GetParError(1)
      << '\n'
      << "k* width: " << f1->GetParameter(2) << "+/-" << f1->GetParError(2)
      << '\n';
  std::cout << "ChiSquare/NDF " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';

  /*
  12)Considerando gli istogrammi di massa invariante:
  • Apportate le necessarie modifiche per una buona presentazione dei grafici
  che avete prodotto (range della scala verticale, etichette degli assi,
  eventuale “cosmetica”) • Disegnate gli istogrammi su delle Canvas che poi
  salverete in formato .pdf (o altro formato grafico), .C,.root
  */

  TCanvas *c[14];
  for (int i{}; i < 14; i++) {
    c[i] = new TCanvas("c" + i, "histo", 200, 10, 600, 400);
  }
  c[0]->cd(0);
  gen_particles->Draw("HEP");
  c[0]->Print("gen_particles.pdf");
  c[0]->Print("gen_particles.C");
  c[0]->Print("gen_particles.root");
  c[1]->cd(0);
  azimuth->Draw("HEP");
  c[1]->Print("azimuth.pdf");
  c[1]->Print("azimuth.C");
  c[1]->Print("azimuth.root");
  c[2]->cd(0);
  polar_angle->Draw("HEP");
  c[2]->Print("polar_angle.pdf");
  c[2]->Print("polar_angle.C");
  c[2]->Print("polar_angle.root");
  c[3]->cd(0);
  p_module->Draw("HEP");
  c[3]->Print("p_module.pdf");
  c[3]->Print("p_module.C");
  c[3]->Print("p_module.root");
  c[4]->cd(0);
  p_trans->Draw("HEP");
  c[4]->Print("p_transverse.pdf");
  c[4]->Print("p_transverse.C");
  c[4]->Print("p_transverse.root");
  c[5]->cd(0);
  energy->Draw("HEP");
  c[5]->Print("energy.pdf");
  c[5]->Print("energy.C");
  c[5]->Print("energy.root");
  c[6]->cd(0);
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
  diff->Draw("HEP");
  c[12]->Print("invariant_mass_opposite_minus_same.pdf");
  c[12]->Print("invariant_mass_opposite_minus_same.C");
  c[12]->Print("invariant_mass_opposite_minus_same.root");
  c[13]->cd(0);
  diff_p_k->Draw("HEP");
  c[13]->Print("invariant_mass_pi_k_opposite_minus_same.pdf");
  c[13]->Print("invariant_mass_pi_k_opposite_minus_same.C");
  c[13]->Print("invariant_mass_pi_k_opposite_minus_same.root");

}