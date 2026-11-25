CC = clang
CXX = clang++
WIN_CXX = x86_64-w64-mingw32-clang++
CCFLAGS = -Wall -Wextra -Iinclude
CXXFLAGS = -std=c++17 $(CCFLAGS)
WINCXXFLAGS = -std=c++17 -Iinclude -O2 -static -static-libgcc -static-libstdc++
TARGET = game
WIN_TARGET = publish/windows/game.exe
TESTFLAGS = MANGOHUD=1 mangohud __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only

SRC = $(shell find src -name '*.cpp') $(shell find src -name '*.c')
OBJ_DIR = build
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/src/%.o)
OBJ := $(OBJ:src/%.c=$(OBJ_DIR)/src/%.o)

LIBS_LINUX = -lglfw    \
	     -lGL      \
	     -ldl      \
	     -lX11     \
	     -lXrandr  \
	     -lXi      \
	     -lXxf86vm \
	     -lXcursor 

LIBS_WINDOWS = -L$(MINGW_GLFW)/lib \
	       -lglfw3dll          \
	       -lopengl32          \
	       -lgdi32             \
	       -lwinmm		   

WINDOWS_DLLS = /usr/x86_64-w64-mingw32/bin/glfw3.dll \
	       /usr/x86_64-w64-mingw32/bin/libassimp.dll \
	       /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll \
	       /usr/x86_64-w64-mingw32/bin/libssp-0.dll \
	       /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll \
	       /usr/x86_64-w64-mingw32/bin/zlib1.dll \
	       /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "CXX   $(TARGET)"
	@$(CXX) $(OBJ) -o $(TARGET) $(LIBS_LINUX)

$(OBJ_DIR)/src/%.o: src/%.cpp
	@if [ ! -d $(dir $@z) ]; then \
		echo "MKDIR $(dir $@z)"; \
		mkdir -p $(dir $@z); \
	fi
	@echo "CXX   $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/src/%.o: src/%.c
	@if [ ! -d $(dir $@z) ]; then \
		echo "MKDIR $(dir $@z)"; \
		mkdir -p $(dir $@z); \
	fi
	@echo "CC    $<"
	@$(CC) $(CCFLAGS) -c $< -o $@

windows:
	mkdir -p build
	mkdir -p publish/windows

	$(WIN_CXX)       \
	$(WINCXXFLAGS)   \
	$(SRC)           \
	-o $(WIN_TARGET) \
	$(LIBS_WINDOWS)  \
	-mwindows

	cp $(MINGW_GLFW)/bin/glfw3.dll publish/windows/

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -rf publish

test: all
	@echo "RUN   $(TARGET)"
	@$(TESTFLAGS) gdb -q -batch -x debug.gdb --args ./$(TARGET)

.PHONY: all clean test windows publish
