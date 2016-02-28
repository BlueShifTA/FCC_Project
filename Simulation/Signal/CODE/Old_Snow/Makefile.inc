# PYTHIA configuration file.
# Generated on Wed Aug 12 15:02:38 CEST 2015 with the user supplied options:
# --enable-shared
# --enable-debug
# --with-root=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.32/x86_64-slc6-gcc48-opt/root/
# --with-hepmc2=/afs/cern.ch/sw/lcg/releases/HepMC/2.06.09-0a23a/x86_64-slc6-gcc48-opt/

# Install directory prefixes.
PREFIX_BIN=/afs/cern.ch/work/s/sekin/private/Project/SnowMass_33TeV/Signal/Software/Pythia/pythia8210/bin
PREFIX_INCLUDE=/afs/cern.ch/work/s/sekin/private/Project/SnowMass_33TeV/Signal/Software/Pythia/pythia8210/include
PREFIX_LIB=/afs/cern.ch/work/s/sekin/private/Project/SnowMass_33TeV/Signal/Software/Pythia/pythia8210/lib
PREFIX_SHARE=/afs/cern.ch/work/s/sekin/private/Project/SnowMass_33TeV/Signal/Software/Pythia/pythia8210/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=true
CXX=g++
CXX_COMMON=-g -ansi -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname
LIB_SUFFIX=.so

# EVTGEN configuration.
EVTGEN_USE=false
EVTGEN_BIN=
EVTGEN_INCLUDE=
EVTGEN_LIB=

# FASTJET3 configuration.
FASTJET3_USE=false
FASTJET3_BIN=
FASTJET3_INCLUDE=
FASTJET3_LIB=

# HEPMC2 configuration.
HEPMC2_USE=true
HEPMC2_BIN=/afs/cern.ch/sw/lcg/releases/HepMC/2.06.09-0a23a/x86_64-slc6-gcc48-opt//bin/
HEPMC2_INCLUDE=/afs/cern.ch/sw/lcg/releases/HepMC/2.06.09-0a23a/x86_64-slc6-gcc48-opt//include
HEPMC2_LIB=/afs/cern.ch/sw/lcg/releases/HepMC/2.06.09-0a23a/x86_64-slc6-gcc48-opt//lib

# HEPMC3 configuration.
HEPMC3_USE=false
HEPMC3_BIN=
HEPMC3_INCLUDE=
HEPMC3_LIB=

# LHAPDF5 configuration.
LHAPDF5_USE=false
LHAPDF5_BIN=
LHAPDF5_INCLUDE=
LHAPDF5_LIB=
LHAPDF5_PLUGIN=LHAPDF5.h

# LHAPDF6 configuration.
LHAPDF6_USE=false
LHAPDF6_BIN=
LHAPDF6_INCLUDE=
LHAPDF6_LIB=
LHAPDF6_PLUGIN=LHAPDF5.h

# POWHEG configuration.
POWHEG_USE=false
POWHEG_BIN=
POWHEG_INCLUDE=
POWHEG_LIB=

# PROMC configuration.
PROMC_USE=false
PROMC_BIN=
PROMC_INCLUDE=
PROMC_LIB=

# ROOT configuration.
ROOT_USE=true
ROOT_BIN=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.32/x86_64-slc6-gcc48-opt/root//bin/
ROOT_INCLUDE=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.32/x86_64-slc6-gcc48-opt/root//include
ROOT_LIB=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.32/x86_64-slc6-gcc48-opt/root//lib

# GZIP configuration.
GZIP_USE=false
GZIP_BIN=
GZIP_INCLUDE=
GZIP_LIB=

# BOOST configuration.
BOOST_USE=false
BOOST_BIN=
BOOST_INCLUDE=
BOOST_LIB=
