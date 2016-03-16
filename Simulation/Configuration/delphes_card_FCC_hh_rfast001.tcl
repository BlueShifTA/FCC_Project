# FCC proposed detector. Aug. 2015 
# taus reconstruction is removed to deal with input slimmed records
# based on version v2 
# Heather Gray and Filip Moortgat
#######################################
# Order of execution of various modules
#######################################

set ExecutionPath {
ParticlePropagator
StatusPid

ChargedHadronTrackingEfficiency

ElectronEfficiency
MuonEfficiency

ChargedHadronMomentumSmearing
ElectronEnergySmearing
MuonMomentumSmearing

TrackMerger
ImpactParameterSmearing
  
Ecal
Hcal
  
TowerMerger
EFlowMerger

PhotonEfficiency
MuonIsolation
ElectronIsolation
PhotonIsolation

MissingET

GenJetFinder
FastJetFinder

JetEnergyScale
  
BTagging
CTagging

UniqueObjectFinder

ScalarHT

TreeWriter
}

#################################
# Propagate particles in cylinder
#################################

module ParticlePropagator ParticlePropagator {
set InputArray Delphes/stableParticles

set OutputArray stableParticles
set ChargedHadronOutputArray chargedHadrons
set ElectronOutputArray electrons
set MuonOutputArray muons

# radius of the magnetic field coverage, in m
set Radius 6.00
# half-length of the magnetic field coverage, in m
set HalfLength 11.5

# magnetic field
set Bz 6.0
}

####################################
# Charged hadron tracking efficiency
####################################

module Efficiency ChargedHadronTrackingEfficiency {
set InputArray ParticlePropagator/chargedHadrons
set OutputArray chargedHadrons

# add EfficiencyFormula {efficiency formula as a function of eta and pt}

# tracking efficiency formula for charged hadrons
set EfficiencyFormula { (pt <= 0.5) * (0.00) + \
(abs(eta) <= 1.5) * (pt > 0.5 && pt <= 1) * (0.90) + \
(abs(eta) <= 1.5) * (pt > 1) * (0.95) + \
(abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 0.5 && pt <= 1) * (0.85) + \
(abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 1) * (0.90) + \
(abs(eta) > 4 && abs(eta) <= 6) * (pt > 0.5 && pt <= 1) * (0.80) + \
(abs(eta) > 4 && abs(eta) <= 6) * (pt > 1.0) * (0.85) + \
(abs(eta) > 6.0) * (0.00)}
}

##############################
# Electron tracking efficiency
##############################

module Efficiency ElectronEfficiency {
set InputArray ParticlePropagator/electrons
set OutputArray electrons

# set EfficiencyFormula {efficiency formula as a function of eta and pt}

# tracking efficiency formula for electrons
# tracking efficiency formula for electrons
set EfficiencyFormula { (pt <= 10) * (0.00) + \
(abs(eta) <= 1.5) * (pt > 10 && pt <= 50) * (0.80) + \
(abs(eta) <= 1.5) * (pt > 50) * (0.90) + \
(abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 10 && pt <= 50) * (0.80) + \
(abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 50) * (0.90) + \
(abs(eta) > 4 && abs(eta) <= 6) * (pt > 10 && pt <= 50) * (0.70) + \
(abs(eta) > 4 && abs(eta) <= 6) * (pt > 50) * (0.80) + \
(abs(eta) > 6) * (0.00)}
}

##########################
# Muon tracking efficiency
##########################

module Efficiency MuonEfficiency {
set InputArray ParticlePropagator/muons
set OutputArray muons

# set EfficiencyFormula {efficiency formula as a function of eta and pt}

# tracking efficiency formula for muons
set EfficiencyFormula { (pt <= 5) * (0.00) + \
(abs(eta) <= 6) * (pt > 5 ) * (0.99) + \
(abs(eta) > 6) * (0.00)}
}

########################################
# Momentum resolution for charged tracks
########################################

