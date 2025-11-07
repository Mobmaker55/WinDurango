#include "pch.h"
#include "WinDurangoConfig.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
using namespace winrt::Windows::Storage;

WinDurangoConfig& WinDurangoConfig::Instance()
{
	static WinDurangoConfig instance;
	return instance;
}

WinDurangoConfigData WinDurangoConfig::GetData() const
{
	return _data;
}

void WinDurangoConfig::SetData(const WinDurangoConfigData& data)
{
	_data = data;
}

using namespace std::string_view_literals;

void WinDurangoConfig::ProcessConfigFile()
{
	static constexpr auto default_config_data = R"(
		[WinDurango]
		Gamertag = "TheDurangler2"
		Gamerscore = 1500
		Reputation = 5
		Game = "Minecraft"
		AgeGroup = "Adult"
		
		[KeyboardMapping]
		A = 32
		B = 81
		X = 82
		Y = 69
		Up = 38
		Down = 40
		Left = 37
		Right = 39
		Menu = 13
		View = 27
		LThumb = 161
		RThumb = 160
		LShoulder = 162
		RShoulder = 163
		LTrigger = 2
		RTrigger = 1
		MovThumbY = 87
		MovThumbYM = 83
		MovThumbX = 68
		MovThumbXM = 65
		MovementStick = "Left"
		MouseStick = "Right"
	)"sv;

	try
	{
		/*
		* We need to use WinRT Storage APIs in UWP
		*/
		StorageFolder localFolder = ApplicationData::Current().LocalFolder();
		std::wstring folderPath = std::wstring(localFolder.Path());
		std::filesystem::path cfgPath = std::filesystem::path(folderPath) / L"config.toml";
		if (!std::filesystem::exists(cfgPath)) {
			winrt::Windows::Storage::StorageFile file = localFolder
				.CreateFileAsync(L"config.toml", winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting)
				.get();

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide = converter.from_bytes(std::string(default_config_data));
			winrt::Windows::Storage::FileIO::WriteTextAsync(file, wide).get();
		}

		StorageFile file = ApplicationData::Current().LocalFolder().GetFileAsync(L"config.toml").get();
		std::wstring cfdata = std::wstring(FileIO::ReadTextAsync(file).get());

		std::string ConfigData(cfdata.begin(), cfdata.end());

		auto tbl = toml::parse(ConfigData);

		auto gamertag_opt = tbl["WinDurango"]["Gamertag"].value<std::string_view>();
		auto gamerscore_opt = tbl["WinDurango"]["Gamerscore"].value<int>();
		auto reputation_opt = tbl["WinDurango"]["Reputation"].value<int>();
		auto agegroup_opt = tbl["WinDurango"]["AgeGroup"].value<std::string_view>();
		auto game_opt = tbl["WinDurango"]["Game"].value<std::string_view>();

		auto a_opt = tbl["KeyboardMapping"]["A"].value<int>();
		auto b_opt = tbl["KeyboardMapping"]["B"].value<int>();
		auto x_opt = tbl["KeyboardMapping"]["X"].value<int>();
		auto y_opt = tbl["KeyboardMapping"]["Y"].value<int>();
		auto up_opt = tbl["KeyboardMapping"]["Up"].value<int>();
		auto down_opt = tbl["KeyboardMapping"]["Down"].value<int>();
		auto left_opt = tbl["KeyboardMapping"]["Left"].value<int>();
		auto right_opt = tbl["KeyboardMapping"]["Right"].value<int>();
		auto menu_opt = tbl["KeyboardMapping"]["Menu"].value<int>();
		auto view_opt = tbl["KeyboardMapping"]["View"].value<int>();
		auto lthumb_opt = tbl["KeyboardMapping"]["LThumb"].value<int>();
		auto rthumb_opt = tbl["KeyboardMapping"]["RThumb"].value<int>();
		auto lshoulder_opt = tbl["KeyboardMapping"]["LShoulder"].value<int>();
		auto rshoulder_opt = tbl["KeyboardMapping"]["RShoulder"].value<int>();
		auto ltrigger_opt = tbl["KeyboardMapping"]["LTrigger"].value<int>();
		auto rtrigger_opt = tbl["KeyboardMapping"]["RTrigger"].value<int>();
		auto movthumby_opt = tbl["KeyboardMapping"]["MovThumbY"].value<int>();
		auto movthumbym_opt = tbl["KeyboardMapping"]["MovThumbYM"].value<int>();
		auto movthumbx_opt = tbl["KeyboardMapping"]["MovThumbX"].value<int>();
		auto movthumbxm_opt = tbl["KeyboardMapping"]["MovThumbXM"].value<int>();
		auto movstick_opt = tbl["KeyboardMapping"]["MovementStick"].value<std::string_view>();
		auto mousestick_opt = tbl["KeyboardMapping"]["MouseStick"].value<std::string_view>();

		const WinDurangoConfigData data
		{
			.gamertag = std::string(gamertag_opt.value_or("WinDurango2")),
			.gamerscore = 0,
			.reputation = 0,
			.ageGroup =
				agegroup_opt.has_value()
					? (agegroup_opt.value_or("Adult") == "Child" ? WinDurangoConfigData::AgeGroup::Child
						: agegroup_opt.value_or("Adult") == "Teen" ? WinDurangoConfigData::AgeGroup::Teen
						: agegroup_opt.value_or("Adult") == "Adult" ? WinDurangoConfigData::AgeGroup::Adult
						: WinDurangoConfigData::AgeGroup::Unknown)
					: WinDurangoConfigData::AgeGroup::Unknown,
			.game =
				game_opt.has_value()
					? (game_opt.value_or("") == "Minecraft" ? WinDurangoConfigData::Game::Minecraft
						: game_opt.value_or("") == "Forza Horizon 2" ? WinDurangoConfigData::Game::Forza_Horizon_2
						: WinDurangoConfigData::Game::Unknown)
					: WinDurangoConfigData::Game::Unknown,
			.A = a_opt.value_or(32),
			.B = b_opt.value_or(81),
			.X = x_opt.value_or(82),
			.Y = y_opt.value_or(69),
			.Up = up_opt.value_or(38),
			.Down = down_opt.value_or(40),
			.Left = left_opt.value_or(37),
			.Right = right_opt.value_or(39),
			.Menu = menu_opt.value_or(13),
			.View = view_opt.value_or(27),
			.LThumb = lthumb_opt.value_or(161),
			.RThumb = rthumb_opt.value_or(160),
			.LShoulder = lshoulder_opt.value_or(162),
			.RShoulder = rshoulder_opt.value_or(163),
			.LTrigger = ltrigger_opt.value_or(2),
			.RTrigger = rtrigger_opt.value_or(1),
			.MovementThumbY = movthumby_opt.value_or(87),
			.MovementThumbYM = movthumbym_opt.value_or(83),
			.MovementThumbX = movthumbx_opt.value_or(68),
			.MovementThumbXM = movthumbxm_opt.value_or(65),
			.MovementStick = std::string(movstick_opt.value_or("left")),
			.MouseStick = std::string(mousestick_opt.value_or("right")),
		};

		SetData(data);
	}
	catch (const toml::parse_error& err)
	{
		LOG_INFO("WinDurangoConfig || Parsing failed: %s\n", err);
		const WinDurangoConfigData data
		{
			.gamertag = std::string("TheDurangler2"),
			.gamerscore = 1500,
			.reputation = 5,
			.ageGroup = WinDurangoConfigData::AgeGroup::Unknown,
			.A = 0,
			.B = 0,
			.X = 0,
			.Y = 0,
			.Up = 0,
			.Down = 0,
			.Left = 0,
			.Right = 0,
			.Menu = 0,
			.View = 0,
			.LThumb = 0,
			.RThumb = 0,
			.LShoulder = 0,
			.RShoulder = 0,
			.LTrigger = 0,
			.RTrigger = 0,
			.MovementThumbY = 0,
			.MovementThumbYM = 0,
			.MovementThumbX = 0,
			.MovementThumbXM = 0,
			.MovementStick = "left",
			.MouseStick = "right",
		};
		SetData(data);
	}
}

WinDurangoConfig::WinDurangoConfig()
{
	ProcessConfigFile();
}