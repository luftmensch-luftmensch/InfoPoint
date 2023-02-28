### Dockerfile ###

# To build it -> docker build -t <TAG> . --no-cache=true

### BUILD STAGE
# Living on the edge
FROM archlinux:base as base

# Global variables
ARG C_COMPILER=gcc
ARG BUILD_TYPE=Release

### Update & install required pkgs ###
RUN echo -e "\033[1;34m Updating the machine [arch]...\033[0m"
RUN pacman -Syy

RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Installing dependencies...\033[0m"
RUN pacman -S --noconfirm make cmake ${C_COMPILER}
RUN echo -e "\033[1;34m Done!\033[0m"


### Configure needed variables ###
ENV CC=${C_COMPILER}

WORKDIR /builder

### Build project w/ cmake ###
RUN echo -e "\033[1;34m Copying src folder...\033[0m"
COPY . .
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Configuring cmake options...\033[0m"
RUN CC=${C_COMPILER} cmake -S . -B build/ -D CMAKE_BUILD_TYPE=${BUILD_TYPE}
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Building project...\033[0m"
RUN CC=${C_COMPILER} cmake --build build/
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Installing the executable...\033[0m"
RUN CC=${C_COMPILER} cmake --install build/ --prefix install/ --config ${BUILD_TYPE}
RUN echo -e "\033[1;34m Done!\033[0m"

### Expose the executable ###
ENTRYPOINT [ "/builder/install/bin/InfoPointServer" ]