module MomentumSmearing ChargedHadronMomentumSmearing {
set InputArray ChargedHadronTrackingEfficiency/chargedHadrons
set OutputArray chargedHadrons

# set ResolutionFormula {resolution formula as a function of eta and pt}

# resolution formula for charged hadrons
set ResolutionFormula {     (abs(eta) <= 1.5) * (pt > 0.5 && pt <= 1.0) * (0.02) + \
                                                    (abs(eta) <= 1.5) * (pt > 1.0 && pt <= 1.0e1) * (0.01) + \
                                                    (abs(eta) <= 1.5) * (pt > 1.0e1 && pt <= 2.0e2) * (0.03) + \
                                                    (abs(eta) <= 1.5) * (pt > 2.0e2) * (0.05) + \
                                                    (abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 0.5 && pt <= 1.0) * (0.03) + \
                                                    (abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 1.0 && pt <= 1.0e1) * (0.02) + \
                                                    (abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 1.0e1 && pt <= 2.0e2) * (0.04) + \
                                                    (abs(eta) > 1.5 && abs(eta) <= 4) * (pt > 2.0e2) * (0.05) + \
                                                    (abs(eta) > 4 && abs(eta) <= 6) * (pt > 0.5 && pt <= 1.0) * (0.06) + \
                                                    (abs(eta) > 4 && abs(eta) <= 6) * (pt > 1.0 && pt <= 1.0e1) * (0.04) + \
                                                    (abs(eta) > 4 && abs(eta) <= 6) * (pt > 1.0e1 && pt <= 2.0e2) * (0.08) + \
                                                    (abs(eta) > 4 && abs(eta) <= 6) * (pt > 2.0e2) * (0.08) + \
                                                    (abs(eta) > 6) * (0.00)}
}
#################################
# Energy resolution for electrons
#################################

module EnergySmearing ElectronEnergySmearing {
set InputArray ElectronEfficiency/electrons
set OutputArray electrons

# set ResolutionFormula {resolution formula as a function of eta and energy}

# resolution formula for electrons
set ResolutionFormula { (abs(eta) <= 4.0) * (energy > 0.1 && energy <= 2.0e1) * (energy*0.007) + \
(abs(eta) <= 4.0) * (energy > 2.0e1) * sqrt(energy^2*0.005^2 + energy*0.02^2) + \
(abs(eta) > 4.0 && abs(eta) <= 6.0) * sqrt(energy^2*0.05^2 + energy*1.00^2)}
}

###############################
# Momentum resolution for muons
###############################

module MomentumSmearing MuonMomentumSmearing {
set InputArray MuonEfficiency/muons
set OutputArray muons

# set ResolutionFormula {resolution formula as a function of eta and pt}

# resolution formula for muons
set ResolutionFormula { (abs(eta) <= 0.5) * (pt > 0.1 && pt <= 5.0) * (0.02) + \
(abs(eta) <= 0.5) * (pt > 5.0 && pt <= 1.0e2) * (0.015) + \
(abs(eta) <= 0.5) * (pt > 1.0e2 && pt <= 2.0e2) * (0.03) + \
(abs(eta) <= 0.5) * (pt > 2.0e2) * (0.05 + pt*1.e-4) + \
(abs(eta) > 0.5 && abs(eta) <= 1.5) * (pt > 0.1 && pt <= 5.0) * (0.03) + \
(abs(eta) > 0.5 && abs(eta) <= 1.5) * (pt > 5.0 && pt <= 1.0e2) * (0.02) + \
(abs(eta) > 0.5 && abs(eta) <= 1.5) * (pt > 1.0e2 && pt <= 2.0e2) * (0.04) + \
(abs(eta) > 0.5 && abs(eta) <= 1.5) * (pt > 2.0e2) * (0.05 + pt*1.e-4) + \
(abs(eta) > 1.5 && abs(eta) <= 6.0) * (pt > 0.1 && pt <= 5.0) * (0.04) + \
(abs(eta) > 1.5 && abs(eta) <= 6.0) * (pt > 5.0 && pt <= 1.0e2) * (0.035) + \
(abs(eta) > 1.5 && abs(eta) <= 6.0) * (pt > 1.0e2 && pt <= 2.0e2) * (0.05) + \
(abs(eta) > 1.5 && abs(eta) <= 6.0) * (pt > 2.0e2) * (0.05 + pt*1.e-4)}
}

