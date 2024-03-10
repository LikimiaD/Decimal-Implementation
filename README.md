# Decimal-Implementation

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white)

The `Decimal-Implementation` project is a custom C library designed to offer decimal arithmetic operations similar to those found in high-level languages but implemented in C for precise decimal computations. It supports arithmetic operations, comparisons, conversions, and rounding functions on decimal numbers with a focus on accuracy and efficiency.

## Features

- Implements arithmetic operations: addition, subtraction, multiplication, and division with precision up to 28 decimal places.
- Provides comparison operations: less than, less than or equal to, greater than, greater than or equal to, equal to, and not equal to.
- Supports conversion operations from and to `int` and `float` data types.
- Offers rounding operations: floor, round, truncate, and negate.
- Handles decimal numbers ranging from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.
- Custom implementation of parsing and formatting functions similar to `sprintf` and `sscanf` for decimal types.
- Ensures error handling for operations that result in overflow, underflow, or division by zero.

For more details, refer to the [header file](include/decimal.h).

## Project Structure

```tree
.
├── Dockerfile
├── LICENSE
├── Makefile
├── functions
│ ├── decimal_arithmetic.c
│ ├── decimal_comparison.c
│ ├── decimal_core.c
│ ├── decimal_parser.c
│ ├── decimal_rounding.c
│ └── decimal_support.c
├── include
│ └── decimal.h
├── scripts
│ └── docker.sh
├── test.txt
└── tests
└── decimal_test.c
```

## Installation and Usage

To use the `Decimal-Implementation` library:

1. Clone the repository.
2. Build the library using the provided Makefile:
   ```bash
   make all
   ```
3. Include the decimal.h header file in your project.
4. Link against the custom_decimal.a static library when compiling your application.

## Example usage:

```c
#include "decimal.h"

int main() {
    custom_decimal value1, value2, result;
    
    custom_from_int_to_decimal(123, &value1);
    custom_from_int_to_decimal(456, &value2);
    
    custom_add(value1, value2, &result);
    
    int intResult;
    custom_from_decimal_to_int(result, &intResult);
    
    printf("Result: %d\n", intResult);
    
    // Continue with other decimal operations...
    return 0;
}
```

## Building and Testing

* To compile the library and tests:
    ```bash
    make all
    ```
* To run unit tests:
    ```bash
    make tests
    ```
* To generate a coverage report:
    ```bash
    make gcov_report
    ```

Check out the [Makefile](Makefile) for build instructions.

## Docker Support

A `Dockerfile` is included for building and testing the library in an isolated environment.

* To build the Docker image:
    ```bash
    docker build -t decimal-implementation .
    ```
* To run tests inside a Docker container:
    ```bash
    docker run decimal-implementation
    ```

You can run container from [Makefile](Makefile)

## Contributing

Contributions are welcome to enhance `Decimal-Implementation`. Feel free to fork the project, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for more details.