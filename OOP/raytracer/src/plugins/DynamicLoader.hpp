/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** DynamicLoader
*/

#pragma once

#include <string>
#include <stdexcept>
#include <utility>
#include <dlfcn.h>

namespace raytracer::plugins {
    class DynamicLoaderError : public std::exception {
    public:
        explicit DynamicLoaderError(std::string text) : text(std::move(text))
        {};

        [[nodiscard]] const char *what() const noexcept override
        {
            return this->text.c_str();
        };

    private:
        std::string text;
    };

    template<typename T>
    class DynamicLoader {
    public:
        explicit DynamicLoader(std::string path) : _path(std::move(path))
        {};

        ~DynamicLoader()
        {
            delete this->plugin;

            if (this->handle == nullptr)
                return;

            dlclose(this->handle);
        }

        void load(const std::string &symbol)
        {
            void *entrypoint;

            this->handle = dlopen(_path.c_str(), RTLD_LAZY);
            if (handle == nullptr)
                throw DynamicLoaderError(dlerror());
            entrypoint = dlsym(handle, symbol.c_str());
            if (entrypoint == nullptr)
                throw DynamicLoaderError(dlerror());
            this->plugin = reinterpret_cast<T *(*)()>(entrypoint)();
        }

        T *get() const
        {
            return this->plugin;
        }

    private:
        std::string _path;
        void *handle = nullptr;
        T *plugin = nullptr;
    };
}
