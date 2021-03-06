#if !defined (__CINT__) || defined (__CLING__)

#include <Riostream.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TParameter.h>

#include "AliESDtrackCuts.h"
#include "AliRDHFCutsDstoKKpi.h"

#endif

//____________________________________________________________________________________________________//
// Methods:
// 1) MakeFileForCutsDs_FiltTree_ITS1_Data --> filtering cuts for tree used for ITS2 Data studies with ML
//
// 2) MakeFileForCutsDs_FiltTree_ITS2 --> filtering cuts for tree used for ITS2 MC simulation studies with ML
//
// 3) MakeFileForCutsDs_FiltTree_ITS3 --> filtering cuts for tree used for ITS3 D studies with ML
//___________________________________________________________________________________________________//

AliRDHFCutsDstoKKpi* MakeFileForCutsDs_FiltTree_ITS1_Data(double ptmin=1., double ptmax=50.) {


    AliESDtrackCuts* esdTrackCuts = new AliESDtrackCuts();
    esdTrackCuts->SetRequireSigmaToVertex(false);
    esdTrackCuts->SetRequireTPCRefit(true);
    esdTrackCuts->SetRequireITSRefit(true); 
    esdTrackCuts->SetMinRatioCrossedRowsOverFindableClustersTPC(0.8);
    esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
                                           AliESDtrackCuts::kAny);
    esdTrackCuts->SetMinDCAToVertexXY(0.);
    esdTrackCuts->SetPtRange(0.4,1.e10);    


    const int nptbins=3; 
    float ptbins[nptbins+1]={0.,5.,10.,50.};

    const int nvars = 20;

    float** anacutsval=new float*[nvars];
    for(int ic=0;ic<nvars;ic++){anacutsval[ic]=new float[nptbins];}

    /*
        Cut list
        0       "inv. mass [GeV]",
        1	    "pTK [GeV/c]",
        2	    "pTPi [GeV/c]",
        3	    "d0K [cm]",
        4	    "d0Pi [cm]",
        5		"dist12 [cm]",
        6		"sigmavert [cm]",
        7		"decLen [cm]",
        8		"ptMax [GeV/c]",
        9		"cosThetaPoint",
        10		"Sum d0^2 (cm^2)",
        11		"dca [cm]",
        12		"inv. mass (Mphi-MKK) [GeV]",
        13		"inv. mass (MKo*-MKpi) [GeV]",
        14   	"Abs(CosineKpiPhiRFrame)^3",
        15 		"CosPiDsLabFrame",
        16 		"DecLengthXY",
        17 		"NormDecayLength",
        18 		"NormDecayLengthXY",
        19 		"cosThetaPointXY"

        WARNING: even if not assigned, mantein ALL the precuts value
     */

    anacutsval[0][0]=0.25;
    anacutsval[1][0]=0.4;
    anacutsval[2][0]=0.4;
    anacutsval[3][0]=0.;
    anacutsval[4][0]=0.;
    anacutsval[5][0]=0.;
    anacutsval[6][0]=0.02;
    anacutsval[7][0]=0.02;
    anacutsval[8][0]=0.;
    anacutsval[9][0]=0.97;
    anacutsval[10][0]=0.;
    anacutsval[11][0]=100000.0;
    anacutsval[12][0]=0.015;
    anacutsval[13][0]=0.001;
    anacutsval[14][0]=0.;
    anacutsval[15][0]=1.;
    anacutsval[16][0]=0.;
    anacutsval[17][0]=0.;
    anacutsval[18][0]=4.;
    anacutsval[19][0]=0.9;

    anacutsval[0][1]=0.25;
    anacutsval[1][1]=0.4;
    anacutsval[2][1]=0.4;
    anacutsval[3][1]=0.;
    anacutsval[4][1]=0.;
    anacutsval[5][1]=0.;
    anacutsval[6][1]=0.02;
    anacutsval[7][1]=0.02;
    anacutsval[8][1]=0.;
    anacutsval[9][1]=0.95;
    anacutsval[10][1]=0.;
    anacutsval[11][1]=100000.0;
    anacutsval[12][1]=0.015;
    anacutsval[13][1]=0.001;
    anacutsval[14][1]=0.;
    anacutsval[15][1]=1.;
    anacutsval[16][1]=0.;
    anacutsval[17][1]=0.;
    anacutsval[18][1]=3.;
    anacutsval[19][1]=0.9;

    anacutsval[0][2]=0.25;
    anacutsval[1][2]=0.4;
    anacutsval[2][2]=0.4;
    anacutsval[3][2]=0.;
    anacutsval[4][2]=0.;
    anacutsval[5][2]=0.;
    anacutsval[6][2]=0.02;
    anacutsval[7][2]=0.02;
    anacutsval[8][2]=0.;
    anacutsval[9][2]=0.;
    anacutsval[10][2]=0.;
    anacutsval[11][2]=100000.0;
    anacutsval[12][2]=0.015;
    anacutsval[13][2]=0.001;
    anacutsval[14][2]=0.;
    anacutsval[15][2]=1.;
    anacutsval[16][2]=0.;
    anacutsval[17][2]=0.;
    anacutsval[18][2]=0.;
    anacutsval[19][2]=0.9;
 
  
    AliRDHFCutsDstoKKpi* analysiscuts=new AliRDHFCutsDstoKKpi();
    analysiscuts->SetName("AnalysisCuts");
    analysiscuts->SetTitle("Cuts for Ds Analysis and CF");
    analysiscuts->SetUsePreSelect(1);
    analysiscuts->SetPtBins(nptbins+1,ptbins);
    analysiscuts->SetCuts(nvars,nptbins,anacutsval);
    analysiscuts->AddTrackCuts(esdTrackCuts);

    analysiscuts->SetRemoveTrackletOutliers(true);
    analysiscuts->SetCutOnzVertexSPD(3);
    analysiscuts->SetUseTimeRangeCutForPbPb2018(true);
    analysiscuts->EnableNsigmaDataDrivenCorrection(true,AliAODPidHF::kPbPb010);

    analysiscuts->SetUseCentrality(AliRDHFCuts::kCentV0M);
    analysiscuts->SetMinCentrality(0.);
    analysiscuts->SetMaxCentrality(10.);
    analysiscuts->SetTriggerClass("");//dont use for ppMB/ppMB_MC
    analysiscuts->ResetMaskAndEnableMBTrigger();//dont use for ppMB/ppMB_MC
    analysiscuts->SetTriggerMask(AliVEvent::kINT7 | AliVEvent::kCentral);

    analysiscuts->SetUsePID(true);
    analysiscuts->SetPidOption(0); //0=kConservative,1=kStrong

    analysiscuts->SetOptPileup(false);
    analysiscuts->SetMinPtCandidate(ptmin);
    analysiscuts->SetMaxPtCandidate(ptmax);
    analysiscuts->SetRemoveDaughtersFromPrim(false);

    std::cout<<"This is the object I'm going to save:"<<nptbins<<std::endl;

    analysiscuts->PrintAll();

    TFile* fout=new TFile(Form("DstoKKpiCutsITS1_filttree_kINT7_kCentral_consPID_pt%0.f_%0.f.root",ptmin,ptmax),"recreate");
    fout->cd();
    analysiscuts->Write();
    fout->Close();

    return analysiscuts;
}


