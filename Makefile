.PHONY: all build run clean rebuild

BUILD_DIR = build
EXEC = $(BUILD_DIR)/elevator_control

all: build

build:
	@echo "Building project..."
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --parallel

run: build
	@echo "Running..."
	./$(EXEC)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build
