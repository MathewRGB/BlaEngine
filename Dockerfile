FROM ubuntu:bionic

ARG DEBIAN_FRONTEND=noninteractive

# misc
RUN apt-get update && apt-get install -y \
  build-essential      \
  cmake                \
  doxygen              \
  doxygen-doc          \
  doxygen-gui

# we need g++7
RUN g++ -v

# install g{test,mock} sources & put headers into /usr/include
RUN apt-get update && apt-get install -y libgtest-dev

# build & install gtest (cmake -DBUILD_SHARED_LIBS=ON . for shlibs)
RUN cd /usr/src/gtest ; cmake . ; make
RUN mv /usr/src/gtest/*.a /usr/lib/

# add project and set working directory
ADD . /blaengine
WORKDIR /blaengine

# cmake build
RUN rm -rf build && mkdir build
RUN cd build && cmake .. && make

# run tests
RUN cd ./build && ./runTests

# doxygen
RUN cd ./docs && doxygen Doxyfile.in 
