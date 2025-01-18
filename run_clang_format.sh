#!/usr/bin/env bash

find ./src/ -not -iname "*.pb.*" -iname '*.h' -o -iname '*.cpp' -not -path "*/build/*" | xargs clang-format --verbose -i --style=file