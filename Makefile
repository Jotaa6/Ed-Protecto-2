# Archivo: Makefile
# Descripcion: Compilacion del proyecto para Windows con MinGW y MSYS2
# Creado: 2026
# Autores: <integrantes>

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -I include -I "C:/msys64/mingw64/include"
LIBS     = -L "C:/msys64/mingw64/lib" -lcurl
SRC_DIR  = src
BUILD_DIR = build
TARGET   = galaxias.exe

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET) 2>nul || true

.PHONY: all clean
