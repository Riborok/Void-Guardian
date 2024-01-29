#pragma once
#include <array>
#include <unordered_map>

#include "AbstractSpriteInfo.hpp"
#include "SpriteInfo.hpp"
#include "../additionally/Initialization.hpp"
#include "../element/ElementType.hpp"

template <size_t StartIndex, size_t Count, typename Abstract, typename Info,
    typename = std::enable_if_t<std::is_base_of_v<AbstractSimpleSpriteInfo, Abstract>>,
    typename = std::enable_if_t<std::is_base_of_v<SimpleSpriteInfo, Info>>>
class SpriteInfos final {
    typedef std::vector<Abstract> AbstractInfoVector;
    typedef std::vector<Info> InfoVector;
    typedef std::array<AbstractInfoVector, Count> AbstractInfos;
    typedef std::array<std::unordered_map<size_t, InfoVector>, Count> Infos;
    
    struct AbstractTextureLoadInfo final {
        static constexpr int DEFAULT_RANGE_VALUE = 0;
        AbstractInfoVector abstract_info_vector;
        sf::Vector2i texture_load_range;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        AbstractTextureLoadInfo(AbstractInfoVector&& info, const sf::Vector2i &texture_load_range
                                    = {DEFAULT_RANGE_VALUE, DEFAULT_RANGE_VALUE}):
                abstract_info_vector(std::move(info)), texture_load_range(texture_load_range){}
    };
    using ElementAbstractTextureLoadInfoList = ElementInitializationList<AbstractTextureLoadInfo>;

    const InfoVector& addInfoFromAbstract(const size_t index, const size_t num);
    void handleTextureLoad(const size_t index, const sf::Vector2i &texture_load_range);

    AbstractInfos _abstract_infos;
    Infos _infos;
public:
    SpriteInfos(const ElementAbstractTextureLoadInfoList &list);

    [[nodiscard]] const InfoVector& getInfo(const ElementType element_type, const size_t num);
    void addInfoFromAbstract(const ElementType element_type, const size_t num);

    ~SpriteInfos() noexcept = default;
    SpriteInfos(SpriteInfos&&) noexcept = default;
    SpriteInfos& operator=(SpriteInfos&&) noexcept = delete;
    SpriteInfos(const SpriteInfos&) noexcept = default;
    SpriteInfos& operator=(const SpriteInfos&) noexcept = delete;
};

#include "..\..\src\sprite\SpriteInfos.hpp"

typedef SpriteInfos<
    static_cast<size_t>(SIMPLE_TYPES_START),
    static_cast<size_t>(SIMPLE_TYPES_END) - static_cast<size_t>(SIMPLE_TYPES_START) + 1,
    AbstractSimpleSpriteInfo, SimpleSpriteInfo
> SimpleSpriteInfos;

typedef SpriteInfos<
    static_cast<size_t>(ANIMATED_TYPES_START),
    static_cast<size_t>(ANIMATION_TYPES_END) - static_cast<size_t>(ANIMATED_TYPES_START) + 1,
    AbstractAnimationSpriteInfo, AnimationSpriteInfo
> AnimatedSpriteInfos;