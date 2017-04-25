c-----------------------------------------------------------------------        
c MANDATORY SUBROUTINE AS EXTERNAL CALL POINT
c Do initialization and call read_ig_rz, readapf107
c-----------------------------------------------------------------------	
!DEC$ ATTRIBUTES DLLEXPORT :: IRI_INVOKE
        SUBROUTINE IRI_INVOKE(jmag,jf,alati,along,iyyyy,mmdd,iut,dhour,
     &          height,h_tec_max,ivar,vbeg,vend,vstp,outf,oar)
c-----------------------------------------------------------------------        
c input:   jmag,alati,along,iyyyy,mmdd,dhour  see IRI_SUB
c          height  height in km
c          h_tec_max  =0 no TEC otherwise upper boundary for integral
c          iut     =1 for UT       =0 for LT
c          ivar    =1      altitude
c                  =2,3    latitude,longitude
c                  =4,5,6  year,month,day
c                  =7      day of year
c                  =8      hour (UT or LT)
c          vbeg,vend,vstp  variable range (begin,end,step)
c output:  a       similar to outf in IRI_SUB
c          b       similar to oarr in IRI_SUB
c
c          numstp  number of steps; maximal 1000
c-----------------------------------------------------------------------        
        LOGICAL		    rzino,igino
        INTEGER             iyyyy, mmdd, iut, ivar
        DIMENSION   		outf(20,1000),oar(100,1000)
        real*4  alati, along, dhour, height,h_tec_max,vbeg, vend, vstp

        COMMON/const2/icalls,nmono,iyearo,idaynro,rzino,igino,ut0

		icalls=0
		nmono=-1
		iyearo=-1
		idaynro=-1
		rzino=.true.
		igino=.true.
		ut0=-1

        call read_ig_rz
        call readapf107
           
        do 6249 i=1,100
6249    oar(i,1)=-1.0

        PRINT *, "======= year, =", iyyyy
        PRINT *, "======= month and day, =", mmdd
        PRINT *, "======= used UT (LOCAL=0), =", iut
        PRINT *, "======= profile type, =", ivar
        PRINT *, "======= latitude, =", alati
        PRINT *, "======= longitude, =", along
        PRINT *, "======= hour of a day, =", dhour
        PRINT *, "======= height, =", height
        PRINT *, "======= TEC upper boundary, =", h_tec_max
        PRINT *, "======= begin range, =", vbeg
        PRINT *, "======= end range, =", vend
        PRINT *, "======= step range, =", vstp

        call iri_web(jmag,jf,alati,along,iyyyy,mmdd,iut,dhour,
     & height,h_tec_max,ivar,vbeg,vend,vstp,outf,oar)

        return
        end
