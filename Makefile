PLUGIN_NAME = FirstVST

BUILD_DIR = build

APP_PATH = $(BUILD_DIR)/FirstVST_artefacts/Standalone/$(PLUGIN_NAME).app

.PHONY: all clean open

all: delete_appledouble cmake_build app

re: clean delete_appledouble cmake_build app

delete_appledouble:
	@echo "Deleting AppleDouble files..."
	@find . -name '._*' -type f -delete

cmake_build:
	@echo "Configuring and building project..."
	@cmake -S . -B  $(BUILD_DIR)  -DFETCHCONTENT_QUIET=Off
	@cmake --build $(BUILD_DIR)

app:
	@echo "Opening the app..."
	@open $(APP_PATH)

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)