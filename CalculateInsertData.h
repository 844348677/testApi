#ifndef CALCULATEINSERTDATA_H_INCLUDED
#define CALCULATEINSERTDATA_H_INCLUDED
#include <iostream>

struct MyCalculateData;
void updateArray(CThostFtdcDepthMarketDataField *pDepthMarketData,float* ptr,int historyT);
void updateArray(vector<CThostFtdcDepthMarketDataField>& data,float* ptr, int historyT,int m);

#endif // CALCULATEINSERTDATA_H_INCLUDED
