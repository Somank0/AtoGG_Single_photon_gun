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

# Range for analytic continuation : -0.3 GeV to 0 GeV


folder=/eos/home-s/sosaha/CMSSW_single_photon/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun
#112K sample
#files=(00012 3657458  3657463 3657462 3657460 3657461)
#files=(3657459)
#files=(3658340 3658265 3658264 3658266 3658339 3659970 3659972 3659974 3660530 3658263 3660526 3659967 3668449 3668445 3668446 3668448 3660973 3668451 3668447 3668450 3668453)
#files=(3668918 3668917 3660972 3660971 3669818 3669820 3670733 3670731 3669801 3669799 3669791 3669803 3669797 3673558 3673577)
#files=(3673549 3673570 3677903 3677902 3678132)
#files=(3693126)
########################################################################################
#160K sample
#files=( 3695346  3695344 3695470 3695347  3695469  3695466 3695343 3695463  3695471  3695467 3695468 3785285  3785286 3785283 3785284 3813420 3813419 3813417)
#############################################################################################
#330K sample
#files=(3813418)
#files=(4151579)
#files=(4151582 4153010 4151580 4151581 4152981 )
#files=(11111)
#files=(11112 11114 11113 11116 11115 4188603 4188604 4185621 4185688 4185627 4185717 11117 11118 11119 11120)

######################################################################
#450K sample
#files=(4210199 4204982 4204977 4262514 4262516 4264828 4210202 4281242 4280077 4280076 4222283 4222284)
#files=(4264829 4281243 4301209 )
#files=(4303849 4303844 4301208)
##########################################################################################
#files=(1000)
#files=(123)
files=(4555949 4561816)
#########################################################################
for i in ${files[@]};
do
echo "Running Skimmer on $folder/${i}_AToGG_RECO_M1000.0.root"
cmsRun SP_Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}_AToGG_RECO_M1000.0.root fileID=${i}
echo "Skimming done"
done
