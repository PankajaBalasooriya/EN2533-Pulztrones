#ifndef PROFILE_H
#define PROFILE_H

#include <Arduino.h>
#include "config.h"

class Profile;



class Profile{
    public:
        enum State : uint8_t {
            PS_IDLE = 0,
            PS_ACCELERATING = 1,
            PS_BRAKING = 2,
            PS_FINISHED = 3,
         };

        void reset();
        bool is_finished();

        /// @brief  Begin a profile. Once started, it will automatically run to completion
        ///         Subsequent calls before completion supercede all the parameters.
        ///         Called may monitor progress using is_finished() method
        /// @param distance     (mm)     always positive
        /// @param top_speed    (mm/s)   negative values move the robot in reverse
        /// @param final_speed  (mm/s)
        /// @param acceleration (mm/s/s)
        void start(float distance, float top_speed, float final_speed, float acceleration);

        // Start a profile and wait for it to finish. This is a blocking call.
        void move(float distance, float top_speed, float final_speed, float acceleration);

        void wait_until_finished();

        /// @brief causes the profile to immediately terminate with the speed to zero
        ///        note that even when the state is PS_FINISHED, the profiler will
        ///        continue to try and reach the target speed. (zero in this case)
        void stop();

        /// @brief  Force a profile to finish with the target speed set to the final speed
        void finish();

        void set_state(State state);

        /// @brief  Calculate the distance needed to get to the final speed from the
        ///         current speed using the current acceleration.
        /// @return distance (mm)
        float get_braking_distance();

        /// @brief  gets the distance travelled (mm) since the last call to start(). If there
        ///         was a prior call to set_position() distance is incremented from there.
        /// @return distance travelled (mm)
        float position();

        /// @brief Get the current speed
        /// @return
        float speed();

        float acceleration();
        void set_speed(float speed);
        void set_target_speed(float speed);

        // normally only used to alter position for forward error correction
        void adjust_position(float adjustment);

        void set_position(float position);

        // update is called from within systick and should be safe from interrupts
        void update();



    private:
        volatile uint8_t r_state = PS_IDLE;
        volatile float r_speed = 0;
        volatile float r_position = 0;
        int8_t r_sign = 1;
        float r_acceleration = 0;
        float r_one_over_acc = 1;
        float r_target_speed = 0;
        float r_final_speed = 0;
        float r_final_position = 0;

};

extern Profile forward;
extern Profile rotation;

#endif