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

# Run the server
./simulation_service
```

## API Endpoints

### POST /sequence/stats

Calculates statistics for multiple sequences and their associated timestamps.

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
    "things": [
        {
            "thingName": "thing1",
            "mean": 3.0,
            "std_dev": 1.4142135623730951,
            "min": 1.0,
            "max": 5.0,
            "correlation": 0.9999999999999999
        },
        {
            "thingName": "thing2",
            "mean": 3.0,
            "std_dev": 1.4142135623730951,
            "min": 1.0,
            "max": 5.0,
            "correlation": 0.9999999999999999
        }
    ],
    "time_difference": 9
}
```

## Error Handling

The service returns a 400 status code with an error message if the request is malformed or contains invalid data.