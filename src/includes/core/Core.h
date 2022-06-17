#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
// Own libs
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>

namespace Cober {

    // From Hazel Engine
    template<typename T>
        using Unique = std::unique_ptr<T>;
        template<typename T, typename ... Args>
        constexpr Unique<T> CreateUnique(Args&& ... args) {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        using Ref = std::shared_ptr<T>;
        template<typename T, typename ... Args>
        constexpr Ref<T> CreateRef(Args&& ... args) {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
}

#define BIT(x)       (1 << x)
#define LOG(x)       std::cout << x << std::endl; 
#define LOG_ERROR(x) std::cerr << x << std::endl;
#define GET_ERROR()  LOG_ERROR(SDL_GetError());