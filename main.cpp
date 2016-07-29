#include <iostream>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "CalculateInsertData.cpp"

using namespace std;

class QCTPMdSpi : public CThostFtdcMdSpi
{
    public:
        QCTPMdSpi(CThostFtdcMdApi *pUserApi) : m_pUserApi(pUserApi){}
        ~QCTPMdSpi(){}

    // 当客户端与交易托管系统建立起通信连接,客户端需要进行登录
    virtual void OnFrontConnected()
    {

    // get BrokerID
    cout << "OnFrontConnected:"<<endl;
    CThostFtdcReqUserLoginField reqUserLogin;

    m_pUserApi->ReqUserLogin(&reqUserLogin,0);


    }
    virtual void OnFrontDisconnected()
    {
        cout << "disconnected:" << endl;
    }
    	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspUserLogin:" <<endl;
        cout << "ErrorCode = " <<pRspInfo->ErrorID << " ,ErrorMsg= " <<pRspInfo->ErrorMsg << endl;
        cout << "RequestID= " << nRequestID << " ,Chain= " <<bIsLast << endl;
        if(pRspInfo->ErrorID != 0){
            cout << "Failed to login, errorcode= " <<pRspInfo->ErrorID << " errormsg= " <<pRspInfo->ErrorMsg
                    << " requestid= " << nRequestID << " chain= " << bIsLast << endl;
        }
        cout << "Login success. " << endl;

