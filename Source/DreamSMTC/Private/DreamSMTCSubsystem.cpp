// Copyright Dream Moon.

/*	Refer To
 *	SMTC : https://github.com/BetterNCM/InfinityLink/blob/main/native/smtc.cpp
 *	WinRT : https://learn.microsoft.com/zh-cn/windows/mixed-reality/develop/unreal/unreal-winrt
 */

#include "DreamSMTCSubsystem.h"

#include "DreamSMTCTypes.h"
#include "Async/Async.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Misc/AsyncTaskNotification.h"

#define CHECK_SMTC() \
	if (!mediaPlayer.has_value()) mediaPlayer = MediaPlayer();

std::optional<winrt::Windows::Media::Playback::MediaPlayer> mediaPlayer;
FDreamSMTCTimelineProperties GSmtcTimelineProperties;

UDreamSMTCSubsystem::UDreamSMTCSubsystem()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = winrt::Windows::Media::Playback::MediaPlayer();

	GetSystemMediaTransportControls().ButtonPressed(
		[&](winrt::Windows::Media::SystemMediaTransportControls Sender,
		    winrt::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs Args)
		{
			// 先在线程上下文中获取参数值
			const EDreamSMTCButtonEvent ButtonEvent = static_cast<EDreamSMTCButtonEvent>(Args.Button());

			// 通过异步任务派发到游戏线程执行
			FAsyncTaskNotificationConfig Config;
			AsyncTask(ENamedThreads::GameThread, [this, ButtonEvent]()
			{
				// 确保在游戏线程执行广播
				ButtonPressed.Broadcast(ButtonEvent);
			});
		});

	const auto commandManager = mediaPlayer->CommandManager();
	commandManager.IsEnabled(false);
}

UDreamSMTCSubsystem::~UDreamSMTCSubsystem()
{
	ClearAll();
	SetEnabled(false);
}

winrt::Windows::Media::SystemMediaTransportControls UDreamSMTCSubsystem::GetSystemMediaTransportControls()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = winrt::Windows::Media::Playback::MediaPlayer();

	return mediaPlayer->SystemMediaTransportControls();
}

winrt::Windows::Media::SystemMediaTransportControlsDisplayUpdater
UDreamSMTCSubsystem::GetSystemMediaTransportControlsDisplayUpdater()
{
	if (!mediaPlayer.has_value())
		mediaPlayer = winrt::Windows::Media::Playback::MediaPlayer();

	return mediaPlayer->SystemMediaTransportControls().DisplayUpdater();
}

