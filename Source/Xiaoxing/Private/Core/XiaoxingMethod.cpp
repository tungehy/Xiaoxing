#include "Core/XiaoxingMethod.h"
#include "Json.h"

namespace XiaoxingMethod
{
	FString XiaoxingBotToString(EXiaoxingBot InBot)
	{
		switch (InBot)
		{
		case EXiaoxingBot::TEACHER_GE:
			return TEXT("1b2yX7oRXN9dcqztJBz7x");
		}

		return TEXT("1b2yX7oRXN9dcqztJBz7x");//默认使用机器人TEACHER_GE
	}
	
	void XiaoxingCompletionParamToString(const FXiaoxingCompletionParam& InParam, FString& OutJson)
	{
		TSharedPtr<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter =
			TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
		
		JsonWriter->WriteObjectStart();//{
		{
			//JsonWriter->WriteValue(TEXT("Bot"), XiaoxingBotToString(InParam.Bot));
			JsonWriter->WriteValue(TEXT("question"), InParam.Question);
			JsonWriter->WriteValue(TEXT("userId"), InParam.UserId);
			
		}

		JsonWriter->WriteObjectEnd();//}
		JsonWriter->Close();//json合并

	}

	void StringToXiaoxingCompletionResponses(const FString& OutJson, FXiaoxingCompletionResponse& OutResponses)
	{
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(OutJson);
		TSharedPtr<FJsonValue> ReadRoot;

		if (FJsonSerializer::Deserialize(JsonReader, ReadRoot))
		{
			if (TSharedPtr<FJsonObject> InJsonObject = ReadRoot->AsObject())
			{
				if (TSharedPtr<FJsonObject> InAnswerJsonObject = InJsonObject->GetObjectField(TEXT("answer")))
				{
					OutResponses.Answer.Type = InAnswerJsonObject->GetStringField(TEXT("type"));
					OutResponses.Answer.Content = InAnswerJsonObject->GetStringField(TEXT("content"));
				}
				if (TSharedPtr<FJsonObject> InMetaJsonObject = InJsonObject->GetObjectField(TEXT("meta")))
				{
					OutResponses.Meta.UserId = InMetaJsonObject->GetStringField(TEXT("userId"));
				}
				
			}
		}
	}

}

