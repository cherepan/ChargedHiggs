#ifndef FATJET_H
#define FATJET_H

#include "interface/Object.hpp"
#include "interface/Smearable.hpp"
#include <algorithm>
#include <string>
#include <map>

//#include <iostream>
//using namespace std;

// ---
class FatJet : virtual public Object, virtual public SmearableBase
{
    // This class take care of the jet definition in the analysis
    //
    float ptcut_; // ** pt cut on the accepted jets
    float etacut_ ; // ** eta cut on the accepted jets
    float tau1cut_ ; // To Set
    float tau2cut_ ; // To Set
    float tau3cut_ ; // To Set
    float tau21cut_ ; // To Set

    float corrprunedMasscut_ ;
    float prunedMasscut_ ;
    float softdropMasscut_ ;
    float nSubjetscut_ ;
    float hbbcut_;

    float hadFlavor_;

    int sdmasssyst_;
    int tau21syst_;
    int tau32syst_;

    // FIXME: add puppi

    TLorentzVector pp4;

    public:

    void SetPtCut(float x){ptcut_= x;}
    void SetEtaCut(float x){etacut_ = x;}

    void SetTau1Cut(float x){tau1cut_ = x;}
    void SetTau2Cut(float x){tau2cut_ = x;}
    void SetTau3Cut(float x){tau3cut_ = x;}

    void SetTau21Cut(float x){tau21cut_ = x;}

    void SetCorrPrunedMassCut(float x){corrprunedMasscut_ = x;}
    void SetPrunedMassCut(float x){prunedMasscut_ = x;}
    void SetSDMassCut(float x){softdropMasscut_ = x;}
    void SetSubjetsCut(float x){nSubjetscut_ = x;}

    void SetDoubleBBCut(float x){hbbcut_ = x;}
    void SetHadFlavor(float x) {hadFlavor_=x;}

    FatJet() ; 
    float tau1; //
    float tau2; //
    float tau3; //
    float sdtau1;
    float sdtau2;
    float sdtau3;
    float softdropMass;
    float CorrectedPrunedMass;
    int nSubjets;
    float subjet_btag;
    int hasSubJetBTag{0};
    int hasSubJetBTagLoose{0};

    //test subjet
    float subjet_btag1{0};
    float subjet_btag2{0};
    float subjet_btag3{0};
    float subjet_btag_max{0};


    int sdmasssyst{0};
    int tau21syst{0};
    int tau32syst{0};

    int isValid;
    //Gen-level info

    // ---

    inline float Tau1() const { return tau1 ; }
    inline float Tau2() const { return tau2 ; }
    inline float Tau3() const { return tau3 ; }

    inline float SDTau1() const { return sdtau1 ; }
    inline float SDTau2() const { return sdtau2 ; }
    inline float SDTau3() const { return sdtau3 ; }

    inline float SDMass() const { return (1+0.05*sdmasssyst)*softdropMass ; }
    //    inline float SDMass() const { return softdropMass ; }
    inline float CorrPrunedMass() const { return CorrectedPrunedMass ; }

    inline float subjetCSV1() const { return subjet_btag1 ; }
    inline float subjetCSV2() const { return subjet_btag2 ; }
    inline float subjetCSV3() const { return subjet_btag3 ; }
    inline float subjetCSVmax() const { return subjet_btag_max ; }
    inline int NSubj() const { return nSubjets ; }

    void clearSyst() override {Object::clearSyst(); sdmasssyst=0; tau21syst=0; tau32syst=0;}

    inline int IsSubjetBTag() const { return hasSubJetBTag ; }
    inline int IsSubjetBTagLoose() const { return hasSubJetBTagLoose ; }

    inline int hadFlavor() const { return hadFlavor_;}

    inline int IsJetExceptValidity() const {
        if( std::isnan(Pt()) ) return 0;
        if( Pt() < ptcut_ ) return 0;
        if( fabs(Eta()) >= etacut_) return 0;
        if( fabs(SDMass()) < softdropMasscut_) return 0;
        return 1;
    }

    inline int IsFatJet() const {
        if (not isValid) return 0;
        return IsJetExceptValidity();
    }

    inline float Tau21() const {
        if(tau2 > 0 and tau1 > 0) return (1+0.11*tau21syst)*(tau2/tau1);
        else return 0.;
    }

    inline float Tau32() const {
        if(tau3 > 0 and tau2 > 0) return (1+0.1*tau32syst)*(tau3/tau2);
        else return 0.;
    }


    // tipically 250 GeV
//    inline int IsWJet() const { if( Pt() > 207. and softdropMass > 65. and softdropMass < 105. and tau2 > 0 and tau1 > 0 and tau2 < tau1*0.6  and IsFatJet() and IsSubjetBTagLoose() == 0 )   return 1; return 0;}
//    inline int IsWJetMirror() const { if( Pt() > 207. and softdropMass > 65. and softdropMass < 105. and tau2 > 0 and tau1 > 0 and tau2 > tau1*0.6  and IsFatJet() and IsSubjetBTagLoose() == 0 )   return 1; return 0;}
    inline int IsWJet() const { if( Pt() > 207. and SDMass() > 65. and SDMass() < 105. and tau2 > 0 and tau1 > 0 and Tau21() < 0.6 and IsFatJet() and IsSubjetBTag() == 0 )   return 1; return 0;}
    inline int IsWJetMirror() const { if( Pt() > 207. and SDMass() > 65. and SDMass() < 105. and tau2 > 0 and tau1 > 0 and Tau21() > 0.6  and IsFatJet() and IsSubjetBTag() == 0 )   return 1; return 0;}
    // tipically 400 GeV
    inline int IsTopJet() const { if( Pt() > 400. and SDMass() > 135. and SDMass() < 220. and tau3 > 0 and tau2 > 0 and Tau32() < 0.67  and IsFatJet() ) return 1; return 0;}
    inline int IsTopJetMirror() const { if( Pt() > 400. and SDMass() > 135. and SDMass() < 220. and tau3 > 0 and tau2 > 0 and Tau32() > 0.67  and IsFatJet() ) return 1; return 0;}
};

#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4 