####################
# Electron isolation
####################

module Isolation ElectronIsolation {
set CandidateInputArray ElectronEfficiency/electrons
set IsolationInputArray EFlowMerger/eflow

set OutputArray electrons

set DeltaRMax 0.3

set PTMin 50

set PTRatioMax 0.1
}

################
# Muon isolation
################

module Isolation MuonIsolation {
set CandidateInputArray MuonEfficiency/muons
set IsolationInputArray EFlowMerger/eflow

set OutputArray muons

set DeltaRMax 0.3

set PTMin 50

set PTRatioMax 0.1
}

###################
# Photon efficiency
###################

module Efficiency PhotonEfficiency {
set InputArray Ecal/eflowPhotons
set OutputArray photons

# set EfficiencyFormula {efficiency formula as a function of eta and pt}
# efficiency formula for photons
set EfficiencyFormula {                                      (pt <= 10.0) * (0.00) + \
(abs(eta) <= 1.5) * (pt > 10.0)  * (0.9635) + \
(abs(eta) > 1.5 && abs(eta) <= 2.5) * (pt > 10.0)  * (0.9624) + \
(abs(eta) > 2.5)                                   * (0.00)}
}

##################
# Photon isolation
##################

module Isolation PhotonIsolation {
set CandidateInputArray Ecal/eflowPhotons
set IsolationInputArray EFlowMerger/eflow

set OutputArray photons

set DeltaRMax 0.3

set PTMin 50.0

set PTRatioMax 0.1
}

##############
# Track merger
##############

module Merger TrackMerger {
# add InputArray InputArray
add InputArray ChargedHadronMomentumSmearing/chargedHadrons
add InputArray ElectronEnergySmearing/electrons
add InputArray MuonMomentumSmearing/muons
set OutputArray tracks
}

################################
# Track impact parameter smearing
################################

module ImpactParameterSmearing ImpactParameterSmearing {
set InputArray TrackMerger/tracks
set OutputArray tracks


# absolute impact parameter smearing formula (in mm) as a function of pt and eta
set ResolutionFormula {(pt > 0.1  && pt <= 5.0)   * (0.010) + \
(pt > 5.0)                 * (0.005)}

}

#############
#   ECAL
#############

module SimpleCalorimeter Ecal {
  set ParticleInputArray ParticlePropagator/stableParticles
  set TrackInputArray ImpactParameterSmearing/tracks

  set TowerOutputArray ecalTowers
  set EFlowTowerOutputArray eflowPhotons
  
  set pi [expr {acos(-1)}]

