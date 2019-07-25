#include <intsafe.h>
#pragma pack(1)

#ifndef __NOVTALDEF__
#define __NOVTALDEF__

#define MY_MAXSATS_ALL 60

typedef struct sat_data
{
	unsigned int sys;//GPS:0 GLO:1 GLA:5 BD:6
	unsigned int prn;
	double 	     elev;
	double 		 az;
	float		 cno[2];//SNR
	UINT32		 status;//health:0 
};


typedef struct novatel
{
	UINT32				msg_id;
	UINT32				msg_len;
	UINT16 				gpsWeek;
	UINT32 				gpsSow;
	double 				lat;
	double 				lon;
	double 				hgt;
	float				solAge;
	float				dulation;
	unsigned char		nSVs;
	unsigned char 		nSolSvs;
	float				gdop;
	float				hdop;
	unsigned int		satnum[4];
	sat_data			sat[4][50];
};


typedef struct
{
	char 	sync1;
	char 	sync2;
	char 	sync3;
	UINT8 	headLen;
	UINT16 	msgID;
	char 	reserved1;
	char 	port;
	UINT16 	msgLen;
	UINT16 	reserved2;
	char 	reserved3;
	char 	reserved4;
	UINT16 	gpsWeek;
	UINT32 	gpsSow;
	UINT32	reserved5;
	UINT16 	reserved6;
	UINT16 	reserved7;

}LogMessHerderBin;	// 28Byte


typedef struct
{
	LogMessHerderBin	header;
	UINT32 				solStatus;
	UINT32 				posType;
	double 				lat;
	double 				lon;
	double 				hgt;
	float				dulation;
	UINT32				datumID;
	float				latSigma;
	float				lonSigma;
	float				hgtSigma;
	char				stnID[4];
	float				diffAge;
	float				solAge;
	unsigned char		nSVs;
	unsigned char 		nSolSvs;
	unsigned char		nL1SVs;
	unsigned char 		nL1L2Svs;
	char 				reserved1;
	char 				reserved2;
	char 				reserved3;
	unsigned char		solSignal;

}LOG_BESTPOS;	// 72 Byte


typedef struct
{
	UINT16 		prn;
	UINT16 		glofreq;
	UINT32 		chTrStatus;
	double 		psr;
	float  		doppler;
	float  		cno;
	float  		locktime;
	float 		psrRes;
	UINT32 		reject;
	float  		psrWeight;

}TRACKSTAT_CHANS;

typedef struct
{
	LogMessHerderBin	header;
	UINT32 				solStatus;
	UINT32 				posType;
	float  				cutoff;
	UINT32 				chanNum;
	TRACKSTAT_CHANS 	chan[300];

}LOG_TRACKSTAT;



typedef struct     //DOP values
{
    LogMessHerderBin	header;
	float gdop;
	float pdop;
	float hdop;
	float htdop;
	float tdop;
	float elev_mask;
	UINT32 nsats;
	UINT32 cal_sats[MY_MAXSATS_ALL];

}LOG_DOP;



typedef struct
{
	UINT32  sys;
	UINT16	sat_id_low;
	UINT16	sat_id_high;
	UINT32  status;
	UINT32  signal_mask;
}BEST_SAT;


typedef struct
{
	LogMessHerderBin	header;
	UINT32	entries;
	BEST_SAT    sat[MY_MAXSATS_ALL];
}LOG_BESTSAT;


typedef struct
{
	UINT16				sat_id_low;
	UINT16				sat_id_high;
	UINT32				health;
	double 				elev;
	double 				az;
	double 				true_dop;
	double 				app_dop;
}SATVIS2_SAT;

typedef struct
{
	LogMessHerderBin	header;
	UINT32 				sat_sys;
	UINT32 				sat_vis;
	UINT32				comp_alm;
	UINT32              sat_number;
	SATVIS2_SAT         sat[MY_MAXSATS_ALL];
}LOG_SATVIS2;

typedef union Double2Bin
{
	double double_num;
	char char_num[8];
};

typedef union Float2Bin
{
	float float_num;
	char char_num[4];
};

typedef union INT2Bin
{
	int int_num;
	char char_num[4];
}; 

typedef union ULONG2Bin
{
	unsigned long ulong_num;
	char char_num[4];
};


typedef union SHORT2Bin
{
	UINT16 int_num;
	char char_num[4];
}; 

typedef union Char2Bin
{
	UINT8 int_unit8;
	char char_num[1];
};


#endif