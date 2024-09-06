import FWCore.ParameterSet.Config as cms

process = cms.Process("ShowerWidthAnalysis")

# Load standard sequences and geometry
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '140X_mcRun4_realistic_v3', '')

process.load("Geometry.CaloEventSetup.HGCalTopology_cfi")

# Exclude unnecessary subdetectors from geometry
process.CaloGeometryBuilder = cms.ESProducer("CaloGeometryBuilder",
    SelectedCalos = cms.vstring('HCAL', 'ZDC', 'EcalBarrel', 'TOWER', 'HGCalEESensitive', 'HGCalHESiliconSensitive', 'HGCalHEScintillatorSensitive')
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/relval/CMSSW_14_0_6/RelValZEE_14/GEN-SIM-RECO/PU_140X_mcRun4_realistic_v3_STD_2026D110_PU-v1/2590000/3eff852c-1b1c-49de-952a-1011c5ccdc92.root'  # Replace with your MINIAOD input file
    )
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

# Analyzer
process.showerWidthAnalyzer = cms.EDAnalyzer("HGCalShowerShapeHelperTest",
    #recHits = cms.InputTag("particleFlowRecHitHGC", "Cleaned", "RECO"),
    recHits = cms.InputTag("particleFlowRecHitHGC"),
    superCluster = cms.InputTag("particleFlowSuperClusterHGCal"),
)

# Path
process.p = cms.Path(process.showerWidthAnalyzer)

# Output (if needed)
# process.TFileService = cms.Service("TFileService", fileName = cms.string("output.root"))

