#include "pch.h"
#include "Windows.Xbox.System.UserDisplayInfo.h"
#include "Windows.Xbox.System.UserDisplayInfo.g.cpp"

namespace winrt::Windows::Xbox::System::implementation
{
	hstring UserDisplayInfo::Gamertag()
	{
		LOG_INFO("UserDisplayInfo::Gamertag() called");
		
		return winrt::to_hstring(wdcfg.GetData().gamertag);
	}

	uint32_t UserDisplayInfo::GamerScore()
	{
		LOG_INFO("UserDisplayInfo::GamerScore() called");

		return wdcfg.GetData().gamerscore;
	}

	hstring UserDisplayInfo::ApplicationDisplayName()
	{
		LOG_INFO("UserDisplayInfo::GameDisplayName() called");

		return winrt::to_hstring(wdcfg.GetData().gamertag);
	}

	hstring UserDisplayInfo::GameDisplayName()
	{
		LOG_INFO("UserDisplayInfo::GameDisplayName() called");

		return winrt::to_hstring(wdcfg.GetData().gamertag);
	}

	int32_t UserDisplayInfo::Reputation()
	{
		LOG_INFO("UserDisplayInfo::Reputation() called");

		return wdcfg.GetData().reputation;
	}

	UserAgeGroup UserDisplayInfo::AgeGroup()
	{
		LOG_INFO("UserDisplayInfo::AgeGroup() called");

		switch (wdcfg.GetData().ageGroup) {
			case WinDurangoConfigData::AgeGroup::Adult:
				return UserAgeGroup::Adult;
			case WinDurangoConfigData::AgeGroup::Child:
				return UserAgeGroup::Child;
			case WinDurangoConfigData::AgeGroup::Teen:
				return UserAgeGroup::Teen;
			case WinDurangoConfigData::AgeGroup::Unknown:
				return UserAgeGroup::Unknown;
			default:
				return UserAgeGroup::Unknown;
		}
	}

	Foundation::Collections::IVectorView<uint32_t> UserDisplayInfo::Privileges()
	{   
		LOG_INFO("UserDisplayInfo::Privileges() called");

		const auto vector = winrt::single_threaded_vector<uint32_t>();

		vector.Append(1);

		return vector.GetView();
	}
}