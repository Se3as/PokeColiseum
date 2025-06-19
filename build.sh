#!/bin/bash

OUTPUT="game"
SRC_DIR="src"
INCLUDE_DIR="include"
ASM_DIR="src"

# Verificar FLTK
command -v fltk-config >/dev/null 2>&1 || { echo "❌ FLTK no está instalado. Ejecutá: sudo apt install libfltk1.3-dev"; exit 1; }

# Flags
FLTK_FLAGS=$(fltk-config --cxxflags)
FLTK_LIBS=$(fltk-config --ldflags)
EXTRA_LIBS="-lfltk_images"
DEBUG_FLAGS="-g -Og"

echo "🔧 Compilando archivos fuente..."

# Compilar archivos .asm a .o
ASM_OBJECTS=""
for asm_file in "$ASM_DIR"/*.asm; do
    obj_file="${asm_file%.asm}.o"
    nasm -f elf64 "$asm_file" -o "$obj_file"
    if [ $? -ne 0 ]; then
        echo "❌ Error compilando $asm_file"
        exit 1
    fi
    ASM_OBJECTS+=" $obj_file"
done

# Compilar archivos .cpp
CPP_SOURCES=$(find "$SRC_DIR" -name '*.cpp' ! -name 'testing.cpp')
g++ $CPP_SOURCES $ASM_OBJECTS -I"$INCLUDE_DIR" $FLTK_FLAGS $FLTK_LIBS $EXTRA_LIBS $DEBUG_FLAGS -no-pie -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "✅ Compilado correctamente: ./$OUTPUT"
    echo
    ./$OUTPUT
else
    echo "❌ Error de compilación"
fi