/*
================================================================================
DISCLAIMER AND LICENSE REQUIREMENT

This code is provided with the condition that if you use, modify, or distribute
this code in your project, you are required to make your project open source
under a license compatible with the GNU General Public License (GPL) or a
similarly strong copyleft license.

By using this code, you agree to:
1. Disclose your complete source code of any project incorporating this code.
2. Include this disclaimer in any copies or substantial portions of this file.
3. Provide clear attribution to the original author.

If you do not agree to these terms, you do not have permission to use this code.

================================================================================
*/
#pragma once

#include <string>
#include <mutex>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "../common/toml.hpp"

struct Config {
private:
    static inline toml::table configTable;
    static inline std::mutex configMutex;
    static inline bool initialized = false;
    static inline std::filesystem::path GetMyDllDir()
    {
        HMODULE hMod = nullptr;
        BOOL ok = ::GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(&GetMyDllDir),
            &hMod
       );
        if (!ok || !hMod) throw std::runtime_error("GetModuleHandleExW failed");

        WCHAR buf[ MAX_PATH ];
        if (GetModuleFileNameW(hMod, buf, MAX_PATH) == 0)
            throw std::runtime_error("GetModuleFileNameW failed");

        return std::filesystem::path(buf).parent_path();
    }
public:

    static inline std::wstring LoadGamertag(const std::string& config_path)
    {
        auto dllDir = GetMyDllDir();
        auto fullPath = dllDir / config_path;
        auto tbl = toml::parse_file(fullPath.string());

        if (auto gt = tbl[ "winrt_x" ][ "gamertag" ].value<std::string>())
        {
            // Convert std::string to std::wstring
            return std::wstring(gt->begin(), gt->end());
        }

        // fallback if missing
        return L"DefaultGamertag";
    }

    static void Load(const std::string& filename = "config.toml") {
        std::lock_guard<std::mutex> lock(configMutex);
        auto dllDir = GetMyDllDir();
        auto fullPath = dllDir / filename;
        if (!std::filesystem::exists(filename)) {
            std::cerr << "[Config] Config file " << filename << " does not exist. Creating default config." << std::endl;

            // Create default config
            configTable = toml::table{
                {"General", toml::table{
                    {"apply_patches", true},
                    {"discord", true}
                }},
                {"Content", toml::table{
                    {"license_mask", 0}
                }},
                {"winrt_x", toml::table{
                    {"gamertag", "durangler_override"}
				}},
				{"Logger", toml::table{
					{"enable_console", true},
                    {"flush_log", false},
					{"log_file", ""},
					{"log_level", 2}//Maximum level to be logged. (0=error, 1=warning, 2=info, 3=debug)
				}},
                {"Storage", toml::table{
                    {"storage_root", ""},
                    {"content_root", ""}
                }}
            };

            // Write it to disk
            try {
                std::ofstream file(fullPath);
				LOG_INFO("Writing default config to %s", filename.c_str());
                file << configTable;
                std::cerr << "[Config] Default config written to " << filename << std::endl;
            }
            catch (...) {
                std::cerr << "[Config] Failed to write default config to " << filename << std::endl;
            }

            initialized = true;
            return;
        }

        try {
            configTable = toml::parse_file(fullPath.string());
			LOG_DEBUG("[Config] Loaded config from %s", fullPath.string().c_str());
        }
        catch (const toml::parse_error& err) {
            std::cerr << "[Config] Failed to parse " << filename << ": " << err.description() << std::endl;
            configTable = toml::table{};
        }

        initialized = true;
    }

    template<typename T>
    static T Get(const std::string& key, const T& defaultValue) {
        std::lock_guard<std::mutex> lock(configMutex);
        if (!initialized) Load();

        auto val = configTable[ key ];
        if constexpr (std::is_same_v<T, std::string>) {
            if (val && val.is_string()) return val.value_or(defaultValue);
        }
        else if constexpr (std::is_same_v<T, int>) {
            if (val && val.is_integer()) return static_cast<int>(val.value_or(defaultValue));
        }
        else if constexpr (std::is_same_v<T, bool>) {
            if (val && val.is_boolean()) return val.value_or(defaultValue);
        }
        else if constexpr (std::is_same_v<T, double>) {
            if (val && val.is_floating_point()) return val.value_or(defaultValue);
        }
        else if constexpr (std::is_same_v<T, float>) {
            if (val && val.is_floating_point()) return static_cast<float>(val.value_or(defaultValue));
        }
        return defaultValue;
    }

    static void Set(const std::string& key, const toml::node& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        configTable.insert_or_assign(key, value);
    }

    static void Save(const std::string& filename = "config.toml") {
        std::lock_guard<std::mutex> lock(configMutex);
        try {
            std::ofstream file(filename);
            file << configTable;
        }
        catch (...) {
            std::cerr << "[Config] Failed to write config to " << filename << std::endl;
        }
    }
};

/*
Usage Example:

#include "Config.h"

int main() {
    Config::Load("config.toml");

    bool enableLogging = Config::Get<bool>("Logger.EnableLogging", true);
    int maxFPS = Config::Get<int>("Graphics.MaxFPS", 60);
    std::string username = Config::Get<std::string>("User.Name", "Guest");
    double gamma = Config::Get<double>("Graphics.Gamma", 2.2);

    Config::Set("User.LastLogin", toml::value("2025-06-30T20:30:00"));
    Config::Save("config.toml");
}
*/
