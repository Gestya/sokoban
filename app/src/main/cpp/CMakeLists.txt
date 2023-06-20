# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("sokoban")

# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(sokoban SHARED
		main.cpp
		AppCore.cpp
		AndroidOut.cpp
		# -- Core
		core/eventlistener.cpp
		core/eventmanager.cpp
		core/taskmanager.cpp
		core/commandmanager.cpp
		# -- Graphics
		graphics/camera.cpp
		graphics/renderer.cpp
		graphics/shader.cpp
		graphics/textureAsset.cpp
		graphics/utility.cpp
		graphics/Shader_2D_src.cpp
		graphics/Shader_3D_src.cpp
		# -- Game
		game/objects/wall.cpp
		game/objects/space.cpp
		game/objects/dude.cpp
		game/objects/box.cpp
		game/objects/target.cpp
		game/field.cpp
		game/manager.cpp
		game/factory.cpp
		# --Ui
		ui/widgets/widget.cpp
		ui/widgets/button.cpp
		ui/widgets/image.cpp
		ui/widgets/window.cpp
		ui/widgets/desktop.cpp
		ui/factory.cpp
		ui/ui.cpp)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(sokoban
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)