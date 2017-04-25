#ifndef IRIADAPTER_H
#define IRIADAPTER_H
#include "vector"

#ifdef __cplusplus
extern "C" {
#endif

#define IRI_TIME 1; // (=0/1,LT/UT)
#define NUM_MAX 1000;

typedef enum {
    HEIGHT=1,
    LATITUDE=2,
    LONGITUDE=3,
    YEAR=4,
    MONTH=5,
    DAY=6,
    DAY_OF_YEAR=7,
    HOUR=8
} IVAR;

typedef struct {
    float lati;
    float longi;
    float height;
    int year;
    int mmdd;
    float dhour;
    float h_tec_max;
    IVAR independentVar;
    float beginRange;
    float endRange;
    float stepRange;
    float outf[1000][20]; // output parameters !!! must be fortran-transposed
    float oar[1000][100]; // output parameters !!! must be fortran-transposed
} MODEL_PARMS;

typedef struct {
    int year;
    int month;
    int day;
    float dhour;
    float lati;
    float longi;
    float height;
    int iisa;
    float foF2;
    float hmF2;
    float dhF2;
    float foF1;
    float hmF1;
    float dhF1;
    float foE;
    float hmE;
    float dhE;
    float tec;
    float nE;
} STANDART_RESULT;

extern const STANDART_RESULT result_default;   /* default result */
extern void call_iri(MODEL_PARMS* inParms);
extern int parse_model_ouput(MODEL_PARMS* modelOutput, std::vector<STANDART_RESULT>* result);

#ifdef __cplusplus
}
#endif
#endif /* IRIADAPTER_H */
