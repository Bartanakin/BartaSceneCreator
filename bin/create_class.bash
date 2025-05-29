#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <classname>"
    exit 1
fi

classname="$1"
root_path="/home/bartanakin/repos/BartaSceneCreator"
current_dir="$(pwd)"

if [[ "$current_dir" != "$root_path/include"* ]]; then
    echo "Error: This script must be run within a subdirectory of $root_path."
    exit 1
fi

relative_dir="$(echo "$current_dir" | sed -n 's|.*\/include/||p')"
rootDirectoryNamespace="Barta::$(echo "$relative_dir" | sed 's|/|::|g')"

# Create the header file
header_dir="$root_path/include/$relative_dir"
header_file="$root_path/include/$relative_dir/$classname.h"

mkdir -p "$header_dir"

if [ ! -f "$header_file" ]; then
    echo "#pragma once" > "$header_file"
    echo "#include <pch.h>" >> "$header_file"
    echo "" >> "$header_file"
    echo "namespace $rootDirectoryNamespace {" >> "$header_file"
    echo "class $classname {};" >> "$header_file"
    echo "}" >> "$header_file"

    echo "Header file '$header_file' created successfully."
else
    echo "Header file '$header_file' already exists."
fi

# Traverse up the directory tree to ensure all CMakeLists.txt files exist and include subdirs
add_cmakelists_recursively() {
    local root_dir="$1"
    local relative_dir="$2"
    local classname="$3"
    local target_name="$4"
    local dir="$root_dir/$relative_dir"

    mkdir -p "$dir"

    # Ensure base CMakeLists.txt exists
    base_cmake="$dir/CMakeLists.txt"
    if [ ! -f "$base_cmake" ]; then
        touch "$base_cmake"
        echo "Created base CMakeLists.txt at $base_cmake"
    fi

    # Ensure the source file is added to target_sources
    if ! grep -q "target_sources(${target_name} PUBLIC" "$base_cmake"; then
        echo "Adding target_sources block to CMakeLists.txt..."
        echo -e "target_sources(${target_name} PUBLIC\n    $classname.cpp\n)" >> "$base_cmake"
    else
        if ! grep -q "$classname.cpp" "$base_cmake"; then
            echo "Adding $classname.cpp to target_sources..."
            sed -i "/target_sources(${target_name} PUBLIC/a \    $classname.cpp" "$base_cmake"
        else
            echo "$classname.cpp is already in CMakeLists.txt."
        fi
    fi

    while [ "$dir" != "$root_dir" ]; do
        parent_dir="$(dirname "$dir")"
        dir_name="$(basename "$dir")"

        cmake_file="$parent_dir/CMakeLists.txt"
        if [ ! -f "$cmake_file" ]; then
            touch "$cmake_file"
            echo "Created CMakeLists.txt at $cmake_file"
        fi

        if ! grep -q "add_subdirectory($dir_name)" "$cmake_file"; then
            echo "" >> "$cmake_file"
            echo "add_subdirectory($dir_name)" >> "$cmake_file"
            echo "Linked $dir_name in $cmake_file"
        fi

        dir="$parent_dir"
    done

    echo "CMakeLists.txt updated successfully."
}


add_cmakelists_recursively "$root_path/src" "$relative_dir" "$classname" "BartaSceneCreator"

# Create the source file
lib_file_path="$root_path/src/$relative_dir/$classname.cpp"

if [ ! -f "$lib_file_path" ]; then
    echo "#include <$relative_dir/$classname.h>" > "$lib_file_path"
    echo "" >> "$lib_file_path"
    echo "namespace $rootDirectoryNamespace {" >> "$lib_file_path"
    echo "}" >> "$lib_file_path"

    echo "Source file '$lib_file_path' created successfully."
else
    echo "Source file '$lib_file_path' already exists."
fi
