#pragma once
#include "Polygon.h"
#include "../../game/identifiable/Identifiable.h"

class IdPolygon : public Identifiable, public Polygon {
public:
    virtual ~IdPolygon() noexcept override = default;
    IdPolygon(const IdPolygon&) noexcept = default;
    IdPolygon& operator=(const IdPolygon&) noexcept = default;
    IdPolygon(IdPolygon&&) noexcept = default;
    IdPolygon& operator=(IdPolygon&&) noexcept = default;
protected:
    explicit IdPolygon(const int id) : Identifiable(id) { }
};
