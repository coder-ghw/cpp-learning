rm -rf build 
mkdir build && cd build

target_name=$1
echo "build target: $target_name"
cmake ../$target_name
make $target_name -j8

./$target_name
