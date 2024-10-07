#!/bin/sh

BUILD_DIR="./build_release"
DIST_PATH="./dist"

# Create a fresh build directory and move into it
rm -rv "$BUILD_DIR"
mkdir -pv "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

cmake .. -DCMAKE_BUILD_TYPE=Release -DBIRB_PROFILER=OFF -DBIRB_RELEASE=ON -DCMAKE_CXX_FLAGS="-static-libstdc++ -static-libgcc"

# Compile
make -j "$(nproc)"

mkdir -pv "$DIST_PATH"
mv "./game" "$DIST_PATH/"
cat >> "$DIST_PATH/run.sh" << EOF
#!/bin/sh
LD_LIBRARY_PATH="./libs" ./game
EOF
chmod +x "$DIST_PATH/run.sh"


# Move the libraries to the lib directory
mkdir -pv "$DIST_PATH/libs"
mv -v "./birb3d/vendor/assimp/bin/libassimp.so" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/assimp/bin/libassimp.so.5" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/assimp/bin/libassimp.so.5.3.0" "$DIST_PATH/libs/"

mv -v "./birb3d/vendor/glfw/src/libglfw.so" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/glfw/src/libglfw.so.3" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/glfw/src/libglfw.so.3.4" "$DIST_PATH/libs/"

mv -v "./birb3d/libglad.so" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/glm/glm/libglm.so" "$DIST_PATH/libs/"

mv -v "./birb3d/vendor/openal-soft/libopenal.so" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/openal-soft/libopenal.so.1" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/openal-soft/libopenal.so.1.23.1" "$DIST_PATH/libs/"

mv -v "./birb3d/vendor/minizip-ng/libminizip.so" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/minizip-ng/libminizip.so.1" "$DIST_PATH/libs/"
mv -v "./birb3d/vendor/minizip-ng/libminizip.so.4.0.7" "$DIST_PATH/libs/"

mv -v "./birb3d/libimgui.so" "$DIST_PATH/libs/"

# Copy the assets in
mv -v ./assets "$DIST_PATH/"

# Copy licenses
../birb3d/scripts/create_license_dir.sh "$DIST_PATH/licenses"

# Create a zip archive
zip -r release_build.zip "$DIST_PATH"
