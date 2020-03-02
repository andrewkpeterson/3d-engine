QT += core gui opengl

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp \
    src/warmup/WarmupApplication.cpp \
    src/engine/common/Application.cpp \
    src/engine/common/Screen.cpp \
    src/warmup/WarmupGameplayScreen.cpp \
    src/warmup/WarmupStartScreen.cpp \
    src/engine/common/GameWorld.cpp \
    src/engine/common/GameObject.cpp \
    src/engine/common/system/TickSystem.cpp \
    src/engine/common/component/CollisionComponent.cpp \
    src/engine/common/component/Component.cpp \
    src/engine/common/component/DrawableComponent.cpp \
    src/engine/common/component/TransformComponent.cpp \
    src/engine/common/system/System.cpp \
    src/engine/common/system/DrawSystem.cpp \
    src/engine/common/system/CollisionSystem.cpp \
    src/engine/util/Input.cpp \
    src/engine/common/system/ControlCallbackSystem.cpp \
    src/engine/util/TypeMap.cpp \
    src/engine/common/component/CameraComponent.cpp \
    src/engine/common/system/CameraSystem.cpp \
    src/engine/common/component/TickComponent.cpp \
    src/engine/common/component/ControlCallbackComponent.cpp \
    src/engine/common/component/CylinderCollisionComponent.cpp \
    src/engine/common/ui/UI.cpp \
    src/engine/common/ui/UIElement.cpp \
    src/engine/common/ui/UILabel.cpp \
    src/warmup/StartControlComponent.cpp \
    src/warmup/NPCChaseComponent.cpp \
    src/warmup/PlayerControlComponent.cpp \
    src/dungeon/DungeonApplication.cpp \
    src/dungeon/DungeonGameplayScreen.cpp \
    src/engine/common/map/MapGenerator.cpp \
    src/dungeon/DungeonPlayerControlComponent.cpp \
    src/dungeon/DungeonEnvironmentComponent.cpp \
    src/engine/graphics/Chunk.cpp \
    src/dungeon/environment/DungeonEnvironmentData.cpp \
    src/engine/common/component/PrimitiveDrawableComponent.cpp \
    src/engine/common/component/ChunkDrawableComponent.cpp \
    src/engine/common/component/SphereCollisionComponent.cpp \
    src/engine/common/component/StaticAABCollisionComponent.cpp \
    src/engine/common/component/DynamicAABCollisionComponent.cpp \
    src/engine/common/component/ChunkComponent.cpp \
    src/engine/common/system/ChunkStreamingSystem.cpp \
    src/dungeon/DungeonEnemyAIComponent.cpp \
    src/engine/common/ai/AStar.cpp \
    src/engine/common/ai/BTNode.cpp \
    src/engine/common/ai/Composite.cpp \
    src/engine/common/ai/Selector.cpp \
    src/engine/common/ai/Sequence.cpp \
    src/engine/common/ai/Action.cpp \
    src/engine/common/ai/Condition.cpp \
    src/dungeon/bt/DungeonApproachAction.cpp \
    src/dungeon/bt/DungeonAttackAction.cpp \
    src/dungeon/bt/DungeonPlayerNearCondition.cpp \
    src/engine/common/ai/Blackboard.cpp \
    src/engine/common/component/AIComponent.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/mainwindow.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h \
    src/warmup/WarmupApplication.h \
    src/engine/common/Application.h \
    src/engine/common/Screen.h \
    src/warmup/WarmupGameplayScreen.h \
    src/warmup/WarmupStartScreen.h \
    src/engine/common/GameWorld.h \
    src/engine/common/GameObject.h \
    src/engine/common/system/TickSystem.h \
    src/engine/common/component/CollisionComponent.h \
    src/engine/common/component/Component.h \
    src/engine/common/component/DrawableComponent.h \
    src/engine/common/component/TransformComponent.h \
    src/engine/common/system/System.h \
    src/engine/common/system/DrawSystem.h \
    src/engine/common/system/CollisionSystem.h \
    src/engine/util/Input.h \
    src/engine/common/system/ControlCallbackSystem.h \
    src/engine/util/TypeMap.h \
    src/engine/common/component/CameraComponent.h \
    src/engine/common/system/CameraSystem.h \
    src/engine/common/component/TickComponent.h \
    src/engine/common/component/ControlCallbackComponent.h \
    src/engine/common/component/CylinderCollisionComponent.h \
    src/engine/common/ui/UI.h \
    src/engine/common/ui/UIElement.h \
    src/engine/common/ui/UILabel.h \
    src/warmup/StartControlComponent.h \
    src/warmup/NPCChaseComponent.h \
    src/warmup/PlayerControlComponent.h \
    src/dungeon/DungeonApplication.h \
    src/dungeon/DungeonGameplayScreen.h \
    src/engine/common/map/MapGenerator.h \
    src/dungeon/DungeonPlayerControlComponent.h \
    src/dungeon/DungeonEnvironmentComponent.h \
    src/engine/graphics/Chunk.h \
    src/dungeon/environment/DungeonEnvironmentData.h \
    src/engine/common/component/PrimitiveDrawableComponent.h \
    src/engine/common/component/ChunkDrawableComponent.h \
    src/engine/common/component/SphereCollisionComponent.h \
    src/engine/common/component/StaticAABCollisionComponent.h \
    src/engine/common/component/DynamicAABCollisionComponent.h \
    src/engine/common/component/ChunkComponent.h \
    src/engine/common/system/ChunkStreamingSystem.h \
    src/dungeon/DungeonEnemyAIComponent.h \
    src/engine/common/ai/AStar.h \
    src/engine/common/ai/BTNode.h \
    src/engine/common/ai/Composite.h \
    src/engine/common/ai/Selector.h \
    src/engine/common/ai/Sequence.h \
    src/engine/common/ai/Action.h \
    src/engine/common/ai/Condition.h \
    src/dungeon/bt/DungeonApproachAction.h \
    src/dungeon/bt/DungeonAttackAction.h \
    src/dungeon/bt/DungeonPlayerNearCondition.h \
    src/engine/common/ai/Blackboard.h \
    src/engine/common/component/AIComponent.h

FORMS += src/mainwindow.ui

RESOURCES += \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag

INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
