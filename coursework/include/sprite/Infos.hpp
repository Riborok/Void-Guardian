#pragma once
#include <array>
#include <unordered_map>

#include "AbstractInfo.hpp"
#include "Info.hpp"
#include "../additionally/Initialization.hpp"
#include "../element/ElementType.hpp"

template <typename T>
struct InitializerInfo final {
    static constexpr int DEFAULT_RANGE_VALUE = 0;
    T info;
    sf::Vector2i texture_load_range;

    // ReSharper disable once CppNonExplicitConvertingConstructor
    InitializerInfo(T&& info, const sf::Vector2i &texture_load_range = {DEFAULT_RANGE_VALUE, DEFAULT_RANGE_VALUE}):
        info(std::move(info)), texture_load_range(texture_load_range){}
};

template <size_t StartIndex, size_t Count, typename Abstract, typename Info,
    typename = std::enable_if_t<std::is_base_of_v<AbstractSimpleInfo, Abstract>>,
    typename = std::enable_if_t<std::is_base_of_v<SimpleInfo, Info>>>
class SpriteInfos final {
    typedef std::vector<Abstract> AbstractInfoVector;
    typedef std::vector<Info> InfoVector;
    typedef std::array<AbstractInfoVector, Count> AbstractInfos;
    typedef std::array<std::unordered_map<int, InfoVector>, Count> Infos;
    using InitializerInfo = InitializerInfo<AbstractInfoVector>;
    using InitList = InitializerList<InitializerInfo>;

    [[nodiscard]] const InfoVector& addInfoFromAbstract(const size_t index, const int num);
    void handleTextureLoad(const size_t index, const sf::Vector2i &texture_load_range);

    AbstractInfos _abstract_infos;
    Infos _infos;
public:
    SpriteInfos(const InitList &pairs);

    [[nodiscard]] const InfoVector& getInfo(const ElementType element_type, const int num);

    ~SpriteInfos() noexcept = default;
    SpriteInfos(SpriteInfos&&) noexcept = default;
    SpriteInfos& operator=(SpriteInfos&&) noexcept = delete;
    SpriteInfos(const SpriteInfos&) noexcept = default;
    SpriteInfos& operator=(const SpriteInfos&) noexcept = delete;
};

#include "../../src/sprite/Infos.hpp"

typedef SpriteInfos<
    static_cast<size_t>(SIMPLE_TYPES_START),
    static_cast<size_t>(SIMPLE_TYPES_END) - static_cast<size_t>(SIMPLE_TYPES_START) + 1,
    AbstractSimpleInfo, SimpleInfo
> SimpleSpriteInfos;

typedef SpriteInfos<
    static_cast<size_t>(ANIMATED_TYPES_START),
    static_cast<size_t>(ANIMATION_TYPES_END) - static_cast<size_t>(ANIMATED_TYPES_START) + 1,
    AbstractAnimationInfo, AnimationInfo
> AnimatedSpriteInfos;