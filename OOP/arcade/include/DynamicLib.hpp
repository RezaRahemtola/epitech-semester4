/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DynamicLib
*/

#pragma once

#include <string>
#include <dlfcn.h>
#include "Arcade.hpp"

namespace arcade {
    template<typename T>
    class DynamicLib {
        public:
            DynamicLib() = default;

            ~DynamicLib()
            {
                this->close();
            }

            void load(const std::string &path)
            {
                void *entrypoint;

                this->close();
                this->handle = dlopen(path.c_str(), RTLD_LAZY);
                if (handle == nullptr)
                    throw arcade::Error(dlerror());
                entrypoint = dlsym(handle, "gameEntrypoint");
                if (entrypoint == nullptr) {
                    entrypoint = dlsym(handle, "displayEntrypoint");
                    if (entrypoint == nullptr)
                        throw arcade::Error(dlerror());
                }
                this->lib = reinterpret_cast<T *(*)()>(entrypoint)();
            }

            void close()
            {
                delete this->lib;
                this->lib = nullptr;

                if (this->handle == nullptr)
                    return;

                dlclose(this->handle);
                this->handle = nullptr;
            }

            T *get() const
            {
                return this->lib;
            }

        private:
            void *handle = nullptr;
            T *lib = nullptr;
    };
}
