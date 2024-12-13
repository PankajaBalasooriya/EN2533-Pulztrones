#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600);

}

int find_destination(int current_location, int box_height, bool ascending) {
    // Define destination mappings for ascending and descending orders
    int destination_ascending[3][3] = {
        {1, 2, 3}, // For location 0, ascending: box height <= 5, <= 10, <= 15
        {4, 5, 6}, // For location 1, ascending: box height <= 5, <= 10, <= 15
        {7, 8, 9}  // For location 2, ascending: box height <= 5, <= 10, <= 15
    };

    int destination_descending[3][3] = {
//        {12, 11, 10}, // For location 0, descending: box height <= 15, <= 10, <= 5
//        {15, 14, 12}, // For location 1, descending: box height <= 15, <= 10, <= 5
//        {18, 17, 16}  // For location 2, descending: box height <= 15, <= 10, <= 5

        {3, 2, 1}, // For location 0, descending: box height <= 5, <= 10, <= 15
        {6, 5, 4}, // For location 1, descending: box height <= 5, <= 10, <= 15
        {9, 8, 7}  // For location 2, descending: box height <= 5, <= 10, <= 15
    };

    // Determine the height index based on the box height
    int height_index = (box_height <= 5) ? 0 : (box_height <= 10) ? 1 : 2;

    // Select the appropriate destination table based on the ordering
    if (ascending) {
        return destination_ascending[current_location][height_index];
    } else {
        return destination_descending[current_location][height_index];
    }
}

void goto_box_destination(int dest){
  switch(dest){
    case 1 : 
      go_forward(); go_forward();
    case 2 :
      go_forward(); turn_left(); go_forward(); turn_right(); go_forward();
    case 3 :
      go_forward(); turn_left(); go_forward(); go_forward(); turn_right(); go_forward();

    case 4 : 
      go_forward(); turn_right(); go_forward(); turn_left(); go_forward();
    case 5 :
      go_forward(); go_forward();
    case 6 :
      go_forward(); turn_left(); go_forward(); turn_right(); go_forward();

    case 7 : 
      go_forward(); turn_right(); go_forward(); go_forward(); turn_left(); go_forward();
    case 8 :
      go_forward(); turn_right(); go_forward(); turn_left(); go_forward();
    case 9 :
      go_forward(); go_forward();  
    
    default:
      Serial.println("Invalid position");
  }
}


void go_forward(){
  
}
void turn_left(){
  
}
void turn_right(){
  
}
