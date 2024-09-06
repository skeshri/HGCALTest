// -*- C++ -*-
//
// Package:    TestHGCAL/HGCalShowerShapeHelperTest
// Class:      HGCalShowerShapeHelperTest
//
/**\class HGCalShowerShapeHelperTest HGCalShowerShapeHelperTest.cc TestHGCAL/HGCalShowerShapeHelperTest/plugins/HGCalShowerShapeHelperTest.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sumit Keshri
//         Created:  Fri, 30 Aug 2024 09:48:02 GMT
//
//

// system include files
#include <memory>
#include <vector>
// HGCalShowerShapeHelperTest.cc
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"      // HGCAL RecHits
#include "Geometry/Records/interface/CaloGeometryRecord.h"             // CaloGeometry record
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"              // CaloGeometry
#include "RecoEgamma/EgammaTools/interface/HGCalShowerShapeHelper.h"   // HGCal shower shape helper
#include "RecoEgamma/EgammaTools/interface/EgammaHGCALIDParamDefaults.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

class HGCalShowerShapeHelperTest : public edm::one::EDAnalyzer<> {
public:
    explicit HGCalShowerShapeHelperTest(const edm::ParameterSet&);
    ~HGCalShowerShapeHelperTest() override = default;

private:
    void analyze(const edm::Event&, const edm::EventSetup&) override;

    edm::EDGetTokenT<reco::PFRecHitCollection> hgcalRecHitToken_;
    edm::EDGetTokenT<std::vector<reco::SuperCluster>> sc_;
    HGCalShowerShapeHelper showerShapeHelper;
};

HGCalShowerShapeHelperTest::HGCalShowerShapeHelperTest(const edm::ParameterSet& iConfig):
    showerShapeHelper(consumesCollector())
{
    // Initialize the token to retrieve RecHits from the event
    hgcalRecHitToken_ = consumes<reco::PFRecHitCollection>(iConfig.getParameter<edm::InputTag>("recHits"));
    sc_ = consumes<std::vector<reco::SuperCluster>>(iConfig.getParameter<edm::InputTag>("superCluster"));
}

void HGCalShowerShapeHelperTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // Retrieve the RecHits from the event
    edm::Handle<reco::PFRecHitCollection> hgcalRecHits;
    iEvent.getByToken(hgcalRecHitToken_, hgcalRecHits);
    
    edm::Handle<std::vector<reco::SuperCluster>> superClus;
    iEvent.getByToken(sc_, superClus);

    // Retrieve the geometry from the event setup
    //edm::ESHandle<CaloGeometry> caloGeometry;
    //iSetup.get<CaloGeometryRecord>().get(caloGeometry);
    
    showerShapeHelper.initPerEvent(iSetup, *hgcalRecHits);
    //showerShapeHelper.initPerEvent(*hgcalRecHits);
    // Initialize and set up the HGCalShowerShapeHelper
    //showerShapeHelper.setGeometry(*caloGeometry);
    //showerShapeHelper.setRecHits(*hgcalRecHits);

    double rCylinder(EgammaHGCALIDParamDefaults::kRCylinder);

    // Example of loop over some collection (e.g., photons or electrons)
    for (const auto& clus : *superClus) {
        //auto ssCalc = showerShapeHelper.createCalc(sc);
        //auto showerWidths = showerShapeHelper.getShowerWidths(hit.detid());
        auto showerWidths = showerShapeHelper.createCalc(clus);
        //float sigma2xx = showerWidths.sigma2xx;
        //float sigma2uu = showerWidths.sigma2uu;
        
        // Output the computed variables (sigma2xx and sigma2uu)
        //edm::LogInfo("HGCalShowerShapeHelperTest") << "sigma2xx: " << sigma2xx << ", sigma2uu: " << sigma2uu;
    }
}

// Define this as a plug-in
DEFINE_FWK_MODULE(HGCalShowerShapeHelperTest);

