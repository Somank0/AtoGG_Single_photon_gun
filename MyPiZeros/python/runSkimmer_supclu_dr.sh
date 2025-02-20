#!/usr/bin/bash
if [ -z $1 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 1;
fi
if [ -z $2 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 2;
fi
if [ -z $3 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 3;
fi
cmsenv;
#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/Tranche3;
folder=/eos/user/s/sosaha/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun;
#folder=fixedSample
#for ((i=$1 ; i<=$2 ; i+=$3));
#files=(8395948 8395949 8395950 8395951 8469823 8469824 8469827 8469826 8469825 8489062 8489053 8492293 8492294 8492295 8524230 8524231 8524232 8524224 8524229 8524226 8524227 8524223 8540541 8540540 8540538 8540532 8540533 8540536 8540529 8540539 8540528 8540531 8540535 8540537 8542512 8542517 8542514 8542519 8542515 8542511 8542518 8542513 8542516 8563751 8563760 8563753 8563757 8563763 8563755 8563765 8563762 8563764 8563761 8563758 8563759 8563756 8563752 8571059 8571061 8571064 8571057 8571058 8571060 8572988 8572989 8572992 8572991 8572984 8572983 8572985 8574765 8574760 8574761 8574759 8574758 8574762 8574769 )

#files=( 8875721 8875723 8875720 8875719 8883504 8883505 8883499 8883507 8883498 8883500 8883503 8904657 8904656 8933591 8933590 8933588 8933587 )
#files=( 9007197 9007198 9007196 9007189 9007191 9007193 9007190 9007195 9007194 9007192 )
#files=( 9120502 )
files=( 3550049 )
#files=( 8875719 )

for i in ${files[@]};
do
echo "Running Skimmer on $folder/${i}_AToGG_RECO_M1000.0.root"
cmsRun Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}_AToGG_RECO_M1000.0.root
echo Done
done
