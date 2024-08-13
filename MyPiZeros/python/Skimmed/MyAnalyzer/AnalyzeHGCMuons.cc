#define ANALYZEHGCMuons_cxx

#include "AnalyzeHGCMuons.h"
#include "TLorentzVector.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
int ctr = 0;
float genMass;
float genAngle;
int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Please give 3 arguments "
         << "runList "
         << " "
         << "outputFileName"
         << " "
         << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName = argv[2];
  const char *data = argv[3];
  const char *massP = argv[4];

  cout<<massP<<endl;
  AnalyzeHGCMuons hgcmuons(inputFileList, outFileName, data,massP);
  // cout << "dataset " << data << " " << endl;

  hgcmuons.EventLoop(data);

  return 0;
}

double DeltaPhi(double phi1, double phi2) {
  double result = phi1 - phi2;
  while (result > M_PI)
    result -= 2 * M_PI;
  while (result <= -M_PI)
    result += 2 * M_PI;
  return result;
}
double DeltaEta(double eta1, double eta2){
double result= abs(eta1-eta2);
return result;
}
double DeltaR(double eta1, double phi1, double eta2, double phi2) {
  double deta = eta1 - eta2;
  double dphi = DeltaPhi(phi1, phi2);
  return std::sqrt(deta * deta + dphi * dphi);
}
double DeltaX(double x1, double x2){
  double result = abs(x1 - x2);
  return result;
}
double DeltaL(double x1, double x2, double y1, double y2){
  double dx = x1-x2;
  double dy = y1-y2;
  double result = sqrt(dx*dx + dy*dy);
  return result;
}
void AnalyzeHGCMuons::EventLoop(const char *data) {
  if (fChain == 0)
    return;

  TLorentzVector p1gen, p2gen, pAgen;
  TLorentzVector p1reco, p2reco,pTreco;
  Long64_t nentries = fChain->GetEntriesFast();
 
  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  int decade = 0;

  for (Long64_t jentry = 0; jentry < nentries; jentry++) {

  
    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int(progress);
    if (k > decade)
      // cout << 10 * k << " %" << endl;
      decade = k;

    // ===============read this entry == == == == == == == == == == ==
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    
    fillhist = 0;
        pAgen.SetPtEtaPhiM(A_Gen_pt->at(0), A_Gen_eta->at(0), A_Gen_phi->at(0), A_Gen_mass->at(0));

	/*if(Pho_Gen_Pt->size() <2)
	  {
		continue;
	  }*/
        
        p1gen.SetPtEtaPhiE(Pho_Gen_Pt->at(0), Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0), Pho_Gen_E->at(0));
        p2gen.SetPtEtaPhiE(Pho_Gen_Pt->at(0), Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0), Pho_Gen_E->at(0));
	//p2gen.SetPtEtaPhiE(Pho_Gen_Pt->at(1), Pho_Gen_Eta->at(1),Pho_Gen_Phi->at(1), Pho_Gen_E->at(1));
        //Defining gen quantities
        genMass = A_Gen_mass->at(0);
        //genAngle = p1gen.Angle(p2gen.Vect());
        float genEnergy = pAgen.Energy();
        float AgenPt = A_Gen_pt->at(0);
        float AgenEta = A_Gen_eta->at(0);
        float AgenPhi = A_Gen_phi->at(0);
         float gamma= pAgen.Gamma();
         float eta1 = p1gen.Eta();
         float eta2 = p2gen.Eta();
         float phi1 = p1gen.Phi();
         float phi2 = p2gen.Phi();
         float pt1 = p1gen.Pt();
         float pt2 = p2gen.Pt();
         float Epho1 = p1gen.Energy();
         float Epho2 = p2gen.Energy();
	float deta=DeltaEta(Pho_Gen_Eta->at(0),Pho_Gen_Eta->at(0));
        float dphi= DeltaPhi(Pho_Gen_Phi->at(0),Pho_Gen_Phi->at(0));
        
	a_gen_gamma->Fill(gamma);
	nGen->Fill(Pho_Gen_Pt->size());
  pho1_gen_eta->Fill(eta1);
  pho1_gen_phi->Fill(phi1);
  pho1_gen_pt->Fill(pt1);
  pho2_gen_eta->Fill(eta2);
  pho2_gen_phi->Fill(phi2);
  pho2_gen_pt->Fill(pt2);
  pho1_gen_E->Fill(Epho1);
  pho2_gen_E->Fill(Epho2);
	nreco->Fill(pt->size());
        Gen_pho_sep->Fill(deta/0.05,dphi/0.05);
  E_pho1_vs_E_pho2->Fill(Epho1, Epho2);
