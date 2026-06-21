# Archivo: Makefile
CXX      = C:/msys64/mingw64/bin/g++
CXXFLAGS = -std=c++17 -Wall -I include -I "C:/msys64/mingw64/include" -DWIN32_LEAN_AND_MEAN -DCURL_STATICLIB
LDFLAGS  = -L "C:/msys64/mingw64/lib" -lcurl -lws2_32 -lwldap32 -lssl -lcrypto -lzstd -lbrotlidec -lbrotlicommon -lwinmm
SRC_DIR  = src
BUILD_DIR = build
TARGET = galaxias.exe

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
