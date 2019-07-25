#include "timer.h"
#include "novtai.h"
const int kmaxbuflen = 40960;
const int kheaderlen = 28;


void setbits(unsigned char *buff, int pos, int len, int data);
void setbitu(unsigned char *buff, int pos, int len, unsigned int data);
void setbitu_r(unsigned char *buff, int pos, int len, unsigned int data);

void setbitfloat(unsigned char *buff, int pos, const float num);
void setbitint(unsigned char *buff, int pos, const int num);
void setbitshort(unsigned char *buff, int pos, const short num);
void setbitdouble(unsigned char *buff, int pos, const double num);
void setbitulong(unsigned char *buff, int pos, const unsigned long num);

void reversal(unsigned char *buff, int pos, int len);
int ConstructLogHeader(unsigned char *, const LogMessHerderBin&,int );

int ConstructBestSats(unsigned char *buf, 
	const LogMessHerderBin& hdmsg, const LOG_BESTSAT& bsatsmsg, int len);

int ConstructDop(unsigned char *buffer, 
	const LogMessHerderBin& headermsg, const LOG_DOP& podmsg, int len);

int ConstructTraceBack(unsigned char *buf,
	const LogMessHerderBin& hdmsg, const LOG_TRACKSTAT& tbmsg,int len);

int ConstructBestPos(unsigned char *buf,
	const LogMessHerderBin& hdmsg, const LOG_BESTPOS& bposmsg, int len);

int ConstructSatVis2(unsigned char *buf,
	const LogMessHerderBin& hdmsg, const LOG_SATVIS2& bsatmsg, int len);

int getbitu(const unsigned char *buff, int pos, int len);

unsigned long CRC32Value(int i);

unsigned long CalculateBlockCRC32(
	unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer); /* Data block */

int convertsatvissys(const int sysnum);

void setbitu_m(unsigned char *buff, int pos, int len, unsigned int data);

int ConstructLogHeader(unsigned char *header, const novatel *msg, int len);
int ConstructDop(unsigned char *buffer, const novatel* msg, int len);
int ConstructTraceBack(unsigned char *buf, const novatel* msg, int len);
int ConstructBestPos(unsigned char *buf, const novatel* msg, int len);
int ConstructBestSats(unsigned char *buf, const novatel* msg, int len);
int ConstructSatVis2(unsigned char *buf, const novatel* msg, int len, int sys);
