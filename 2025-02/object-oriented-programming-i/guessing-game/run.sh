#!/bin/bash

MAIN_CLASS=$1

if [ -z "$MAIN_CLASS" ]; then
    echo "Usage: $0 <main-class-name>"
    exit 1
fi

if [ ! -d build ]; then
    mkdir -p build

    javac -d build $(find -name '*.java')

    if [ $? -ne 0 ]; then
        exit 1
    fi
fi

java -cp build src.${MAIN_CLASS}
