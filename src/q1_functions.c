

#include "q1.h"
#include <ctype.h>

/**
 * Validates a car's plate number to ensure it follows the format rules.
 * The plate must:
 * - Be between 2 and 8 characters in length.
 * - Contain only letters (A-Z, a-z) or numbers (0-9).
 * 
 * @param plate The car's plate number (string).
 * @return true if the plate is valid, false otherwise.
 */
bool is_valid_plate(const char *plate) {
    int length = 0;

    for (int i = 0; plate[i] != '\0'; i++) {
        // Ensure that the character is either a letter or a number.
        if (!isalnum(plate[i])) {
            return false; // Invalid character found.
        }
        length++;
    }

    // Ensure the length of the plate is between 2 and 8 characters.
    if (length < 2 || length > 8) {
        return false;
    }

    return true; // The plate is valid.
}

/*
 * Converts a given string to lowercase.
 * This function iterates over each character in the input string and,
 * if the character is an uppercase letter, converts it to its lowercase counterpart.
 *
 * @param str: The string to be converted to lowercase.
 */

// Helper function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // Convert each character to lowercase using ASCII comparison
        str[i] = tolower(str[i]);
    }
}

/*
 * Checks if a given date in the format YYMMDD is valid.
 * This function checks the validity of the day and month extracted from the date.
 * It assumes a simple check for February (always 28 days, no leap year handling).
 *
 * @param date: The date in the YYMMDD format as an integer.
 * @return: Returns true if the date is valid, false otherwise.
 */
bool is_valid_date(int date) { // Checks if a given date in the format YYMMDD is valid
    int month = (date / 100) % 100; // Extract month from date
    int day = date % 100; // Extract day from date
    // Check if month is valid (1-12)
    if (month < 1 || month > 12) return false;
    // Check if day is valid (1-31, depends on the month)
    if (day < 1 || day > 31) return false;
    // Handle months with 30 days (April, June, September, November)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    // Check for February (no leap year support, max 28 days)
    if (month == 2 && day > 28) return false; 

    return true; // Date is valid
}

/*All the function above are exstra functions that I have created to help me with the main function.
They are all icluded in q1.h + all the explanations on why did I add them are in the Redme file.
*/


/*
 * Displays the main user interface menu with different car management options.
 * This function prints the available options to the console.
 */
void prompt() {
    printf("1. Add a new car to the available for rent list,\n");
    printf("2. Add a returned car to the available-for-rent list,\n");
    printf("3. Add a returned car to the repair list,\n");
    printf("4. Transfer a car from the repair list to the available for rent list,\n");
    printf("5. Rent the first available car,\n");
    printf("6. Print all the lists,\n");
    printf("7. Quit.\n");
    printf("Enter your chosen option please: ");
}

/*
 * Inserts a new car into a sorted linked list.
 * The sorting criteria depend on the car's mileage or return date.
 * It first converts the plate number to lowercase for consistent storage.
 *
 * @param head: Pointer to the head of the linked list.
 * @param plate: The plate number of the car.
 * @param mileage: The car's current mileage.
 * @param return_date: The return date of the car (or -1 if not applicable).
 * @return: Returns a pointer to the newly inserted car node.
 */
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date) {
    // Allocate memory for a new car node
    struct car *new_car = (struct car *)malloc(sizeof(struct car));
    if (new_car == NULL) return NULL; // Handle memory allocation failure

    // Safely copy the plate number and convert to lowercase for consistent storage
    strncpy(new_car->plate, plate, 6);  // Use 6 to leave room for '\0'
    new_car->plate[6] = '\0';           // Manually add the null terminator
    to_lowercase(new_car->plate);       // Convert to lowercase before inserting

    // Initialize car's attributes: 
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;
    // If the list is empty or the new car should be inserted at the head
    if (*head == NULL || (return_date == -1 && (*head)->mileage > mileage) || 
        (return_date != -1 && (*head)->return_date > return_date)) {
        new_car->next = *head;
        *head = new_car;
        return new_car;
    }
    // Traverse the list to find the correct insertion point
    struct car *current = *head;
    while (current->next != NULL && 
          ((return_date == -1 && current->next->mileage < mileage) || 
           (return_date != -1 && current->next->return_date < return_date))) {
        current = current->next;
    }
    // Insert the new car node in the correct position
    new_car->next = current->next;
    current->next = new_car;

    return new_car;
}