  # lists of the edges of each tower in eta and phi
  # each list starts with the lower edge of the first tower
  # the list ends with the higher edged of the last tower
  # ECAL is x4 better than HCAL
  # 0.02453125 rad (1.40625 deg) in Phi (256 modules)
  # Eta: 0.025   
  set PhiBins {}
  for {set i -128} {$i <= 128} {incr i} {
    add PhiBins [expr {$i * $pi/128.0}]
  }
  foreach eta {-1.6 -1.575 -1.55 -1.525 -1.5 -1.475 -1.45 -1.425 -1.4 -1.375 -1.35 -1.325 -1.3 -1.275 -1.25 -1.225 -1.2 -1.175 -1.15 -1.125 -1.1 -1.075 -1.05 -1.025 -1.0 -0.975 -0.95 -0.925 -0.9 -0.875 -0.85 -0.825 -0.8 -0.775 -0.75 -0.725 -0.7 -0.675 -0.65 -0.625 -0.6 -0.575 -0.55 -0.525 -0.5 -0.475 -0.45 -0.425 -0.4 -0.375 -0.35 -0.325 -0.3 -0.275 -0.25 -0.225 -0.2 -0.175 -0.15 -0.125 -0.1 -0.075 -0.05 -0.025 0.0 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2 0.225 0.25 0.275 0.3 0.325 0.35 0.375 0.4 0.425 0.45 0.475 0.5 0.525 0.55 0.575 0.6 0.625 0.65 0.675 0.7 0.725 0.75 0.775 0.8 0.825 0.85 0.875 0.9 0.925 0.95 0.975 1.0 1.025 1.05 1.075 1.1 1.125 1.15 1.175 1.2 1.225 1.25 1.275 1.3 1.325 1.35 1.375 1.4 1.425 1.45 1.475 1.5 1.525 1.55 1.575 1.6} {
    add EtaPhiBins $eta $PhiBins
  }

  # 0.05 eta  x 0.05 deg phi 
  set PhiBins {}
  for {set i -64} {$i <= 64} {incr i} {
    add PhiBins [expr {$i * $pi/64.0}]
  }
  foreach eta {-4.5 -4.45 -4.4 -4.35 -4.3 -4.25 -4.2 -4.15 -4.1 -4.05 -4.0 -3.95 -3.9 -3.85 -3.8 -3.75 -3.7 -3.65 -3.6 -3.55 -3.5 -3.45 -3.4 -3.35 -3.3 -3.25 -3.2 -3.15 -3.1 -3.05 -3.0 -2.95 -2.9 -2.85 -2.8 -2.75 -2.7 -2.65 -2.6 -2.55 -2.5 -2.45 -2.4 -2.35 -2.3 -2.25 -2.2 -2.15 -2.1 -2.05 -2.0 -1.95 -1.9 -1.85 -1.8 -1.75 -1.7  1.7 1.75 1.8 1.85 1.9 1.95 2.0 2.05 2.1 2.15 2.2 2.25 2.3 2.35 2.4 2.45 2.5 2.55 2.6 2.65 2.7 2.75 2.8 2.85 2.9 2.95 3.0 3.05 3.1 3.15 3.2 3.25 3.3 3.35 3.4 3.45 3.5 3.55 3.6 3.65 3.7 3.75 3.8 3.85 3.9 3.95 4.0 4.05 4.1 4.15 4.2 4.25 4.3 4.35 4.4 4.45 4.5} {
    add EtaPhiBins $eta $PhiBins
  }

  # 0.2 degrees towers, 20 degree 
  set PhiBins {}
  for {set i -9} {$i <= 9} {incr i} {
    add PhiBins [expr {$i * $pi/9.0}]
  }
  foreach eta {-6.0 -5.8 -5.6 -5.4 -5.2 -5.0 -4.8 -4.6  4.6 4.8 5.0 5.2 5.4 5.6 5.8 6.0} {
    add EtaPhiBins $eta $PhiBins
  }
  # default energy fractions {abs(PDG code)} {fraction of energy deposited in ECAL}
  
  add EnergyFraction {0} {0.4}
  # energy fractions for e, gamma and pi0
  add EnergyFraction {11} {1.0}
  add EnergyFraction {22} {1.0}
  add EnergyFraction {111} {1.0}
  # energy fractions for muon, neutrinos and neutralinos
  # Addition 4/2/2016 graviton (39 & 5000039)
  add EnergyFraction {12} {0.0}
  add EnergyFraction {13} {0.0}
  add EnergyFraction {14} {0.0}
  add EnergyFraction {16} {0.0}
  add EnergyFraction {39} {0.0}
  add EnergyFraction {97} {0.0}
  add EnergyFraction {98} {0.0}
  add EnergyFraction {5000039} {0.0}
  add EnergyFraction {1000022} {0.0}
  add EnergyFraction {1000023} {0.0}
  add EnergyFraction {1000025} {0.0}
  add EnergyFraction {1000035} {0.0}
  add EnergyFraction {1000045} {0.0}
  # energy fractions for K0short and Lambda
  # add EnergyFraction {310} {0.3}
  # add EnergyFraction {3122} {0.3}

