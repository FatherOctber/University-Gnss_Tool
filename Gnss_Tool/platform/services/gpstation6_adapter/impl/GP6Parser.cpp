#include "GP6Parser.h"
#include <windows.h>
#include <QDateTime>

GP6Parser::GP6Parser()
{
}

GP6Parser::~GP6Parser()
{
}

void GP6Parser::parse(QByteArray data, Context *workingContext)
{
    if(data.size()>0) {
        for ( int i = 0; i <data.count(); i++) {
            raw_t* raw = workingContext->getRaw();
            int status = input_oem4(raw, data[i]);
            if(status > 0) {
                scanNovatelMessage(workingContext, status);
            }
        }
    }
}

void GP6Parser::scanNovatelMessage(Context *ctx, int type)
{
    QString ass;
    obsd_t obs_r[64*2];

    raw_t* raw = ctx->getRaw();
    bool ok;
    if (type == 1) //rangecmpb
    {
        GNSSOBS obs;
        int i = raw->obs.n;
        for(int j=0, n = 0; j<i; j++) {
            obs_r[n++]=raw->obs.data[j];
        }
        //qDebug()<<"raw->obs="<<raw->obs.n;
        //qDebug()<<"raw->obs=SN "<<raw->obs.data->SNR[0]<<raw->obs.data->SNR[1];
        time_t tim = raw->obs.data->time.time;
        double ep[6];
        gtime_t  curtime = gpst2utc(raw->obs.data->time);
        time2epoch(curtime, ep);
        double ds = raw->obs.data->time.sec;
        SYSTEMTIME tsys, tsysold;
        int dtm = QDateTime::currentDateTime().toTime_t() - curtime.time;
        int dtm1 = QDateTime::currentDateTime().toTime_t() - raw->obs.data->time.time;
        GetSystemTime(&tsysold);

        obs.sec = ep[5];
        obs.min = (int)ep[4];
        obs.hour = (int)ep[3];
        obs.day = (int)ep[2];
        obs.mes = (int)ep[1];
        obs.year = (int)ep[0];
        tsys.wMilliseconds = (int)(ds/1000);
        tsys.wSecond = (int)ep[5];
        tsys.wMinute = (int)ep[4];
        tsys.wHour = (int)ep[3];
        tsys.wDay = (int)ep[2];
        tsys.wMonth = (int)ep[1];
        tsys.wYear = (int)ep[0];

        if( abs(dtm) >= 1) {
            SetSystemTime(&tsys);
        }

        for(int j=0; j<i; j++) {
            int prn;
            unsigned int sys=obs_r[j].sys;
            //qDebug()<<"code="<<obs_r[j].sat<<obs_r[j].sys<<sys;
            obs.azi = -1.;
            ass.sprintf("%d",obs_r[j].SNR[0]);
            obs.S1=ass.toInt(&ok,10)*0.25;
            ass.sprintf("%d",obs_r[j].SNR[1]);
            obs.S2=ass.toInt(&ok,10)*0.25;
            ass.sprintf("%2d",obs_r[j].sat);
            obs.prn=ass.toInt(&ok,10);
            //qDebug()<<"prn1="<<obs.prn<<"sys="<<sys<<obs_r[j].sat<<sys;

            if(sys==2)  obs.prn+=119-32;
            if(sys==4)  obs.prn+=5;

            //qDebug()<<"prn="<<obs.prn<<"sys="<<sys;
            obs.el = -1;
            obs.P1 = obs_r[j].P[0];
            obs.P2 = obs_r[j].P[1];
            obs.L1 = obs_r[j].L[0];
            obs.L2 = obs_r[j].L[1];
            ctx->obs_tek.insert(obs.prn, obs);
        }
        //qDebug()<<"map="<<obs_tek.count();
    }
    if (type == 7) { //bestpos
        BESTPOS position;
        char * time_c = time_str(raw->obs.data->time,1);
        QString time = time_c;
        strncpy(position.time_pos, time_c, time.length());
        position.lat = raw->bestpost[0];
        position.lon = raw->bestpost[1];
        position.height = raw->bestpost[2];
        ctx->setPosition(position);
    }
    if (type == 10) //redobs
    {
        REDOBS robs;
        double ep[6];
        time2epoch(raw->obs.data->time, ep);
        robs.sec = ep[5];
        robs.min = (int)ep[4];
        robs.hour = (int)ep[3];
        robs.day = (int)ep[2];
        robs.mes = (int)ep[1];
        robs.year = (int)ep[0];
        int n = raw->tec_rec.size;
        for (int i=0; i<84; i++)
        {
            if(raw->redobs[i].fElevation>0 )
            {
                ass.sprintf("%d",raw->redobs[i].ucPrn);
                robs.prn = ass.toInt(&ok,10);
                robs.fElevation = raw->redobs[i].fElevation;
                robs.fAzimuth = raw->redobs[i].fAzimuth;
                ass.sprintf("%d",raw->redobs[i].cFreq);
                robs.freq = ass.toInt(&ok,10);
                ass.sprintf("%d",raw->redobs[i].ucSvSys);
                robs.sys = ass.toInt(&ok,10);
                if(robs.sys == 1) {
                    robs.prn += 37;
                }
                ass.sprintf("%d",raw->redobs[i].ucSigType);
                robs.type = ass.toInt(&ok,10);

                robs.fCNo = raw->redobs[i].fCNo;
                robs.fLockTime = raw->redobs[i].fLockTime;
                robs.fCMCAvrg = raw->redobs[i].fCMCAvrg;
                robs.fCMCStd = raw->redobs[i].fCMCStd;
                robs.fS4=raw->redobs[i].fS4;
                robs.fS4Correction=raw->redobs[i].fS4Correction;
                robs.f1SecSigma=raw->redobs[i].f1SecSigma;
                robs.f3SecSigma=raw->redobs[i].f3SecSigma;
                robs.f10SecSigma=raw->redobs[i].f10SecSigma;
                robs.f30SecSigma=raw->redobs[i].f30SecSigma;
                robs.f60SecSigma=raw->redobs[i].f60SecSigma;
                robs.ftec=-999.;
                robs.fdtec=-999.;
                // int n=raw->tec_rec.size;
                for(int j=0; j<n; j++)
                {
                    int kka = raw->tec_rec.sat[j];
                    if(raw->tec_rec.sys[j] == 1) {
                        kka += 37;
                    }
                    if(kka == robs.prn)
                    {
                        robs.ftec = raw->tec_rec.tec[j];
                        robs.fdtec = raw->tec_rec.dtec[j];
                    }
                }
                ctx->red_obs.insertMulti(robs.prn,robs);
            }
        }
    }
    if (type == 11){//tecobs
        int n = raw->tec_rec.size;
        double az[2], postpp[2], mapf=0;
        double pos[3];
        double ep[6];
        TEC tec_st;
        time2epoch(raw->obs.data->time, ep);
        tec_st.sec=ep[5];
        tec_st.min=(int)ep[4];
        tec_st.hour=(int)ep[3];
        tec_st.day=(int)ep[2];
        tec_st.mes=(int)ep[1];
        tec_st.year=(int)ep[0];
        BESTPOS currentPosition = ctx->getPosition();
        pos[0]= currentPosition.lat * D2R;
        pos[1]= currentPosition.lon * D2R;
        pos[2] = 0.;

        for(int j=0; j<n; j++) {
            tec_st.az=raw->tec_rec.azim[j];
            tec_st.el=raw->tec_rec.el[j];
            tec_st.n_ka=raw->tec_rec.sat[j];
            if(raw->tec_rec.sys[j] == 1) {
                tec_st.n_ka+=37;
            }
            az[0]=tec_st.az*D2R;
            az[1]=tec_st.el*D2R;
            mapf = ionppp(pos, az, EARTH_RAD, 350., postpp);
            tec_st.lat_pp=postpp[0]*R2D;
            tec_st.lon_pp=postpp[1]*R2D;
            tec_st.lon_st=pos[1];
            tec_st.lat_st=pos[0];
            tec_st.obq=1.;
            if(mapf != 0) {
                tec_st.obq = 1./mapf;
            }
            tec_st.tec = raw->tec_rec.tec[j] * tec_st.obq; /** todo is there VTEC ??? **/
            ctx->tec_tek.insertMulti(tec_st.n_ka,tec_st);
        }

        currentPosition.lat = raw->bestpost[0];
        currentPosition.lon = raw->bestpost[1];
        currentPosition.height = raw->bestpost[2];
        ctx->setPosition(currentPosition);

    }
    if (type == 3) //sbas
    {
        double tau=0.;
        nav_t* nav = ctx->getNav();
        sbsupdatecorr(&raw->sbsmsg, nav);
        const sbsigp_t *p;

        TEC_SBAS tec_s;

        for (int i=0;i<=MAXBAND;i++) {
            for (p = nav->sbsion[i].igp; p < nav->sbsion[i].igp + nav->sbsion[i].nigp; p++) {
                if((p->delay<63) && (p->delay>0))
                {
                    double ep[6];
                    time2epoch(p->t0, ep);
                    int week=0;
                    tau=time2gpst(p->t0,&week);
                    int weeks=(int)tau;
                    tec_s.year=(int)ep[0];
                    tec_s.mes=(int)ep[1];
                    tec_s.day=(int)ep[2];
                    tec_s.hour=(int)ep[3];
                    tec_s.min=(int)ep[4];
                    tec_s.sec=(int)ep[5];
                    tec_s.lat_pp=p->lat;
                    tec_s.lon_pp=p->lon;
                    tec_s.tec=p->delay*6.1417;
                    BESTPOS pose = ctx->getPosition();
                    if((fabs(pose.lat - tec_s.lat_pp) <= 5) && (fabs(pose.lon - tec_s.lon_pp) <=5 )) {
                        ctx->setTecCal(tec_s.tec);
                    }

                    if(p->lon>=0) {
                        weeks = p->lat * 100 + p->lon;
                    }
                    if(p->lon<0) {
                        weeks = (p->lat*100+abs(p->lon)) * -1;
                    }

                    if((ep[1]>0)&&(ep[2]>0)) {
                        ctx->sbas_tec.insert(weeks,tec_s);
                    }
                }
            }
        }
        if(ctx->sbas_tec.count() > 131) {
            ctx->tau_sbas = tau;
        }
    }
}
