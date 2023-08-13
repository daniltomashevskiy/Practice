#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

class Configuration
{
public:
    // Конструктор класса Configuration.
    Configuration(const std::string& config_path_);

    // Метод для чтения и разбора файла конфигурации.
    bool read_config();
    
    // Метод для получения значения точности.
    double get_precision() const;

    // Метод для получения значения точности угла.
    double get_precision_angle() const;

private:
    std::string config_path;
    double precision;
    double precision_angle;
};