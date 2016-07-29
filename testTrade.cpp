#include <iostream>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include <string.h>
#include <stdio.h>
//#include <iomanip>

using namespace std;



class QCTPTraderSpi : public CThostFtdcTraderSpi
{
    public:
        QCTPTraderSpi(CThostFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi){}
        ~QCTPTraderSpi(){}
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){
        cout << "OnFrontConnected:" <<endl;
        CThostFtdcReqUserLoginField reqUserLogin;

        memset(&reqUserLogin,0,sizeof(reqUserLogin));
        strcpy(reqUserLogin.BrokerID,"9999");
        strcpy(reqUserLogin.UserID,"065801");
        strcpy(reqUserLogin.Password,"123456");

        int ret = m_pUserApi->ReqUserLogin(&reqUserLogin,0);
        //	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;


	};


		///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspUserLogin:"<<endl;
        cout << "ErrorCode= " << pRspInfo->ErrorID << " ,ErrorMsg= " << pRspInfo->ErrorMsg << endl;
        cout << "RequestID= " <<nRequestID << " ,Chain= " <<bIsLast << endl;
        if(pRspInfo->ErrorID != 0){
            cout << "Faileed to login,errorcode= " << pRspInfo->ErrorID << " ,errormsg= " <<pRspInfo->ErrorMsg << " requestid= " << nRequestID
            << " ,chian= " << bIsLast << endl;
        }
        cout << "FrontID:" << pRspUserLogin->FrontID <<endl;
        cout << "SessionID:"<<pRspUserLogin->SessionID <<endl;
        cout << "MaxOrderRef:"<<pRspUserLogin->MaxOrderRef <<endl;
        CThostFtdcQryTradingAccountField pTradingAccount;
        memset(&pTradingAccount,0,sizeof(pTradingAccount));
        strcpy(pTradingAccount.BrokerID,"9999");
        strcpy(pTradingAccount.InvestorID,"065801");
        //m_pUserApi->ReqQryTradingAccount(&pTradingAccount,0);

        CThostFtdcQrySettlementInfoField pQrySettlementInfo;
        strcpy(pQrySettlementInfo.BrokerID,"9999");
        strcpy(pQrySettlementInfo.InvestorID,"065801");
        strcpy(pQrySettlementInfo.TradingDay,"20160720");
        //m_pUserApi->ReqQrySettlementInfo(&pQrySettlementInfo,0);
        //测试下单
        CThostFtdcInputOrderField ord;
        memset(&ord,0,sizeof(ord));
        strcpy(ord.BrokerID,"9999");
        strcpy(ord.InvestorID,"065801");
        strcpy(ord.InstrumentID,"rb1610");
        //strcpy(ord.OrderRef,"000000000001");
        //strcpy(ord.UserID,"065801");
        ord.OrderPriceType=THOST_FTDC_OPT_LimitPrice;
        ord.Direction = THOST_FTDC_D_Buy;
        strcpy(ord.CombOffsetFlag,"0");
        strcpy(ord.CombHedgeFlag,"1");
        ord.LimitPrice=2400;
        ord.VolumeTotalOriginal=1;
        ord.TimeCondition=THOST_FTDC_TC_GFD;
        strcpy(ord.GTDDate,"");
        ord.VolumeCondition=THOST_FTDC_VC_AV;
        ord.MinVolume=0;
        ord.ContingentCondition=THOST_FTDC_CC_Immediately;
        ord.StopPrice=0;
        ord.ForceCloseReason=THOST_FTDC_FCC_NotForceClose;
        ord.IsAutoSuspend=0;
        m_pUserApi->ReqOrderInsert(&ord,1);

        CThostFtdcInputForQuoteField pInputForQuote;
        strcpy(pInputForQuote.BrokerID,"9999");
        strcpy(pInputForQuote.InvestorID,"065801");
        strcpy(pInputForQuote.InstrumentID,"if1608");
        //m_pUserApi->ReqForQuoteInsert(&pInputForQuote,5);

        CThostFtdcQryOrderField pQryOrder;
       // strcpy(pQryOrder.InsertTimeStart,"20160722");
        //strcpy(pQryOrder.InsertTimeEnd,"20160722");
        //m_pUserApi->ReqQryOrder(&pQryOrder, 0); //报单查询请求


        CThostFtdcQryTradeField pQryTrade;
        //m_pUserApi->ReqQryTrade(&pQryTrade,0);//成交单查询请求。

        CThostFtdcQryInvestorField pQryInvestor;
        //m_pUserApi->ReqQryInvestor(&pQryInvestor,0); //会员客户查询请求。

        CThostFtdcQryTradingCodeField pQryTradingCode;
        //m_pUserApi->ReqQryTradingCode(&pQryTradingCode,0); //请求查询交易编码。

        CThostFtdcQryInvestorPositionField pQryInvestorPosition;
        //m_pUserApi->ReqQryInvestorPosition(&pQryInvestorPosition,0); //会员持仓查询请求。

        CThostFtdcQryExchangeField pQryExchange;
        //m_pUserApi->ReqQryExchange(&pQryExchange,0);    //请求查询合约。




	};

		///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "!!!!!!!!!!!!!!!1" <<endl;
        cout << "OnRspOrderInsert:" << endl;
        cout << "BrokerID:"<<pInputOrder->BrokerID << endl;
        cout << "InvestorID:"<<pInputOrder->InvestorID << endl;

	};
	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {
        cout << "OnRtnOrder:"<<endl;

	};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {
        cout << "OnRtnTrade:" << endl;
	};

		///请求查询交易所响应
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryExchange:" << endl;
        cout << "ExchangeID:" << pExchange->ExchangeID << endl;
        cout << "ExchangeName:" << pExchange->ExchangeName << endl;
        cout << "ExchangeProperty:" << pExchange->ExchangeProperty << endl;
        cout <<endl;
	};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryInvestorPosition"<< endl;
        cout << "InstrumentID:" << pInvestorPosition->InstrumentID << endl;
        cout << "BrokerID:" << pInvestorPosition->BrokerID << endl;
        cout << "InvestorID:" << pInvestorPosition->InvestorID << endl;
        cout << "PosiDirection:" << pInvestorPosition->PosiDirection << endl;
        cout << "HedgeFlag:" << pInvestorPosition->HedgeFlag << endl;
        cout << "PositionDate:" << pInvestorPosition->PositionDate << endl;
        cout << "YdPosition:" << pInvestorPosition->YdPosition << endl;
        cout << "Position:" << pInvestorPosition->Position << endl;
        cout << "LongFrozen:" << pInvestorPosition->LongFrozen << endl;
        cout << "ShortFrozen:" << pInvestorPosition->ShortFrozen << endl;
        cout << "LongFrozenAmount:" << pInvestorPosition->LongFrozenAmount << endl;
        cout << "ShortFrozenAmount:" << pInvestorPosition->ShortFrozenAmount << endl;
        cout << "OpenVolume:" << pInvestorPosition->OpenVolume << endl;
        cout << "CloseVolume:" << pInvestorPosition->CloseVolume << endl;
        cout << "OpenAmount:" << pInvestorPosition->OpenAmount << endl;
        cout << "CloseAmount:" << pInvestorPosition->CloseAmount << endl;
        cout << "PositionCost:" << pInvestorPosition->PositionCost << endl;
        cout << "PreMargin:" << pInvestorPosition->PreMargin << endl;
        cout << "UseMargin:" << pInvestorPosition->UseMargin << endl;
        cout << "FrozenMargin:" << pInvestorPosition->FrozenMargin << endl;
        cout << "FrozenCash:" << pInvestorPosition->FrozenCash << endl;
        cout << "FrozenCommission:" << pInvestorPosition->FrozenCommission << endl;
        cout << "CashIn:" << pInvestorPosition->CashIn << endl;
        cout << "Commission:" << pInvestorPosition->Commission << endl;
        cout << "CloseProfit:" << pInvestorPosition->CloseProfit << endl;
        cout << "PositionProfit:" << pInvestorPosition->PositionProfit << endl;
        cout << "PreSettlementPrice:" << pInvestorPosition->PreSettlementPrice << endl;
        cout << "SettlementPrice:" << pInvestorPosition->SettlementPrice << endl;
        cout << "TradingDay:" << pInvestorPosition->TradingDay << endl;
        cout << "OpenCost:" << pInvestorPosition->OpenCost << endl;
        cout << "ExchangeMargin:" << pInvestorPosition->ExchangeMargin << endl;
        cout << "CombPosition:" << pInvestorPosition->CombPosition << endl;
        cout << "CombLongFrozen:" << pInvestorPosition->CombLongFrozen << endl;
        cout << "CombShortFrozen:" << pInvestorPosition->CombShortFrozen << endl;
        cout << "CloseProfitByDate:" << pInvestorPosition->CloseProfitByDate << endl;
        cout << "CloseProfitByTrade:" << pInvestorPosition->CloseProfitByTrade << endl;
        cout << "TodayPosition:" << pInvestorPosition->TodayPosition << endl;
        cout << "MarginRateByMoney:" << pInvestorPosition->MarginRateByMoney << endl;
        cout << "MarginRateByVolume:" << pInvestorPosition->MarginRateByVolume << endl;
        cout << "StrikeFrozen:" << pInvestorPosition->StrikeFrozen << endl;
        cout << "StrikeFrozenAmount:" << pInvestorPosition->StrikeFrozenAmount << endl;
        cout << "AbandonFrozen:" << pInvestorPosition->AbandonFrozen << endl;

        cout << endl;
	};


	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryTradingCode:" << endl;
        cout <<"InvestorID:"<<pTradingCode->InvestorID << endl;
        cout <<"BrokerID:"<<pTradingCode->BrokerID << endl;
        cout <<"ExchangeID:"<<pTradingCode->ExchangeID << endl;
        cout <<"ClientID:"<<pTradingCode->ClientID << endl;
        cout <<"IsActive:"<<pTradingCode->IsActive << endl;
        cout <<"ClientIDType:"<<pTradingCode->ClientIDType << endl;

        cout << endl;
	};



	///请求查询投资者响应
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryInvestor:" << endl;
        cout << "InvestorID:" <<pInvestor->InvestorID  << endl;
        cout << "BrokerID:" <<pInvestor->BrokerID  << endl;
        cout << "InvestorGroupID:" <<pInvestor->InvestorGroupID  << endl;
        cout << "InvestorName:" <<pInvestor->InvestorName  << endl;
        cout << "IdentifiedCardType:" <<pInvestor->IdentifiedCardType  << endl;
        cout << "IdentifiedCardNo:" <<pInvestor->IdentifiedCardNo  << endl;
        cout << "IsActive:" <<pInvestor->IsActive  << endl;
        cout << "Telephone:" <<pInvestor->Telephone  << endl;
        cout << "Address:" <<pInvestor->Address  << endl;
        cout << "OpenDate:" <<pInvestor->OpenDate  << endl;
        cout << "Mobile:" <<pInvestor->Mobile  << endl;
        cout << "CommModelID:" <<pInvestor->CommModelID  << endl;
        cout << "MarginModelID:" <<pInvestor->MarginModelID  << endl;

        cout << endl;
	};


	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryTrade:" <<endl;
        cout << "BrokerID:" << pTrade->BrokerID << endl;
        cout << "InvestorID:" << pTrade->InvestorID << endl;
        cout << "InstrumentID:" << pTrade->InstrumentID << endl;
        cout << "OrderRef:" << pTrade->OrderRef << endl;
        cout << "UserID:" << pTrade->UserID << endl;
        cout << "ExchangeID:" << pTrade->ExchangeID << endl;
        cout << "TradeID:" << pTrade->TradeID << endl;
        cout << "OrderSysID:" << pTrade->OrderSysID << endl;
        cout << "ParticipantID:" << pTrade->ParticipantID << endl;
        cout << "ClientID:" << pTrade->ClientID << endl;
        cout << "TradingRole:" << pTrade->TradingRole << endl;
        cout << "ExchangeInstID:" << pTrade->ExchangeInstID << endl;
        cout << "OffsetFlag:" << pTrade->OffsetFlag << endl;
        cout << "HedgeFlag:" << pTrade->HedgeFlag << endl;
        cout << "Price:" << pTrade->Price << endl;
        cout << "Volume:" << pTrade->Volume << endl;
        cout << "TradeDate:" << pTrade->TradeDate << endl;
        cout << "TradeTime:" << pTrade->TradeTime << endl;
        cout << "TradeType:" << pTrade->TradeType << endl;
        cout << "PriceSource:" << pTrade->PriceSource << endl;
        cout << "TraderID:" << pTrade->TraderID << endl;
        cout << "OrderLocalID:" << pTrade->OrderLocalID << endl;
        cout << "ClearingPartID:" << pTrade->ClearingPartID << endl;
        cout << "BusinessUnit:" << pTrade->BusinessUnit << endl;
        cout << "SequenceNo:" << pTrade->SequenceNo << endl;
        cout << "TradingDay:" << pTrade->TradingDay << endl;
        cout << "SettlementID:" << pTrade->SettlementID << endl;
        cout << "BrokerOrderSeq:" << pTrade->BrokerOrderSeq << endl;
        cout << "TradeSource:" << pTrade->TradeSource << endl;

        cout << endl;

    };



	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryOrder" <<endl;
        cout << "nRequestID:" << nRequestID<<endl;;
        cout <<  "InvestorID:" << pOrder->InvestorID << endl;
        cout <<  "InstrumentID:" << pOrder->InstrumentID << endl;
        cout <<  "OrderRef:" << pOrder->OrderRef << endl;
        cout <<  "UserID:" << pOrder->UserID << endl;
        cout <<  "OrderPriceType:" << pOrder->OrderPriceType << endl;
        cout <<  "Direction:" << pOrder->Direction << endl;
        cout <<  "CombOffsetFlag:" << pOrder->CombOffsetFlag << endl;
        cout <<  "CombHedgeFlag:" << pOrder->CombHedgeFlag << endl;
        cout <<  "LimitPrice:" << pOrder->LimitPrice << endl;
        cout <<  "VolumeTotalOriginal:" << pOrder->VolumeTotalOriginal << endl;
        cout <<  "TimeCondition:" << pOrder->TimeCondition << endl;
        cout <<  "GTDDate:" << pOrder->GTDDate << endl;
        cout <<  "VolumeCondition:" << pOrder->VolumeCondition << endl;
        cout <<  "MinVolume:" << pOrder->MinVolume << endl;
        cout <<  "ContingentCondition:" << pOrder->ContingentCondition << endl;
        cout <<  "StopPrice:" << pOrder->StopPrice << endl;
        cout <<  "ForceCloseReason:" << pOrder->ForceCloseReason << endl;
        cout <<  "IsAutoSuspend:" << pOrder->IsAutoSuspend << endl;
        cout <<  "BusinessUnit:" << pOrder->BusinessUnit << endl;
        cout <<  "RequestID:" << pOrder->RequestID << endl;
        cout <<  "OrderLocalID:" << pOrder->OrderLocalID << endl;
        cout <<  "ExchangeID:" << pOrder->ExchangeID << endl;
        cout <<  "ParticipantID:" << pOrder->ParticipantID << endl;
        cout <<  "ClientID:" << pOrder->ClientID << endl;
        cout <<  "ExchangeInstID:" << pOrder->ExchangeInstID << endl;
        cout <<  "TraderID:" << pOrder->TraderID << endl;
        cout <<  "InstallID:" << pOrder->InstallID << endl;
        cout <<  "OrderSubmitStatus:" << pOrder->OrderSubmitStatus << endl;
        cout <<  "NotifySequence:" << pOrder->NotifySequence << endl;
        cout <<  "TradingDay:" << pOrder->TradingDay << endl;
        cout <<  "SettlementID:" << pOrder->SettlementID << endl;
        cout <<  "OrderSysID:" << pOrder->OrderSysID << endl;
        cout <<  "OrderSource:" << pOrder->OrderSource << endl;
        cout <<  "OrderStatus:" << pOrder->OrderStatus << endl;
        cout <<  "OrderType:" << pOrder->OrderType << endl;
        cout <<  "VolumeTraded:" << pOrder->VolumeTraded << endl;
        cout <<  "VolumeTotal:" << pOrder->VolumeTotal << endl;
        cout <<  "InsertDate:" << pOrder->InsertDate << endl;
        cout <<  "InsertTime:" << pOrder->InsertTime << endl;
        cout <<  "ActiveTime:" << pOrder->ActiveTime << endl;
        cout <<  "SuspendTime:" << pOrder->SuspendTime << endl;
        cout <<  "UpdateTime:" << pOrder->UpdateTime << endl;
        cout <<  "CancelTime:" << pOrder->CancelTime << endl;
        cout <<  "ActiveTraderID:" << pOrder->ActiveTraderID << endl;
        cout <<  "ClearingPartID:" << pOrder->ClearingPartID << endl;
        cout <<  "SequenceNo:" << pOrder->SequenceNo << endl;
        cout <<  "FrontID:" << pOrder->FrontID << endl;
        cout <<  "SessionID:" << pOrder->SessionID << endl;
        cout <<  "UserProductInfo:" << pOrder->UserProductInfo << endl;
        cout <<  "StatusMsg:" << pOrder->StatusMsg << endl;
        cout <<  "UserForceClose:" << pOrder->UserForceClose << endl;
        cout <<  "ActiveUserID:" << pOrder->ActiveUserID << endl;
        cout <<  "BrokerOrderSeq:" << pOrder->BrokerOrderSeq << endl;
        cout <<  "RelativeOrderSysID:" << pOrder->RelativeOrderSysID << endl;
        cout <<  "ZCETotalTradedVolume:" << pOrder->ZCETotalTradedVolume << endl;
        cout <<  "IsSwapOrder:" << pOrder->IsSwapOrder << endl;
        cout <<  "BranchID:" << pOrder->BranchID << endl;
        cout <<  "InvestUnitID:" << pOrder->InvestUnitID << endl;
        cout <<  "AccountID:" << pOrder->AccountID << endl;
        cout <<  "CurrencyID:" << pOrder->CurrencyID << endl;
        cout <<  "IPAddress:" << pOrder->IPAddress << endl;
        cout <<  "MacAddress:" << pOrder->MacAddress << endl;

        cout << endl;
	};


	///询价录入请求响应
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspForQuoteInsert" <<endl;
        /*
        ///输入的询价
struct CThostFtdcInputForQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///询价引用
	TThostFtdcOrderRefType	ForQuoteRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
};
        */
        cout << "BrokerID:" <<pInputForQuote->BrokerID<<endl;
        cout << "InvestorID:" <<pInputForQuote->InvestorID <<endl;
        cout << "InstrumentID:" <<pInputForQuote->InstrumentID <<endl;
        cout << "ForQuoteRef:" <<pInputForQuote->ForQuoteRef <<endl;
        cout << "UserID:" <<pInputForQuote->UserID <<endl;
        cout << "ExchangeID:" <<pInputForQuote->ExchangeID <<endl;
        cout << "InvestUnitID:" <<pInputForQuote->InvestUnitID <<endl;
        cout << "IPAddress:" <<pInputForQuote->IPAddress <<endl;
        cout << "MacAddress:" <<pInputForQuote->MacAddress <<endl;
	};


	///预埋单录入请求响应
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspParkedOrderInsert"<<endl;
	};

		///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	/*
	///投资者结算结果
