#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/plugins/tools/kitPlugins
cp     $BIN_DIR/Trik.Core.dll                                 $PWD/../data/
