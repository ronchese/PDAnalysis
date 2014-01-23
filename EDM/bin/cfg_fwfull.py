import FWCore.ParameterSet.Config as cms

process = cms.Process("PD")

process.load('Configuration.StandardSequences.Services_cff')
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
##process.GlobalTag.globaltag = cms.string('MC_42_V15B::All')
#process.GlobalTag.globaltag = cms.string('GR_R_52_V9D::All')
#process.load("Configuration.StandardSequences.Reconstruction_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load('Configuration/StandardSequences/GeometryExtended_cff')
#process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

process.load("FWCore.MessageService.MessageLogger_cfi")

# Quiet Mode or event dump
#process.MessageLogger.cerr.threshold = 'ERROR'
process.MessageLogger.cerr.threshold = 'WARNING'
#process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

filename = open('pat_files.list', 'r')
#filename = open('SingleMu-Run2012B-13Jul2012-v1_BsMuMu_Data2012_v4_01.list', 'r')
fileList = cms.untracked.vstring( filename.readlines() )

process.source = cms.Source ("PoolSource", fileNames=fileList)

process.pdAnalyzer = cms.EDAnalyzer('PDPATAnalyzer',

    ## optional
#    eventList = cms.string('evtlist'),
    verbose = cms.untracked.string('f'),

    ## mandatory
    ## ntuple file name: empty string to drop ntuple filling
    ntuName = cms.untracked.string('ntu.root'),
    ## histogram file name
    histName = cms.untracked.string('hist.root'),

    labelTrigResults  = cms.string('TriggerResults'),
    labelTrigEvent    = cms.string('patTriggerEvent'),
    labelBeamSpot     = cms.string('offlineBeamSpot'),
    labelMets         = cms.string('patMETsPFlow'),
    labelMuons        = cms.string('selectedPatMuonsPFlow'),
#    labelElectrons    = cms.string('userDataSelectedPFElectronsAK5PFNoPU'),
#    labelTaus         = cms.string('selectedPatTausAK5PFNoPU'),
#    labelTaus         = cms.string('selectedPatTausPFlow'),
    labelElectrons    = cms.string(''),
    labelTaus         = cms.string(''),
    labelJets         = cms.string('selectedPatJetsPFlow'),
#    labelPFCandidates = cms.string('particleFlow'),
    labelPFCandidates = cms.string('selectedPatJetsPFlow:pfCandidates:PAT'),
    labelGeneralTracks = cms.string('generalTracks'),
    labelPVertices    = cms.string('offlinePrimaryVerticesWithBS'),
    labelSVertices    = cms.string('secondaryVertexTagInfosAODPFlow'),
    labelGen          = cms.string(''),

#    write_hlto  = cms.string('f'),
#    write_pflow = cms.string('f'),

    selectAssociatedPF = cms.string('t'),
    selectAssociatedTk = cms.string('t'),

    jetPtMin  = cms.double(  5.0 ),
    jetEtaMax = cms.double(  2.5 ),
    trkDzMax  = cms.double(  0.8 ),
    trkPtMin  = cms.double(  0.5 ),
    trkEtaMax = cms.double(  3.0 ),
    dRmatchHLT = cms.double( 0.5 ),
    dPmatchHLT = cms.double( 0.5 ),

    ## trigger paths to save on ntuple: '*' to save all paths
    savedTriggerPaths = cms.vstring(
        'HLT_Mu40_eta2p1_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v',
        'HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v',
        'HLT_DoubleMu4_Jpsi_Displaced_v'
    ),

    ## trigger objects to save on ntuple:
    savedTriggerObjects = cms.vstring(
        'hltMuon',
        'hltJet'
    )

)


process.p = cms.Path(process.pdAnalyzer)
