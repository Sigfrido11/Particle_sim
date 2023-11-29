#include <iostream>

void analyse()
{
  TH1::AddDirectory(kFALSE);
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
  file->Close();

  if (gen_particles->GetEntries() == 1e7)
  {
    std::cout << "entries in gen particles histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in gen particles histo: unexpected value" << '\n';
  }
  if (azimuth->GetEntries() == 1e7)
  {
    std::cout << "entries in azimuth histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in azimuth histo: unexpected value" << '\n';
  }
  if (polar_angle->GetEntries() == 1e7)
  {
    std::cout << "entries in polar angle histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in polar angle histo: unexpected value" << '\n';
  }
  if (p_module->GetEntries() == 1e7)
  {
    std::cout << "entries in p module histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in p module histo: unexpected value" << '\n';
  }
  if (p_trans->GetEntries() == 1e7)
  {
    std::cout << "entries in p trans histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in p trans histo: unexpected value" << '\n';
  }
  if (energy->GetEntries() == 1e7)
  {
    std::cout << "entries in energy histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in energy histo: unexpected value" << '\n';
  }
  if (all_inv_mass->GetEntries() < 1e5 * 60 * 119 &&
      all_inv_mass->GetEntries() > 1e5 * 40 * 79)
  {
    std::cout << "entries in gen particles histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in gen particles histo: unexpected value" << '\n';
  }
  if (same_charge_inv_mass->GetEntries() < 1e5 * 40 * 119 &&
      same_charge_inv_mass->GetEntries() > 1e5 * 30 * 79)
  {
    std::cout << "entries in same charge inv mass histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in same charge inv mass histo: unexpected value"
              << '\n';
  }
  if (opposite_charge_inv_mass->GetEntries() < 1e5 * 40 * 119 &&
      opposite_charge_inv_mass->GetEntries() > 1e5 * 30 * 79)
  {
    std::cout << "entries in opposite charge inv mass histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in opposite charge inv mass histo: unexpected value"
              << '\n';
  }
  if (pi_k_same->GetEntries() < 1e5 * 30 * 119 &&
      pi_k_same->GetEntries() > 1e5 * 20 * 79)
  {
    std::cout << "entries in pi k same histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in pi k same histo: unexpected value" << '\n';
  }
  if (pi_k_opposite->GetEntries() < 1e5 * 30 * 119 &&
      pi_k_opposite->GetEntries() > 1e5 * 20 * 79)
  {
    std::cout << "entries in pi k opposite histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in pi k opposite histo: unexpected value" << '\n';
  }
  if (dec_inv_mass->GetEntries() < 1e6 && dec_inv_mass->GetEntries() > 1e4)
  {
    std::cout << "entries in dec inv mass histo: ok" << '\n';
  }
  else
  {
    std::cout << "entries in dec inv mass histo: unexpected value" << '\n';
  }

  if (gen_particles->GetBinContent(1) - gen_particles->GetBinError(1) <=
          gen_particles->GetEntries() * 0.4 &&
      gen_particles->GetBinContent(1) + gen_particles->GetBinError(1) >=
          gen_particles->GetEntries() * 0.4)
  {
    std::cout << "n pi+: ok" << '\n';
  }
  else
  {
    std::cout << "n pi+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(2) - gen_particles->GetBinError(2) <=
          gen_particles->GetEntries() * 0.4 &&
      gen_particles->GetBinContent(2) + gen_particles->GetBinError(2) >=
          gen_particles->GetEntries() * 0.4)
  {
    std::cout << "n pi-: ok" << '\n';
  }
  else
  {
    std::cout << "n pi-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(3) - gen_particles->GetBinError(3) <=
          gen_particles->GetEntries() * 0.05 &&
      gen_particles->GetBinContent(3) + gen_particles->GetBinError(3) >=
          gen_particles->GetEntries() * 0.05)
  {
    std::cout << "n k+: ok" << '\n';
  }
  else
  {
    std::cout << "n k+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(4) - gen_particles->GetBinError(4) <=
          gen_particles->GetEntries() * 0.05 &&
      gen_particles->GetBinContent(4) + gen_particles->GetBinError(4) >=
          gen_particles->GetEntries() * 0.05)
  {
    std::cout << "n k-: ok" << '\n';
  }
  else
  {
    std::cout << "n k-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(5) - gen_particles->GetBinError(5) <=
          gen_particles->GetEntries() * 0.045 &&
      gen_particles->GetBinContent(5) + gen_particles->GetBinError(5) >=
          gen_particles->GetEntries() * 0.045)
  {
    std::cout << "n p+: ok" << '\n';
  }
  else
  {
    std::cout << "n p+: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(6) - gen_particles->GetBinError(6) <=
          gen_particles->GetEntries() * 0.045 &&
      gen_particles->GetBinContent(6) + gen_particles->GetBinError(6) >=
          gen_particles->GetEntries() * 0.045)
  {
    std::cout << "n p-: ok" << '\n';
  }
  else
  {
    std::cout << "n p-: unexpected" << '\n';
  }
  if (gen_particles->GetBinContent(7) - gen_particles->GetBinError(7) <=
          gen_particles->GetEntries() * 0.01 &&
      gen_particles->GetBinContent(7) + gen_particles->GetBinError(7) >=
          gen_particles->GetEntries() * 0.01)
  {
    std::cout << "n k*: ok" << '\n';
  }
  else
  {
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
      (f1->GetParameter(1) - 1) / f1->GetParError(1) > -2)
  {
    std::cout << "p module distrution is as expexted" << '\n';
  }
  else
  {
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
  diff_p_k->Add(pi_k_same, -1);
  diff->GetMaximumBin();
  diff_p_k->GetMaximumBin();
  dec_inv_mass->GetMaximumBin();
  f1 = new TF1("f3", "gaus(0)", 0, 10);
  diff->Fit(f1);
  std::cout << "from difference opposite and same charge inv mass: " << '\n'
            << "k* mass: " << f1->GetParameter(1) << "+/-" << f1->GetParError(1)
            << '\n'
            << f1->GetParameter(1) << "+/-" << f1->GetParError(1) << '\n'
            << "k* width: " << f1->GetParameter(2) << "+/-"
            << f1->GetParError(2) << '\n';
  std::cout << "ChiSquare/NDF " << f1->GetChisquare() / f1->GetNDF() << '\n';
  std::cout << "probability: " << f1->GetProb() << '\n';
  diff_p_k->Fit(f1);
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

  // impostando lavoro per 5 canvas

  TCanvas *c1 = new TCanvas("c1", "n gen, p module and angles", 200, 10, 600, 400);
  c1->Divide(2, 2);
  c1->cd(1);
  gen_particles->Draw("HEP");
  c1->cd(2);
  p_module->Draw("HEP");
  c1->cd(3);
  azimuth->Draw("HEP");
  c1->cd(4);
  polar_angle->Draw("HEP");
  c1->Print("N_P_Angles.pdf");
  c1->Print("N_P_Angles.C");
  c1->Print("N_P_Angles.root");

  TCanvas *c2 = new TCanvas("c2", "p trans", 200, 10, 600, 400);
  p_trans->Draw("HEP");
  c2->Print("PTrans.pdf");
  c2->Print("PTrans.C");
  c2->Print("PTrans.root");

  TCanvas *c3 = new TCanvas("c3", "energy and all inv mass", 200, 10, 600, 400);
  c3->Divide(1, 2);
  c3->cd(1);
  energy->Draw("HEP");
  c3->cd(2);
  all_inv_mass->Draw("HEP");
  c3->Print("Energy_AllInvMass.pdf");
  c3->Print("Energy_AllInvMass.C");
  c3->Print("Energy_AllInvMass.root");

  TCanvas *c4 = new TCanvas("c4", "inv mass same and opposite (all and pi-k)", 200, 10, 600, 400);
  c4->Divide(2, 2);
  c4->cd(1);
  same_charge_inv_mass->Draw("HEP");
  c4->cd(2);
  opposite_charge_inv_mass->Draw("HEP");
  c4->cd(3);
  pi_k_same->Draw("HEP");
  c4->cd(4);
  pi_k_opposite->Draw("HEP");
  c4->Print("InvMassSameOpposite.pdf");
  c4->Print("InvMassSameOpposite.C");
  c4->Print("InvMassSameOpposite.root");

  TCanvas *c5 = new TCanvas("c5", "invariant mass from decay and differences", 200, 10, 600, 400);
  c5->Divide(1, 3);
  c5->cd(1);
  dec_inv_mass->Draw("HEP");
  c5->cd(2);
  diff->Draw("HEP");
  c5->cd(3);
  diff_p_k->Draw("HEP");
  c5->Print("Decay_Diffs.pdf");
  c5->Print("Decay_Diffs.C");
  c5->Print("Decay_Diffs.root");

  //
}
// PROBABILMENTE NOME SBAGLIATO HISTO FITTATI