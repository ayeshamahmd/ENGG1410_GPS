#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct user_t {
    double latitude;
    double longitude;
    double altitude;
    double time;
    char name[100];
};

//function that reads user data from the file
//stores in user_t struct 
//if value returned is not 1 then prints error and exits
void scan_user(struct user_t *user, FILE *file) {
    if (fscanf(file, "%s", user->name) != 1) {
        printf("Error reading name.\n");
        exit(1);
    }
  //reads a double value from the file and stores in the time member of the user struct
    if (fscanf(file, "%lf", &user->latitude) != 1) {
        printf("Error reading time.\n");
        exit(1);
    }
  //reads a double value from the file and stores in the latitude member of the user struct
    if (fscanf(file, "%lf", &user->longitude) != 1) {
        printf("Error reading latitude.\n");
        exit(1);
    }
    if (fscanf(file, "%lf", &user->altitude) != 1) {
        printf("Error reading longitude.\n");
        exit(1);
    }
    if (fscanf(file, "%lf", &user->time) != 1) {
        printf("Error reading altitude.\n");
        exit(1);
    }}
//function to calculate the distance between two users 
//const used to prevent parameter from being changed 
double calculate_distance(const struct user_t *user1, const struct user_t *user2) {
    double lat_diff = user1->latitude - user2->latitude;
    double long_diff = user1->longitude - user2->longitude;
    double alt_diff = user1->altitude - user2->altitude;
    return sqrt(lat_diff * lat_diff + long_diff * long_diff + alt_diff * alt_diff);

}
    
//function to find the closest user
      struct user_t find_closest_user(const struct user_t *our_user, const struct user_t *other_users, int num_users) {
    struct user_t closest_user;
    double min_distance = calculate_distance(our_user, &other_users[0]);
    closest_user = other_users[0];

  //loops through other_users array starting from index 1 and calculates distance
    for (int i = 1; i < num_users; i++) {
        double distance = calculate_distance(our_user, &other_users[i]);

      //updates minimum distance and closest_user if one is found
        if (distance < min_distance) {
            min_distance = distance;
            closest_user = other_users[i];
        }
    }
      
      
    return closest_user;
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
//opens file to read
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
//reads the number of users from file (reads integer values)
    int num_users;
    if (fscanf(file, "%d", &num_users) != 1) {
        printf("Error reading the number of users.\n");
        fclose(file);
        return 1;
    }
//reads data from the file and stores in our_user struct
    struct user_t our_user;
    scan_user(&our_user, file);
  
//an array created to store user data for other users using the scan_user function
  struct user_t other_users[num_users - 1];
    for (int i = 0; i < num_users - 1; i++) {
        scan_user(&other_users[i], file);
    }

    fclose(file);
//print reference user data
    printf("Reference user:\n");
    printf("User %s:\n", our_user.name);
    printf("Longitude: %lf\n", our_user.longitude);
    printf("Latitude: %lf\n", our_user.latitude);
    printf("Altitude: %lf\n", our_user.altitude);
    printf("Time: %lf\n\n", our_user.time);

    printf("List of other users:\n");
    for (int i = 0; i < num_users - 1; i++) {
        printf("User %s:\n", other_users[i].name);
        printf("Longitude: %lf\n", other_users[i].longitude);
        printf("Latitude: %lf\n", other_users[i].latitude);
        printf("Altitude: %lf\n", other_users[i].altitude);
        printf("Time: %lf\n\n", other_users[i].time);
    }
//finds closest user
    struct user_t closest = find_closest_user(&our_user, other_users, num_users - 1);

  //calculates and prints distance between our user and each of the other users
  printf("Actual distances from our user were:\n");
    for (int i = 0; i < num_users - 1; i++) {
        double distance = calculate_distance(&our_user, &other_users[i]);
        printf("User number: %d at distance %f named %s\n", i + 1, distance, other_users[i].name);
    }

    printf("\nNearest user from reference user:\n");
    printf("User %s:\n", closest.name);
    printf("Longitude: %lf\n", closest.longitude);
    printf("Latitude: %lf\n", closest.latitude);
    printf("Altitude: %lf\n", closest.altitude);
    printf("Time: %lf\n", closest.time);

    return 0;
  }


// gcc -o main main.c -lm 
//./main other_users2.txt
