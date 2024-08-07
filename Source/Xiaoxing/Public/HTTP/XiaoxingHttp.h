#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "XiaoxingType.h"

namespace XiaoxingHTTP
{
	enum EHTTPVerbType
	{
		XIAOXING_POST,
		XIAOXING_PUT,
		XIAOXING_GET,
	};
	
	
	//XIAOXING_API ��һ���꣬����ָʾ�����������͵�����ţ�symbols���Ĺ淶
	struct XIAOXING_API FHTTPDelegate
	{
		FHttpRequestCompleteDelegate					SimpleCompleteDelegate;
		FHttpRequestProgressDelegate                    SimpleSingleRequestProgressDelegate;
		FHttpRequestHeaderReceivedDelegate              SimpleSingleRequestHeaderReceivedDelegate;
	};
	
	//TSharedFromThis<FHTTP, ESPMode::ThreadSafe>  �̰߳�ȫģʽ
	struct XIAOXING_API FHTTP :public TSharedFromThis<FHTTP>
	{

		static TSharedPtr<FHTTP> CreateHTTPObject(FHTTPDelegate InDelegate);
	
	public:
		FHTTP(FHTTPDelegate InDelegate);

		//�����������HTTP����
	public:
		bool Request(
			const FString& InURL,
			const FString& InContent,
			const TMap<FString,FString> &InCustomMetadataHeader, 
			EHTTPVerbType VerbType = EHTTPVerbType::XIAOXING_POST);

		bool Request(
			const FString& InURL,
			const FXiaoxingCompletionParam& CompletionParam,
			const TMap<FString, FString>& InCustomMetadataHeader,
			EHTTPVerbType VerbType = EHTTPVerbType::XIAOXING_POST);

	public:
		bool IsLeaveUnused() const { return bLeaveUnused; }
		void SetKey(const FString& InKey) { XiaoxingKey = InKey; }

	private:
		void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bsucceeded);
	
	private:
		FString HTTPVerbToString(EHTTPVerbType InVerbType);



	private:
		FString XiaoxingKey;
		bool bLeaveUnused;//�Ƿ�����
		FHTTPDelegate Delegate;
	};
}