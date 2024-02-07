#include <stdio.h>
#include <memory>

namespace ly
{
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;


//macro
#define LOG(M, ...) printf(M"\n", ##__VA_ARGS__);
}