if(pt1>=pt2){E_sublead_by_E_lead->Fill(Epho2/Epho1);}
else{E_sublead_by_E_lead->Fill(Epho1/Epho2);}
E_pho2_by_E_pho1->Fill(Epho2/Epho1);
             
  double Ez = sqrt(pAgen.E()*pAgen.E() - pAgen.Et()*pAgen.Et());
  
 
  a_gen_mass->Fill(genMass);
  a_gen_pt->Fill(AgenPt);
  a_gen_eta->Fill(AgenEta);
  a_gen_phi->Fill(AgenPhi);
  a_gen_E->Fill(genEnergy);
  a_gen_mass_vs_pt->Fill(genMass,AgenPt);
  a_gen_eta_vs_phi->Fill(abs(AgenEta),AgenPhi);
  gen_eta1_vs_eta2->Fill(eta1,eta2);
  if(genMass>=0.24 && genMass<=0.26){
   angle_240_260->Fill(genAngle);
   angle_vs_gamma_Ma_240_260->Fill(gamma,genAngle);}
  if(genMass >=0.49 && genMass<=0.51){
   angle_490_510->Fill(genAngle);
   angle_vs_gamma_Ma_490_510->Fill(gamma,genAngle);}
  if (genMass>=0.74 && genMass<=0.76){
   angle_740_760->Fill(genAngle); 
   angle_vs_gamma_Ma_740_760->Fill(gamma,genAngle);}
  if(genMass>=0.99 && genMass<=1.01) {
   angle_990_1010->Fill(genAngle);
   angle_vs_gamma_Ma_990_1010->Fill(gamma,genAngle);}
  for (int i=0;i<eta->size();i++){
    if(1.44<=eta->at(i) && eta->at(i)<=1.57){r9_eta_1->Fill(Pho_R9->at(i));}
    if(1.57< eta->at(i) && eta->at(i)<=2){r9_eta_2->Fill(Pho_R9->at(i));}
    if(2< eta->at(i) && eta->at(i)<=2.5){r9_eta_3->Fill(Pho_R9->at(i));}
  }


float P1TotalRecE=0;
float P1TotalUncRecE=0;
float P1TotalCluRecE=0;
float P2TotalRecE=0;
float P2TotalUncRecE=0;
float P2TotalCluRecE=0;



for(int i =0;i<Hit_X_Pho1->size();i++){

pho1_hitX->Fill(Hit_X_Pho1->at(i));
pho1_hitY->Fill(Hit_Y_Pho1->at(i));
pho1_hit_Z->Fill(abs(Hit_Z_Pho1->at(i)));
pho1_hit_E->Fill(RecHitEnPho1->at(i));

EE_XY_occupancy->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i),RecHitEnPho1->at(i));
P1TotalRecE= P1TotalRecE +RecHitEnPho1->at(i);
if (RecHitFracPho1->at(i) <0){ P1TotalUncRecE = P1TotalUncRecE + RecHitEnPho1->at(i); }
else {P1TotalCluRecE= P1TotalCluRecE + RecHitEnPho1->at(i);} 
}
Pho1_RechitE_vs_A_gen_E->Fill(genEnergy,P1TotalRecE);
Pho1_UnclRechitE_vs_A_gen_E->Fill(genEnergy,P1TotalUncRecE);
Pho1_ClusRechitE_vs_A_gen_E->Fill(genEnergy,P1TotalCluRecE);

for(int i =0;i<Hit_X_Pho2->size();i++){

pho2_hitX->Fill(Hit_X_Pho2->at(i));
pho2_hitY->Fill(Hit_Y_Pho2->at(i));
pho2_hit_Z->Fill(abs(Hit_Z_Pho2->at(i)));
pho2_hit_E->Fill(RecHitEnPho2->at(i));

EE_XY_occupancy->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i),RecHitEnPho2->at(i));
P2TotalRecE = P2TotalRecE + RecHitEnPho2->at(i);
if(RecHitFracPho2->at(i) <0){P2TotalUncRecE = P2TotalUncRecE + RecHitEnPho2->at(i) ;}
else {P2TotalCluRecE = P2TotalCluRecE + RecHitEnPho2->at(i);}
}

Pho2_RechitE_vs_A_gen_E->Fill(genEnergy,P2TotalRecE);
Pho2_UnclRechitE_vs_A_gen_E->Fill(genEnergy,P2TotalUncRecE);
Pho2_ClusRechitE_vs_A_gen_E->Fill(genEnergy,P2TotalCluRecE);

float TotRecE = P1TotalRecE + P2TotalRecE;
float TotUncRecE = P1TotalUncRecE + P2TotalUncRecE;
float TotCluRecE = P1TotalCluRecE + P2TotalCluRecE;

int EE_hits = Hit_X_Pho1->size() + Hit_X_Pho2->size();
int ES_hits = Hit_ES_X_Pho1->size() + Hit_ES_X_Pho2->size();

float ES_pho1_en = 0;
float ES_pho2_en =0;

for(int i=0; i<Hit_ES_X_Pho1->size();i++){
pho1_ES_hitX->Fill(Hit_ES_X_Pho1->at(i));  
pho1_ES_hitY->Fill(Hit_ES_Y_Pho1->at(i));  
pho1_ES_hit_Z->Fill(abs(Hit_ES_Z_Pho1->at(i)));
pho1_ES_hit_E->Fill(ES_RecHitEnPho1->at(i));  
ES_pho1_en = ES_pho1_en +ES_RecHitEnPho1->at(i);
}
for(int i=0; i<Hit_ES_X_Pho2->size();i++){
  ES_pho2_en = ES_pho2_en +ES_RecHitEnPho2->at(i);
}
float Tot_ES_en = ES_pho1_en + ES_pho2_en;

