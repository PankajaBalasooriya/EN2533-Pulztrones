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
    int height_index = (box_height = 5) ? 0 : (box_height <= 10) ? 1 : 2;

    // Select the appropriate destination table based on the ordering
    if (ascending) {
        return destination_ascending[current_location][height_index];
    } else {
        return destination_descending[current_location][height_index];
    }
}

int meassure_box_height(){
  int top_tof_dist = robot.get_front_distance_from_bottom_tof();
  int mid_tof_dist = robot.get_front_distance_from_bottom_tof();
  int bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
  
  if (top_tof_dist <= 10 && mid_tof_dist <= 10 && bottom_tof_dist <= 10){
      return 15;
  }
  else if (top_tof_dist > 10 && mid_tof_dist <= 10 && bottom_tof_dist <= 10) {
    return 10;
  }
  else if (top_tof_dist > 10 && mid_tof_dist > 10 && bottom_tof_dist <= 10){
    return 5;
  }
  else{
    Serial.println("No Box detected");
  }
}

// void goto_box_destination(int dest){
//   switch(dest){
//     case 1 : //--
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); 
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//     case 2 : //_|-

//       FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();
//     case 3 :  // _||-
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
    
//     case 4 : //-|_
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//     case 5 ://--
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//     case 6 ://_|-
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();

//     case 7 ://-||_ 
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();

//     case 8 ://-|_
//       grab_box();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction();
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
//     case 9 :
//       grab_box();
//       FollowBlackLineUntilJunction(); FollowBlackLineUntilJunction();  
//       drop_box(); robot.turn_left_180();
//       FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward();
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
  int bottom_tof_dist;

  switch(dest){
    case 1 : //--
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(210);
      bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;
    case 2 : //_|-
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /* drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;
    case 3 :  // _||-
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10);  FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;

    case 4 : //-|_
      //grab_box();
      robot.turn_left_180();
      Buzzer_Toggle(100);
      FollowBlackLineUntilJunction(); robot.turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;
    case 5 ://--
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;
    case 6 ://_|-
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { 
        Serial2.println("No box detected"); 
        break;}
      break;

    case 7 ://-||_ 
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLine_GivenDistance(210);
       bottom_tof_dist = robot.get_front_distance_from_bottom_tof();
      if (bottom_tof_dist < 200){
        FollowBlackLine_GivenDistance(bottom_tof_dist);
      }
      else { break;}
      break;
    case 8 ://-|_
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); robot.Black_turn_Left_90_after_moving_forward(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(10); FollowBlackLineUntilJunction();
      break;
    case 9 :
      //grab_box();
      robot.turn_left_180();
      FollowBlackLineUntilJunction(); FollowBlackLine_GivenDistance(330);
      /*drop_box();*/ robot.turn_left_180();
      FollowBlackLineUntilJunction(); robot.Black_turn_Right_90_after_moving_forward(); FollowBlackLineUntilJunction();
      break;
    default:
      Serial.println("Invalid position");
      break;
  }
}