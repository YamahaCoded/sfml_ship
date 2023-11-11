# Compiler
CC = g++

# Flags 
CFLAGS = -DSFML_STATIC -Os -s 

# Libs
LIBS = 
LIBSWINDOWS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -mwindows -lopenal32 -static-libstdc++ -static-libgcc
LIBSLINUX = -lsfml-graphics -lsfml-window -lsfml-system
# Source files
SRCS = src/*.cpp 

# Name of binary
TARGET = Ship

# Check if some libs and folders are unnecessary
ifeq ($(OS), Windows_NT)
	INCLUDE_FOLDER = -Iinclude
	LIB_FOLDER = -Llib
else 
	INCLUDE_FOLDER =
	LIB_FOLDER = 
	LIBS := $(filter-out LIBSWINDOWS, $(-lsfml-graphics -lsfml-window -lsfml-system))
endif

# Build binary
$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(INCLUDE_FOLDER) $(LIB_FOLDER) $(LIBS) $(CFLAGS) 

# Clean temp files
clean:
	rm -f $(TARGET)

# Rebuild 
rebuild: clean $(TARGET)
