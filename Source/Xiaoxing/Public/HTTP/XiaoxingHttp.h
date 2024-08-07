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
	
	
	//XIAOXING_API 是一个宏，用来指示编译器导出和导入符号（symbols）的规范
	struct XIAOXING_API FHTTPDelegate
	{
		FHttpRequestCompleteDelegate					SimpleCompleteDelegate;
		FHttpRequestProgressDelegate                    SimpleSingleRequestProgressDelegate;
		FHttpRequestHeaderReceivedDelegate              SimpleSingleRequestHeaderReceivedDelegate;
	};
	
	//TSharedFromThis<FHTTP, ESPMode::ThreadSafe>  线程安全模式
	struct XIAOXING_API FHTTP :public TSharedFromThis<FHTTP>
	{

		static TSharedPtr<FHTTP> CreateHTTPObject(FHTTPDelegate InDelegate);
	
	public:
		FHTTP(FHTTPDelegate InDelegate);

		//向服务器发送HTTP请求
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
		bool bLeaveUnused;//是否闲置
		FHTTPDelegate Delegate;
	};
}