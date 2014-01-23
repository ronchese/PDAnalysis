import FWCore.ParameterSet.Config as cms

process = cms.PSet()
#process = cms.Process("PD")

filename = open('pat_files.list', 'r')
filelist = cms.vstring( filename.readlines() )

process.fwliteInput = cms.PSet(
    fileNames   = filelist,               ## mandatory
    maxEvents   = cms.int32(500),        ## optional, use maxEvents<=0
                                          ##           to read all events
    outputEvery = cms.uint32(10),         ## optional (usage not clear...)
)
    
process.fwliteOutput = cms.PSet(
    fileName = cms.string('hist.root'),   ## mandatory
)

process.pdAnalyzer = cms.PSet(

    ## optional
#    eventList = cms.string('evtlist'),
    verbose = cms.untracked.string('t'),

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
    labelElectrons    = cms.string(''),
    labelTaus         = cms.string(''),
    labelJets         = cms.string('selectedPatJetsPFlow'),
#    labelPFCandidates = cms.string('particleFlow'),
    labelPFCandidates = cms.string('selectedPatJetsPFlow:pfCandidates:PAT'),
#    labelPFCandidates = cms.string(''),
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
        'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_20_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_v',
        'HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v',
        'HLT_Mu12_DoubleCentralJet65_v',
        'HLT_Mu12_v'
    ),

    ## trigger objects to save on ntuple:
    savedTriggerObjects = cms.vstring(
        'muon',
        'jet'
    )

)


