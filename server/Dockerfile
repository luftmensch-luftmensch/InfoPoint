### Dockerfile ###

## GUIDE: 
# To build it -> docker build -t <TAG> . --no-cache=true

## Links:
# Docker fails to create the image -> https://stackoverflow.com/questions/51115856/docker-failed-to-export-image-failed-to-create-image-failed-to-get-layer
# (use DOCKER_BUILDKIT=1)

### BUILD STAGE
FROM gcc:11.3.0 as buildstage

WORKDIR /builder

COPY ./src/ ./src

