#include <iostream>
#include "serial.h"

void GetHeaderDOP(LogMessHerderBin& hd_msg);
void GetHeaderSatvis2(LogMessHerderBin& hd_msg);
void GetHeaderBestsats(LogMessHerderBin& hd_msg);
void GetHeaderTrackstat(LogMessHerderBin& hd_msg);
void GetHeaderBestpos(LogMessHerderBin& hd_msg);




void GetDop(LOG_DOP& dop_msg);
void GetSatvis2(LOG_SATVIS2& satvis2_msg);
void GetBestsats(LOG_BESTSAT& bestsats_msg);
void GetTrackstat(LOG_TRACKSTAT& bestsats_msg);
void GetBestpos(LOG_BESTPOS& bestsats_msg);



int GenerateDop(unsigned char *buf);
int GenerateSatvis2(unsigned char *buf);
int GenerateBestsats(unsigned char *buf);
int GenerateBestpos(unsigned char *buf);
int GenerateTrackstat(unsigned char *buf);



int GetNovetal_data(novatel& nov_data);
