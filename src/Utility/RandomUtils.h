#pragma once
#include <random>
#include <SFML/Graphics.hpp>

namespace gd
{
	class RandomUtils
	{
	public:
		template <typename T>
		static T random(const T& min, const T& max) {
			static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

			if constexpr (std::is_floating_point_v<T>) {
				std::uniform_real_distribution<T> dist(min, max);
				return dist(gen);
			}
			else if constexpr (std::is_integral_v<T>) {
				std::uniform_int_distribution<T> dist(min, max);
				return dist(gen);
			}

			return T{};
		}

		template <typename T>
		static sf::Vector2<T> randomVector2(const sf::Vector2<T>& min, const sf::Vector2<T>& max) {
			return { random(min.x, max.x), random(min.y, max.y) };
		}

		// Random UNIFORM vector. 
		template <typename T>
		static sf::Vector2<T> randomVector2(const T& min, const T& max) {
			T r = random(min, max);
			return { r , r };
		}

		template <typename T>
		static sf::Vector3<T> randomVector3(const sf::Vector3<T>& min, const sf::Vector3<T>& max) {
			return { random(min.x, max.x), random(min.y, max.y), random(min.z, max.z) };
		}

	private:
		static std::random_device rd;
		static std::mt19937 gen;
	};
}