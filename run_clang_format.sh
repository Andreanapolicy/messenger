#!/bin/bash

find ./src/ -iname '*.h' -o -iname '*.cpp' -not -path "*/build/*" | xargs clang-format --verbose -i --style=file