  # set ECalResolutionFormula {resolution formula as a function of eta and energy}
  set ResolutionFormula {                     (abs(eta) <= 4.0) * sqrt(energy^2*0.01^2 + energy*0.10^2) + \
                            (abs(eta) > 4.0 && abs(eta) <= 6.0) * sqrt(energy^2*0.05^2  + energy*1.00^2)}

 
}


#############
#   HCAL
#############

module SimpleCalorimeter Hcal {
  set ParticleInputArray ParticlePropagator/stableParticles
  set TrackInputArray ImpactParameterSmearing/tracks

  set TowerOutputArray hcalTowers
  set EFlowTowerOutputArray eflowNeutralHadrons
  
  set pi [expr {acos(-1)}]

  # lists of the edges of each tower in eta and phi
  # each list starts with the lower edge of the first tower
  # the list ends with the higher edged of the last tower

 # 128 modules in phi like in ATLAS 
 # 1.40625 degree in Phi
  set PhiBins {}
  for {set i -128} {$i <= 128} {incr i} {
    add PhiBins [expr {$i * $pi/128.0}]
  }
  # Use the  0.025 bin in Eta (better than ATLAS 0.1)  
  foreach eta {-1.6 -1.575 -1.55 -1.525 -1.5 -1.475 -1.45 -1.425 -1.4 -1.375 -1.35 -1.325 -1.3 -1.275 -1.25 -1.225 -1.2 -1.175 -1.15 -1.125 -1.1 -1.075 -1.05 -1.025 -1.0 -0.975 -0.95 -0.925 -0.9 -0.875 -0.85 -0.825 -0.8 -0.775 -0.75 -0.725 -0.7 -0.675 -0.65 -0.625 -0.6 -0.575 -0.55 -0.525 -0.5 -0.475 -0.45 -0.425 -0.4 -0.375 -0.35 -0.325 -0.3 -0.275 -0.25 -0.225 -0.2 -0.175 -0.15 -0.125 -0.1 -0.075 -0.05 -0.025 0.0 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2 0.225 0.25 0.275 0.3 0.325 0.35 0.375 0.4 0.425 0.45 0.475 0.5 0.525 0.55 0.575 0.6 0.625 0.65 0.675 0.7 0.725 0.75 0.775 0.8 0.825 0.85 0.875 0.9 0.925 0.95 0.975 1.0 1.025 1.05 1.075 1.1 1.125 1.15 1.175 1.2 1.225 1.25 1.275 1.3 1.325 1.35 1.375 1.4 1.425 1.45 1.475 1.5 1.525 1.55 1.575 1.6 } {
    add EtaPhiBins $eta $PhiBins
  }

  # 5.625 degrees x 0.1 in eta towers
  set PhiBins {}
  for {set i -32} {$i <= 32} {incr i} {
    add PhiBins [expr {$i * $pi/32.0}]
  }
  foreach eta {-4.5 -4.45 -4.4 -4.35 -4.3 -4.25 -4.2 -4.15 -4.1 -4.05 -4.0 -3.95 -3.9 -3.85 -3.8 -3.75 -3.7 -3.65 -3.6 -3.55 -3.5 -3.45 -3.4 -3.35 -3.3 -3.25 -3.2 -3.15 -3.1 -3.05 -3.0 -2.95 -2.9 -2.85 -2.8 -2.75 -2.7 -2.65 -2.6 -2.55 -2.5 -2.45 -2.4 -2.35 -2.3 -2.25 -2.2 -2.15 -2.1 -2.05 -2.0 -1.95 -1.9 -1.85 -1.8 -1.75 -1.7  1.7 1.75 1.8 1.85 1.9 1.95 2.0 2.05 2.1 2.15 2.2 2.25 2.3 2.35 2.4 2.45 2.5 2.55 2.6 2.65 2.7 2.75 2.8 2.85 2.9 2.95 3.0 3.05 3.1 3.15 3.2 3.25 3.3 3.35 3.4 3.45 3.5 3.55 3.6 3.65 3.7 3.75 3.8 3.85 3.9 3.95 4.0 4.05 4.1 4.15 4.2 4.25 4.3 4.35 4.4 4.45 4.5} {
    add EtaPhiBins $eta $PhiBins
  }

