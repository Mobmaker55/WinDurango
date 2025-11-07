#pragma once
#include "toml.hpp"
#include <locale>
#include <codecvt>
#include <filesystem>

struct WinDurangoConfigData
{
	std::string gamertag{ "TheDurangler" };
	int gamerscore{ 0 };
	int reputation{ 0 };
	enum class AgeGroup
	{
		Child,
		Teen,
		Adult,
		Unknown
	} ageGroup{ AgeGroup::Unknown };
	enum class Game
	{
		Minecraft,
		Forza_Horizon_2,
		Unknown
	} game{ Game::Unknown };
	int A = 0;
	int B = 0;
	int X = 0;
	int Y = 0;
	int Up = 0;
	int Down = 0;
	int Left = 0;
	int Right = 0;
	int Menu = 0;
	int View = 0;
	int LThumb = 0;
	int RThumb = 0;
	int LShoulder = 0;
	int RShoulder = 0;
	int LTrigger = 0;
	int RTrigger = 0;
	int MovementThumbY = 0;
	int MovementThumbYM = 0;
	int MovementThumbX = 0;
	int MovementThumbXM = 0;
	std::string MovementStick = "Left";
	std::string MouseStick = "Right";
};

class WinDurangoConfig
{
public:
	static WinDurangoConfig& Instance();

	[[nodiscard]] WinDurangoConfigData GetData() const;
	void SetData(const WinDurangoConfigData& data);

	WinDurangoConfig(const WinDurangoConfig&) = delete;
	WinDurangoConfig& operator=(const WinDurangoConfig&) = delete;
	WinDurangoConfig(WinDurangoConfig&&) = delete;
	WinDurangoConfig& operator=(WinDurangoConfig&&) = delete;

private:
	WinDurangoConfig();
	~WinDurangoConfig() = default;

	void ProcessConfigFile();

	WinDurangoConfigData _data{};

	std::string _configFilePath{};
};