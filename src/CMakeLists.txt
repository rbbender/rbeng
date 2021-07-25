include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(rbengine STATIC "glad.c" "../include/CFont.h" "CFont.cpp" "../include/CText.h" "../include/CDrawable.h" "../include/CShaderProgram.h" "CShaderProgram.cpp" "../include/CTexture.h" "CTexture.cpp" "../include/CDecal.h" "CDecal.cpp" "CText.cpp" "../include/CWindow2D.h" "CWindow2D.cpp" "../include/rbengine.h" "rbengine.cpp" "../include/common.h" "common.cpp"  "../include/CBasicWindow.h" "../include/CCircle.h" "CCircle.cpp" "../include/glwrappers/CGLBaseObject.h" "../include/glwrappers/CGLTexture.h" "../include/glwrappers/CGLTexture.cpp" "../include/glwrappers/CGLBuffer.h" "../include/glwrappers/CGLBuffer.cpp" "../include/glwrappers/CGLVertexArray.h" "../include/glwrappers/CGLVertexArray.cpp" "../include/glwrappers/glwrappers.h")
set_target_properties(rbengine PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:rocket>")
target_link_libraries(rbengine PRIVATE project_options
                        CONAN_PKG::spdlog
                        CONAN_PKG::glfw
                        CONAN_PKG::glm
                        CONAN_PKG::freetype
                        )

add_custom_command(TARGET rbengine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" $<TARGET_FILE_DIR:rbengine>/shaders )
add_custom_command(TARGET rbengine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/fonts" $<TARGET_FILE_DIR:rbengine>/fonts )
add_custom_command(TARGET rbengine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/include" $<TARGET_FILE_DIR:rbengine>/include )
