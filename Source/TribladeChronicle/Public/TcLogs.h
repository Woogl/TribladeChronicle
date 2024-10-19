// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
TRIBLADECHRONICLE_API DECLARE_LOG_CATEGORY_EXTERN(LogTc, Log, All);

#define TC_LOG(Format, ...) UE_LOG(LogTc, Log, Format, ##__VA_ARGS__)
#define TC_WARNING(Format, ...) UE_LOG(LogTc, Warning, Format, ##__VA_ARGS__)
#define TC_ERROR(Format, ...) UE_LOG(LogTc, Error, Format, ##__VA_ARGS__)
#define TC_SCREEN(Format, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(Format, ##__VA_ARGS__)); }