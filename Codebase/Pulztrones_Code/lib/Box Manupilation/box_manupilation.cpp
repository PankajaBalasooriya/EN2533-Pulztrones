#include <Arduino.h>
#include <controller.h>
#include <robot.h>

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


// void goto_box_destination(int dest){
//   switch(dest){
//     case 1 : //--
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); 
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//     case 2 : //_|-

//       FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();
//     case 3 :  // _||-
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
    
//     case 4 : //-|_
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//     case 5 ://--
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//     case 6 ://_|-
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();

//     case 7 ://-||_ 
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();

//     case 8 ://-|_
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
//     case 9 :
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();  
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.turn_right_90();
//     default:
//       Serial.println("Invalid position");
//   }
// }


// void FollowBlackLineUntilJunction(){
  
// }
// void turn_left(){
  
// }
// void turn_right(){
  
// }
// void grab_box(){

// }
// void drop_box(){

// }
// void turn180(){

// }

void goto_box_destination(int dest){
  switch(dest){
    case 1 : //--
      //grab_box();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_right_90();/*robot.Black_turn_Right_90_after_moving_forward();*/ FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
    case 2 : //_|-
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLine_GivenDistance(330);
      /* drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);
    case 3 :  // _||-
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10);  FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLine_GivenDistance(330);
    
    case 4 : //-|_
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
    case 5 ://--
      //grab_box();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
    case 6 ://_|-
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(330);

    case 7 ://-||_ 
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);

    case 8 ://-|_
      //grab_box();
      FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction(); robot.turn_left_90(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_right_90(); FollowBlackLineUntilJunction();
    case 9 :
      //grab_box();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_right_90();
    default:
      Serial.println("Invalid position");
  }
}