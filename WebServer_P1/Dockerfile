# Use the latest alpine linux image as the base container for app to run in
FROM alpine:latest AS base
WORKDIR /app
EXPOSE 8080

# Use another container for creating the binaries
FROM alpine:latest AS build
RUN apk add --no-cache asio-dev g++ cmake ninja sqlite sqlite-dev
WORKDIR /src
COPY WebServer_P1/ .
RUN mkdir -p build
RUN cmake -G Ninja -B build
RUN cmake --build build

# Add compiled binaries to base image to create final image
FROM base AS final
WORKDIR /app
RUN apk add --no-cache libstdc++ libgcc sqlite-dev
COPY --from=build /src/build/crow_project .
CMD ["./crow_project"]
