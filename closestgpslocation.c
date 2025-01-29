#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define EARTH_RADIUS 6371.0 // in km

// Define a struct to store GPS location in decimal degree format
struct GPSLocation {
    double longitude;
    double latitude;
};

// Calculate distance between two GPS coordinates using haversine formnula
double calculateDistance(double long1, double lat1, double long2, double lat2) {
    // Convert GPS coordinates from degrees to radians
    double long1Rad = long1 * M_PI / 180;
    double lat1Rad = lat1 * M_PI / 180;
    double long2Rad = long2 * M_PI / 180;
    double lat2Rad = lat2 * M_PI / 180;

    // Calculate differences in longitudes and latitudes
    double dlong = long2Rad - long1Rad;
    double dlat = lat2Rad - lat1Rad;

    // Haversine formula
    double a = pow(sin(dlat/2), 2) + cos(lat1Rad) * cos(lat2Rad) * pow(sin(dlong/2), 2);
    // Inverse haversine formula to calculate distance
    double distance = 2 * EARTH_RADIUS * asin(sqrt(a));

    return distance;
}

// Match each GPS location in Array 1 with closest GPS location in Array 2
void findClosestGPSLocation(struct GPSLocation * arr1, int n1, struct GPSLocation * arr2, int n2) {
    for (int i = 0; i < n1; i++) {
        double minDistance = -1;
        int closestIndex = -1;
        for (int j = 0; j < n2; j++) {
            double distance = calculateDistance(arr1[i].longitude, arr1[i].latitude, arr2[j].longitude, arr2[j].latitude);
            if (minDistance == -1 || distance < minDistance) {
                minDistance = distance;
                closestIndex = j;
            }
        }

        printf("GPS location {%lf, %lf} in Array 1 is closest to GPS location {%lf, %lf} in Array 2 with a distance of %lf km.\n", arr1[i].longitude, arr1[i].latitude, arr2[closestIndex].longitude, arr2[closestIndex].latitude, minDistance);
    }
}

// stolen from stackoverflow
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}

// function to detect and convert between longitude and latitude formats
void convertGPSLocation(struct GPSLocation * coords) {
    // detect DMS format

    // convert DMS to decimal degree format

    // detect DM format

    // convert DM to decimal degree format

    // detect decimal degree format

    // return decimal degree format
}

// function to store categories of the data table in an array
void storeCategories(char *categories, char **categoriesArray) {
    int i = 0;
    while (categories != NULL) {
        while (isspace(*categories)) categories++; // ignore leading spaces

        // ignore trailing spaces
        char *end = categories + strlen(categories) - 1;
        while (end > categories && isspace(*end)) {
            *end = '\0';
            end--;
        }

        categoriesArray[i] = strdup(categories);
        categories = strtok(NULL, ",");
        i++;
    }
}

// function for determining file length
int fileLength(FILE *infile) {
    int length = 0;
    char row[1024];
    while (fgets(row, sizeof(row), infile)) {
        length++;
    }
    // reset file pointer to beginning of file
    fseek(infile, 0, SEEK_SET);
    return length;
}

// function for file processing
struct GPSLocation *processFile(FILE *infile, char fileType, char **categoriesArray, int longIndex, int latIndex) {
    if (fileType == 'c') {
        // process csv file
        
        // if empty or invalid cell, ignore row
        // store the data in a struct array
        // remove leading and trailing spaces, leading and trailing quotes
        char row[1024];
        char *col;
        int length = fileLength(infile);
        struct GPSLocation *coordsArray = (struct GPSLocation *)malloc((length + 1) * sizeof(struct GPSLocation));
        if (coordsArray == NULL) {
            printf("Error: Unable to allocate memory.\n");
            return NULL;
        }

        int rowCounter = 0;

        while (fgets(row, sizeof(row), infile)) {
            col = strtok(row, ",");
            int currentIndex = 0;
            while (col != NULL) {
                while (isspace(*col)) col++; // ignore leading spaces

                // ignore trailing spaces
                char *end = col + strlen(col) - 1;
                while (end > col && isspace(*end)) {
                    *end = '\0';
                    end--;
                }

                // ignore leading and trailing quotes
                if (*col == '"') {
                    col++;
                }
                if (*(end) == '"') {
                    *end = '\0';
                }

                if (currentIndex == longIndex) {
                    coordsArray[rowCounter].longitude = atof(col);
                } else if (currentIndex == latIndex) {
                    coordsArray[rowCounter].latitude = atof(col);
                }

                col = strtok(NULL, ",");
                currentIndex++;
            }
            rowCounter++;
            
        }
        // convert the data to decimal degree format (call function)

        // reset file pointer to beginning of file
        fseek(infile, 0, SEEK_SET);

        return coordsArray;

    } else if (fileType == 'j') {
        // process json file
    }
    return NULL;
}