struct CThostFtdcSettlementInfoField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///消息正文
	TThostFtdcContentType	Content;
};
	*/
        cout << "OnRspQrySettlementInfo" <<endl;

        cout <<"TradingDay:" << pSettlementInfo->TradingDay<<endl;
        /*        cout <<"SettlementID:" << pSettlementInfo->SettlementID<<endl;
        cout <<"BrokerID:" << pSettlementInfo->BrokerID<<endl;
        cout <<"InvestorID:" << pSettlementInfo->InvestorID<<endl;
        cout <<"SequenceNo:" << pSettlementInfo->SequenceNo<<endl;
        cout <<"Content:" << pSettlementInfo->Content<<endl;
        */
	};


		///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspQryTradingAccount:" << endl;
        /*
        cout << "ErrorCode= " << pRspInfo->ErrorID << " ,ErrorMsg= " << pRspInfo->ErrorMsg << endl;
        cout << "RequestID= " <<nRequestID << " ,Chain= " <<bIsLast << endl;

        if(pRspInfo->ErrorID != 0){
            cout << "Faileed to login,errorcode= " << pRspInfo->ErrorID << " ,errormsg= " <<pRspInfo->ErrorMsg << " requestid= " << nRequestID
            << " ,chian= " << bIsLast << endl;
        }
        */
        cout << "BrokerID:"<< pTradingAccount->BrokerID << endl;
        cout << "AccountID:"<< pTradingAccount->AccountID << endl;
        cout << "PreMortgage:"<< pTradingAccount->PreMortgage << endl;
        cout << "PreCredit:"<< pTradingAccount->PreCredit << endl;
        cout << "PreDeposit:"<< pTradingAccount->PreDeposit << endl;
        cout << "PreBalance:"<< pTradingAccount->PreBalance << endl;
        cout << "PreMargin:"<< pTradingAccount->PreMargin << endl;
        cout << "InterestBase:"<< pTradingAccount->InterestBase << endl;
        cout << "Interest:"<< pTradingAccount->Interest << endl;
        cout << "Deposit:"<< pTradingAccount->Deposit << endl;
        cout << "Withdraw:"<< pTradingAccount->Withdraw << endl;
        cout << "FrozenMargin:"<< pTradingAccount->FrozenMargin << endl;
        cout << "FrozenCash:"<< pTradingAccount->FrozenCash << endl;
        cout << "FrozenCommission:"<< pTradingAccount->FrozenCommission << endl;
        cout << "CurrMargin:"<< pTradingAccount->CurrMargin << endl;
        cout << "CashIn:"<< pTradingAccount->CashIn << endl;
        cout << "Commission:"<< pTradingAccount->Commission << endl;
        cout << "CloseProfit:"<< pTradingAccount->CloseProfit << endl;
        cout << "PositionProfit:"<< pTradingAccount->PositionProfit << endl;
        cout << "Balance:"<< pTradingAccount->Balance << endl;
        cout << "Available:"<< pTradingAccount->Available << endl;
        cout << "WithdrawQuota:"<< pTradingAccount->WithdrawQuota << endl;
        cout << "Reserve:"<< pTradingAccount->Reserve << endl;
        cout << "TradingDay:"<< pTradingAccount->TradingDay << endl;
        cout << "SettlementID:"<< pTradingAccount->SettlementID << endl;
        cout << "Credit:"<< pTradingAccount->Credit << endl;
        cout << "Mortgage:"<< pTradingAccount->Mortgage << endl;
        cout << "ExchangeMargin:"<< pTradingAccount->ExchangeMargin << endl;
        cout << "DeliveryMargin:"<< pTradingAccount->DeliveryMargin << endl;
        cout << "ExchangeDeliveryMargin:"<< pTradingAccount->ExchangeDeliveryMargin << endl;
        cout << "ReserveBalance:"<< pTradingAccount->ReserveBalance << endl;
        cout << "CurrencyID:"<< pTradingAccount->CurrencyID << endl;
        cout << "PreFundMortgageIn:"<< pTradingAccount->PreFundMortgageIn << endl;
        cout << "PreFundMortgageOut:"<< pTradingAccount->PreFundMortgageOut << endl;
        cout << "FundMortgageIn:"<< pTradingAccount->FundMortgageIn << endl;
        cout << "FundMortgageOut:"<< pTradingAccount->FundMortgageOut << endl;
        cout << "FundMortgageAvailable:"<< pTradingAccount->FundMortgageAvailable << endl;
        cout << "MortgageableFund:"<< pTradingAccount->MortgageableFund << endl;
        cout << "SpecProductMargin:"<< pTradingAccount->SpecProductMargin << endl;
        cout << "SpecProductFrozenMargin:"<< pTradingAccount->SpecProductFrozenMargin << endl;
        cout << "SpecProductCommission:"<< pTradingAccount->SpecProductCommission << endl;
        cout << "SpecProductFrozenCommission:"<< pTradingAccount->SpecProductFrozenCommission << endl;
        cout << "SpecProductPositionProfit:"<< pTradingAccount->SpecProductPositionProfit << endl;
        cout << "SpecProductCloseProfit:"<< pTradingAccount->SpecProductCloseProfit << endl;
        cout << "SpecProductPositionProfitByAlg:"<< pTradingAccount->SpecProductPositionProfitByAlg << endl;
        cout << "SpecProductExchangeMargin:"<< pTradingAccount->SpecProductExchangeMargin << endl;




	};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "OnRspError:"<<endl;
        cout << "ErrorCode= " << pRspInfo->ErrorID << " ,ErrorMsg= " << pRspInfo->ErrorMsg << endl;
        cout << "RequestID= " <<nRequestID << " ,Chain= " <<bIsLast << endl;
	};

    private:
        CThostFtdcTraderApi *m_pUserApi;
};


int main6()
{
    cout << "Hello world!" << endl;

    CThostFtdcTraderApi* pUserTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./outfile/");
    QCTPTraderSpi* pUserTraderSpi = new QCTPTraderSpi(pUserTraderApi);
    pUserTraderApi->RegisterSpi(pUserTraderSpi);
    pUserTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);
    pUserTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);

    //pUserApi->RegisterFront("tcp://ctp24-front3.financial-trading-platform.com:41213");
    pUserTraderApi->RegisterFront("tcp://180.168.146.187:10000");
    //pUserApi->RegisterFront("tcp://180.169.40.126:21213");
    pUserTraderApi->Init();
    pUserTraderApi->Join();


    cout << "-----" <<endl;
    /*
        CThostFtdcReqUserLoginField req;
        memset(&req,0,sizeof(req));
        strcpy(req.BrokerID,"2011");
        strcpy(req.UserID,"1000022");
        strcpy(req.Password,"1");
        int requestId = 0;
        int ret = pUserApi->ReqUserLogin(&req,++requestId);

        cout << ret;
    */
    return 0;
}
