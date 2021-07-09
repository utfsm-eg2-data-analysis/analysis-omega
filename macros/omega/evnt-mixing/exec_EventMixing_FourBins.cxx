#include "EventMixing_FourBins.cxx"

void exec_EventMixing_FourBins() {
  EventMixing_FourBins("D", "Q2", 1);
  EventMixing_FourBins("D", "Nu", 1);
  EventMixing_FourBins("D", "wZ", 1);
  EventMixing_FourBins("D", "wPt2", 1);

  EventMixing_FourBins("C", "Q2", 1);
  EventMixing_FourBins("C", "Nu", 1);
  EventMixing_FourBins("C", "wZ", 1);
  EventMixing_FourBins("C", "wPt2", 1);

  EventMixing_FourBins("Fe", "Q2", 1);
  EventMixing_FourBins("Fe", "Nu", 1);
  EventMixing_FourBins("Fe", "wZ", 1);
  EventMixing_FourBins("Fe", "wPt2", 1);

  EventMixing_FourBins("Pb", "Q2", 1);
  EventMixing_FourBins("Pb", "Nu", 1);
  EventMixing_FourBins("Pb", "wZ", 1);
  EventMixing_FourBins("Pb", "wPt2", 1);
}