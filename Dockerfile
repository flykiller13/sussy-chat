FROM ubuntu:latest

WORKDIR /sussy-chat

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*

COPY . .

# Build the project
RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build .

# Run server
CMD ["./build/chat_server"]

# Open port
EXPOSE 3490