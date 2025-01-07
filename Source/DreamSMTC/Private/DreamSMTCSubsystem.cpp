// Copyright Dream Moon.

/*	Refer To
 *	SMTC : https://github.com/BetterNCM/InfinityLink/blob/main/native/smtc.cpp
 *	WinRT : https://learn.microsoft.com/zh-cn/windows/mixed-reality/develop/unreal/unreal-winrt
 */

#include "DreamSMTCSubsystem.h"


std::optional<MediaPlayer> mediaPlayer;

UDreamSMTCSubsystem::UDreamSMTCSubsystem()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = MediaPlayer();
	
	GetSMTC().ButtonPressed([&](SystemMediaTransportControls Sender, SystemMediaTransportControlsButtonPressedEventArgs Args)
	{
		auto Button = static_cast<int32_t>(Args.Button());
		UE_LOG(LogDreamSMTC, Log, TEXT("Button pressed: %d"), Button);
	});

	const auto commandManager = mediaPlayer->CommandManager();
	commandManager.IsEnabled(false);
	
	auto updater = GetSMTC().DisplayUpdater();
	updater.ClearAll();
	updater.Type(MediaPlaybackType::Music);
	auto properties = updater.MusicProperties();

	properties.Title(to_hstring(std::string("Loading")));

	updater.Update();

	UE_LOG(LogDreamSMTC, Log, TEXT("SMTC enabled."));
}

UDreamSMTCSubsystem::~UDreamSMTCSubsystem()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = MediaPlayer();

	GetSMTC().IsEnabled(false);

	UE_LOG(LogDreamSMTC, Log, TEXT("SMTC disable."));
}

SystemMediaTransportControls UDreamSMTCSubsystem::GetSMTC()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = MediaPlayer();

	return mediaPlayer->SystemMediaTransportControls();
}

void UDreamSMTCSubsystem::UpdateSMTC(FString Title)
{
	if (!mediaPlayer.has_value())
		mediaPlayer = MediaPlayer();

	try
	{
		GetSMTC().IsEnabled(true);
		GetSMTC().IsPlayEnabled(true);
		GetSMTC().IsPauseEnabled(true);

		auto updater = GetSMTC().DisplayUpdater();
		updater.ClearAll();
		updater.Type(MediaPlaybackType::Music);

		auto properties = updater.MusicProperties();
		properties.Title(*Title);
		updater.Update();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}
