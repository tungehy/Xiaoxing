#include "HTTP/XiaoxingHttp.h"
#include "Core/XiaoxingMethod.h"

namespace XiaoxingHTTP
{

	FHTTP::FHTTP(FHTTPDelegate InDelegate)
		:Delegate(InDelegate)
	{
		bLeaveUnused = true;
	}

	TSharedPtr<FHTTP> FHTTP::CreateHTTPObject(FHTTPDelegate InDelegate)
	{
		return MakeShareable(new FHTTP(InDelegate));
	}


	bool FHTTP::Request(
		const FString& InURL, 
		const FString& InContent, 
		const TMap<FString, FString>& InCustomMetadataHeader, 
		EHTTPVerbType VerbType)
	{
		if (!XiaoxingKey.IsEmpty())
		{


			if (bLeaveUnused)
			{
				bLeaveUnused = false;
				
				//url = http://180.208.58.128:31696/api/v1/public/kbBot/{助手标识ID}/chat
				TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
				Request->SetURL(InURL);

				Request->SetHeader(TEXT("Content-Type"),FString("application/json"));
				Request->SetHeader(TEXT("x-public-token"), FString(*XiaoxingKey));
				//Request->SetHeader(TEXT("x-public-token"), FString::Printf(TEXT("Bearer %s"),*XiaoxingKey));
				//Authorization 头部  Bearer %s openaikey格式
				
				for (auto &Tmp : InCustomMetadataHeader)
				{
					Request->SetHeader(Tmp.Key, Tmp.Value);
				}

				//用VerbType枚举来描述当前动作（POST、GET等）
				Request->SetVerb(HTTPVerbToString(VerbType));
				
				Request->SetContentAsString(InContent);

				Request->OnProcessRequestComplete().BindSP(this, &FHTTP::OnRequestComplete);

				return Request->ProcessRequest();
			}
		}

		return false;
	}

	FString FHTTP::HTTPVerbToString(EHTTPVerbType InVerbType)
	{
		switch (InVerbType)
		{
		case XiaoxingHTTP::XIAOXING_POST:
			return TEXT("POST");
		case XiaoxingHTTP::XIAOXING_PUT:
			return TEXT("PUT");
		case XiaoxingHTTP::XIAOXING_GET:
			return TEXT("GET");

		}
		return TEXT("POST");
	}

	void FHTTP::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bsucceeded)
	{
		bLeaveUnused = true;

		Delegate.SimpleCompleteDelegate.ExecuteIfBound(HttpRequest, HttpResponse, bsucceeded);
	}

	bool FHTTP::Request(
		const FString& InURL,
		const FXiaoxingCompletionParam& InCompletionParam,
		const TMap<FString, FString>& InCustomMetadataHeader,
		EHTTPVerbType VerbType)
	{
		FString ParamJson;
		XiaoxingMethod::XiaoxingCompletionParamToString(InCompletionParam, ParamJson);

		return Request(InURL,ParamJson,InCustomMetadataHeader,VerbType);
	}

}