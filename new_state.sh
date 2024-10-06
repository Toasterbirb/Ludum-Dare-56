#!/bin/bash
[ -z "$1" ] && echo "Usage: new_state.sh [state_name]" && exit 1

src_path="./src/$1.cpp"
include_path="./include/${1^}.hpp"
[ -f "$src_path" ] && echo "This state exists already" && exit 1
[ -f "$include_path" ] && echo "This state exists already" && exit 1

cp -v ./templates/state.cpp "$src_path"
cp -v ./templates/State.hpp "$include_path"

sed -i "s/#include \"TEMPLATE.hpp\"/#include \"${1^}.hpp\"/g" "$src_path"
sed -i "s/TEMPLATE/$1/g" "$src_path"
sed -i "s/TEMPLATE/$1/g" "$include_path"