if(genMass>=0.24 && genMass <=0.26){
Tot_rechit_E_Ma_250->Fill(TotRecE); Tot_unc_rechit_E_Ma_250 ->Fill(TotUncRecE); Tot_clu_rechit_E_Ma_250->Fill(TotCluRecE); nreco_Ma_250->Fill(eta->size());
n_EE_rechit_Ma_250->Fill(EE_hits);n_ES_rechit_ma_250->Fill(ES_hits);
}
if(genMass>=0.49 && genMass <=0.51){
  Tot_rechit_E_Ma_500->Fill(TotRecE);Tot_unc_rechit_E_Ma_500->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_500->Fill(TotCluRecE);nreco_Ma_500->Fill(eta->size());
  n_EE_rechit_Ma_500->Fill(EE_hits);n_ES_rechit_ma_500->Fill(ES_hits);
}
if(genMass>=0.74 && genMass<=0.76){
  Tot_rechit_E_Ma_750->Fill(TotRecE);Tot_unc_rechit_E_Ma_750->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_750->Fill(TotCluRecE);nreco_Ma_750->Fill(eta->size());
  n_EE_rechit_Ma_750->Fill(EE_hits);n_ES_rechit_ma_750->Fill(ES_hits);
}
if(genMass>=0.99 && genMass<=1.01){
  //1D histograms
  Tot_rechit_E_Ma_1000->Fill(TotRecE);Tot_unc_rechit_E_Ma_1000->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_1000->Fill(TotCluRecE);nreco_Ma_1000->Fill(eta->size());
  n_EE_rechit_Ma_1000->Fill(EE_hits);n_ES_rechit_ma_1000->Fill(ES_hits);
  //2D histograms
}
if(genMass>=0.2 && genMass<0.3){Tot_unc_rechit_E_Ma_200_300->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_200_300->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_200_300->Fill(Tot_ES_en);
}
if(genMass>=0.3 && genMass<0.4){Tot_unc_rechit_E_Ma_300_400->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_300_400->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_300_400->Fill(Tot_ES_en);
}
if(genMass>=0.4 && genMass<0.5){Tot_unc_rechit_E_Ma_400_500->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_400_500->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_400_500->Fill(Tot_ES_en);
}
if(genMass>=0.5 && genMass<0.6){Tot_unc_rechit_E_Ma_500_600->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_500_600->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_500_600->Fill(Tot_ES_en);
}
if(genMass>=0.6 && genMass<0.7){Tot_unc_rechit_E_Ma_600_700->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_600_700->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_600_700->Fill(Tot_ES_en);
}
if(genMass>=0.7 && genMass<0.8){Tot_unc_rechit_E_Ma_700_800->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_700_800->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_700_800->Fill(Tot_ES_en);
}
if(genMass>=0.8 && genMass<0.9){Tot_unc_rechit_E_Ma_800_900->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_800_900->Fill(TotCluRecE); 
Tot_ES_RH_E_Ma_800_900->Fill(Tot_ES_en);
}
if(genMass>=0.9 && genMass<1.0){Tot_unc_rechit_E_Ma_900_1000->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_900_1000->Fill(TotCluRecE);
Tot_ES_RH_E_Ma_900_1000->Fill(Tot_ES_en);
}

for (int i=0; i<Hit_Eta_Pho1->size();i++){pho1_EE_hit_eta->Fill(Hit_Eta_Pho1->at(i));}
for (int i=0; i<Hit_Eta_Pho2->size();i++){pho2_EE_hit_eta->Fill(Hit_Eta_Pho2->at(i));}

int n_es_l1_hits =0;
int n_es_l2_hits =0;
if(Hit_ES_X_Pho1->size()>0){ 
  for(int i =0; i<Hit_ES_X_Pho1->size(); i++){
  if(abs(Hit_ES_Z_Pho1->at(i))>302 && abs(Hit_ES_Z_Pho1->at(i)<305)){n_es_l1_hits = n_es_l1_hits + 1;}
  if(abs(Hit_ES_Z_Pho1->at(i))>=308 && abs(Hit_ES_Z_Pho1->at(i))<310){n_es_l2_hits = n_es_l2_hits + 1;}
}
}
if(Hit_ES_X_Pho2->size()>0){ 
  for(int i =0; i<Hit_ES_X_Pho2->size(); i++){
  if(abs(Hit_ES_Z_Pho2->at(i))>303 && abs(Hit_ES_Z_Pho2->at(i)<305)){ n_es_l1_hits = n_es_l1_hits + 1;}
  if(abs(Hit_ES_Z_Pho2->at(i))>=308 && abs(Hit_ES_Z_Pho2->at(i))<310){ n_es_l2_hits = n_es_l2_hits + 1;}
}
}
ES_L1_hits->Fill(n_es_l1_hits);
ES_L2_hits->Fill(n_es_l2_hits);
 }
 
}
