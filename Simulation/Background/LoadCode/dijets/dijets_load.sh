# Arrange file 
#more WZ_Jet_rfast001 | awk '{print "wget http://faxbox.usatlas.org/group/hepsim/events/pp/100tev/wzjet_pythia8_ptbins/rfast001/"$2 RS "mv *root /home/orion/Project/ParticlePhysics/FCC/Simulation/Data/FCC_Project/Background/wzjet/"}' > wzjet_load.sh
