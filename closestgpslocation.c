#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <ctype.h>

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

int main() {
    // Declare buffer to store user input
    char buffer[100];

    // Read number of GPS locations in Array 1
    printf("Enter the number of GPS locations in Array 1: ");
    int n1;
    fgets(buffer, sizeof(buffer), stdin);

    // Check for valid input (valid integer less than or equal to 1)
    while (sscanf(buffer, "%d", &n1) != 1 || n1 < 1) {
        printf("Invalid input. Enter an integer greater than 0: ");
        fgets(buffer, sizeof(buffer), stdin);
    }

    // Read GPS locations in Array 1
    struct GPSLocation arr1[n1];
    for (int i = 0; i < n1; i++) {
        printf("Enter GPS location %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);

        // Check for valid input (valid GPS location in decimal degree format)
        while (sscanf(buffer, "%lf %lf", &arr1[i].longitude, &arr1[i].latitude) != 2 || arr1[i].longitude < -180 || arr1[i].longitude > 180 || arr1[i].latitude < -90 || arr1[i].latitude > 90) {
            printf("Invalid input. Enter a valid GPS location in decimal degree format {longitude latitude}: ");
            fgets(buffer, sizeof(buffer), stdin);
        }
    }

    // Read number of GPS locations in Array 2
    printf("Enter the number of GPS locations in Array 2: ");
    int n2;

    // Check for valid input (valid integer less than or equal to 1)
    fgets(buffer, sizeof(buffer), stdin);
    while (sscanf(buffer, "%d", &n2) != 1 || n2 < 1) {
        printf("Invalid input. Enter an integer greater than 0: ");
        fgets(buffer, sizeof(buffer), stdin);
    }

    // Read GPS locations in Array 2
    struct GPSLocation arr2[n2];
    for (int i = 0; i < n2; i++) {
        printf("Enter GPS location %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);

        // Check for valid input (valid GPS location in decimal degree format)
        while (sscanf(buffer, "%lf %lf", &arr2[i].longitude, &arr2[i].latitude) != 2 || arr2[i].longitude < -180 || arr2[i].longitude > 180 || arr2[i].latitude < -90 || arr2[i].latitude > 90) {
            printf("Invalid input. Enter a valid GPS location in decimal degree format {longitude latitude}: ");
            fgets(buffer, sizeof(buffer), stdin);
        }
    }

    // Match each GPS location in Array 1 with closest GPS location in Array 2
    findClosestGPSLocation(arr1, n1, arr2, n2);

    return 0;

}