// Copyright Dream Moon.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "CommonWinRT.h"
#include "DreamSMTCLog.h"

#include "winrt/windows.media.control.h"
#include "winrt/windows.media.playback.h"
#include "winrt/windows.applicationmodel.core.h"
#include "DreamSMTCSubsystem.generated.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Media;
using namespace Playback;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace Control;
using namespace winrt;

/**
 * SMTC Subsystem
 * Parent : GameInstanceSubsystem
 */
UCLASS()
class DREAMSMTC_API UDreamSMTCSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDreamSMTCSubsystem();
	~UDreamSMTCSubsystem();
private:
	SystemMediaTransportControls GetSMTC();
public:
	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void UpdateSMTC(FString Title);
};
