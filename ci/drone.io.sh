# License: GNU General Public License 3+

# This script contains the commands for the build process on drone.io.
# drone.io currently uses Ubuntu 12.04 LTS.


# install dependencies
sudo apt-get update
sudo apt-get install -y libxml2-dev zlib1g-dev

# pre-build test: C++ syntax check
./cpplint.sh

# build it
mkdir ./build
cd ./build
cmake ../
make -j2
ctest -V
