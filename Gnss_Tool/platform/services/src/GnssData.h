#ifndef GNSSDATA_H
#define GNSSDATA_H
#include <string.h>
#include <QString>

namespace gnss {

const double EARTH_RAD = 6371.;

struct IISA  //структура для записи и чтение данных о индексе солнечыной активности
{
    double lat_st;// широта станции
    double lon_st;// долгота станции
    char st_name[5];// название станции
    int year;//год
    int mes;//месяц
    int day;//день
    int hour;//час
    int min;//минута
    float W;//ионосферный индекс солнечной активности
};


struct TEC_SBAS //структура для записи и чтение данных о ПЭС
{
    int lat_pp;
    int lon_pp;
    int year;//год
    int mes;//месяц
    int day;//день
    int hour;//час
    int min;//минута
    int sec;//секунда
    float tec;
};


struct vis
{
    double elev;
    double azi;
    double dop1;
    double dop2;
    unsigned short sys;
    unsigned long sat;
};

struct BESTPOS // позиция станции диагностики (в центре антенны)
{
    double lat;
    double lon;
    double height;
    char time_pos[64];
};


struct TEC //структура для записи и чтение данных о ПЭС
{
    double lat_st;// широта станции
    double lon_st;// долгота станции
    char st_name[5/*4*/];// название станции
    double lat_pp;// широта подионосферной точки
    double lon_pp;// долгота подионосферной точки
    int year;//год
    int mes;//месяц
    int day;//день
    int hour;//час
    int min;//минута
    int sec;//секунда
    int  n_ka;//номер КА
    double tec;//ПЭС по кодовым измерениям
    double tec_ph;//ПЭС комбинированное
    double obq;//функция наклона !!!!NEW
    double az;//азим !!!!NEW
    double el;//угол места !!!!NEW
};

struct GNSSOBS //структура для записи исходной измерительной информации
{
    int year;//год
    int mes;//месяц
    int day;//день
    int hour;//час
    int min;//минута
    double sec;//секунда
    int prn;//номер КА
    int freq;//номер частотной литеры
    double L1;//фаза по 1 частоте
    double L2;//фаза по 2 частоте
    double P1;//псевдодальность 1 частоте
    double P2;//псевдодальность 2 частоте
    double C1;//псевдодальность по С/А коду
    double D1;//Доплеровский сдвиг 1 частоте
    double D2;//Доплеровский сдвиг 2 частоте
    double S1;//Отношение сигнал/шум по 1 частоте
    double S2;//Отношение сигнал/шум по 2 частоте
    float azi;//азимут на КА
    float el;//угол места на КА
    double dcb;
    char pok_kach[11]; //Показатель качества данных
};


struct GPSPAR //структура для записи данных о модели ионосферы с навиг. файла и параметрах времени
{
    double a1;
    double a2;
    double a3;
    double a4;
    double b1;
    double b2;
    double b3;
    double b4;
    double A0;
    double A1;
    int T;
    int W;
    int del_t;
};


struct  GLONAV//структура для записи исходной навигационной информации для системы ГЛОНАСС
{
    int prn ;
    int year;
    int mes ;
    int day ;
    int hour ;
    int min  ;
    float  sec;
    double t_b;
    int freq  ;
    int health;
    double x  ;
    double y  ;
    double z  ;
    double vx ;
    double vy  ;
    double vz  ;
    double ax  ;
    double ay  ;
    double az  ;
    float gamma ;
    float tau_n ;
    double tau_c;
    unsigned short int  e ;
};


struct  GPSNAV//структура для записи исходной навигационной информации для системы GPS
{
    short int  prn;
    short int year;
    short int mes;
    short int day;
    short int hour;
    short int min;
    float sec;
    double sv_clock_bias;
    double sv_clock_drift;
    double sv_clock_dfrate;
    double iode;
    double crs;
    double delte_n;
    double Mo;
    double Cuc;
    double e;
    double Cus;
    double sqrta;
    double toe;
    double toc;
    double Cic;
    double omega;
    double Cis;
    double io;
    double Crc;
    double omega_m;
    double omega_dot;
    double idot;
    double code_l2;
    double GPS_week;
    double L2_p;
    double SV_acc;
    double SV_healt;
    double Trg;
    double iodc;
    double sec_week;
};


struct GPSTIME //структура для записи времени для системы GPS
{
    int god_n;
    int mes_n;
    int den_n;
    int Chas_n;
    int min_n;
    double sec_n;

};

struct SVS//структура для записи и чтения о положении КА для системы GPS
{
    double x_ka;
    double y_ka;
    double z_ka;
    double ugl_ka;
    double az_ka;
    float chir_p;
    float dolg_p;
    float vus_p;
};


struct GNSSRES
{
    QString datetime;
    int kolKa;
    float chir;
    float dolg;
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
};


struct REDOBS
{
    int year;
    int mes;
    int day;
    int hour;
    int min;
    int sec;
    int prn;
    int   freq;
    int sys;
    int type;
    float         fAzimuth;
    float         fElevation;
    float         fCNo;
    float         fLockTime;
    float         fCMCAvrg;
    float         fCMCStd;
    float         fS4;
    float         fS4Correction;
    float         f1SecSigma;
    float         f3SecSigma;
    float         f10SecSigma;
    float         f30SecSigma;
    float         f60SecSigma;
    float         ftec;
    float         fdtec;
};

struct SHARED_GNSS_DATA
{
    bool condition;
    TEC tecData;
    GNSSOBS obsData;

    SHARED_GNSS_DATA(bool cond = false)
    {
        condition = cond;
    }

};

}
#endif
