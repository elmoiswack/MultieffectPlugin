PLUGIN_NAME = FirstVST

BUILD_DIR = build

APP_PATH = $(BUILD_DIR)/FirstVST_artefacts/Standalone/$(PLUGIN_NAME).app
EXECUTABLE_PATH = $(BUILD_DIR)/FirstVST_artefacts/Standalone/$(PLUGIN_NAME).app/Contents/MacOS/FirstVST

.PHONY: all app re delete_appledouble cmake_build openapp executable clean

all: delete_appledouble cmake_build executable

app: delete_appledouble cmake_build openapp

re: clean delete_appledouble cmake_build executable

delete_appledouble:
	@echo "Deleting AppleDouble files..."
	@find . -name '._*' -type f -delete

cmake_build:
	@echo "Configuring and building project..."
	@cmake -S . -B  $(BUILD_DIR)  -DFETCHCONTENT_QUIET=Off
	@cmake --build $(BUILD_DIR)

openapp:
	@echo "Opening the app..."
	@open $(APP_PATH)

executable:
	@echo "Running debug mode..."
	@./${EXECUTABLE_PATH}

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)