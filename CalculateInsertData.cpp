struct MyCalculateData{
    float Price0;
    float MidPrice0;
    float AveragePrice0;
    float BidPrice0;
    float AskPrice0;
    float AskVolume0;
    float BidVolume0;
    float Volume0;
    float AskBidRatio0;
    float TradeRatio0;
    float PriceRatio0;
    float midtemp;
};

/*
    int structNum = 12;
    int historyT = 10;
    float * ptr =(float *) malloc(structNum*historyT*sizeof(float));
*/
void updateArray(CThostFtdcDepthMarketDataField *pDepthMarketData,float* ptr,int historyT)
{
    int structNum = 12; //struct中的个数

    //数据往后移动
    for(int i=0;i<(historyT-1)*structNum;++i){
            ptr[historyT*structNum-i-1] = ptr[historyT*structNum-i-1-structNum];
    }

    MyCalculateData* cell_ptr =  (MyCalculateData*)ptr ;
    cell_ptr[0].Price0 = (pDepthMarketData->LastPrice-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
    cell_ptr[0].MidPrice0 = (pDepthMarketData->BidPrice1+pDepthMarketData->AskPrice1-2*pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
    cell_ptr[0].AveragePrice0 = (pDepthMarketData->Turnover/pDepthMarketData->Volume-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
    cell_ptr[0].BidPrice0 = (pDepthMarketData->BidPrice1-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
    cell_ptr[0].AskPrice0 = (pDepthMarketData->AskPrice1-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
    cell_ptr[0].AskVolume0 = pDepthMarketData->AskVolume1;
    cell_ptr[0].BidVolume0 = pDepthMarketData->BidVolume1;
    cell_ptr[0].Volume0 = pDepthMarketData->Volume;
    cell_ptr[0].AskBidRatio0 = cell_ptr[0].AskVolume0/(cell_ptr[0].BidVolume0+cell_ptr[0].BidVolume0);
    cell_ptr[0].TradeRatio0 = cell_ptr[0].Volume0/(cell_ptr[0].BidVolume0+cell_ptr[0].BidVolume0);
    cell_ptr[0].PriceRatio0 = cell_ptr[0].BidPrice0*pDepthMarketData->BidVolume1/(cell_ptr[0].BidPrice0*pDepthMarketData->BidVolume1+cell_ptr[0].AskPrice0*pDepthMarketData->AskVolume1);
    cell_ptr[0].midtemp = (pDepthMarketData->BidPrice1+pDepthMarketData->AskPrice1)/2000;


    using namespace std;
        for(int i=0;i<historyT;++i){
            for(int j=0;j<structNum;++j){
                cout <<ptr[i*structNum+j] << "  " ;
                //cout << i*structNum+j << " ";
            }
            cout << endl;
        }

};
