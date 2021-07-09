#include "RadCorr_EventMixing.cxx"

void exec_RadCorr_EventMixing() {
  RadCorr_EventMixing("D", "Q2", 1, 1);
  RadCorr_EventMixing("D", "Nu", 1, 1);
  RadCorr_EventMixing("D", "wZ", 1, 1);
  RadCorr_EventMixing("D", "wPt2", 1, 1);

  RadCorr_EventMixing("C", "Q2", 1, 1);
  RadCorr_EventMixing("C", "Nu", 1, 1);
  RadCorr_EventMixing("C", "wZ", 1, 1);
  RadCorr_EventMixing("C", "wPt2", 1, 1);

  RadCorr_EventMixing("Fe", "Q2", 1, 1);
  RadCorr_EventMixing("Fe", "Nu", 1, 1);
  RadCorr_EventMixing("Fe", "wZ", 1, 1);
  RadCorr_EventMixing("Fe", "wPt2", 1, 1);

  RadCorr_EventMixing("Pb", "Q2", 1, 1);
  RadCorr_EventMixing("Pb", "Nu", 1, 1);
  RadCorr_EventMixing("Pb", "wZ", 1, 1);
  RadCorr_EventMixing("Pb", "wPt2", 1, 1);
}