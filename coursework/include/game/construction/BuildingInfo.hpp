#pragma once
#include "BuildingParameters.hpp"
#include "../../additionally/LevelParameters.hpp"

struct BackgroundInfo final {
    size_t num;
    BackgroundParameters background_parameters;
    BackgroundInfo(const size_t num, const BackgroundParameters& background_parameters): num(num),
        background_parameters(background_parameters) { }
};

struct BoundaryInfo final {
    size_t num;
    BoundaryParameters boundary_parameters;
    BoundaryInfo(const size_t num, const BoundaryParameters &boundary_parameters): num(num), boundary_parameters(boundary_parameters){ }
};

struct BuildingInfo final {
    BackgroundInfo background_info;
    BoundaryInfo boundary_info;
    BuildingInfo(const BuildingParameters &building_parameters, const size_t lvl):
        background_info(LevelParameters::getBackgroundNum(lvl), building_parameters.background_parameters),
        boundary_info(LevelParameters::getBoundaryNum(lvl), building_parameters.boundary_parameters) {}
};