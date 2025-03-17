// Copyright Dream Moon.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "DreamSMTCWindowsRuntimeInclude.h"
#include "DreamSMTCLog.h"
#include "DreamSMTCSubsystem.generated.h"

class UTexture2D;

enum class EDreamSMTCMediaPlaybackType : uint8;
enum class EDreamSMTCMediaSoundLevel : uint8;
enum class EDreamSMTCButtonEvent : uint8;

struct FDreamSMTCTimelineProperties;
struct FDreamSMTCMusicDisplayProperties;
struct FDreamSMTCImageDisplayProperties;
struct FDreamSMTCVideoDisplayProperties;


using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Core;

/**
 * System Media Transport Controls (SMTC) Subsystem
 * Implementation Of Unreal Engine SMTC
 * API Documentation :
 * - Windows System Media Transport Controls : https://learn.microsoft.com/zh-cn/uwp/api/windows.media.systemmediatransportcontrols?view=winrt-26100
 * - Windows System Media Transport Controls Display Updater : https://learn.microsoft.com/zh-cn/uwp/api/windows.media.systemmediatransportcontrols.displayupdater?view=winrt-26100#windows-media-systemmediatransportcontrols-displayupdater
 */
UCLASS(DisplayName = "Dream System Media Transport Controls Subsystem")
class DREAMSMTC_API UDreamSMTCSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UDreamSMTCSubsystem();
	virtual ~UDreamSMTCSubsystem() override;

	static winrt::Windows::Media::SystemMediaTransportControls GetSystemMediaTransportControls();
	static winrt::Windows::Media::SystemMediaTransportControlsDisplayUpdater
	GetSystemMediaTransportControlsDisplayUpdater();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonPressed, EDreamSMTCButtonEvent, ButtonEvent);

public:
	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetAutoRepeatMode(bool bAutoRepeatMode);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetAutoRepeatMode() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetIsChannelDownEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetIsChannelDownEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetIsChannelUpEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetIsChannelUpEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetEnabled(bool bEnable) const;

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool IsEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetFastForwardEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetFastForwardEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetNextEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetNextEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetPauseEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetPauseEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetPlayEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetPlayEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetPreviousEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetPreviousEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetRecordEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetRecordEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetRewindEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetRewindEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetStopEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetStopEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetPlaybackRate(double Rate);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	double GetPlaybackRate() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetPlaybackStatus(EDreamSMTCMediaPlaybackStatus Status);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	EDreamSMTCMediaPlaybackStatus GetPlaybackStatus() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC")
	void SetShuffleEnabled(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	bool GetShuffleEnabled() const;

	UFUNCTION(BlueprintPure, Category = "DreamSMTC")
	EDreamSMTCMediaSoundLevel GetSoundLevel() const;

public:
	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetAppMediaId(FString AppID);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	FString GetAppMediaId() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetImageProperties(FDreamSMTCImageDisplayProperties ImageDisplayProperties);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	FDreamSMTCImageDisplayProperties GetImageProperties() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetMusicProperties(FDreamSMTCMusicDisplayProperties MusicDisplayProperties);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	FDreamSMTCMusicDisplayProperties GetMusicProperties() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetVideoProperties(FDreamSMTCVideoDisplayProperties VideoDisplayProperties);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	FDreamSMTCVideoDisplayProperties GetVideoProperties() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetThumbnail(UTexture2D* InThumbnail);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	UTexture2D* GetThumbnail() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void SetType(EDreamSMTCMediaPlaybackType Type);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|DisplayUpdater")
	EDreamSMTCMediaPlaybackType GetType() const;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void ClearAll();

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	void Update();

public:
	// UFUNCTION(BlueprintCallable, Category = "DreamSMTC|DisplayUpdater")
	// void UpdateSMTC(FString Title);

	// Doc : https://learn.microsoft.com/zh-cn/uwp/api/windows.media.systemmediatransportcontrols.buttonpressed?view=winrt-26100#windows-media-systemmediatransportcontrols-buttonpressed
	UPROPERTY(BlueprintAssignable, Category = "DreamSMTC|Event")
	FButtonPressed ButtonPressed;

	UFUNCTION(BlueprintCallable, Category = "DreamSMTC|Time")
	void SetUpdateTimelineProperties(FDreamSMTCTimelineProperties TimelineProperties);

	UFUNCTION(BlueprintPure, Category = "DreamSMTC|Time")
	FDreamSMTCTimelineProperties GetTimelineProperties() const;
	
private:
	TObjectPtr<UTexture2D> Thumbnail = nullptr;

	FTimespan WinRTToUnrealTimespan(const winrt::Windows::Foundation::TimeSpan& WinRTTime)
	{
		// 获取 WinRT 的 100 纳秒单位值
		int64_t WinRTTicks = WinRTTime.count();
		// 转换为微秒：除以 10
		int64_t UnrealTicks = WinRTTicks / 10;
		// 构造 Unreal 的 FTimespan
		return FTimespan(UnrealTicks);
	}

	winrt::Windows::Foundation::TimeSpan UnrealToWinRTTimespan(const FTimespan& UnrealTime)
	{
		// 获取 Unreal 的微秒值
		int64_t UnrealTicks = UnrealTime.GetTicks();
		// 转换为 100 纳秒单位：乘以 10
		int64_t WinRTTicks = UnrealTicks * 10;
		// 构造 WinRT 的 TimeSpan
		winrt::Windows::Foundation::TimeSpan WinRTTime(WinRTTicks);
		return WinRTTime;
	}
};
