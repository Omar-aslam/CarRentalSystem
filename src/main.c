#include "q1.h"

/*
 * The main function manages a car rental system using three linked lists:
 * one for available cars, one for rented cars, and one for cars under repair.
 * The function displays a menu to allow users to add cars, rent cars, return cars,
 * transfer cars between lists, and view the lists.
 */

int main() {
    /* Initialize the heads of the three linked lists (all start empty).
    * 'available_head' stores cars that are available for rent.
    * 'rented_head' stores cars that are currently rented out.
    * 'repair_head' stores cars that are under repair.
    */
    struct car *available_head = NULL;
    struct car *rented_head = NULL;
    struct car *repair_head = NULL;
    
    // Variables to store user inputs (choice from the menu, car details like plate, mileage, return date).
    int choice;
    char plate[9]; // Car plate numbers have a maximum length of 8 characters plus the null terminator.
    int mileage, return_date;

    // Load the initial car data from text files into the corresponding linked lists.
    // Each file (available.txt, rented.txt, repair.txt) contains information about the cars in the respective lists.
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    // Main loop that continuously displays the menu and processes user input until the user chooses to quit.
    do {
        // Display the menu options to the user.
        prompt();
        printf("Enter a Choice: ");
        // Get the user's choice and validate that it's a valid integer input.
        if (scanf("%d", &choice) != 1) {  // Check if the input is a valid integer.
            printf("Invalid input! Please enter a valid choice.\n");
            while (getchar() != '\n');  // Clear the input buffer if the user entered an invalid input.
            continue;
        }

        // Use a switch-case structure to handle the user's choice.
        switch (choice) {
            // Case 1: Add a new car to the available-for-rent list.
            case 1:
                // Prompt the user for the car's plate number.
            printf("Enter plate number: ");
            printf("Plate number must be between 2 to 8 characters and contain only letters or numbers (e.g., AB1234).\n");
            if (scanf("%8s", plate) != 1) {  // Read up to 8 characters for the plate.
                printf("Invalid plate input!\n");
                while (getchar() != '\n');  // Clear the input buffer.
                continue;
            }
              // Validate plate input to ensure it meets the criteria.
                if (!is_valid_plate(plate)) {
                    printf("Invalid plate number! Please enter a valid plate (2-8 letters/numbers).\n");
                    continue;  // Ask for input again if the plate is invalid.
                }

                // If there are still characters in the input buffer, reject the input as invalid.
                if (getchar() != '\n') {
                    printf("Error: Plate number too long. It should be between 2 and 8 characters.\n");
                    while (getchar() != '\n');  // Clear the rest of the input buffer.
                    continue;
                }
            
                to_lowercase(plate);  // Convert the plate number to lowercase to ensure case consistency (AB1234 -> ab1234).

            printf("Enter mileage: "); // Get the car's mileage from the user.
            if (scanf("%d", &mileage) != 1) {  // Check for valid integer input
                printf("Invalid mileage input!\n");
                while (getchar() != '\n');  // Clear the input buffer
                continue;
            }
                
                // Check if the car's plate number already exists in any of the lists (to prevent duplicates).
            if (is_plate_in_list(available_head, plate) || is_plate_in_list(rented_head, plate) || is_plate_in_list(repair_head,  plate)) {
                printf("Error: Duplicate plate number.\n");
            } else 
                // If no duplicate is found, insert the new car into the available list.
            {
                insert_to_list(&available_head, plate, mileage, -1);
                printf("New car added to available-for-rent list.\n");
            }
            break;

            // Case 2: Add a returned car back to the available-for-rent list.
            case 2:
            printf("Enter plate number: ");
                // Ensure plate number follows the correct format.
            printf("Plate number must be between 2 to 8 characters and contain only letters or numbers (e.g., AB1234).\n");
            if (scanf("%8s", plate) != 1) { // Read plate number (up to 8 characters).
                printf("Invalid plate input!\n");
                while (getchar() != '\n'); // Clear input buffer.
                continue;
            }
            to_lowercase(plate);  // Convert the plate number to lowercase for consistent handling
              
                // Prompt the user for the car's "updated" mileage.
            printf("Enter new mileage: ");
            if (scanf("%d", &mileage) != 1) { // Validate mileage input.
                printf("Invalid mileage input!\n");
                while (getchar() != '\n'); // Clear input buffer.
                continue;
            }

                 // Remove the car from the rented list (if it exists there).
            struct car *returned_car = remove_car_from_list(&rented_head, plate);
            if (returned_car != NULL) // Ensure that the returned car's mileage hasn't decreased (error if true).
            {
                if (mileage < returned_car->mileage) {
                    printf("Error: Mileage cannot be less than before. Please re-enter the Mileage\n");
                } else {
                    // Calculate the profit based on the difference in mileage.
                    double profit = profit_calculator(returned_car->mileage, mileage);
                    printf("Car returned. Profit: $%.2f\n", profit);
                    
                    // Add the car back to the available list and free its memory.
                    insert_to_list(&available_head, plate, mileage, -1);
                    free(returned_car); // Free the memory for the removed car.
                }
            } else {
                // If the car wasn't found in the rented list, show an error.
                printf("Error: Car cannot be found in rented list.\n");
            }
            break;

            // Case 3: Add a returned car to the repair list.
            case 3:
                 // Get the car's plate number from the user.
            printf("Enter car's plate number: ");
            printf("Plate number must be between 2 to 8 characters and contain only letters or numbers (e.g., AB1234).\n");
            if (scanf("%8s", plate) != 1) { // Read plate number (up to 8 characters).
                printf("Invalid plate number input!\n");
                while (getchar() != '\n'); // Clear input buffer.
                continue;
            }
            to_lowercase(plate);  // Convert the plate number to lowercase

                // Get the new mileage of the car:
            printf("Enter new mileage: ");
            if (scanf("%d", &mileage) != 1) { // Validate mileage input as an integer.
                printf("Invalid mileage input!\n");
                while (getchar() != '\n'); // Clear input buffer.
                continue;
            }

                // Remove the car from the rented list and validate mileage.
            struct car *repair_car = remove_car_from_list(&rented_head, plate);
            if (repair_car != NULL) {
                // Ensure that the mileage hasn't decreased (error if true).
                if (mileage < repair_car->mileage) {
                    printf("Error: Mileage cannot be less than before.\n");
                } else {
                    // Calculate the rental profit based on mileage.
                    double profit = profit_calculator(repair_car->mileage, mileage);
                    printf("Car returned and sent to repair. Profit: $%.2f\n", profit);
                    
                    // Insert the car into the repair list and free its memory.
                    insert_to_list(&repair_head, plate, mileage, -1);
                    free(repair_car); // Free the memory for the removed car.
                }
            } else {
                // If the car wasn't found in the rented list, show an error message.
                printf("Error: Car not found in rented list.\n");
            }
            break;


                // Case 4: Transfer a car from the repair list back to the available-for-rent list.
            case 4:
                    // Get the car's plate number from the user.
            printf("Enter plate number: ");
            printf("Plate number must be between 2 to 8 characters and contain only letters or numbers (e.g., AB1234).\n");
            if (scanf("%8s", plate) != 1) { // Read plate number (up to 8 characters).
                printf("Invalid plate input!\n");
                while (getchar() != '\n'); // Clear input buffer.
                continue;
            }
            to_lowercase(plate);  // Convert the plate number to lowercase for consistent handling

                // Remove the car from the repair list.
            struct car *transfer_car = remove_car_from_list(&repair_head, plate);
            if (transfer_car != NULL) {
                // Add the car to the available-for-rent list and free its memory.
                insert_to_list(&available_head, plate, transfer_car->mileage, -1);
                printf("Car transferred from repair to available-for-rent list.\n");
                free(transfer_car); // Free the memory for the removed car.
            } else {
                // If the car wasn't found in the repair list, show an error.
                printf("Error: Car not found in repair list.\n");
            }
            break;


                    // Case 5: Rent the first available car, recording the return date.
                    case 5:
                        // Loop until a valid return date is entered by the user.
                while (1) {
                    printf("Enter return date (YYMMDD): ");
                    if (scanf("%d", &return_date) != 1) { // Ensure valid integer input for date.
                        printf("Invalid date input! Please enter a valid date in the format YYMMDD.\n");
                        while (getchar() != '\n');  // Clear the input buffer
                        continue;
                    }

                    // Validate the entered date using month and day checks
                    int month = (return_date / 100) % 100;    // Extract the month
                    int day = return_date % 100;              // Extract the day

                    // Validate the month and day values.
                    if (month < 1 || month > 12) {
                        printf("Error: Invalid month. Please enter a month between 01 and 12.\n");
                        continue;
                    }

                    // Check if the day is valid
                    if (day < 1 || day > 31) {
                        printf("Error: Invalid day. Please enter a day between 01 and 31.\n");
                        continue;
                    }

                    // Additional checks for specific months with fewer days
                    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                        printf("Error: Invalid day. The entered month has only 30 days. Please enter a day between 01 and 30.\n");
                        continue;
                    }

                    if (month == 2 && day > 28) {  // February has only up to 28 days (ignoring leap years)
                        printf("Error: Invalid day. February has only 28 days. Please enter a day between 01 and 28.\n");
                        continue;
                    }

                    // If all validations pass, break out of the loop
                    break;
                }

                        // Check if there are any available cars to rent.
                if (available_head == NULL) {
                    printf("Error: No cars available for rent.\n");
                } else {
                    // Rent out the first available car.
                    struct car *rented_car = remove_first_from_list(&available_head);
                    insert_to_list(&rented_head, rented_car->plate, rented_car->mileage, return_date);
                    // Confirm the rental and display the return date.
                    printf("Car %s rented out. Return Date: ", rented_car->plate);
                    date(return_date);
                    printf("\n");
                    free(rented_car); // Free the removed car's memory.
                }
                break;

            // Case 6: Print the details of all three car lists.
            case 6:
                printf("\nAvailable-for-Rent List:\n");
                print_list(available_head);  // Print the available car list.
                printf("\nRented List:\n");
                print_list(rented_head);  // Print the rented car list.
                printf("\nRepair List:\n");
                print_list(repair_head);  // Print the repair car list.
                break;

            // Case 7: Save the car lists to their respective files and quit the program.
            case 7:
                // Save the current state of all three lists to text files.
                write_list_to_file("available.txt", available_head);
                write_list_to_file("rented.txt", rented_head);
                write_list_to_file("repair.txt", repair_head);
                printf("Data saved successfully. Exiting...\n");
                // Free all memory allocated for the car lists to avoid memory leaks.
                free_list(&available_head);
                free_list(&rented_head);
                free_list(&repair_head);
                return 0; // Exit the program.

            // Default case: Handle invalid menu choices.
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (1); // Continue the menu loop indefinitely until the user quits.

    return 0;
}