        char * Instrumnet[] = {"rb1610"};
        m_pUserApi->SubscribeMarketData(Instrumnet,1);
        //m_pUserApi->UnSubscribeMarketData(Instrumnet,1);

	};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspSubMarketData:" << endl;
        cout << "ErrorCode= " <<pRspInfo->ErrorID << " ,ErrorMsg= " <<pRspInfo->ErrorMsg <<endl;
	};





    int index = 0;
    int structNum = 12;
    int historyT = 10;
    vector<CThostFtdcDepthMarketDataField *> dataList;
    float * ptr =(float *) malloc(structNum*historyT*sizeof(float));
    //MyCalculateData * ptr2 = (MyCalculateData *) malloc(historyT*sizeof(MyCalculateData));


    void update(CThostFtdcDepthMarketDataField *pDepthMarketData,float* ptr)
    {
    };

    //void update(vector<CThostFtdcDepthMarketDataField>& data,float* ptr, int m)

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
        dataList.push_back(pDepthMarketData);
        index ++;

        cout << "OnRtnDepthMarketData:" << endl;
        cout <<"TradingDay交易日:"<< pDepthMarketData->TradingDay<< endl;
        cout <<"InstrumentID合约代码:"<<pDepthMarketData->InstrumentID<<endl;
        cout <<"ExchangeID交易所代码:"<<pDepthMarketData->ExchangeID<<endl;
        cout <<"ExchangeInstID合约在交易所的代码:"<<pDepthMarketData->ExchangeInstID<<endl;
        cout <<"LastPrice最新价:"<<pDepthMarketData->LastPrice<<endl;
        cout <<"PreSettlementPrice上次结算价:"<<pDepthMarketData->PreSettlementPrice<<endl;
        cout <<"Volume数量:"<<pDepthMarketData->Volume<<endl;
        cout <<"Turnover成交金额:"<<pDepthMarketData->Turnover<<endl;
        cout <<"UpdateTime最后修改时间:"<<pDepthMarketData->UpdateTime<<endl;
        cout <<"UpdateMillisec最后修改毫秒:"<<pDepthMarketData->UpdateMillisec<<endl;
        cout <<"BidPrice申买价一:"<<pDepthMarketData->BidPrice1<<endl;
        cout <<"BidVolume1申买量一:"<<pDepthMarketData->BidVolume1<<endl;
        cout <<"AskPrice1申卖价一:"<<pDepthMarketData->AskPrice1<<endl;
        cout <<"AskVolume1申卖量一:"<<pDepthMarketData->AskVolume1<<endl;

        cout << index<<"    "<<dataList.size()<<endl;

        updateArray(pDepthMarketData,ptr,10);

    /*
        MyCalculateData * testData = new MyCalculateData();

        MyCalculateData* cell_ptr =  (MyCalculateData*)ptr ;
        testData->Price0 = (pDepthMarketData->LastPrice-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
        testData->MidPrice0 = (pDepthMarketData->BidPrice1+pDepthMarketData->AskPrice1-2*pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
        testData->AveragePrice0 = (pDepthMarketData->Turnover/pDepthMarketData->Volume-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
        testData->BidPrice0 = (pDepthMarketData->BidPrice1-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
        testData->AskPrice0 = (pDepthMarketData->AskPrice1-pDepthMarketData->PreSettlementPrice)/pDepthMarketData->PreSettlementPrice;
        testData->AskVolume0 = pDepthMarketData->AskVolume1;
        testData->BidVolume0 = pDepthMarketData->BidVolume1;
        testData->Volume0 = pDepthMarketData->Volume;

        testData->AskBidRatio0 = testData->AskVolume0/(testData->BidVolume0+testData->BidVolume0);
        testData->TradeRatio0 = testData->Volume0/(testData->BidVolume0+testData->BidVolume0);
        testData->PriceRatio0 = testData->BidPrice0*pDepthMarketData->BidVolume1/(testData->BidPrice0*pDepthMarketData->BidVolume1+testData->AskPrice0*pDepthMarketData->AskVolume1);

        testData->midtemp = (pDepthMarketData->BidPrice1+pDepthMarketData->AskPrice1)/2000;

        cout << "Price0:" << testData->Price0 << endl;
        cout << "MidPrice0:" << testData->MidPrice0 << endl;
        cout << "AveragePrice0:" << testData->AveragePrice0 << endl;
        cout << "BidPrice0:" << testData->BidPrice0 << endl;
        cout << "AskPrice0:" << testData->AskPrice0 << endl;
        cout << "AskVolume0:" << testData->AskVolume0 << endl;
        cout << "BidVolume0:" << testData->BidVolume0 << endl;
        cout << "Volume0:" << testData->Volume0 << endl;
        cout << "AskBidRatio0:" << testData->AskBidRatio0 << endl;
        cout << "TradeRatio0:" << testData->TradeRatio0 << endl;
        cout << "PriceRatio0:" << testData->PriceRatio0 << endl;
        cout << "midtemp:" << testData->midtemp << endl;

        for(int i=0;i<(historyT-1)*structNum;++i){
            ptr[historyT*structNum-i-1] = ptr[historyT*structNum-i-1-structNum];
        }
        */

        /*
        MyCalculateData * testData = new MyCalculateData();
        testData->Price0 = (float) pDepthMarketData->LastPrice /1000;
        testData->MidPrice0 = (float) (pDepthMarketData->BidPrice1 + pDepthMarketData->AskPrice1)/2000;
        testData->AveragePrice0 = (float) pDepthMarketData->Turnover/pDepthMarketData->Volume;  //取整
        testData->BidPrice0 = (float) pDepthMarketData->BidPrice1/1000;
        testData->AskPrice0 = (float) pDepthMarketData->AskPrice1/1000;
        testData->PriceRatio0 = (float) pDepthMarketData->BidPrice1*pDepthMarketData->BidVolume1/(pDepthMarketData->BidPrice1*pDepthMarketData->BidVolume1+pDepthMarketData->AskPrice1*pDepthMarketData->AskVolume1);
        testData->P_T0= (float) pDepthMarketData->BidVolume1/(pDepthMarketData->BidVolume1+pDepthMarketData->AskVolume1);

        cout << "Price0:" << testData->Price0 << endl;
        cout << "MidPrice0:" << testData->MidPrice0 << endl;
        cout << "AveragePrice0:" << testData->AveragePrice0 << endl;
        cout << "BidPrice0:" << testData->BidPrice0 << endl;
        cout << "AskPrice0:" << testData->AskPrice0 << endl;
        cout << "PriceRatio0:" << testData->PriceRatio0 << endl;
        cout << "Price0:" << testData->P_T0 << endl;

        for(int i=0;i<(historyT-1)*structNum;++i){
            ptr[historyT*structNum-i-1] = ptr[historyT*structNum-i-8];
        }

        ptr[0] = testData->Price0;
        ptr[1] = testData->MidPrice0;
        ptr[2] = testData->AveragePrice0;
        ptr[3] = testData->BidPrice0;
        ptr[4] = testData->AskPrice0;
        ptr[5] = testData->PriceRatio0;
        ptr[6] = testData->P_T0;

        for(int i=0;i<historyT;++i){
            for(int j=0;j<structNum;++j){
                cout <<ptr[i*structNum+j] << "  " ;
                //cout << i*structNum+j << " ";
            }
            cout << endl;
        }

*/

        //float * ptr =(float *) malloc(structNum*historyT*sizeof(float));
