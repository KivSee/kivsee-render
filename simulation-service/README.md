# Simulation Service

A C++ HTTP server that provides sequence statistics calculations.

## Prerequisites

- CMake (version 3.5 or higher)
- C++17 compatible compiler

## Building the Project

```bash
# Create and enter build directory
mkdir build
cd build

# Configure and build the project
cmake ..
cmake --build . --config Release
cmake --install .

# Run the server
./install/bin/simulation_service
```

## Docker Build and Run

You can also build and run the service using Docker:

```bash
# Build the Docker image
docker build -f simulation-service/Dockerfile -t simulation-service .

# Run the container
docker run -it -p 8084:80 --rm simulation-service
```

## API Endpoints

### POST /sequence/stats

Calculates statistics for multiple sequences and their associated timestamps, including detailed HSV color analysis.

#### Request Format

```json
{
    "startTimeMs": 1234567890,
    "endTimeMs": 1234567899,
    "things": [
        {
            "thingName": "thing1",
            "sequenceProto": "base64_encoded_sequence_protobuf",
            "objectProto": "base64_encoded_objects_data"
        },
        {
            "thingName": "thing2",
            "sequenceProto": "base64_encoded_sequence_protobuf",
            "objectProto": "base64_encoded_objects_data"
        }
    ]
}
```

Each sequence in the array represents a single "controller" which renders a group of Leds that are physically connected:

- `thingName`: Identifier for the sequence
- `sequenceProto`: Base64-encoded string representation of the sequence data
- `objectProto`: Base64-encoded string representation of the objects data

#### Response Format

```json
{
    "average_brightness": 0.5449641777245727,
    "hsv_stats": {
        "hue_histogram": [4320, 0, 0, 0, 53184, 30672, 17952, 106368, 0, 106704],
        "mean_hue": 0.8503544863181492,
        "mean_saturation": 0.91263632479375,
        "mean_value": 0.5449641777245727,
        "prominent_hue": 0.95,
        "prominent_saturation": 0.85,
        "prominent_value": 0.05,
        "saturation_histogram": [9792, 5472, 5184, 5472, 5184, 5184, 5760, 5184, 218736, 5472],
        "std_dev_hue": 1.4827991023817995,
        "std_dev_saturation": 0.16970089393528437,
        "std_dev_value": 0.405950747085864,
        "value_histogram": [215377, 29373, 29419, 44680, 93736, 37325, 31082, 26056, 33583, 30713]
    },
    "time_difference": 117430
}
```

The response includes:
- `average_brightness`: Average brightness across all LEDs and frames
- `hsv_stats`: Detailed HSV color analysis including:
  - `hue_histogram`: Distribution of hue values across 10 buckets
  - `mean_hue`: Average hue value (accounting for cyclic nature)
  - `mean_saturation`: Average saturation value
  - `mean_value`: Average brightness value
  - `prominent_hue`: Most frequent hue value
  - `prominent_saturation`: Most frequent saturation value
  - `prominent_value`: Most frequent brightness value
  - `saturation_histogram`: Distribution of saturation values across 10 buckets
  - `std_dev_hue`: Standard deviation of hue values
  - `std_dev_saturation`: Standard deviation of saturation values
  - `std_dev_value`: Standard deviation of brightness values
  - `value_histogram`: Distribution of brightness values across 10 buckets
- `time_difference`: Duration of the sequence in milliseconds

## Error Handling

The service provides detailed error responses with appropriate HTTP status codes:

- 400 Bad Request: For malformed JSON or invalid data types
  ```json
  {
    "error": "Invalid JSON format",
    "details": "error message"
  }
  ```
- 500 Internal Server Error: For unexpected server errors
  ```json
  {
    "error": "Internal server error",
    "details": "error message"
  }
  ```

All errors are logged to the console with detailed information about where and why they occurred.