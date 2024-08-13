How to run:
cmsrel CMSSW_10_6_29
cd CMSSW_10_6_29/src
git clone https://github.com/Somank0/AtoGG_Single_photon_gun
cd MySampleProduction
cmsenv
scram b
cd MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO

#To generate single photon samples in the ECAL endcaps (for domain continuation of the mass regressor):

cd MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun/HomeDirScripts

#Change the afs and eos paths in the runSampleGen_SP_EE_plus.sh (or runSampleGen_SP_EE_minus.sh).
./runSampleGen_SP_EE_plus(minus).sh [Massmin] [Massmax] [Stepsize] [UniqueID]

#To make the ntuples from the reco file :

cd MySampleProduction/MyPiZeros/python

#Edit the 'folder'="path to the RECO file" and 'files'=(UniqueID)
./runSkimmer_unclustered.sh 1 1 1

#The skimmer calls the file 'PhotonRefinedRechitNtuplelizer.cc' that has been modified for the single photon samples for domain continuation of the mass regressor.

#The skimmer will assign a random mass to the photons. The range of masses can be modified in the 'PhotonRefinedRechitNtuplelizer.cc' file as per required.

#Analyze the ntuplelized/skimmed file using the analyzer.

cd /MySampleProduction/MyPiZeros/python/Skimmed/Analyzer

