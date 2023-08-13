#include "Configuration.h"

Configuration::Configuration(const std::string& config_path_)
{
    config_path = config_path_;
    precision = 1e-5;
    precision_angle = 1e-2;
}

bool Configuration::read_config()
{
    std::ifstream file(config_path);
    if (!file.is_open())
    {
        std::cout << "Unable to open the config file: " << config_path << std::endl;
        return false;
    }

    try
    {
        nlohmann::json jsonData;
        file >> jsonData;

        precision = jsonData["precision"];
        precision_angle = jsonData["precision_angle"];
    }
    catch (const nlohmann::json::exception& ex)
    {
        std::cout << "Error while parsing the config file: " << ex.what() << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

double Configuration::get_precision() const
{
    return precision;
}

double Configuration::get_precision_angle() const
{
    return precision_angle;
}