#!/bin/bash

OUTPUT="game"
SRC_DIR="src"
INCLUDE_DIR="include"

# Encontrar todos los .cpp y .asm
CPP_SOURCES=$(find "$SRC_DIR" -name '*.cpp')
ASM_SOURCES=$(find "$SRC_DIR" -name '*.asm')
ASM_OBJECTS=""

# Verificación de herramientas necesarias
command -v fltk-config >/dev/null 2>&1 || { echo "❌ FLTK no está instalado. Ejecutá: sudo apt install libfltk1.3-dev"; exit 1; }
command -v nasm >/dev/null 2>&1 || { echo "❌ NASM no está instalado. Ejecutá: sudo apt install nasm"; exit 1; }

# Flags
FLTK_FLAGS=$(fltk-config --cxxflags)
FLTK_LIBS=$(fltk-config --ldflags)
EXTRA_LIBS="-lfltk_images"
DEBUG_FLAGS="-g -Og"

# Compilar todos los archivos ASM
echo "🔧 Compilando archivos ensamblador..."
for asm_file in $ASM_SOURCES; do
    obj_file="${asm_file%.asm}.o"
    nasm -f elf64 "$asm_file" -o "$obj_file"
    
    if [ $? -ne 0 ]; then
        echo "❌ Error al compilar $asm_file"
        exit 1
    fi

    ASM_OBJECTS="$ASM_OBJECTS $obj_file"
done

# Compilar C++ y enlazar
echo "🛠️  Compilando C++ y enlazando con ensamblador..."
g++ $CPP_SOURCES $ASM_OBJECTS -no-pie -I"$INCLUDE_DIR" $FLTK_FLAGS $FLTK_LIBS $EXTRA_LIBS $DEBUG_FLAGS -o "$OUTPUT"

if [ $? -eq 0 ]; then
    echo "✅ Compilado correctamente: ./$OUTPUT"
    echo
    ./"$OUTPUT"
else
    echo "❌ Error de compilación"
fi