void UDreamSMTCSubsystem::SetAutoRepeatMode(bool bAutoRepeatMode)
{
	try
	{
		GetSystemMediaTransportControls().AutoRepeatMode(bAutoRepeatMode
			                                                 ? winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List
			                                                 : winrt::Windows::Media::MediaPlaybackAutoRepeatMode::None);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetAutoRepeatMode() const
{
	try
	{
		return GetSystemMediaTransportControls().AutoRepeatMode() ==
			winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List;
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetIsChannelDownEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsChannelDownEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetIsChannelDownEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsChannelDownEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetIsChannelUpEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsChannelUpEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetIsChannelUpEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsChannelUpEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetEnabled(bool bEnable) const
{
	try
	{
		GetSystemMediaTransportControls().IsEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::IsEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetFastForwardEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsFastForwardEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetFastForwardEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsFastForwardEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetNextEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsNextEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetNextEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsNextEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetPauseEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsPauseEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetPauseEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsPauseEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetPlayEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsPlayEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetPlayEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsPlayEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetPreviousEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsPreviousEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetPreviousEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsPreviousEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetRecordEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsRecordEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetRecordEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsRecordEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetRewindEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsRewindEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetRewindEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsRewindEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetStopEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().IsStopEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetStopEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().IsStopEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

void UDreamSMTCSubsystem::SetPlaybackRate(double Rate)
{
	try
	{
		GetSystemMediaTransportControls().PlaybackRate(Rate);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

double UDreamSMTCSubsystem::GetPlaybackRate() const
{
	try
	{
		return GetSystemMediaTransportControls().PlaybackRate();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return -1.0f;
	}
}

void UDreamSMTCSubsystem::SetPlaybackStatus(EDreamSMTCMediaPlaybackStatus Status)
{
	try
	{
		GetSystemMediaTransportControls().PlaybackStatus(
			static_cast<winrt::Windows::Media::MediaPlaybackStatus>(Status));
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

EDreamSMTCMediaPlaybackStatus UDreamSMTCSubsystem::GetPlaybackStatus() const
{
	try
	{
		return static_cast<EDreamSMTCMediaPlaybackStatus>(GetSystemMediaTransportControls().PlaybackStatus());
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return EDreamSMTCMediaPlaybackStatus::Closed;
	}
}

void UDreamSMTCSubsystem::SetShuffleEnabled(bool bEnable)
{
	try
	{
		GetSystemMediaTransportControls().ShuffleEnabled(bEnable);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

bool UDreamSMTCSubsystem::GetShuffleEnabled() const
{
	try
	{
		return GetSystemMediaTransportControls().ShuffleEnabled();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return false;
	}
}

EDreamSMTCMediaSoundLevel UDreamSMTCSubsystem::GetSoundLevel() const
{
	try
	{
		return static_cast<EDreamSMTCMediaSoundLevel>(GetSystemMediaTransportControls().SoundLevel());
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return EDreamSMTCMediaSoundLevel::Muted;
	}
}

void UDreamSMTCSubsystem::SetAppMediaId(FString AppID)
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().AppMediaId(*AppID);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

FString UDreamSMTCSubsystem::GetAppMediaId() const
{
	try
	{
		return GetSystemMediaTransportControlsDisplayUpdater().AppMediaId().c_str();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return FString();
	}
}

void UDreamSMTCSubsystem::SetImageProperties(FDreamSMTCImageDisplayProperties ImageDisplayProperties)
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().ImageProperties().Subtitle(*ImageDisplayProperties.Subtitle);
		GetSystemMediaTransportControlsDisplayUpdater().ImageProperties().Title(*ImageDisplayProperties.Title);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
	}
}

FDreamSMTCImageDisplayProperties UDreamSMTCSubsystem::GetImageProperties() const
{
	try
	{
		return FDreamSMTCImageDisplayProperties(
			GetSystemMediaTransportControlsDisplayUpdater().ImageProperties().Title().c_str(),
			GetSystemMediaTransportControlsDisplayUpdater().ImageProperties().Subtitle().c_str()
		);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return FDreamSMTCImageDisplayProperties();
	}
}

void UDreamSMTCSubsystem::SetMusicProperties(FDreamSMTCMusicDisplayProperties MusicDisplayProperties)
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().AlbumArtist(
			*MusicDisplayProperties.AlbumArtist);
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().
		                                                AlbumTitle(*MusicDisplayProperties.AlbumTitle);
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().AlbumTrackCount(
			MusicDisplayProperties.AlbumTrackCount);
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().Artist(*MusicDisplayProperties.Artist);
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().Title(*MusicDisplayProperties.Title);
		GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().TrackNumber(
			MusicDisplayProperties.TrackNumber);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

FDreamSMTCMusicDisplayProperties UDreamSMTCSubsystem::GetMusicProperties() const
{
	try
	{
		TArray<FString> Genres;
		for (auto Genre : GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().Genres())
		{
			Genres.Add(Genre.c_str());
		}
		return FDreamSMTCMusicDisplayProperties(
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().AlbumArtist().c_str(),
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().AlbumTitle().c_str(),
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().AlbumTrackCount(),
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().Artist().c_str(),
			Genres,
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().Title().c_str(),
			GetSystemMediaTransportControlsDisplayUpdater().MusicProperties().TrackNumber()
		);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return FDreamSMTCMusicDisplayProperties();
	}
}

void UDreamSMTCSubsystem::SetVideoProperties(FDreamSMTCVideoDisplayProperties VideoDisplayProperties)
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().VideoProperties().Subtitle(*VideoDisplayProperties.Subtitle);
		GetSystemMediaTransportControlsDisplayUpdater().VideoProperties().Title(*VideoDisplayProperties.Title);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
	}
}

FDreamSMTCVideoDisplayProperties UDreamSMTCSubsystem::GetVideoProperties() const
{
	try
	{
		TArray<FString> Genres;
		for (auto Genre : GetSystemMediaTransportControlsDisplayUpdater().VideoProperties().Genres())
		{
			Genres.Add(Genre.c_str());
		}
		return FDreamSMTCVideoDisplayProperties(
			Genres,
			GetSystemMediaTransportControlsDisplayUpdater().VideoProperties().Subtitle().c_str(),
			GetSystemMediaTransportControlsDisplayUpdater().VideoProperties().Title().c_str()
		);
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return FDreamSMTCVideoDisplayProperties();
	}
}

void UDreamSMTCSubsystem::SetThumbnail(UTexture2D* InThumbnail)
{
	if (!InThumbnail)
	{
		UE_LOG(LogDreamSMTC, Warning, TEXT("Invalid thumbnail texture."));
		return;
	}

	// 定义缓存路径
	FString FilePath = FPaths::ProjectSavedDir() / TEXT("DreamSMTCCache");
	FString FileName = TEXT("ThumbnailCache.jpg");
	FString FileFullName = FPaths::Combine(FilePath, FileName);

	// 确保目录存在
	IFileManager::Get().MakeDirectory(*FilePath, true);

	// 同步保存纹理到文件
	UKismetRenderingLibrary::ExportTexture2D(GetWorld(), InThumbnail, FilePath, FileName);

	// 转换为 WinRT 兼容路径
	FString FullPath = FPaths::ConvertRelativePathToFull(FileFullName);
	FullPath.ReplaceInline(TEXT("/"), TEXT("\\"));
	std::wstring winrtPath = *FullPath;

	// 异步获取文件并设置缩略图
	AsyncTask(ENamedThreads::GameThread, [this, winrtPath]()
	{
		try
		{
			// auto file = winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(winrtPath).get();
			// auto thumbnailRef = winrt::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromFile(file);
			// GetSystemMediaTransportControlsDisplayUpdater().Thumbnail(thumbnailRef);
			// GetSystemMediaTransportControlsDisplayUpdater().Update();
		}
		catch (const winrt::hresult_error& ex)
		{
			UE_LOG(LogDreamSMTC, Error, TEXT("SetThumbnail failed: 0x%08X - %s"),
			       ex.code().value, *FString(ex.message().c_str()));
		}
	});
}

UTexture2D* UDreamSMTCSubsystem::GetThumbnail() const
{
	return Thumbnail;
}

void UDreamSMTCSubsystem::SetType(EDreamSMTCMediaPlaybackType Type)
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().Type(
			static_cast<winrt::Windows::Media::MediaPlaybackType>(Type));
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

EDreamSMTCMediaPlaybackType UDreamSMTCSubsystem::GetType() const
{
	try
	{
		return static_cast<EDreamSMTCMediaPlaybackType>(GetSystemMediaTransportControlsDisplayUpdater().Type());
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return EDreamSMTCMediaPlaybackType::Unknown;
	}
}

void UDreamSMTCSubsystem::ClearAll()
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().ClearAll();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

void UDreamSMTCSubsystem::Update()
{
	try
	{
		GetSystemMediaTransportControlsDisplayUpdater().Update();
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return;
	}
}

void UDreamSMTCSubsystem::SetUpdateTimelineProperties(FDreamSMTCTimelineProperties TimelineProperties)
{
	try
	{
		winrt::Windows::Media::SystemMediaTransportControlsTimelineProperties Time;
		Time.StartTime(UnrealToWinRTTimespan(TimelineProperties.StartTime));
		Time.EndTime(UnrealToWinRTTimespan(TimelineProperties.EndTime));
		Time.MinSeekTime(UnrealToWinRTTimespan(TimelineProperties.MinSeekTime));
		Time.MaxSeekTime(UnrealToWinRTTimespan(TimelineProperties.MaxSeekTime));
		Time.Position(UnrealToWinRTTimespan(TimelineProperties.Position));
		GetSystemMediaTransportControls().UpdateTimelineProperties(Time);
		GSmtcTimelineProperties = TimelineProperties;
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error,TEXT("SMTC update failed: %s"), *FString(e.what()))
		return;
	}
}

FDreamSMTCTimelineProperties UDreamSMTCSubsystem::GetTimelineProperties() const
{
	try
	{
		return GSmtcTimelineProperties;
	}
	catch (std::exception& e)
	{
		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
		return FDreamSMTCTimelineProperties();
	}
}

// void UDreamSMTCSubsystem::UpdateSMTC(FString Title)
// {
//
// 	try
// 	{
// 		GetSystemMediaTransportControls().IsEnabled(true);
// 		GetSystemMediaTransportControls().IsPlayEnabled(true);
// 		GetSystemMediaTransportControls().IsPauseEnabled(true);
//
// 		auto updater = GetSystemMediaTransportControls().DisplayUpdater();
// 		updater.ClearAll();
// 		updater.Type(winrt::Windows::Media::MediaPlaybackType::Music);
//
// 		auto properties = updater.MusicProperties();
// 		properties.Title(*Title);
// 		updater.Update();
// 	}
// 	catch (std::exception& e)
// 	{
// 		UE_LOG(LogDreamSMTC, Error, TEXT("SMTC update failed: %s"), *FString(e.what()));
// 		return;
// 	}
// }
