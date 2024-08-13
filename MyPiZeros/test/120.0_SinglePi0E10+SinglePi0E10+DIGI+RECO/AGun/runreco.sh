#!/usr/bin/bash
cd /eos/user/s/sosaha/CMSSW_single_photon/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun/;
export HOME=/afs/cern.ch/user/s/sosaha
if [ -z $1 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID]" && exit 1;
fi
if [ -z $2 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID]" && exit 2;
fi
if [ -z $3 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID]" && exit 3;
fi
if [ -z $4 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID]" && exit 3;
fi
cmsenv;
for ((i=$1 ; i<=$2 ; i+=$3));
do
	
	echo "==============================Starting Sample generation for mass $i. GEN-SIM step=============================="
	echo "------------------------------Using CMSSW_10_6_29------------------------------"
#	cmsRun AToGG_GEN_SIM_MeV_mass_fixed.py mass=$i ptMin=20 ptMax=100 etaMin=1.44 etaMax=2.5 maxEvents=2000 clusterID=$4;
	echo "==============================GEN-SIM step complete! Starting DIGI-PREMIX-RAW step=============================="
#	cmsRun genSimDigiRaw_mcProd_SS.py mass=$i clusterID=$4;
	echo "==============================DIGI-PREMIX-RAW step complete! Starting HLT step=============================="
#	cd CMSSW_10_2_16_UL/src;
	cmsenv;
	echo "------------------------------Using CMSSW_10_2_16_UL------------------------------"
#	cmsRun hlt_SS.py mass=$i clusterID=$4;
	echo "==============================HLT step complete! Starting RECO-AOD step=============================="
#	cd ../../;
	cmsenv;
	echo "------------------------------Using CMSSW_10_6_29------------------------------"
	cmsRun recoStepUL2018_SS.py mass=$i clusterID=$4;
	echo "==============================RECO-AOD step complete! Sample generation complete !=============================="
done
