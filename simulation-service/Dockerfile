# Build stage
FROM debian:bullseye-slim AS builder

# Install required dependencies
RUN apt-get update && apt-get install -y \
    curl \
    git \
    build-essential \
    python3 \
    libpthread-stubs0-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Bazelisk
RUN curl -L https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-arm64 -o /usr/local/bin/bazelisk \
    && chmod +x /usr/local/bin/bazelisk

WORKDIR /workspace

# Copy the entire project
COPY . .

# Build the simulation service
RUN bazelisk build //simulation-service:simulation_service

# Runtime stage
FROM debian:bullseye-slim

WORKDIR /app

# Copy the built binary from the builder stage
COPY --from=builder /workspace/bazel-bin/simulation-service/simulation_service /app/

# Run the simulation service
CMD ["./simulation_service"]
