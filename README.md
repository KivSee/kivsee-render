# kivsee-render
LED render library suitable for esp32 controller

# Goals
- run on esp-32 micro-controllers. e.g - limited memory and libraries support. library should also run on pc (should not use specific arduino framework headers)
- simple bulding blocks, that can be easily combined to create more interesting and sophisticated visual effects
- low level commands. the library api is intended to be used by intermidiate scripts and tools which simplify the usage to human user.

## Running Tests

install bazel

```shell
brew install bazel
```

run tests suite

```shell
bazel test --test_output=all //test:kivsee-render-test
```

