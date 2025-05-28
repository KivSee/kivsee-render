# Build stage
FROM alpine:3.19 AS builder

# Install required dependencies
RUN apk add --no-cache \
    curl \
    git \
    build-base \
    python3 \
    linux-headers \
    cmake

WORKDIR /workspace

# Copy the entire project
COPY . .

# Build the simulation service
WORKDIR /workspace/simulation-service
RUN mkdir build && cd build \
    && cmake .. \
    && cmake --build . --config Release \
    && cmake --install .

# Runtime stage
FROM alpine:3.19

# Install runtime dependencies
RUN apk add --no-cache \
    libstdc++ \
    libgcc

WORKDIR /app

# Copy the built binary from the builder stage
COPY --from=builder /workspace/simulation-service/install/bin/simulation_service /app/

# Run the simulation service
CMD ["./simulation_service"]
