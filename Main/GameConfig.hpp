#pragma once
#include "Shared/Config.hpp"
#include "Input.hpp"

DefineEnum(GameConfigKeys,
	// Screen settings
	ScreenWidth,
	ScreenHeight,
	FullScreenWidth,
	FullScreenHeight,
	ScreenX,
	ScreenY,
	Fullscreen,
	FullscreenMonitorIndex,
	WindowedFullscreen,
	AntiAliasing,
	MasterVolume,
	VSync,
	ForcePortrait,

	// Game settings
	HiSpeed,
    UseMMod,
    UseCMod,
    ModSpeed,
	GlobalOffset,
	InputOffset,
	SongFolder,
	Skin,
	Laser0Color,
	Laser1Color,
	FPSTarget,
	LaserAssistLevel,
	LaserPunish,
	LaserSlamBoost,

	// Input device setting per element
	LaserInputDevice,
	ButtonInputDevice,

	// Mouse settings (primary axes are x=0, y=1)
	Mouse_LaserLAxis,
	Mouse_LaserRAxis,
	Mouse_Sensitivity,

	// Key bindings
	Key_BTS,
	Key_BTA,
	Key_BTB,
	Key_BTC,
	Key_BTD,
	Key_BTAAlt,
	Key_BTBAlt,
	Key_BTCAlt,
	Key_BTDAlt,
	Key_FXL,
	Key_FXR,
	Key_FXLAlt,
	Key_FXRAlt,
	Key_LaserLPos,
	Key_LaserLNeg,
	Key_LaserRPos,
	Key_LaserRNeg,
	Key_Sensitivity,
	Key_LaserReleaseTime,

	// Controller bindings
	Controller_DeviceID,
	Controller_BTS,
	Controller_BTA,
	Controller_BTB,
	Controller_BTC,
	Controller_BTD,
	Controller_FXL,
	Controller_FXR,
	Controller_LaserLAxis,
	Controller_LaserRAxis,
	Controller_Deadzone,
	Controller_Sensitivity,
	InputBounceGuard,

	LastSelected,
	LevelFilter,
	FolderFilter,

	AutoResetSettings, //Reset game settings after each song (good for convention setups)
	AutoResetToSpeed, //Mod-Speed to reset to after each song (when AutoResetSettings is true)

	EditorPath,
	EditorParamsFormat,

	WASAPI_Exclusive,

	CheckForUpdates
	);

// Config for game settings
class GameConfig : public Config<Enum_GameConfigKeys>
{
public:
	GameConfig();
	void SetKeyBinding(GameConfigKeys key, Key value);

protected:
	virtual void InitDefaults() override;

};

// Main config instance
extern class GameConfig g_gameConfig;
