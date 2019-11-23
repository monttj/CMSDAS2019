#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "Math/Vector4D.h"
#include "TStyle.h"

using namespace ROOT::VecOps;
using rvec_f = const RVec<float> &;

// Compute mass of Higgs from four leptons of the same kind
float compute_mass(rvec_f pt, rvec_f eta, rvec_f phi, rvec_f mass, rvec_f btag)
{
    float dR = 999;
    float mbb = 999;
    for( int i = 0; i < pt.size()-1 ; i++){
      for( int j = i+1; j < pt.size() ; j++){
        if( btag[i] <=  0.2770 || btag[j] <= 0.2770) continue;
        float tmp = DeltaR(eta[i], eta[j], phi[i], phi[j]);
        if(tmp < dR) {
          ROOT::Math::PtEtaPhiMVector p1(pt[i], eta[i], phi[i], mass[i]);
          ROOT::Math::PtEtaPhiMVector p2(pt[j], eta[j], phi[j], mass[j]);
          mbb = (p1 + p2).M();
        }    
      } 
    }

    return mbb;
}

float compute_dR(rvec_f pt, rvec_f eta, rvec_f phi, rvec_f mass, rvec_f btag)
{

    float dR = 999;
    float mbb = 999;
    float tmp = DeltaR(eta[2], eta[3], phi[2], phi[3]);
    for( int i = 0; i < pt.size()-1 ; i++){
      for( int j = i+1; j < pt.size() ; j++){
        if( btag[i] <=  0.2770 || btag[j] <= 0.2770) continue;
        float tmp = DeltaR(eta[2], eta[3], phi[2], phi[3]);
        if(tmp < dR) {
          dR = tmp;
        }
      }
    }
    return dR;
}

template <typename T>
void plot(T sig, const std::string &name, const std::string &filename){

  auto h = *sig;
  auto c = new TCanvas( name.c_str(), "c", 1);
  h.DrawClone("Hist");
  c->SaveAs(filename.c_str());
}

