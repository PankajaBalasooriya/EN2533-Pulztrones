#include "tasks.h"




void Tasks:: start_square() {
    // Code to execute the start square task
    Serial2.println("Starting.......");
}

// Tasks
//Task1
float error_enc_NEW = 0.0;
float correction_enc_NEW = 0.0;

int barcode[12];
int barcode_index = 0;
int stripCounter = 0;
int consecutiveEdges = 0;
Tasks:: Counting_and_Line_Navigation(){
    int distance = 2000;
    const int target_encoder_count = distance / MM_PER_COUNT;
    int encoder_count_left = 0;
    int encoder_count_right = 0;
   
    int currentColor = 1;
    int previousColor = 1;
    int lastStripStart = 0;
    resetEncoders();

    while(encoder_count_left < target_encoder_count && encoder_count_right < target_encoder_count){
        encoder_count_left = getLeftEncoderCounts();
        encoder_count_right = getRightEncoderCounts();

        float distance = (encoder_count_left + encoder_count_right) * 0.5 * MM_PER_COUNT;

        //int ir = analogRead(LEFT_MARKER_SENSOR);

        int leftSensorValue = analogRead(LEFT_MARKER_SENSOR);
        int rightSensorValue = analogRead(RIGHT_MARKER_SENSOR);
        // white 1
        //blacck 0

        if (leftSensorValue > 100 && rightSensorValue > 100){
            currentColor = 0;
        }
        else{
            currentColor = 1;
        }

        if(currentColor == 1 && previousColor == 0){
            lastStripStart = distance;
            previousColor = 1;
        }
        if(currentColor == 0 && previousColor == 1){
            if(stripCounter == 0){
                stripCounter++;
                previousColor = 0;
                continue;
            }
            float strip_length = distance - lastStripStart;

            if(strip_length < 40 && strip_length > 20){
                consecutiveEdges++;
                barcode[barcode_index] = 0;
                barcode_index++;
            }
            else if(strip_length > 40){
                barcode[barcode_index] = 1;
                barcode_index++;
                consecutiveEdges = 0;
            }

            //barcode[barcode_index] = distance - di;
            //Serial2.println(barcode[barcode_index - 1]);
            //barcode_index++;
            previousColor = 0;

        }

        if(consecutiveEdges == 3){
            break;
        }

        



        // Calculate encoder-based PID
        error_enc_NEW = encoder_count_right - encoder_count_left;
        correction_enc_NEW = PIDEnc(error_enc_NEW);

        // Combine encoder and IR corrections (with priority on encoder)
        float total_correction = correction_enc_NEW;

        // Calculate motor speeds
        float left_speed = BASE_SPEED - 10 + total_correction;
        float right_speed = BASE_SPEED - 10 - total_correction;

        setMotorLPWM(left_speed);
        setMotorRPWM(right_speed);

    }
    // MotorBreak();
    // setMotorLPWM(0);
    // setMotorRPWM(0);
    MoveDistanceForward(40);


    return calculateModulo5(binaryToDecimal(barcode, barcode_index - 3));
}



void Tasks:: execute_MoveToMaze() {
    // Code to execute the white line following task
    Serial2.println("Executing WHITE_LINE_FOLLOW");
    //MoveDistanceForward(40)
    FollowWhiteLineUntilJunction();
    turnRight90();
    FollowWhiteLineUntilJunction();

}

void Tasks:: execute_maze(int VB_POS) {
    // Code to execute the maze task
    Serial2.println("Executing MAZE");

    if(VB_POS == 0){
        robot.pick_virtual_box();
        
        MoveDistanceForward_and_not_stop(30);
        FollowWhiteLineUntilJunction();
        robot.drop_virtual_box();

        MoveDistanceReverse_and_not_stop(30);
        MoveReverseUntillJunction();
        turnRight90();
        FollowWhiteLineUntilJunction();
        turnLeft90();
        FollowWhiteLineUntilJunction();
        turnLeft90();
        FollowWhiteLineUntilJunction();

        //check open

        robot.pick_virtual_box();
        MoveDistanceReverse(30);
        MoveReverseUntillJunction();
        robot.drop_virtual_box();

        MoveReverseUntillJunction();
        turnLeft90();
        FollowWhiteLineUntilJunction();
        turnRight90();
        FollowWhiteLineUntilJunction();
        turnRight90();
        FollowWhiteLineUntilJunction();

        robot.pick_virtual_box();
        MoveReverseUntillJunction();

    }
}
void Tasks:: bar_code(){ //execute the task 

}
void Tasks:: executeColorLine(){

}
void Tasks:: executeDashedLine(){//execute the task 

}
void Tasks::executePortalNavigation(){//execute the task 

}
void Tasks:: executeBoxArranging(){//execute the task 

}
void Tasks:: executeChamberInsertion(){//execute the task 

}
void Tasks:: executeHiddenTask(){//execute the task 

}
void Tasks::executeUnevenTerrain(){
    
}