/*
        CThostFtdcDepthMarketDataField *previousData;
        CThostFtdcDepthMarketDataField *previousTwoData;

        if(index > 2){
                previousData = dataList.at(index - 2);
                previousTwoData = dataList.at(index-3);
                cout << "lalala previos previosTwo" <<endl;
        }


        if(index >2 ){
            MyCalculateData * testData = new MyCalculateData();
            testData->Price0 = pDepthMarketData->LastPrice /1000;
            testData->MidPrice0 = (pDepthMarketData->BidPrice1 + pDepthMarketData->AskPrice1)/2000;
            testData->AveragePrice0 = pDepthMarketData->Turnover/pDepthMarketData->Volume;


        }

/*

	/*
        cout << "OnRtnDepthMarketData:" << endl;
        cout <<"TradingDay:"<< pDepthMarketData->TradingDay<< endl;
        cout <<"InstrumentID:"<<pDepthMarketData->InstrumentID<<endl;
        cout <<"ExchangeID:"<<pDepthMarketData->ExchangeID<<endl;
        cout <<"ExchangeInstID:"<<pDepthMarketData->ExchangeInstID<<endl;
        cout <<"LastPrice:"<<pDepthMarketData->LastPrice<<endl;
        cout <<"PreSettlementPrice:"<<pDepthMarketData->PreSettlementPrice<<endl;
        cout <<"PreClosePrice:"<<pDepthMarketData->PreClosePrice<<endl;
        cout <<"PreOpenInterest:"<<pDepthMarketData->PreOpenInterest<<endl;
        cout <<"OpenPrice:"<<pDepthMarketData->OpenPrice<<endl;
        cout <<"HighestPrice:"<<pDepthMarketData->HighestPrice<<endl;
        cout <<"LowestPrice:"<<pDepthMarketData->LowestPrice<<endl;
        cout <<"Volume:"<<pDepthMarketData->Volume<<endl;
        cout <<"Turnover:"<<pDepthMarketData->Turnover<<endl;
        cout <<"OpenInterest:"<<pDepthMarketData->OpenInterest<<endl;
        cout <<"ClosePrice:"<<pDepthMarketData->ClosePrice<<endl;
        cout <<"SettlementPrice:"<<pDepthMarketData->SettlementPrice<<endl;
        cout <<"UpperLimitPrice:"<<pDepthMarketData->UpperLimitPrice<<endl;
        cout <<"LowerLimitPrice:"<<pDepthMarketData->LowerLimitPrice<<endl;
        cout <<"PreDelta:"<<pDepthMarketData->PreDelta<<endl;
        cout <<"CurrDelta:"<<pDepthMarketData->CurrDelta<<endl;
        cout <<"UpdateTime:"<<pDepthMarketData->UpdateTime<<endl;
        cout <<"UpdateMillisec:"<<pDepthMarketData->UpdateMillisec<<endl;
        cout <<"BidPrice1:"<<pDepthMarketData->BidPrice1<<endl;
        cout <<"BidVolume1:"<<pDepthMarketData->BidVolume1<<endl;
        cout <<"AskPrice1:"<<pDepthMarketData->AskPrice1<<endl;
        cout <<"AskVolume1:"<<pDepthMarketData->AskVolume1<<endl;
        cout <<"BidPrice2:"<<pDepthMarketData->BidPrice2<<endl;
        cout <<"BidVolume2:"<<pDepthMarketData->BidVolume2<<endl;
        cout <<"AskPrice2:"<<pDepthMarketData->AskPrice2<<endl;
        cout <<"AskVolume2:"<<pDepthMarketData->AskVolume2<<endl;
        cout <<"BidPrice3:"<<pDepthMarketData->BidPrice3<<endl;
        cout <<"BidVolume3:"<<pDepthMarketData->BidVolume3<<endl;
        cout <<"AskPrice3:"<<pDepthMarketData->AskPrice3<<endl;
        cout <<"AskVolume3:"<<pDepthMarketData->AskVolume3<<endl;
        cout <<"BidPrice4:"<<pDepthMarketData->BidPrice4<<endl;
        cout <<"BidVolume4:"<<pDepthMarketData->BidVolume4<<endl;
        cout <<"AskPrice4:"<<pDepthMarketData->AskPrice4<<endl;
        cout <<"AskVolume4:"<<pDepthMarketData->AskVolume4<<endl;
        cout <<"BidPrice5:"<<pDepthMarketData->BidPrice5<<endl;
        cout <<"BidVolume5:"<<pDepthMarketData->BidVolume5<<endl;
        cout <<"AskPrice5:"<<pDepthMarketData->AskPrice5<<endl;
        cout <<"AskVolume5:"<<pDepthMarketData->AskVolume5<<endl;
        cout <<"ActionDay:"<<pDepthMarketData->ActionDay<<endl;
        cout <<endl;
        */


        cout << endl;
	};

    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,bool bIsLast)
    {
        cout << "OnRspError!!!!!"<<endl;
    }
    private:
        CThostFtdcMdApi *m_pUserApi;
};


int main()
{
    cout << "Hello world!" << endl;

    CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi("./outfile/",true);
    QCTPMdSpi* pUserSpi = new QCTPMdSpi(pUserApi);
    pUserApi->RegisterSpi(pUserSpi);
    //pUserApi->RegisterFront("tcp://ctp24-front3.financial-trading-platform.com:41213");
    //pUserApi->RegisterFront("tcp://180.169.40.126:21205");
    pUserApi->RegisterFront("tcp://180.168.146.187:10010");
    cout << "before init(): " << endl;
    pUserApi->Init();
    pUserApi->Join();


    cout << "-----" <<endl;

    CThostFtdcReqUserLoginField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,"2011");
    strcpy(req.UserID,"1000022");
    strcpy(req.Password,"1");
    int requestId = 0;
    int ret = pUserApi->ReqUserLogin(&req,++requestId);

    cout << ret;

    return 0;
}
