add_library(base SHARED
    src/Scene.cpp src/Scene.hpp
    src/camera/Camera.cpp src/camera/Camera.hpp
    plugins/base/Base.cpp plugins/base/Base.hpp
    plugins/base/lights/PointLight.cpp plugins/base/lights/PointLight.hpp
    plugins/base/shapes/PlaneShape.cpp plugins/base/shapes/PlaneShape.hpp
    plugins/base/shapes/ShereShape.cpp plugins/base/shapes/SphereShape.hpp
    plugins/base/shapes/CylinderShape.cpp plugins/base/shapes/CylinderShape.hpp
    plugins/base/shapes/ConeShape.cpp plugins/base/shapes/ConeShape.hpp
    plugins/base/output/SFMLOutputGenerator.cpp plugins/base/output/SFMLOutputGenerator.hpp
    plugins/base/output/PPMOutputGenerator.cpp plugins/base/output/PPMOutputGenerator.hpp
    plugins/base/render/RenderBasic.cpp plugins/base/render/RenderBasic.hpp
    )
target_include_directories(base PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(base PRIVATE cxx_std_20)
target_link_libraries(raytracer PRIVATE sfml-graphics sfml-window sfml-system)
set_target_properties(base PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/plugins"
    PREFIX ""
    SUFFIX ".plugin.so"
    )
