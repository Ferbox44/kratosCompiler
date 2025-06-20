# Kratos

A Qt-based lexical and syntactic analyzer for the Kratos programming language.

## Description

Kratos is a compiler frontend that implements lexical and syntactic analysis for a custom programming language. The application provides a graphical user interface for analyzing source code, generating quadruples (intermediate code representation), and performing semantic analysis.

## Features

- **Lexical Analysis**: Token recognition and classification
- **Syntactic Analysis**: Grammar parsing and syntax validation
- **Semantic Analysis**: Type checking and operation validation
- **Symbol Table Management**: Variable and function tracking
- **Quadruple Generation**: Intermediate code representation
- **Error Reporting**: Comprehensive error detection and reporting
- **GUI Interface**: User-friendly Qt-based interface

## Screenshots

The application features a modern interface with:
- Code editor/input area
- Token display
- Symbol table viewer
- Quadruple generation display
- Error reporting panel

## Prerequisites

- **Qt**: Version 5 or 6 (Qt6 recommended)
- **CMake**: Version 3.5 or higher
- **C++ Compiler**: Supporting C++17 standard
- **MinGW** (Windows) or equivalent compiler

## Installation

### Building from Source

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd Kratos
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**:
   ```bash
   cmake ..
   ```

4. **Build the project**:
   ```bash
   cmake --build .
   ```

### Using Qt Creator

1. Open Qt Creator 13.0.0 or later
2. Open the project by selecting the `CMakeLists.txt` file
3. Configure the project with MinGW compiler
4. Build and run the project

## Usage

1. **Launch the application**
2. **Load or enter source code** using the file menu
3. **Run lexical analysis** to tokenize the input
4. **Execute syntactic analysis** to validate grammar
5. **View results** in the respective panels:
   - Token list
   - Symbol table
   - Quadruples
   - Error messages

## Project Structure

```
Kratos/
├── main.cpp              # Application entry point
├── MainWindow.h          # Main window header
├── MainWindow.cpp        # Main window implementation
├── MainWindow.ui         # Qt Designer UI file
├── CMakeLists.txt        # CMake build configuration
├── cuadruplos.txt        # Sample quadruple output
├── LEEME.txt            # Original project notes
├── recursos/            # Resource files
│   ├── omega.png        # Application icon
│   └── omega1.ico       # Windows icon
└── README.md            # This file
```

## Key Components

### Lexical Analyzer
- Token recognition and classification
- Reserved word identification
- Error detection in lexical phase

### Syntactic Analyzer
- Grammar parsing using state machines
- Production rule validation
- Syntax error reporting

### Semantic Analyzer
- Type checking for operations
- Variable declaration validation
- Operation compatibility verification

### Quadruple Generator
- Intermediate code generation
- Operation and operand tracking
- Result assignment management

## Sample Output

The application generates quadruples in the format:
```
number, operator, operand1, operand2, result
```

Example:
```
1, *, 2, 4, Res 1
2, =, c, NULL, Res 1
3, +, 4, 5, Res 2
```

## Development

### Author
- **Fernando Israel Gomez Sandoval** (ID: 21041252)

### Development Environment
- **IDE**: Qt Creator 13.0.0
- **Compiler**: MinGW
- **Framework**: Qt (Widgets module)
- **Language**: C++17

## License

This project is licensed under the terms specified in the LICENSE file.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## Issues

If you encounter any issues or have questions, please:
1. Check the existing issues
2. Create a new issue with detailed information
3. Include system information and error messages

## Acknowledgments

- Qt Framework for the GUI components
- CMake for build system management
- MinGW for compilation support

---

**Note**: This is an educational project demonstrating compiler construction principles and Qt application development.