AliRDHFCutsDstoKKpi* MakeFileForCutsDs_FiltTree_ITS2(double ptmin=1., double ptmax=50.) {

    AliESDtrackCuts* esdTrackCuts = new AliESDtrackCuts();
    esdTrackCuts->SetRequireSigmaToVertex(false);
    esdTrackCuts->SetRequireTPCRefit(true);
    esdTrackCuts->SetRequireITSRefit(true); 
    esdTrackCuts->SetMinRatioCrossedRowsOverFindableClustersTPC(0.8);
    esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
                                           AliESDtrackCuts::kAny);
    esdTrackCuts->SetMinDCAToVertexXY(0.);
    esdTrackCuts->SetPtRange(0.4,1.e10);


    const int nptbins=3; 
    float ptbins[nptbins+1]={0.,5.,10.,50.};

    const int nvars = 20;

    float** anacutsval=new float*[nvars];
    for(int ic=0;ic<nvars;ic++){anacutsval[ic]=new float[nptbins];}

    /*
        Cut list
        0       "inv. mass [GeV]",
        1	    "pTK [GeV/c]",
        2	    "pTPi [GeV/c]",
        3	    "d0K [cm]",
        4	    "d0Pi [cm]",
        5		"dist12 [cm]",
        6		"sigmavert [cm]",
        7		"decLen [cm]",
        8		"ptMax [GeV/c]",
        9		"cosThetaPoint",
        10		"Sum d0^2 (cm^2)",
        11		"dca [cm]",
        12		"inv. mass (Mphi-MKK) [GeV]",
        13		"inv. mass (MKo*-MKpi) [GeV]",
        14   	"Abs(CosineKpiPhiRFrame)^3",
        15 		"CosPiDsLabFrame",
        16 		"DecLengthXY",
        17 		"NormDecayLength",
        18 		"NormDecayLengthXY",
        19 		"cosThetaPointXY"

        WARNING: even if not assigned, mantein ALL the precuts value
     */

    anacutsval[0][0]=0.25;
    anacutsval[1][0]=0.4;
    anacutsval[2][0]=0.4;
    anacutsval[3][0]=0.;
    anacutsval[4][0]=0.;
    anacutsval[5][0]=0.;
    anacutsval[6][0]=0.02;
    anacutsval[7][0]=0.02;
    anacutsval[8][0]=0.;
    anacutsval[9][0]=0.97;
    anacutsval[10][0]=0.;
    anacutsval[11][0]=100000.0;
    anacutsval[12][0]=0.015;
    anacutsval[13][0]=0.001;
    anacutsval[14][0]=0.;
    anacutsval[15][0]=1.;
    anacutsval[16][0]=0.;
    anacutsval[17][0]=0.;
    anacutsval[18][0]=4.;
    anacutsval[19][0]=0.9;

    anacutsval[0][1]=0.25;
    anacutsval[1][1]=0.4;
    anacutsval[2][1]=0.4;
    anacutsval[3][1]=0.;
    anacutsval[4][1]=0.;
    anacutsval[5][1]=0.;
    anacutsval[6][1]=0.02;
    anacutsval[7][1]=0.02;
    anacutsval[8][1]=0.;
    anacutsval[9][1]=0.95;
    anacutsval[10][1]=0.;
    anacutsval[11][1]=100000.0;
    anacutsval[12][1]=0.015;
    anacutsval[13][1]=0.001;
    anacutsval[14][1]=0.;
    anacutsval[15][1]=1.;
    anacutsval[16][1]=0.;
    anacutsval[17][1]=0.;
    anacutsval[18][1]=3.;
    anacutsval[19][1]=0.9;

    anacutsval[0][2]=0.25;
    anacutsval[1][2]=0.4;
    anacutsval[2][2]=0.4;
    anacutsval[3][2]=0.;
    anacutsval[4][2]=0.;
    anacutsval[5][2]=0.;
    anacutsval[6][2]=0.02;
    anacutsval[7][2]=0.02;
    anacutsval[8][2]=0.;
    anacutsval[9][2]=0.;
    anacutsval[10][2]=0.;
    anacutsval[11][2]=100000.0;
    anacutsval[12][2]=0.015;
    anacutsval[13][2]=0.001;
    anacutsval[14][2]=0.;
    anacutsval[15][2]=1.;
    anacutsval[16][2]=0.;
    anacutsval[17][2]=0.;
    anacutsval[18][2]=0.;
    anacutsval[19][2]=0.9;
 
  
    AliRDHFCutsDstoKKpi* analysiscuts=new AliRDHFCutsDstoKKpi();
    analysiscuts->SetName("AnalysisCuts");
    analysiscuts->SetTitle("Cuts for Ds Analysis and CF");
    analysiscuts->SetUsePreSelect(1);
    analysiscuts->SetPtBins(nptbins+1,ptbins);
    analysiscuts->SetCuts(nvars,nptbins,anacutsval);
    analysiscuts->AddTrackCuts(esdTrackCuts);

    analysiscuts->SetUseCentrality(AliRDHFCuts::kCentOff); //
    analysiscuts->SetTriggerClass("");//dont use for ppMB/ppMB_MC
    analysiscuts->ResetMaskAndEnableMBTrigger();//dont use for ppMB/ppMB_MC
    analysiscuts->SetTriggerMask(AliVEvent::kAny);

    analysiscuts->SetUsePID(true);
    analysiscuts->SetPidOption(0); //0=kConservative,1=kStrong

    analysiscuts->SetOptPileup(false);
    analysiscuts->SetMinPtCandidate(ptmin);
    analysiscuts->SetMaxPtCandidate(ptmax);
    analysiscuts->SetRemoveDaughtersFromPrim(false);

    std::cout<<"This is the object I'm going to save:"<<nptbins<<std::endl;

    analysiscuts->PrintAll();

    TFile* fout=new TFile(Form("DstoKKpiCutsITS2_filttree_kAny_consPID_pt%0.f_%0.f.root",ptmin,ptmax),"recreate");
    fout->cd();
    analysiscuts->Write();
    fout->Close();

    return analysiscuts;
}