  # 20 degrees towers
  set PhiBins {}
  for {set i -9} {$i <= 9} {incr i} {
    add PhiBins [expr {$i * $pi/9.0}]
  }
  foreach eta {6 -5.6 -5.3 -5 -4.7 -4.525 4.7 5 5.3 5.6 6} {
    add EtaPhiBins $eta $PhiBins
  }
  
  # default energy fractions {abs(PDG code)} {Fecal Fhcal}
  add EnergyFraction {0} {0.6}
  # energy fractions for e, gamma and pi0
  add EnergyFraction {11} {0.0}
  add EnergyFraction {22} {0.0}
  add EnergyFraction {111} {0.0}
  # energy fractions for muon, neutrinos and neutralinos
  add EnergyFraction {12} {0.0}
  add EnergyFraction {13} {0.0}
  add EnergyFraction {14} {0.0}
  add EnergyFraction {16} {0.0}
  add EnergyFraction {1000022} {0.0}
  add EnergyFraction {1000023} {0.0}
  add EnergyFraction {1000025} {0.0}
  add EnergyFraction {1000035} {0.0}
  add EnergyFraction {1000045} {0.0}
  # energy fractions for K0short and Lambda
  # add EnergyFraction {310} {0.7}
  # add EnergyFraction {3122} {0.7}

   # set HCalResolutionFormula {resolution formula as a function of eta and energy}
  set ResolutionFormula {                     (abs(eta) <= 4.0) * sqrt(energy^2*0.03^2 + energy*0.50^2) + \
                            (abs(eta) > 4.0 && abs(eta) <= 6.0) * sqrt(energy^2*0.05^2 + energy*1.00^2)}
}




####################
# Tower Merger (in case not using e-flow algorithm)
####################

module Merger TowerMerger {
# add InputArray InputArray
add InputArray Ecal/ecalTowers
add InputArray Hcal/hcalTowers
set OutputArray towers
}

####################
# Energy flow merger
####################

module Merger EFlowMerger {
# add InputArray InputArray
add InputArray ImpactParameterSmearing/tracks
add InputArray Ecal/eflowPhotons
add InputArray Hcal/eflowNeutralHadrons
set OutputArray eflow
}


###################
# Missing ET merger
###################

module Merger MissingET {
# add InputArray InputArray
add InputArray EFlowMerger/eflow
set MomentumOutputArray momentum
}
                    

##################
# Scalar HT merger
##################

module Merger ScalarHT {
# add InputArray InputArray
add InputArray EFlowMerger/eflow
set EnergyOutputArray energy
}

#####################
# MC truth jet finder
#####################

module FastJetFinder GenJetFinder {
set InputArray Delphes/stableParticles

set OutputArray jets

# To compute N-subjettiness variables (see JHEP 1103:015 (2011) and JHEP 1202:093 (2012)), use option 7
# algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
set JetAlgorithm 7
set ParameterR 0.5
set ComputeNsubjettiness 1
set Beta 2.0
set AxisMode 1

set JetPTMin 50.0
}

############
# Jet finder
############

