// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Author: Mikhail Kirsanov, Mikhail.Kirsanov@cern.ch, based on main01.cc.
// This program illustrates how HepMC can be interfaced to Pythia8.
// It studies the charged multiplicity distribution at the LHC.
// HepMC events are output to the hepmcout41.dat file.

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

int main() {

  // Interface for conversion from Pythia8::Event to HepMC event.
  HepMC::Pythia8ToHepMC ToHepMC;

  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io("ADD_pythia.hep", std::ios::out);
  // # Event
  int maxEvent = IN3;

  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;

  Event& pyEvent = pythia.event;
  int nlist = 3;

  pythia.readString("Beams:eCM=33000.");
  pythia.readString("ExtraDimensionsLED:n = IN1");
  pythia.readString("ExtraDimensionsLED:MD = IN2.");
  pythia.readString("5000039:m0 = 1200.");
  pythia.readString("5000039:mWidth = 1000.");
  pythia.readString("5000039:mMin = 1.");
  pythia.readString("5000039:mMax = 13990.");
  pythia.readString("Tune:pp = 5");
  pythia.readString("PDF:pSet = 8"); // CTEQ6L1
  pythia.readString("ExtraDimensionsLED:monojet = on");
  pythia.readString("ExtraDimensionsLED:CutOffmode = 1");
  pythia.readString("ExtraDimensionsLED:t = 0.5");
  pythia.readString("PhaseSpace:pTHatMin = 80.");
  pythia.readString("PartonLevel:MPI = on");
  pythia.readString("PartonLevel:ISR = on");
  pythia.readString("PartonLevel:FSR = on");
  pythia.readString("ParticleDecays:limitTau0 = on");
  pythia.readString("ParticleDecays:tauMax = 10");
  //pythia.readString("Init:showAllSettings = on ");
  //pythia.particleData.listAll();

  pythia.init();

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < maxEvent; ++iEvent) {
    if (!pythia.next()) continue;

    if (iEvent < nlist){
      pyEvent.list();
      pyEvent.listJunctions();
    }


    // Construct new empty HepMC event and fill it.
    // Units will be as chosen for HepMC build; but can be changed
    // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    ToHepMC.fill_next_event( pythia, hepmcevt );

    // Write the HepMC event to file. Done with it.
    ascii_io << hepmcevt;
    delete hepmcevt;

  // End of event loop. Statistics. Histogram.
  }
  pythia.stat();

  // Done.
  return 0;

}


