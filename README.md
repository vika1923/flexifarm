# Egg Incubator Simulator

A C++ console-based egg incubator simulation module for a farming application prototype.

## Description

This program simulates an automated egg incubator system that:
- Generates random eggs (5-20) with random fertilization status
- Loads fertilized eggs into an incubator
- Simulates the hatching process with realistic success rates
- Returns detailed statistics for integration with a larger farming system

## Features

- **Object-Oriented Design**: Fully encapsulated IncubatorSimulator class
- **Random Generation**: Uses rand() to simulate realistic egg production
- **Automatic Operation**: No user input required - uses optimal default settings
- **Data Return**: Returns all statistics via getter methods for system integration
- **Simple Arrays**: Uses basic C++ arrays (no vectors or advanced features)
- **Well Commented**: Every line explained for educational purposes

## Technical Requirements

- **Language**: C++ (C++11 standard)
- **Compiler**: MinGW G++ or any C++11 compatible compiler
- **Libraries**: Standard library only (cstdlib, ctime)
- **Platform**: Cross-platform (Windows, Linux, macOS)

## Compilation

### Windows (MinGW)
```bash
g++ -std=c++11 IncubatorSimulator.cpp -o IncubatorSimulator.exe
```

### Linux/macOS
```bash
g++ -std=c++11 IncubatorSimulator.cpp -o IncubatorSimulator
```

## Usage

### As Standalone Module (Testing)
```bash
./IncubatorSimulator
```

### Integration in Farming System
```cpp
#include "IncubatorSimulator.cpp"

int main() {
    srand(time(0));
    
    IncubatorSimulator incubator;
    incubator.runSimulation();
    
    // Get results
    int hatched = incubator.getHatchedChicks();
    int total = incubator.getTotalEggs();
    double success = incubator.getSuccessRate();
    
    // Use in your farming system...
}
```

## Return Values

The simulator provides the following data through getter methods:

| Method | Return Type | Description |
|--------|-------------|-------------|
| `getTotalEggs()` | int | Total eggs generated (5-20) |
| `getFertilizedEggs()` | int | Number of fertilized eggs |
| `getNotFertilizedEggs()` | int | Number of not fertilized eggs |
| `getEggsInIncubator()` | int | Eggs loaded in incubator |
| `getHatchedChicks()` | int | Successfully hatched chicks |
| `getFailedToHatch()` | int | Eggs that didn't hatch |
| `getSuccessRate()` | double | Hatch success percentage |
| `getTemperature()` | double | Incubator temperature (°C) |
| `getHumidity()` | double | Incubator humidity (%) |

## Concepts Demonstrated

### Object-Oriented Programming (OOP)
- Class with encapsulation
- Private member variables
- Public interface methods
- Constructor initialization

### Programming Fundamentals
- Constants (const variables)
- Multiple data types (int, bool, double)
- Arrays for data storage
- Loops (for loops)
- Conditional logic (if/else, nested conditions)
- Random number generation
- Methods that return values

### Code Quality
- CamelCase naming convention
- Comprehensive comments
- Clean code structure
- Modular design

## Default Settings

- **Temperature**: 37.5°C (optimal for chicken eggs)
- **Humidity**: 55% (optimal for chicken eggs)
- **Hatch Success Rate**: 85% (realistic simulation)
- **Egg Range**: 5-20 eggs per simulation
- **Fertilization Rate**: 50% (random)

## Project Structure

```
final proj/
├── IncubatorSimulator.cpp    # Main simulator file
└── README.md                  # This file
```

## Author

Created as part of an Introduction to Programming course project.

## License

Open source - feel free to use for educational purposes.

## Future Enhancements

- Integration with full farming management system
- GUI interface
- Database storage for historical data
- Real-time monitoring
- Multiple incubator management
