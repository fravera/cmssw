#ifndef RecoParticleFlow_PFEGammaCandidateChecker_
#define RecoParticleFlow_PFEGammaCandidateChecker_

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

/**\class PFEGammaCandidateChecker 
\brief Checks what a re-reco changes in PFCandidates.

\author Patrick Janot
\date   August 2011
*/

class PFEGammaCandidateChecker : public edm::EDAnalyzer {
public:
  explicit PFEGammaCandidateChecker(const edm::ParameterSet&);

  ~PFEGammaCandidateChecker();

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  virtual void beginRun(const edm::Run& r, const edm::EventSetup& c);

private:
  void printJets(const reco::PFJetCollection& pfJetsReco, const reco::PFJetCollection& pfJetsReReco) const;

  void printMet(const reco::PFCandidateCollection& pfReco, const reco::PFCandidateCollection& pfReReco) const;

  void printElementsInBlocks(const reco::PFCandidate& cand, std::ostream& out = std::cout) const;

  /// PFCandidates in which we'll look for pile up particles
  edm::InputTag inputTagPFCandidatesReco_;
  edm::InputTag inputTagPFCandidatesReReco_;
  edm::InputTag inputTagPFJetsReco_;
  edm::InputTag inputTagPFJetsReReco_;

  /// Cuts for comparison
  double deltaEMax_;
  double deltaEtaMax_;
  double deltaPhiMax_;

  /// verbose ?
  bool verbose_;

  /// print the blocks associated to a given candidate ?
  bool printBlocks_;

  /// rank the candidates by Pt
  bool rankByPt_;

  /// Counter
  unsigned entry_;

  static bool greaterPt(const reco::PFCandidate& a, const reco::PFCandidate& b) { return (a.pt() > b.pt()); }
};

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
DEFINE_FWK_MODULE(PFEGammaCandidateChecker);

#endif