/*
 * Prints the details of all cars in a linked list.
 * This function iterates through the linked list and prints each car's plate, mileage, and return date (if applicable).
 *
 * @param head: Pointer to the head of the linked list.
 */
void print_list(struct car *head) {
    struct car *current = head;
    // Traverse the list and print each car's details
    while (current != NULL) {
        printf("Plate: %s, Mileage: %d", current->plate, current->mileage);
        if (current->return_date != -1) {
            printf(", Return Date: ");
            date(current->return_date); // Print return date in YY/MM/DD format
        }
        printf("\n");
        current = current->next;
    }
}

/*
 * Checks if a car with a given plate number exists in a linked list.
 * The comparison is case-insensitive. The input plate number is first converted to lowercase for comparison.
 *
 * @param head: Pointer to the head of the linked list.
 * @param plate: The plate number to be searched.
 * @return: Returns true if the car with the given plate number is found, false otherwise.
 */
bool is_plate_in_list(struct car *head, char plate[]) {
    char lower_plate[7];
    strncpy(lower_plate, plate, 7);  // Copy the input plate to a temporary variable
    lower_plate[6] = '\0';           // Ensure the string is null-terminated
    to_lowercase(lower_plate);       // Convert the input plate to lowercase

    struct car *current = head;
    // Traverse the list to search for the plate number
    while (current != NULL) {
        char stored_plate[7];
        strncpy(stored_plate, current->plate, 7);  // Copy the stored plate to a temporary variable
        stored_plate[6] = '\0';
        to_lowercase(stored_plate);  // Convert the stored plate to lowercase

        if (strcmp(lower_plate, stored_plate) == 0) {
            return true;  // Found a match (case insensitive)
        }
        current = current->next;
    }
    return false; // No match found
}


/*
 * Swaps the details of two car nodes in the linked list.
 *
 * @param a: Pointer to the first car node.
 * @param b: Pointer to the second car node.
 */
void swap(struct car *a, struct car *b) {
    struct car temp = *a; // Temporary storage for swapping
    *a = *b;
    *b = temp;
}

/*
 * Sorts the linked list of cars based on mileage or return date.
 * The function allows sorting by mileage or by return date, depending on the flags provided.
 *
 * @param head: Pointer to the head of the linked list.
 * @param sort_by_mileage: Boolean flag indicating if sorting should be done by mileage.
 * @param sort_by_return_date: Boolean flag indicating if sorting should be done by return date.
 */
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date) {
    if (*head == NULL || (*head)->next == NULL) return; // List is empty or has only one car

    struct car *current;
    struct car *index;
    // Traverse and sort the list using a basic bubble sort approach
    for (current = *head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if ((sort_by_mileage && current->mileage > index->mileage) || 
                (sort_by_return_date && current->return_date > index->return_date)) {
                swap(current, index); // Swap the two nodes if the order is incorrect
            }
        }
    }
}

/*
 * Removes a car from the list based on its plate number (case-insensitive).
 * The function searches for the car with the given plate number and removes it from the linked list.
 *
 * @param head: Pointer to the pointer of the linked list's head.
 * @param plate: The plate number of the car to be removed.
 * @return: Returns a pointer to the removed car node, or NULL if no car is found.
 */
struct car *remove_car_from_list(struct car **head, char plate[]) {
    char lower_plate[7];
    strncpy(lower_plate, plate, 7);  // Copy the input plate to a temporary variable
    lower_plate[6] = '\0';
    to_lowercase(lower_plate);       // Convert the input plate to lowercase