// waiting for ITS3 MC Data
AliRDHFCutsDstoKKpi* MakeFileForCutsDs_FiltTree_ITS3(double ptmin=1., double ptmax=50.) {


    AliESDtrackCuts* esdTrackCuts = new AliESDtrackCuts();
    esdTrackCuts->SetRequireSigmaToVertex(false);
    esdTrackCuts->SetRequireTPCRefit(true);
    esdTrackCuts->SetRequireITSRefit(true);
    esdTrackCuts->SetMinRatioCrossedRowsOverFindableClustersTPC(0.8);
    esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
                                           AliESDtrackCuts::kAny);
    esdTrackCuts->SetMinDCAToVertexXY(0.);
    esdTrackCuts->SetPtRange(0.4,1.e10);  


    const int nptbins=3; 
    float ptbins[nptbins+1]={0.,5.,10.,50.};

    const int nvars = 20;

    float** anacutsval=new float*[nvars];
    for(int ic=0;ic<nvars;ic++){anacutsval[ic]=new float[nptbins];}

    /*
        Cut list
        0       "inv. mass [GeV]",
        1	    "pTK [GeV/c]",
        2	    "pTPi [GeV/c]",
        3	    "d0K [cm]",
        4	    "d0Pi [cm]",
        5		"dist12 [cm]",
        6		"sigmavert [cm]",
        7		"decLen [cm]",
        8		"ptMax [GeV/c]",
        9		"cosThetaPoint",
        10		"Sum d0^2 (cm^2)",
        11		"dca [cm]",
        12		"inv. mass (Mphi-MKK) [GeV]",
        13		"inv. mass (MKo*-MKpi) [GeV]",
        14   	"Abs(CosineKpiPhiRFrame)^3",
        15 		"CosPiDsLabFrame",
        16 		"DecLengthXY",
        17 		"NormDecayLength",
        18 		"NormDecayLengthXY",
        19 		"cosThetaPointXY"

        WARNING: even if not assigned, mantein ALL the precuts value
     */

    anacutsval[0][0]=0.25;
    anacutsval[1][0]=0.4;
    anacutsval[2][0]=0.4;
    anacutsval[3][0]=0.;
    anacutsval[4][0]=0.;
    anacutsval[5][0]=0.;
    anacutsval[6][0]=0.02;
    anacutsval[7][0]=0.02;
    anacutsval[8][0]=0.;
    anacutsval[9][0]=0.97;
    anacutsval[10][0]=0.;
    anacutsval[11][0]=100000.0;
    anacutsval[12][0]=0.015;
    anacutsval[13][0]=0.001;
    anacutsval[14][0]=0.;
    anacutsval[15][0]=1.;
    anacutsval[16][0]=0.;
    anacutsval[17][0]=0.;
    anacutsval[18][0]=4.;
    anacutsval[19][0]=0.9;

    anacutsval[0][1]=0.25;
    anacutsval[1][1]=0.4;
    anacutsval[2][1]=0.4;
    anacutsval[3][1]=0.;
    anacutsval[4][1]=0.;
    anacutsval[5][1]=0.;
    anacutsval[6][1]=0.02;
    anacutsval[7][1]=0.02;
    anacutsval[8][1]=0.;
    anacutsval[9][1]=0.95;
    anacutsval[10][1]=0.;
    anacutsval[11][1]=100000.0;
    anacutsval[12][1]=0.015;
    anacutsval[13][1]=0.001;
    anacutsval[14][1]=0.;
    anacutsval[15][1]=1.;
    anacutsval[16][1]=0.;
    anacutsval[17][1]=0.;
    anacutsval[18][1]=3.;
    anacutsval[19][1]=0.9;

    anacutsval[0][2]=0.25;
    anacutsval[1][2]=0.4;
    anacutsval[2][2]=0.4;
    anacutsval[3][2]=0.;
    anacutsval[4][2]=0.;
    anacutsval[5][2]=0.;
    anacutsval[6][2]=0.02;
    anacutsval[7][2]=0.02;
    anacutsval[8][2]=0.;
    anacutsval[9][2]=0.;
    anacutsval[10][2]=0.;
    anacutsval[11][2]=100000.0;
    anacutsval[12][2]=0.015;
    anacutsval[13][2]=0.001;
    anacutsval[14][2]=0.;
    anacutsval[15][2]=1.;
    anacutsval[16][2]=0.;
    anacutsval[17][2]=0.;
    anacutsval[18][2]=0.;
    anacutsval[19][2]=0.9;
 
  
    AliRDHFCutsDstoKKpi* analysiscuts=new AliRDHFCutsDstoKKpi();
    analysiscuts->SetName("AnalysisCuts");
    analysiscuts->SetTitle("Cuts for Ds Analysis and CF");
    analysiscuts->SetUsePreSelect(1);
    analysiscuts->SetPtBins(nptbins+1,ptbins);
    analysiscuts->SetCuts(nvars,nptbins,anacutsval);
    analysiscuts->AddTrackCuts(esdTrackCuts);

    analysiscuts->SetUseCentrality(AliRDHFCuts::kCentOff); //
    analysiscuts->SetTriggerClass("");//dont use for ppMB/ppMB_MC
    analysiscuts->ResetMaskAndEnableMBTrigger();//dont use for ppMB/ppMB_MC
    analysiscuts->SetTriggerMask(AliVEvent::kAny);

    analysiscuts->SetUsePID(true);
    analysiscuts->SetPidOption(0); //0=kConservative,1=kStrong

    analysiscuts->SetOptPileup(false);
    analysiscuts->SetMinPtCandidate(ptmin);
    analysiscuts->SetMaxPtCandidate(ptmax);
    analysiscuts->SetRemoveDaughtersFromPrim(false);

    std::cout<<"This is the object I'm going to save:"<<nptbins<<std::endl;

    analysiscuts->PrintAll();

    TFile* fout=new TFile(Form("DstoKKpiCutsITS3_filttree_kAny_consPID_pt%0.f_%0.f.root",ptmin,ptmax),"recreate");
    fout->cd();
    analysiscuts->Write();
    fout->Close();

    return analysiscuts;
} 
