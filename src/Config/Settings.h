#pragma once

#include <cstdint>
#include <SFML/System/Time.hpp>

static constexpr sf::Time FixedDeltaTime = sf::seconds(1.f / 60.f);
static constexpr uint8_t FramerateCap = 60;

static constexpr uint16_t WindowWidth = 1920u;
static constexpr uint16_t WindowHeight = 1080u;