#pragma once
#include "BuildingData.hpp"
#include "../../additionally/LevelParameters.hpp"

struct BackgroundInfo final {
    size_t num;
    BackgroundData background_data;
    BackgroundInfo(const size_t num, const BackgroundData& background_data): num(num), background_data(background_data) { }
};

struct BoundaryInfo final {
    size_t num;
    BoundaryData boundary_data;
    BoundaryInfo(const size_t num, const BoundaryData &boundary_data): num(num), boundary_data(boundary_data){ }
};

struct BuildingInfo final {
    BackgroundInfo background_info;
    BoundaryInfo boundary_info;
    BuildingInfo(const BuildingData &building_data, const size_t lvl):
        background_info(LevelParameters::getBackgroundNum(lvl), building_data.background_data),
        boundary_info(LevelParameters::getBoundaryNum(lvl), building_data.boundary_data) {}
};