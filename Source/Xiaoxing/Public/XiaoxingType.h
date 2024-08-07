#pragma once

#include "CoreMinimal.h"
#include "XiaoxingType.generated.h"

UENUM(BlueprintType)
enum class EXiaoxingBot :uint8
{
	TEACHER_GE            UMETA(DisplayName = "teacher-ge"),
	TEACHER_ZHNANG,
};


USTRUCT(BlueprintType)
struct XIAOXING_API FXiaoxingCompletionParam
{
	GENERATED_USTRUCT_BODY()


	FXiaoxingCompletionParam();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "completionParam")
	EXiaoxingBot Bot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "completionParam")
	FString UserId;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "completionParam")
	FString Question;
};

USTRUCT(BlueprintType)
struct XIAOXING_API FXiaoxingAnswer
{
	GENERATED_USTRUCT_BODY()

	FXiaoxingAnswer();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "XiaoxingAnswer")
	FString Type;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "XiaoxingAnswer")
	FString Content;
};

USTRUCT(BlueprintType)
struct XIAOXING_API FXiaoxingMeta
{
	GENERATED_USTRUCT_BODY()

	FXiaoxingMeta();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "XiaoxingMeta")
	FString UserId;

};



USTRUCT(BlueprintType)
struct XIAOXING_API FXiaoxingCompletionResponse
{
	GENERATED_USTRUCT_BODY()

	FXiaoxingCompletionResponse();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "completionResponse")
	FXiaoxingAnswer Answer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "completionResponse")
	FXiaoxingMeta Meta;

};