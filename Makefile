OUTPUT_DIR=build
VERSION=Debug
CONFIGURE=./configure

all: cppCodeFeaturesExtractor
.PHONY: cppCodeFeaturesExtractor

$(OUTPUT_DIR)/Makefile:
	@make prepare

$(OUTPUT_DIR)/CMakeFiles:
	$(CONFIGURE) -DCMAKE_BUILD_TYPE=$(VERSION)

prepare:$(OUTPUT_DIR)/CMakeFiles
	@cmake --build $(OUTPUT_DIR) --target libgit2
	@rm -rf $(OUTPUT_DIR)
	@$(CONFIGURE) -DCMAKE_BUILD_TYPE=$(VERSION)

cppCodeFeaturesExtractor: $(OUTPUT_DIR)/Makefile
	@cmake --build $(OUTPUT_DIR) --target cppCodeFeaturesExtractor