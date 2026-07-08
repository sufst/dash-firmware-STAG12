.PHONY: all configure build flash clean

# Defaults to the Debug preset, override with `make PRESET=Release ...`
PRESET ?= Debug
BUILD_DIR = build/$(PRESET)
CMAKE := $(shell which cmake)

all build: $(BUILD_DIR)/CMakeCache.txt
	$(CMAKE) --build --preset $(PRESET)

$(BUILD_DIR)/CMakeCache.txt:
	$(CMAKE) --preset $(PRESET)

flash: $(BUILD_DIR)/CMakeCache.txt
	$(CMAKE) --build --preset $(PRESET) --target flash

clean:
	rm -rf build
