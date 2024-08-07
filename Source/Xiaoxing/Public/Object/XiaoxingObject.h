#pragma once

#include "CoreMinimal.h"
#include "HTTP/XiaoxingHttp.h"
#include "XiaoxingObject.generated.h"

//InData,InMsgÊÇchatGPTÖÐµÄ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpXiaoxingResponseDelegate, const TArray<FString>&, InData, const FString&, InMsg);


UCLASS(BLueprintType, Blueprintable)
class XIAOXING_API UXiaoxingObject :public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FHttpXiaoxingResponseDelegate OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FHttpXiaoxingResponseDelegate OnFailure;

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateXiaoxingObject", Keywords = "Xiaoxing", WorldContext = "WorldContextObject"), Category = "Xiaoxing")
	static UXiaoxingObject* CreateObject(UObject* WorldContextObject,UClass* InClass = NULL, UObject* InParent = NULL);

public:
	UFUNCTION(BlueprintCallable, Category = "Xiaoxing")
	bool Request(
		const FString& InURL,
		const FString& InContent,
		const TMap<FString, FString>& InCustomMetadataHeader);
	
	UFUNCTION(BlueprintCallable, Category = "Xiaoxing")
	bool RequestByParam(
		const FString& InURL,
		const FXiaoxingCompletionParam& InCompletionParam,
		const TMap<FString, FString>& InCustomMetadataHeader);
	
	UFUNCTION(BlueprintPure, Category = "Xiaoxing")
	bool IsLeaveUnused() const;

	UFUNCTION(BlueprintCallable, Category = "Xiaoxing")
	void SetXiaoxingKey(const FString& InKey);
public:
	UXiaoxingObject();

protected:
	void InitXiaoxing();

protected:
	void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bsucceeded);

private:
	TSharedPtr<XiaoxingHTTP::FHTTP> HTTP;
};