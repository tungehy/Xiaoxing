#pragma once

#include "CoreMinimal.h"
#include "XiaoxingType.h"

namespace XiaoxingMethod
{
	FString XIAOXING_API XiaoxingBotToString(EXiaoxingBot InBot);

	void XIAOXING_API XiaoxingCompletionParamToString(const FXiaoxingCompletionParam &InParam,FString &OutJson);
	void XIAOXING_API StringToXiaoxingCompletionResponses(const FString& OutJson, FXiaoxingCompletionResponse& OutResponses);
}