void ana(){

  // Enable multi-threading
  ROOT::EnableImplicitMT();

  ROOT::RDataFrame df_ttbb("Events","/home/cmsdas/public/store/mc/RunIIAutumn18NanoAODv5/ttbb_4FS_ckm_NNPDF31_TuneCP5_amcatnlo_madspin_pythia/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19_ext1-v1/110000/0C13A890-B620-EA4D-BE7B-303C80D215FD.root");

  ROOT::RDataFrame df_ttH("Events","/home/cmsdas/public/store/mc/RunIIAutumn18NanoAODv5/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/110000/0C188E39-E5D8-DE47-A7DC-09F0F64BFBC4.root");

  auto fileName_ttbb = "myntuple_ttbb.root";
  auto fileName_ttH = "myntuple_ttH.root";
  auto treeName = "mytree";

  //event selection
  //step1
  auto df_ttbb_sel = df_ttbb.Filter("(nMuon + nElectron )>= 2 ", "Events with at least two leptons");
  auto df_ttH_sel = df_ttH.Filter("(nMuon + nElectron) >=2 ", "Events with at least two leptons");
 
  //step2
  auto df_ttbb_njet = df_ttbb_sel.Filter("Sum(Jet_jetId == 6 ) >= 4", "Events with at least four jets");
  auto df_ttH_njet = df_ttH_sel.Filter("Sum(Jet_jetId == 6) >= 4", "Events with at least four jets");

  //step3 
  //select b-tagged jets with DeepFlavorJet tagging at medium working point of 0.2770
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
  auto df_ttbb_btag = df_ttbb_njet.Filter("Sum(Jet_btagDeepFlavB > 0.2770) >=2","Require jet to be b-tagged");  
  auto df_ttH_btag = df_ttH_njet.Filter("Sum(Jet_btagDeepFlavB > 0.2770) >= 2","Require jet to be b-tagged"); 

  //Define variables
  auto df_ttbb_final = df_ttbb_btag.Define("nbjets", "Sum(Jet_btagDeepFlavB > 0.2770 )")
                                   .Define("mbb", compute_mass, {"Jet_pt","Jet_eta","Jet_phi","Jet_mass","Jet_btagDeepFlavB"})
                                   .Define("dR", compute_dR, {"Jet_pt","Jet_eta","Jet_phi","Jet_mass","Jet_btagDeepFlavB"});
  auto df_ttH_final = df_ttH_btag.Define("nbjets", "Sum(Jet_btagDeepFlavB > 0.2770 )") 
                                 .Define("mbb", compute_mass, {"Jet_pt","Jet_eta","Jet_phi","Jet_mass","Jet_btagDeepFlavB"})
                                 .Define("dR", compute_dR, {"Jet_pt","Jet_eta","Jet_phi","Jet_mass","Jet_btagDeepFlavB"});

  //Histograms
  auto h_ttbb_nbtag = df_ttbb_final.Histo1D({"h_ttbb_nbtag", "", 5, 0, 5}, "nbjets", "nbjets");
  auto h_ttbb_njets= df_ttbb_final.Histo1D({"h_ttbb_njets", "", 5, 0, 5}, "nJet", "nJet");
  auto h_ttbb_mbb= df_ttbb_final.Histo1D({"h_ttbb_mbb", "", 10, 70, 170}, "mbb", "mbb");
  auto h_ttbb_dR= df_ttbb_final.Histo1D({"h_ttbb_dR", "", 20 , 0, 4}, "dR", "dR");

  auto h_ttH_nbtag = df_ttH_final.Histo1D({"h_ttH_nbtag", "", 5, 0, 5}, "nbjets", "nbjets");
  auto h_ttH_njets= df_ttH_final.Histo1D({"h_ttH_njets", "", 5, 0, 5}, "nJet", "nJet");
  auto h_ttH_mbb= df_ttH_final.Histo1D({"h_ttH_mbb", "", 10, 70, 170}, "mbb", "mbb");
  auto h_ttH_dR= df_ttH_final.Histo1D({"h_ttH_dR", "", 20 , 0, 4}, "dR", "dR");

  //create ntuple 
  df_ttbb_final.Snapshot(treeName, fileName_ttbb, {"nbjets","nJet","mbb","dR"});
  df_ttH_final.Snapshot(treeName, fileName_ttH, {"nbjets","nJet","mbb","dR"});

  //count number of events
  auto n_df_ttbb = df_ttbb.Count();
  auto n_df_ttH = df_ttH.Count();
  auto n_df_ttbb_sel = df_ttbb_sel.Count();
  auto n_df_ttH_sel = df_ttH_sel.Count();
  auto n_df_ttbb_btag = df_ttbb_btag.Count();
  auto n_df_ttH_btag = df_ttH_btag.Count();

  std::cout << "ttbb : number of events = " << *n_df_ttbb << " , preselection = " << *n_df_ttbb_sel << " , final selection = " << *n_df_ttbb_btag << std::endl;
  std::cout << "ttH : number of events = " << *n_df_ttH << " , preselection = " << *n_df_ttH_sel << " , final selection = " << *n_df_ttH_btag << std::endl;

  //plotting 
  plot(h_ttbb_nbtag, "ttbb_nbtag", "h_ttbb_nbtag.pdf");
  plot(h_ttbb_njets, "ttbb_jets", "h_ttbb_nbtag.pdf");
  plot(h_ttbb_mbb, "ttbb_mbb", "h_ttbb_mbb.pdf");
  plot(h_ttbb_dR, "ttbb_dR", "h_ttbb_dR.pdf");
 
  plot(h_ttbb_nbtag, "ttbb_nbtag", "h_ttbb_njets.pdf");
  plot(h_ttH_njets, "ttH_njets", "h_ttH_njets.pdf");
  plot(h_ttH_mbb, "ttH_mbb", "h_ttH_mbb.pdf");
  plot(h_ttH_dR, "ttH_dR", "h_ttH_dR.pdf");

}
