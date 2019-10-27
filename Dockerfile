FROM ubuntu:bionic

ARG DEBIAN_FRONTEND=noninteractive

# misc
RUN apt-get update && apt-get install -y \
    build-essential      \
    wget                 \
    git                  \
    cmake                \
    doxygen              \ 
    doxygen-doc          \
    doxygen-gui          \ 
    graphviz

# install rapid json
RUN git clone https://github.com/Tencent/rapidjson.git && \
    cd rapidjson && mkdir build && cd build && \
    cmake .. && make && make install

# install g{test,mock} sources & put headers into /usr/include
RUN apt-get update && apt-get install -y \
libgtest-dev

# build & install gtest (cmake -DBUILD_SHARED_LIBS=ON . for shlibs)
RUN cd /usr/src/gtest ; cmake . ; make
RUN mv /usr/src/gtest/*.a /usr/lib/

# cmake build
ADD . /blaengine
RUN cd /blaengine/ && rm -rf build && mkdir build && cd build && cmake .. && make

# run tests
RUN cd /blaengine/build && ./runTests

# doxygen
RUN cd /blaengine/docs && doxygen Doxyfile.in 
