add_library(rbengine STATIC "glad.c" "CFont.h" "CFont.cpp" "CText.h" "CDrawable.h" "CShaderProgram.h" "CShaderProgram.cpp" "CTexture.h" "CTexture.cpp" "CDecal.h" "CDecal.cpp" "CText.cpp" "CWindow2D.h" "CWindow2D.cpp" "rbe.h" "rbe.cpp" "common.h" "common.cpp"  "CBasicWindow.h" "CCircle.h" "CCircle.cpp" "glwrappers/CGLBaseObject.h" "glwrappers/CGLTexture.h" "glwrappers/CGLTexture.cpp" "glwrappers/CGLBuffer.h" "glwrappers/CGLBuffer.cpp" "glwrappers/CGLVertexArray.h" "glwrappers/CGLVertexArray.cpp" "glwrappers/glwrappers.h")
set_target_properties(rbengine PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:rocket>")
target_link_libraries(rbengine PRIVATE project_options
                        CONAN_PKG::spdlog
                        CONAN_PKG::glfw
                        CONAN_PKG::glm
                        CONAN_PKG::freetype
                        )
add_custom_command(TARGET rbengine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" $<TARGET_FILE_DIR:rbengine>/shaders )
add_custom_command(TARGET rbengine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/fonts" $<TARGET_FILE_DIR:rbengine>/fonts )
