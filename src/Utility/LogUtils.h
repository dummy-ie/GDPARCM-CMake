#pragma once
#include <string>
#include <iostream>
#include <winerror.h>


constexpr bool DEBUG_LOGS = true;
constexpr bool ERROR_LOGS = true;
constexpr bool SUCCESS_LOGS = false;

namespace gd
{
	class LogUtils
	{
	public:
		template <class T>
		static void log(T* sender, const std::string& message)
		{
			if constexpr (!DEBUG_LOGS)
				return;

			std::cout << "[" << getType(sender) << " DEBUG]: " << message << '\n';
		}

		static void log(const std::string& message)
		{
			if constexpr (!DEBUG_LOGS)
				return;

			std::cout << "[DEBUG]: " << message << '\n';
		}

		template <class T>
		static bool logHResult(T* sender, const long hResult)
		{
			if (FAILED(hResult)) {
				const std::string message = std::system_category().message(hResult);
				log(sender, message);
				throw std::exception(message.data());
				return false;
			}

			if (SUCCESS_LOGS)
				log(sender, "Operation was successful.");

			return true;
		}

		template <class T>
		static bool logBool(T* sender, const bool bResult)
		{
			if (!bResult) {
				std::string message = "[" + std::to_string(bResult) + "] Operation failed!";
				log(sender, message);
				throw std::exception(message.data());
				return false;
			}

			if (SUCCESS_LOGS)
				log(sender, "Operation was successful.");

			return true;
		}

		template <class T>
		static void error(T* sender, const std::string& msg)
		{
			if constexpr (!ERROR_LOGS)
				return;

			std::string message = "[" + getType(sender) + " ERROR]: " + msg + '\n';
			std::cout << message;
			throw std::exception(message.data());
		}

	private:
		template <class T>
		static std::string getType(T* type)
		{
			return typeid(*type).name();
		}
	};
}