module FastJetFinder FastJetFinder {
#  set InputArray Calorimeter/towers
set InputArray EFlowMerger/eflow

set OutputArray jets

# To compute N-subjettiness variables (see JHEP 1103:015 (2011) and JHEP 1202:093 (2012)), use option 7
# algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
set JetAlgorithm 7
set ParameterR 0.5
set ComputeNsubjettiness 1
set Beta 2.0
set AxisMode 1


set JetPTMin 50.0
}

##################
# Jet Energy Scale
##################

module EnergyScale JetEnergyScale {
set InputArray FastJetFinder/jets
set OutputArray jets

# scale formula for jets
set ScaleFormula {1.00}
}

##########################
# tau-tagging
##########################


#module TauTagging TauTagging {
#set ParticleInputArray Delphes/allParticles
#set PartonInputArray Delphes/partons
#set JetInputArray JetEnergyScale/jets
#set DeltaR 0.4
#set TauPTMin 50.0
#set TauEtaMax 6
## add EfficiencyFormula {abs(PDG code)} {efficiency formula as a function of eta and pt}
#add EfficiencyFormula {0} {0.01} 
#add EfficiencyFormula {11} {0.005} 
#add EfficiencyFormula {15} {0.6} 
#}
#

##########################
# b-tagging
##########################

module BTagging BTagging { # need to check that this module exists or write it
set ParticleInputArray Delphes/allParticles
set PartonInputArray Delphes/partons
set JetInputArray JetEnergyScale/jets

set DeltaR 0.4
set BPTMin 50.0
set BEtaMax 6.0 

# add EfficiencyFormula {abs(PDG code)} {efficiency formula as a function of eta and pt}

# default efficiency formula (misidentification rate)
add EfficiencyFormula {0} {0.001} 
add EfficiencyFormula {4} {0.04} 
add EfficiencyFormula {5} {0.75}
}

##########################
# c-tagging
##########################


module BTagging CTagging {
set ParticleInputArray Delphes/allParticles
set PartonInputArray Delphes/partons
set JetInputArray JetEnergyScale/jets

set DeltaR 0.4
set BPTMin 30.0 
set BEtaMax 6.0

# add EfficiencyFormula {abs(PDG code)} {efficiency formula as a function of eta and pt}
add EfficiencyFormula {0} {0.01} 
add EfficiencyFormula {5} {0.10} 
add EfficiencyFormula {4} {0.25} 
}

####################################
# StatusPidFilter
# This module removes all generated particles
# except electrons, muons, taus, and status==3
####################################

module StatusPidFilter StatusPid {
#    set InputArray Delphes/stableParticles
    set InputArray Delphes/allParticles
    set OutputArray filteredParticles

    set PTMin 0.5
}


#####################################################
# Find uniquely identified photons/electrons/tau/jets
#####################################################

module UniqueObjectFinder UniqueObjectFinder {
# earlier arrays take precedence over later ones
# add InputArray InputArray OutputArray
add InputArray PhotonIsolation/photons photons
add InputArray ElectronIsolation/electrons electrons
add InputArray MuonIsolation/muons muons
add InputArray FastJetFinder/jets jets
}

##################
# ROOT tree writer
##################

module TreeWriter TreeWriter {
# add Branch InputArray BranchName BranchClass
# add Branch Delphes/allParticles Particle GenParticle
add Branch StatusPid/filteredParticles Particle GenParticle
add Branch GenJetFinder/jets GenJet Jet
  
# add Branch ChargedHadronMomentumSmearing/chargedHadrons ChargedHadron Track
# add Branch Hcal/eflowNeutralHadrons NeutralHadron Tower

add Branch Ecal/eflowPhotons Photon Photon
add Branch ElectronEnergySmearing/electrons Electron Electron
add Branch MuonMomentumSmearing/muons Muon Muon
add Branch JetEnergyScale/jets Jet Jet
add Branch MissingET/momentum MissingET MissingET
add Branch ScalarHT/energy ScalarHT ScalarHT
}


