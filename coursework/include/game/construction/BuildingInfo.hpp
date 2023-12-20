#pragma once
#include "BuildingData.hpp"
#include "../../additionally/LevelParameters.hpp"

struct BackgroundInfo final {
    int num;
    BackgroundData background_data;
    BackgroundInfo(const int num, const BackgroundData& background_data): num(num), background_data(background_data) { }
};

struct BoundaryInfo final {
    int num;
    BoundaryData boundary_data;
    BoundaryInfo(const int num, const BoundaryData &boundary_data): num(num), boundary_data(boundary_data){ }
};

struct BuildingInfo final {
    BackgroundInfo background_info;
    BoundaryInfo boundary_info;
    BuildingInfo(const BuildingData &building_data, const size_t lvl):
        background_info(LevelParameters::getBackgroundNum(lvl), building_data.background_data),
        boundary_info(LevelParameters::getBoundaryNum(lvl), building_data.boundary_data) {}
};