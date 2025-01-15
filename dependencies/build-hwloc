#!/bin/bash

set -e

############################################################
# Help
Help()
{
   # Display Help
   echo "Build HWLOC library for macOS or Linux."
   echo
   echo "Syntax: build-hwloc macOS|Linux Debug|Release {install_path} ({macos-sdk-version})"
   echo
}

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]
  then
    Help
    exit 0
fi

if [ "$1" = "macOS" ]; then
  IS_LINUX=0

  if [ -z "$4" ]; then
    echo "Specify the targeted SDK for macOS as fourth argument !"
    exit 1
  fi
elif [ "$1" = "Linux" ]; then
  IS_LINUX=1
else
  echo "The first argument should be macOS or Linux !"
  exit 1
fi

if [ "$2" = "Debug" ]; then
  IS_RELEASE=0
elif [ "$2" = "Release" ]; then
  IS_RELEASE=1
else
  echo "The second argument should be Debug or Release !"
  exit 1
fi

cd hwloc

echo "Preparing the source directory ..."
./autogen.sh
#make distclean

echo "Preparing the build directory ..."
mkdir -p build-"$2"
cd build-"$2"

echo "Configuring the compilation ..."
../configure --enable-static=yes --enable-shared=no --disable-cairo --disable-libxml2 --disable-io --disable-libudev --prefix="$3"

echo "Compiling the library ..."
if [ $IS_LINUX = 1 ]; then
  echo "Building for Linux ($2) ..."

  if [ $IS_RELEASE = 1 ]; then
    make CFLAGS="-fPIC -O2" -j
  else
    make CFLAGS="-fPIC -g3 -O0" -j
  fi
else
  echo "Building for macOS ($2) ..."

  if [ $IS_RELEASE = 1 ]; then
    make CFLAGS="-mmacosx-version-min=$4 -fPIC -O2" -j
  else
    make CFLAGS="-mmacosx-version-min=$4 -fPIC -g3 -O0" -j
  fi
fi

echo "Installing the library to '$3' ..."
make install

echo "Completed !"
echo ""