int main() {
    char row[100];
    char entryType1; // set as m for manual or f for file
    char entryType2; // set as m or f
    char fileType1; // set as c for csv or j for json
    char fileType2; // set as c or j
    char *categories;
    char *categories1Array[100];
    char *categories2Array[100];

    FILE *infile1;
    FILE *infile2;

    struct GPSLocation *arr1 = NULL;
    struct GPSLocation *arr2 = NULL;
    int n1 = 0;
    int n2 = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // Array 1
    // ask if user wants to input data manually or from a file
    printf("Array 1: Would you like to input the data manually or from a file? (m/f): ");
    fgets(row, sizeof(row), stdin);
    
    entryType1 = row[0];
    while (entryType1 != 'm' && entryType1 != 'f') {
        printf("Error: Invalid entry type. Please try again: ");
        fgets(row, sizeof(row), stdin);
        entryType1 = row[0];
    }

    if (entryType1 == 'm') { // if user wants to input data manually
        // Declare buffer to store user input
        char buffer[100];

        // Read number of GPS locations in Array 1
        printf("Enter the number of GPS locations in Array 1: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Check for valid input (valid integer less than or equal to 1)
        while (sscanf(buffer, "%d", &n1) != 1 || n1 < 1) {
            printf("Invalid input. Enter an integer greater than 0: ");
            fgets(buffer, sizeof(buffer), stdin);
        }

        // Read GPS locations in Array 1
        arr1 = (struct GPSLocation *)malloc(n1 * sizeof(struct GPSLocation));

        for (int i = 0; i < n1; i++) {
            printf("Enter GPS location %d: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);

            // Check for valid input (valid GPS location in decimal degree format)
            while (sscanf(buffer, "%lf %lf", &arr1[i].longitude, &arr1[i].latitude) != 2 || arr1[i].longitude < -180 || arr1[i].longitude > 180 || arr1[i].latitude < -90 || arr1[i].latitude > 90) {
                printf("Invalid input. Enter a valid GPS location in decimal degree format {longitude latitude}: ");
                fgets(buffer, sizeof(buffer), stdin);
            }
        }
    } else { // if user wants to input data from a file
        // allow user to input file name of of the first csv/json file
        printf("Enter the name of the first data file: ");
    
        fgets(row, sizeof(row), stdin);
        row[strcspn(row, "\n")] = 0; // remove newline character

        infile1 = fopen(row, "r");

        if (infile1 == NULL) {
            printf("Error: Unable to open file.\n");
            return -1;
        }

        // check if the file is a csv or json file
        if (strcmp(get_filename_ext(row), "csv") == 0) {
            fileType1 = 'c';
        } else if (strcmp(get_filename_ext(row), "json") == 0) {
            fileType1 = 'j';
        } else {
            printf("Error: File type not supported.\n");
            return -1;
        }

        printf("Enter the categories of the data table in order from left to right, separated by commas: ");
        fgets(row, sizeof(row), stdin);
        categories = strtok(row, ",");

        // store categories in an array
        storeCategories(categories, categories1Array);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // Array 2
    // ask if user wants to input data manually or from a file
    printf("Array 2: Would you like to input the data manually or from a file? (m/f): ");
    fgets(row, sizeof(row), stdin);
    
    entryType2 = row[0];
    while (entryType2 != 'm' && entryType2 != 'f') {
        printf("Error: Invalid entry type. Please try again: ");
        fgets(row, sizeof(row), stdin);
        entryType2 = row[0];
    }

    if (entryType2 == 'm') {
        // Declare buffer to store user input
        char buffer[100];
        // Read number of GPS locations in Array 2
        printf("Enter the number of GPS locations in Array 2: ");

        // Check for valid input (valid integer less than or equal to 1)
        fgets(buffer, sizeof(buffer), stdin);
        while (sscanf(buffer, "%d", &n2) != 1 || n2 < 1) {
            printf("Invalid input. Enter an integer greater than 0: ");
            fgets(buffer, sizeof(buffer), stdin);
        }

        // Read GPS locations in Array 2
        arr2 = (struct GPSLocation *)malloc(n2 * sizeof(struct GPSLocation));

        for (int i = 0; i < n2; i++) {
            printf("Enter GPS location %d: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);

            // Check for valid input (valid GPS location in decimal degree format)
            while (sscanf(buffer, "%lf %lf", &arr2[i].longitude, &arr2[i].latitude) != 2 || arr2[i].longitude < -180 || arr2[i].longitude > 180 || arr2[i].latitude < -90 || arr2[i].latitude > 90) {
                printf("Invalid input. Enter a valid GPS location in decimal degree format {longitude latitude}: ");
                fgets(buffer, sizeof(buffer), stdin);
            }
        }
    } else {
        // allow user to input file name of of the second csv/json file
        printf("Enter the name of the second data file: ");
        fgets(row, sizeof(row), stdin);

        row[strcspn(row, "\n")] = 0; // remove newline character
        
        infile2 = fopen(row, "r");
        if (infile2 == NULL) {
            printf("Error: Unable to open file.\n");
            return -1;
        }
        
        // check if the file is a csv or json file
        if (strcmp(get_filename_ext(row), "csv") == 0) {
            fileType2 = 'c';
        } else if (strcmp(get_filename_ext(row), "json") == 0) {
            fileType2 = 'j';
        } else {
            printf("Error: File type not supported.\n");
            return -1;
        }

        printf("Enter the categories of the data table in order from left to right, seperated by commas: ");
        fgets(row, sizeof(row), stdin);
        categories = strtok(row, ",");

        // store categories in an array
        storeCategories(categories, categories2Array);
    }
   
    /////////////////////////////////////////////////////////////////////////////////////
    // for files: identify the longitude and latitude columns
    int long1Index = -1;
    int lat1Index = -1;
    int long2Index = -1;
    int lat2Index = -1;

    if (entryType1 == 'f') {
        int i = 0;
        while(i < 100 && categories1Array[i] != NULL) {
            if (strcasecmp(categories1Array[i], "longitude") == 0 || \
            strcasecmp(categories1Array[i], "long") == 0 || \
            strcasecmp(categories1Array[i], "lon") == 0 || \
            strcasecmp(categories1Array[i], "lng") == 0 ) {
                long1Index = i;
            } else if (strcasecmp(categories1Array[i], "latitude") == 0 || \
            strcasecmp(categories1Array[i], "lat") == 0 ) {
                lat1Index = i;
            }
            i++;
        }
        if (long1Index == -1 || lat1Index == -1) {
            printf("Error: Longitude and latitude columns not found in the first data file.\n");
            return -1;
        }
    }
    
    if (entryType2 == 'f') {
        int i = 0;
        while (i < 100 && categories2Array[i] != NULL) {
            if (strcasecmp(categories2Array[i], "longitude") == 0 || \
            strcasecmp(categories2Array[i], "long") == 0 || \
            strcasecmp(categories2Array[i], "lon") == 0 || \
            strcasecmp(categories2Array[i], "lng") == 0 ) {
                long2Index = i;
            } else if (strcasecmp(categories2Array[i], "latitude") == 0 || \
            strcasecmp(categories2Array[i], "lat") == 0 ) {
                lat2Index = i;
            }
            i++;
        }
        if (long2Index == -1 || lat2Index == -1) {
            printf("Error: Longitude and latitude columns not found in the second data file.\n");
            return -1;
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////
    // read the data from the csv/json files


    if (entryType1 == 'f') {
        arr1 = processFile(infile1, fileType1, categories1Array, long1Index, lat1Index);
        n1 = fileLength(infile1);
    }
    if (entryType2 == 'f') {
        arr2 = processFile(infile2, fileType2, categories2Array, long2Index, lat2Index);
        n2 = fileLength(infile2);
    }

    findClosestGPSLocation(arr1, n1, arr2, n2);
    
    free(arr1);
    free(arr2);

    // if empty or invalid cell, ignore row

    


    
    // // Match each GPS location in Array 1 with closest GPS location in Array 2
    // findClosestGPSLocation(arr1, n1, arr2, n2);

    return 0;

}