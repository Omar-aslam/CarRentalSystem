
# Car Rental System 

## Steps to Run in VS Code

1. Open the `CarRentalSystem` folder in VS Code.
2. Ensure the [C/C++ extension by Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) is installed.
3. Open the integrated terminal (`Ctrl + ``).
4. Navigate to the `src` directory:
   ```bash
   cd src
   ```
5. Compile the project:
   ```bash
   make
   ```
6. Run the program:
   ```bash
   ./car_rental
   ```

## Notes

- You can modify and debug using breakpoints in VS Code.
- To clean the build, run:
  ```bash
  make clean
  ```

## Technical Explanation

1. Data Structures:
The system uses linked lists to manage three categories of cars: Available, Rented, and Under Repair. Each car is represented as a node containing its license plate, mileage, return date, and a pointer to the next node. This allows dynamic insertion and removal of items, which is critical for managing live data in a rental system.

2. Input Validation and Consistency:
Functions such as is_valid_plate(), to_lowercase(), and is_valid_date() ensure that user input adheres to rules for license plate formatting, mileage entries, and dates respectively. This helps maintain data consistency and prevents errors like duplicate entries or invalid dates.

3. File I/O for Persistence:
The project implements file input and output routines using read_file_into_list() and write_list_to_file(). This allows the system to save the current state to text files and reload data on subsequent runs, ensuring persistence even after the program terminates.

4. Modular Design:
The project is split across multiple files:

q1.h: Contains function declarations, structure definitions, and documentation.

main.c: Houses the core user interface and control flow logic.

q1_functions.c: Implements the functions that perform operations such as insertion, deletion, and list sorting.

This modularity promotes code reuse, easier maintenance, and clarity.

5. Compilation Flags:
The Makefile uses flags such as -Wall, -std=c99, and -pedantic to enforce best practices in C programming. These flags help catch common errors and ensure the code adheres to the C99 standard.

6. Memory Management:
Dynamic memory allocation is used to create nodes for the linked lists. Careful management of memory (including freeing memory using free_list()) prevents memory leaks, as confirmed by testing with tools like Valgrind.
