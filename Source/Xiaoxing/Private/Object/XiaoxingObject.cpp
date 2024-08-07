#include "Object/XiaoxingObject.h"
#include "Core/XiaoxingMethod.h"

UXiaoxingObject::UXiaoxingObject()
{

}

void UXiaoxingObject::InitXiaoxing()
{
	XiaoxingHTTP::FHTTPDelegate HTTPDelegate;
	HTTPDelegate.SimpleCompleteDelegate.BindLambda(
	[&](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bsucceeded)
	{
		OnRequestComplete(HttpRequest, HttpResponse, bsucceeded);
	});

	HTTP = XiaoxingHTTP::FHTTP::CreateHTTPObject(HTTPDelegate);
}

UXiaoxingObject* UXiaoxingObject::CreateObject(UObject* WorldContextObject,UClass* InClass, UObject* InParent)
{
	check(WorldContextObject != NULL);

	UClass* MyClass = InClass;
	if (!InClass)
	{
		MyClass = UXiaoxingObject::StaticClass();
	}

	if (InParent)
	{
		if (UXiaoxingObject* Obj = NewObject<UXiaoxingObject>(InParent, MyClass))
		{
			Obj->InitXiaoxing();

			return Obj;
		}
	}
	else
	{
		if (UXiaoxingObject* Obj = NewObject<UXiaoxingObject>(WorldContextObject, MyClass))
		{
			Obj->InitXiaoxing();

			return Obj;
		}
	}
	
	
	return NULL;
}

//InURL地址、InContent需要发送的内容、InCustomMetadataHeader自定义元数据
bool UXiaoxingObject::Request(
	const FString& InURL,
	const FString& InContent,
	const TMap<FString, FString>& InCustomMetadataHeader)
{
	return HTTP->Request(InURL, InContent, InCustomMetadataHeader);
}

bool UXiaoxingObject::RequestByParam(
	const FString& InURL,
	const FXiaoxingCompletionParam& InCompletionParam,
	const TMap<FString, FString>& InCustomMetadataHeader)
{
	return HTTP->Request(InURL, InCompletionParam, InCustomMetadataHeader);
}


void UXiaoxingObject::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bsucceeded)
{
	/*
	if (bsucceeded)
	{
		int32 ResponseCode = HttpResponse->GetResponseCode();
		if (ResponseCode == 200)
		{
			if (OnSuccess.IsBound())
			{
				FString JsonString = HttpResponse->GetContentAsString();

				FXiaoxingCompletionResponse XiaoxingCompletionResponse;
				XiaoxingMethod::StringToXiaoxingCompletionResponses(JsonString,XiaoxingCompletionResponse);

				//TArray<FString> TextContent;

				//for (auto& Tmp : XiaoxingCompletionResponse.Answer)
				//{
				//	TextContent.Add(Tmp.Text);
				//}
				FString TextContent;
				TextContent = XiaoxingCompletionResponse.Answer.Content;
				OnSuccess.Broadcast(TextContent,TEXT(""));

				return;
			}
		}
	}
	*/
}

bool UXiaoxingObject::IsLeaveUnused() const
{
	return HTTP->IsLeaveUnused();
}

void UXiaoxingObject::SetXiaoxingKey(const FString& InKey)
{
	return HTTP->SetKey(InKey);
}

