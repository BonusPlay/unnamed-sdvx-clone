#include "stdafx.h"
#include "GameConfig.hpp"
#ifdef _WIN32
#include "SDL_keycode.h"
#else
#include "SDL2/SDL_keycode.h"
#endif

GameConfig::GameConfig()
{
	// Default state
	Clear();
}

void GameConfig::SetKeyBinding(GameConfigKeys key, Graphics::Key value)
{
	SetEnum<Enum_Key>(key, value);
}

void GameConfig::InitDefaults()
{
	Set(GameConfigKeys::ScreenWidth, 1280);
	Set(GameConfigKeys::ScreenHeight, 720);
	Set(GameConfigKeys::FullScreenWidth, -1);
	Set(GameConfigKeys::FullScreenHeight, -1);
	Set(GameConfigKeys::Fullscreen, false);
	Set(GameConfigKeys::FullscreenMonitorIndex, 0);
	Set(GameConfigKeys::WindowedFullscreen, false);
	Set(GameConfigKeys::AntiAliasing, 0);
	Set(GameConfigKeys::MasterVolume, 1.0f);
	Set(GameConfigKeys::ScreenX, -1);
	Set(GameConfigKeys::ScreenY, -1);
	Set(GameConfigKeys::VSync, 0);
	Set(GameConfigKeys::ForcePortrait, false);
	Set(GameConfigKeys::HiSpeed, 1.0f);
	Set(GameConfigKeys::GlobalOffset, 0);
	Set(GameConfigKeys::InputOffset, 0);
	Set(GameConfigKeys::FPSTarget, 0);
	Set(GameConfigKeys::LaserAssistLevel, 1.5f);
	Set(GameConfigKeys::LaserPunish, 1.5f);
	Set(GameConfigKeys::LaserSlamBoost, 2.0f);
	Set(GameConfigKeys::UseMMod, false);
	Set(GameConfigKeys::UseCMod, false);
	Set(GameConfigKeys::ModSpeed, 300.0f);
	Set(GameConfigKeys::SongFolder, "songs");
	Set(GameConfigKeys::Skin, "Default");
	Set(GameConfigKeys::Laser0Color, 200.0f);
	Set(GameConfigKeys::Laser1Color, 330.0f);


	// Input settings
	SetEnum<Enum_InputDevice>(GameConfigKeys::ButtonInputDevice, InputDevice::Keyboard);
	SetEnum<Enum_InputDevice>(GameConfigKeys::LaserInputDevice, InputDevice::Keyboard);

	// Default keyboard bindings
	Set(GameConfigKeys::Key_BTS, SDLK_1); // Start button on Dao controllers
	Set(GameConfigKeys::Key_BTA, SDLK_d);
	Set(GameConfigKeys::Key_BTB, SDLK_f);
	Set(GameConfigKeys::Key_BTC, SDLK_j);
	Set(GameConfigKeys::Key_BTD, SDLK_k);
	Set(GameConfigKeys::Key_BTAAlt, -1);
	Set(GameConfigKeys::Key_BTBAlt, -1);
	Set(GameConfigKeys::Key_BTCAlt, -1);
	Set(GameConfigKeys::Key_BTDAlt, -1);
	Set(GameConfigKeys::Key_FXL, SDLK_c);
	Set(GameConfigKeys::Key_FXR, SDLK_m);
	Set(GameConfigKeys::Key_FXLAlt, -1);
	Set(GameConfigKeys::Key_FXRAlt, -1);
	Set(GameConfigKeys::Key_LaserLNeg, SDLK_w);
	Set(GameConfigKeys::Key_LaserLPos, SDLK_e);
	Set(GameConfigKeys::Key_LaserRNeg, SDLK_o);
	Set(GameConfigKeys::Key_LaserRPos, SDLK_p);
	Set(GameConfigKeys::Key_Sensitivity, 3.0f);
	Set(GameConfigKeys::Key_LaserReleaseTime, 0.0f);

	// Default controller settings
	Set(GameConfigKeys::Controller_DeviceID, 0); // First device
	Set(GameConfigKeys::Controller_BTS, 0);
	Set(GameConfigKeys::Controller_BTA, 1);
	Set(GameConfigKeys::Controller_BTB, 2);
	Set(GameConfigKeys::Controller_BTC, 3);
	Set(GameConfigKeys::Controller_BTD, 4);
	Set(GameConfigKeys::Controller_FXL, 5);
	Set(GameConfigKeys::Controller_FXR, 6);
	Set(GameConfigKeys::Controller_LaserLAxis, 0);
	Set(GameConfigKeys::Controller_LaserRAxis, 1);
	Set(GameConfigKeys::Controller_Sensitivity, 1.0f);
	Set(GameConfigKeys::Controller_Deadzone, 0.f);

	// Default mouse settings
	Set(GameConfigKeys::Mouse_LaserLAxis, 0);
	Set(GameConfigKeys::Mouse_LaserRAxis, 1);
	Set(GameConfigKeys::Mouse_Sensitivity, 1.0f);

	// Default to 0ms input bounce guard
	Set(GameConfigKeys::InputBounceGuard, 0);

	Set(GameConfigKeys::LastSelected, 0);
	Set(GameConfigKeys::LevelFilter, 0);
	Set(GameConfigKeys::FolderFilter, 0);

	Set(GameConfigKeys::AutoResetSettings, false);
	Set(GameConfigKeys::AutoResetToSpeed, 400.0f);

	Set(GameConfigKeys::EditorPath, "PathToEditor");
	Set(GameConfigKeys::EditorParamsFormat, "%s");
	Set(GameConfigKeys::WASAPI_Exclusive, false);

	Set(GameConfigKeys::CheckForUpdates, true);
}
