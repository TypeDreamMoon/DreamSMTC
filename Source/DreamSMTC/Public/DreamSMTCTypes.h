#pragma once

#include "CoreMinimal.h"
#include "DreamSMTCTypes.generated.h"


UENUM(BlueprintType)
enum class EDreamSMTCMediaPlaybackStatus : uint8
{
	Closed,
	Changing,
	Stopped,
	Playing,
	Paused,
};

UENUM(BlueprintType)
enum class EDreamSMTCMediaSoundLevel : uint8
{
	Muted,
	Low,
	Full,
};

USTRUCT(BlueprintType)
struct FDreamSMTCImageDisplayProperties
{
	GENERATED_BODY()

public:
	FDreamSMTCImageDisplayProperties()
	{
	};

	FDreamSMTCImageDisplayProperties(FString InTitle, FString InSubtitle)
		: Title(InTitle), Subtitle(InSubtitle)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Subtitle;
};

USTRUCT(BlueprintType)
struct FDreamSMTCMusicDisplayProperties
{
	GENERATED_BODY()

public:
	FDreamSMTCMusicDisplayProperties()
	{
	};

	FDreamSMTCMusicDisplayProperties(FString InAlbumArtist, FString InAlbumTitle, uint32 InAlbumTrackCount,
	                                 FString InArtist, TArray<FString> InGenres, FString InTitle, uint32 InTrackNumber)
		: AlbumArtist(InAlbumArtist), AlbumTitle(InAlbumTitle), AlbumTrackCount(InAlbumTrackCount), Artist(InArtist),
		  Genres(InGenres), Title(InTitle), TrackNumber(InTrackNumber)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AlbumArtist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AlbumTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AlbumTrackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Artist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Genres;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TrackNumber;
};

USTRUCT(BlueprintType)
struct FDreamSMTCVideoDisplayProperties
{
	GENERATED_BODY()

public:
	FDreamSMTCVideoDisplayProperties()
	{
	};

	FDreamSMTCVideoDisplayProperties(TArray<FString> InGenres, FString InSubtitle, FString InTitle)
		: Genres(InGenres), Subtitle(InSubtitle), Title(InTitle)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Genres;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Subtitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;
};

UENUM(BlueprintType)
enum class EDreamSMTCMediaPlaybackType : uint8
{
	Unknown,
	Music,
	Video,
	Image,
};

UENUM(BlueprintType)
enum class EDreamSMTCButtonEvent : uint8
{
	Play = 0,
	Pause = 1,
	Stop = 2,
	Record = 3,
	FastForward = 4,
	Rewind = 5,
	Next = 6,
	Previous = 7,
	ChannelUp = 8,
	ChannelDown = 9,
};

USTRUCT(BlueprintType)
struct FDreamSMTCTimelineProperties
{
	GENERATED_BODY()
public:
	FDreamSMTCTimelineProperties()
	{
	}

	FDreamSMTCTimelineProperties(FTimespan InStartTime, FTimespan InEndTime, FTimespan InPosition,
	                             FTimespan InMaxSeekTime, FTimespan InMinSeekTime)
		: StartTime(InStartTime), EndTime(InEndTime), Position(InPosition), MaxSeekTime(InMaxSeekTime),
		  MinSeekTime(InMinSeekTime)
	{
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan EndTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MaxSeekTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MinSeekTime;
};