    struct car *current = *head;
    struct car *previous = NULL;
    
    // Traverse the list to search for the plate number
    while (current != NULL) {
        char stored_plate[7];
        strncpy(stored_plate, current->plate, 7);  // Copy the stored plate to a temporary variable
        stored_plate[6] = '\0';
        to_lowercase(stored_plate);  // Convert the stored plate to lowercase

        // Match found, remove the car from the list
        if (strcmp(lower_plate, stored_plate) == 0) {
            // Match found, remove the car from the list
            if (previous == NULL) {
                *head = current->next; // If the car is at the head
            } else {
                previous->next = current->next; // Remove the car from the middle or end
            }
            return current; // Return the removed car node
        }
        previous = current;
        current = current->next;
    }
    return NULL;  // Car with the given plate not found
}


/*
 * Removes the first car from the list.
 * This function removes the first node in the linked list and returns a pointer to it.
 *
 * @param head: Pointer to the pointer of the list's head.
 * @return: Returns the removed car node.
 */
struct car *remove_first_from_list(struct car **head) {
    if (*head == NULL) return NULL; // List is empty

    struct car *temp = *head;
    *head = (*head)->next; // Update head to the next car in the list
    return temp;
}

/*
 * Calculates the profit made by renting a car based on mileage difference.
 * The profit formula is $80 for up to 200 miles, and an additional $0.15 for every extra mile.
 *
 * @param initial_mileage: The mileage of the car before renting.
 * @param final_mileage: The mileage of the car after renting.
 * @return: Returns the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage) { 
    int distance = final_mileage - initial_mileage; // Calculate the distance traveled
    if (distance <= 200) {
        return 80.0; // Flat rate for distances 200 miles or less
    } else {
        return 80.0 + (distance - 200) * 0.15; // Extra charge for distances over 200 miles
    }
}

/*
 * Writes the details of all cars in the list to a file.
 * Each car's details (plate, mileage, and return date) are written to the file in CSV format.
 *
 * @param filename: The name of the file to write to.
 * @param head: Pointer to the head of the linked list.
 */
void write_list_to_file(char *filename, struct car *head) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return; // File opening failed

    struct car *current = head;
    
    // Write each car's details to the file in CSV format
    while (current != NULL) {
        fprintf(file, "%s,%d,%d\n", current->plate, current->mileage, current->return_date);
        current = current->next;
    }

    fclose(file); // Close the file
}

/*
 * Reads car details from a file and adds them to the list.
 * The function reads each car's details from the file (in CSV format) and inserts them into the list.
 *
 * @param filename: The name of the file to read from.
 * @param head: Pointer to the pointer of the list's head.
 */
void read_file_into_list(char *filename, struct car **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return; // File opening failed

    char plate[7];
    int mileage;
    int return_date;
    
    // Read each car's details from the file and insert into the list
    while (fscanf(file, "%6[^,],%d,%d\n", plate, &mileage, &return_date) == 3) {
        insert_to_list(head, plate, mileage, return_date);
    }

    fclose(file); // Close the file
}

/*
 * Prints a date in the format YY/MM/DD.
 * This function extracts the year, month, and day from the given date integer and prints it in a readable format.
 *
 * @param date: The date to be printed (YYMMDD format).
 */
void date(int date) {
    int year = date / 10000; // Extract the year
    int month = (date / 100) % 100; // Extract the month
    int day = date % 100; // Extract the day
    printf("%02d/%02d/%02d", year, month, day); // Print date in YY/MM/DD format
}

/*
 * Frees all the memory allocated for the cars in the list.
 * This function deallocates memory for each node in the list to avoid memory leaks.
 *
 * @param head: Pointer to the pointer of the list's head.
 */
void free_list(struct car **head) {
    struct car *current = *head;
    struct car *temp;
    // Traverse the list and free each car's memory
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL; // Set the head to NULL after freeing all nodes
}
