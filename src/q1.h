#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Our Linked List Node structure
// This structure represents each car in the system. Each car has:
// - a 'plate' for the car's license plate
// - 'mileage' representing the car's current mileage
// - 'return_date' which is either a valid date (YYMMDD) or -1 for cars with no set return date
// - 'next' to link to the next car in the list (for the linked list structure)
struct car {
    char plate[9];          // License plate (maximum 8 characters + null terminator)
    int mileage;            // Current mileage of the car
    int return_date;        // Return date should be -1 for a car with no return date
    struct car *next;       // Pointer to the next car in the list
};

// Function Prototypes

// Displays the primary user interface menu
// This function shows the available options for the user to interact with the system.
void prompt();

// Inserts a new car into the list in a sorted order based on either mileage or return date.
// Parameters:
// - head: A pointer to the pointer of the first node of the linked list.
// - plate: The license plate of the car (input as a string).
// - mileage: The mileage of the car.
// - return_date: The return date of the car (-1 if no return date).
// Returns: A pointer to the newly inserted car.
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date);

// Prints the details of the cars in the linked list.
// Parameters:
// - head: A pointer to the first node of the linked list (the start of the list).
// This function iterates through the list and prints out each car's plate, mileage, and return date (if applicable).
void print_list(struct car *head);


// Checks if a given plate number is already in the list (to avoid duplicates).
// Parameters:
// - head: A pointer to the first node of the linked list.
// - plate: The license plate to search for.
// Returns: 'true' if the plate is found in the list, 'false' otherwise.
bool is_plate_in_list(struct car *head, char plate[]);

// Swaps the details of two car nodes in the linked list.
// Parameters:
// - a: A pointer to the first car to swap.
// - b: A pointer to the second car to swap.
// This function is typically used for sorting the list based on certain criteria (e.g., mileage or return date).
void swap(struct car *a, struct car *b);

// Sorts the linked list based on mileage or return date.
// Parameters:
// - head: A pointer to the pointer of the first node of the linked list.
// - sort_by_mileage: A boolean flag to sort by mileage if true.
// - sort_by_return_date: A boolean flag to sort by return date if true.
// This function sorts the list in ascending order based on the provided criteria
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date);

// Removes a specific car from the list by its plate number.
// Parameters:
// - head: A pointer to the pointer of the first node of the linked list.
// - plate: The license plate of the car to remove.
// Returns: A pointer to the removed car (if found), or NULL if the car is not found in the list.
struct car *remove_car_from_list(struct car **head, char plate[]);

// Removes the first car from the list (typically used to rent out the first available car).
// Parameters:
// - head: A pointer to the pointer of the first node of the linked list.
// Returns: A pointer to the removed car.
struct car *remove_first_from_list(struct car **head);

// Calculates the profit based on the difference in mileage (for rented cars).
// Parameters:
// - initial_mileage: The car's mileage when it was rented out.
// - final_mileage: The car's mileage when it was returned.
// Returns: The profit as a double based on the number of miles driven.
double profit_calculator(int initial_mileage, int final_mileage);

// Writes the details of the cars in the list to a file (saves the list).
// Parameters:
// - filename: The name of the file to write the list to.
// - head: A pointer to the first node of the linked list.
// This function writes the plate, mileage, and return date of each car in the list to the specified file.
void write_list_to_file(char *filename, struct car *head);

// Reads car details from a file and adds them to the list (loads the list from a file).
// Parameters:
// - filename: The name of the file to read the list from.
// - head: A pointer to the pointer of the first node of the linked list.
// This function reads car details (plate, mileage, return date) from a file and inserts them into the linked list.
void read_file_into_list(char *filename, struct car **head);

// Prints the date in the format year/month/day (for displaying return dates).
// Parameters:
// - date: The date in YYMMDD format to print.
// This function formats and prints the date as 'YY/MM/DD'.
void date(int date);

// Frees all memory allocated for the linked list (clears the list).
// Parameters:
// - head: A pointer to the pointer of the first node of the linked list.
// This function iterates through the list and frees all memory used by the cars.
void free_list(struct car **head);

// Checks if the given date in YYMMDD format is valid (e.g., no invalid months or days).
// Parameters:
// - date: The date to check in YYMMDD format.
// Returns: 'true' if the date is valid, 'false' if it is invalid.
bool is_valid_date(int date);

// Converts a string to lowercase (for uniform handling of license plates).
// Parameters:
// - str: The string (car's plate) to convert to lowercase.
// This function iterates through the string and converts any uppercase characters to lowercase using ASCII values.
void to_lowercase(char *str);

// Validates if a plate number is between 2 and 8 characters and contains only letters or digits.
bool is_valid_plate(const char *plate);
