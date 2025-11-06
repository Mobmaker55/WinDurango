#include "pch.h"
#include "WinDurangoConfig.h"
#include <winrt/Windows.Storage.h>
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
		Game = "Unknown"
		AgeGroup = "Adult"
	)"sv;

	try
	{
		/*
		* We need to use WinRT Storage APIs in UWP
		*/
		StorageFolder localFolder = ApplicationData::Current().LocalFolder();
		std::string pathStr(localFolder.Path().begin(), localFolder.Path().end());
		if (!std::filesystem::exists(pathStr + "/config.toml")) {
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

		const WinDurangoConfigData data
		{
			.gamertag = std::string(gamertag_opt.value()),
			.gamerscore = gamerscore_opt.value_or(0),
			.reputation = reputation_opt.value_or(0),
			.ageGroup =
				agegroup_opt.has_value()
					? (agegroup_opt.value() == "Child" ? WinDurangoConfigData::AgeGroup::Child
						: agegroup_opt.value() == "Teen" ? WinDurangoConfigData::AgeGroup::Teen
						: agegroup_opt.value() == "Adult" ? WinDurangoConfigData::AgeGroup::Adult
						: WinDurangoConfigData::AgeGroup::Unknown)
					: WinDurangoConfigData::AgeGroup::Unknown,
			.game =
				game_opt.has_value()
					? (game_opt.value() == "Minecraft" ? WinDurangoConfigData::Game::Minecraft
						: game_opt.value() == "Forza Horizon 2" ? WinDurangoConfigData::Game::Forza_Horizon_2
						: WinDurangoConfigData::Game::Unknown)
					: WinDurangoConfigData::Game::Unknown
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
			.ageGroup = WinDurangoConfigData::AgeGroup::Unknown
		};
	}
}

WinDurangoConfig::WinDurangoConfig()
{
	ProcessConfigFile();
}