#include "iri_adapter.h"
#include "math.h"
#include "iostream"

extern "C" {
void iri_invoke_(int* jmag, int jf[], float* alati, float* along,int* iyyyy, int* mmdd, int* iut, float* dhour,
              float* height, float* h_tec_max,int* ivar, float* vbeg, float* vend, float* vstp, float outf[][20], float oar[][100]);
}

const STANDART_RESULT result_default={
    0, 0, 0, 0,     // year, month, day, dhour
    0.0, 0.0,       // lati, longi
    0,              // iisa
    0.0, 0.0, 0.0,  // foF2, hmF2, dhF2
    0.0, 0.0, 0.0,  // foF1, hmF1, dhF1
    0.0,            // foE
    0.0,            // hmE
    0.0,            // dhE
    0.0             // tec
};

void default_jf(int* jf) {
    jf[3] = 0; // t=B0table f=other models (f)
    jf[4] = 0; // t=B0table f=other models (f)
    jf[5] = 0; // t=DS95+DY85   f=RBV10+TTS03 (f)
    jf[20] = 0; // t=DS95+DY85   f=RBV10+TTS03 (f)
    jf[22] = 0; // t=AEROS/ISIS f=TTS Te with PF10.7
    jf[27] = 0; // f=spread-F not computed (f)
    jf[28] = 0; // t=old  f=New Topside options (f)
    jf[29] = 0; // t=corr f=NeQuick topside (f)
    jf[32] = 0; // f=auroral boundary off (f)
    jf[34] = 0; // f=auroral E-storm model off
}

extern void call_iri(MODEL_PARMS* inParms)
{
    int jmag = 0; // geographic coordinates
    int jf[50];
    for(int i=0; i<50; i++) {
        jf[i] = 1;
    }
    default_jf(jf);
    int iut = IRI_TIME;
    int ivar = inParms->independentVar;

    iri_invoke_(&jmag, jf, &inParms->lati, &inParms->longi, &inParms->year, &inParms->mmdd, &iut, &inParms->dhour, &inParms->height, &inParms->h_tec_max,
             &ivar, &inParms->beginRange, &inParms->endRange, &inParms->stepRange, inParms->outf, inParms->oar);
}

extern int parse_model_ouput(MODEL_PARMS* modelOutput, std::vector<STANDART_RESULT>* result)
{
    if (modelOutput->stepRange == 0) {
        return -1;
    }
    result->clear(); // result must be clear
    int num = (modelOutput->beginRange - modelOutput->endRange)/modelOutput->stepRange;
    std::cout << "NUM = " << num << " " << modelOutput->beginRange << " " << modelOutput->endRange <<" " << modelOutput->stepRange <<   std::endl;
    num = abs(num);
    int max = NUM_MAX;
    if(num  > max) {
        num = max;
    }
    float beginStep = modelOutput->beginRange;
    for(int i=0; i<num; i++) {
        if(modelOutput->independentVar == HEIGHT) {
            modelOutput->oar[i][0] = modelOutput->oar[0][0];
            modelOutput->oar[i][35] = modelOutput->oar[0][35];
            modelOutput->oar[i][36] = modelOutput->oar[0][36];
        }
        STANDART_RESULT res = result_default;
        res.lati = modelOutput->lati;
        res.longi = modelOutput->longi;
        res.year = modelOutput->year;
        res.month = modelOutput->mmdd / 100;
        res.day = modelOutput->mmdd - (res.month* 100);
        switch(modelOutput->independentVar)
        {
        case HOUR: {
            res.dhour = modelOutput->stepRange * i;
            res.height = modelOutput->height;
        }
            break;
        case HEIGHT: {
            res.height = modelOutput->stepRange * i;
            res.dhour = modelOutput->dhour;
        }
            break;
        default:
            break;
        }
        float tec = modelOutput->oar[i][36];
        if(tec > 0.0) {
            tec = tec/1.e16;
        } else {
            tec=-1.0;
        }
        res.tec = tec;
        int jne =int(modelOutput->outf[i][0]/1.e6+.5);
        res.nE = jne;
        result->push_back(res);
    }

    return 1;
}
