#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <functional>
#include <vector>
#include <memory>


namespace gon {

	// Scope for control lifetime and other
	// sand class, etc.

	template<typename T>
	using u_ptr = std::unique_ptr<T>;

	template<typename T>
	using s_ptr  = std::shared_ptr<T>;
}

