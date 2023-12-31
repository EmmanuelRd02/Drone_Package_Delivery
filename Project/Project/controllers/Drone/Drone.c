#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/compass.h>
#include <webots/gps.h>
#include <webots/gyro.h>
#include <webots/inertial_unit.h>
#include <webots/keyboard.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/accelerometer.h>

#define SIGN(x) ((x) > 0) - ((x) < 0)
#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))
#define PI 3.14159265358979323846

int errorCount = 0;
int cPoints = 0;
struct Coordenadas { int x; int y; };

void calcularDiferencia(double x_atual, double y_atual, double angle, double x_desejado, double y_desejado, double* pitch, double* roll, double* yaw, int* rotating, double* yawVelocity,double* error) {
	double deltaX = x_desejado - x_atual;
	double deltaY = y_desejado - y_atual;
	double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	double destinationAngle = atan2(deltaY, deltaX);
	double errorAngle = angle - destinationAngle;
	if (errorAngle < -PI || errorAngle > PI) {
		errorAngle = destinationAngle + angle;
	}
	double kpYaw = -1;
	double kiYaw = 0.5;
	double kdYaw = 0.0;
	*yaw = CLAMP(kpYaw * errorAngle + kiYaw * errorAngle + kdYaw * errorAngle, -1, 1);
	double media = 0;
	if (*rotating == 1) {
                error[errorCount] = errorAngle;
                errorCount++;
                if (errorCount == 1000) {
                    errorCount = 0;
                    cPoints = 1;
                }
                    if (cPoints == 0) {
		for (int i = 0; i < errorCount; i++) {
            	     media += error[i];
		}
		media /= errorCount;
  	         }
        	         else {
		   for (int i = 0; i < 1000; i++) {
		        media += error[i];
		   }
	          media /= 1000;
	          }
	         if (!((media < -0.0005 || media > 0.0005) && (*yawVelocity < -0.00005 || *yawVelocity > 0.00005))) {
		 *rotating = 0;
	          }
	}
	if (*rotating == 0) {
	    double kpPitch = 0.3;
	    double kiPitch = -0.005;
	    double kdPitch = 0.0;
	    *pitch = -CLAMP(kpPitch * distance + kiPitch * distance + kdPitch * distance, -2, 2);
	}
}


int main(int argc, char** argv) {
	wb_robot_init();
	int timestep = (int)wb_robot_get_basic_time_step();

	// Get and enable devices.
	WbDeviceTag camera = wb_robot_get_device("camera");
	wb_camera_enable(camera, timestep);
	WbDeviceTag front_left_led = wb_robot_get_device("front left led");
	WbDeviceTag front_right_led = wb_robot_get_device("front right led");
	WbDeviceTag imu = wb_robot_get_device("inertial unit");
	wb_inertial_unit_enable(imu, timestep);
	WbDeviceTag gps = wb_robot_get_device("gps");
	wb_gps_enable(gps, timestep);
	WbDeviceTag compass = wb_robot_get_device("compass");
	wb_compass_enable(compass, timestep);
	WbDeviceTag gyro = wb_robot_get_device("gyro");
	wb_gyro_enable(gyro, timestep);
	wb_keyboard_enable(timestep);
	WbDeviceTag camera_roll_motor = wb_robot_get_device("camera roll");
	WbDeviceTag camera_pitch_motor = wb_robot_get_device("camera pitch");
	WbDeviceTag camera_yaw_motor = wb_robot_get_device("camera yaw");  // Not used in this example.

	// Get propeller motors and set them to velocity mode.
	WbDeviceTag front_left_motor = wb_robot_get_device("front left propeller");
	WbDeviceTag front_right_motor = wb_robot_get_device("front right propeller");
	WbDeviceTag rear_left_motor = wb_robot_get_device("rear left propeller");
	WbDeviceTag rear_right_motor = wb_robot_get_device("rear right propeller");
	WbDeviceTag motors[4] = { front_left_motor, front_right_motor, rear_left_motor, rear_right_motor };
	int m;
	for (m = 0; m < 4; ++m) {
		wb_motor_set_position(motors[m], INFINITY);
		wb_motor_set_velocity(motors[m], 10.0);
	}
	struct Coordenadas arrayDeCoordenadas[50] = {
		{-14, 7}, //First delivery.
		{0, 0}, // #2
		
		{-14, -7}, //Second delivery.
		{0, 0}, // #4
		
		{-14, -1}, // #5
		{-37, -5}, //Third delivery.
		{0, 0}, // #7
		
		{-14, -1}, // #8
		{-30, -5}, // #9
		{-26, -20}, //Fourth delivery.
		{-30, -5}, // #11
		{0, 0}, // #12

		{-14, -1}, // #13
		{-30, -5}, // #14
		{-30, -40},  // #15
		{-16, -43}, //Fifth delivery.
		{-30, -45}, // #17
		{-30, -5}, // #18
		{0, 0}, // #19

		{-14, -1}, // #20
		{-30, -5}, // #21
		{-37, -55}, //Sixth delivery.
		{-30, -5}, // #23
		{0, 0}, // #24
		
		{-14, -1}, // #25
		{-30, -5}, // #26
		{-30, -70}, // #27
		{-18, -79}, //Seventh delivery.
		{-30, -70}, // #29
		{-30, -5}, // #30
		{0, 0}, // #31
		
		{-14, 5}, // #32
		{-35, 8}, // #33
		{-37, 40}, //Eighth delivery.
		{-35, 8}, // #35
		{0, 0}, // #36
		
		{-14, 5}, // #37
		{-30, 7}, // #38
		{-30, 51}, //Nineth delivery.
		{-22, 51}, // #40
		{-30, 45}, // #41
		{-30, 7}, // #42
		{0, 0}, // #43
		
		{-14, 5}, // #44
		{-30, 7}, // #45
		{-30, 55}, //Tenth delivery.
		{-44, 68}, // #47
		{-30, 55}, // #48
		{-30, 7}, // #49
		{0, 0}, // #50 
	};

	size_t sizePoints = sizeof(arrayDeCoordenadas) / sizeof(arrayDeCoordenadas[0]);
	int point = 0;
	int rotating = 1;
	double error[1000];
	for (int i = 0; i < 1000; i++) {
		error[i] = 0.0;
	}
	printf("Start the drone...\n"); // Display the welcome message.
	while (wb_robot_step(timestep) != -1) { // Wait one second.
		if (wb_robot_get_time() > 1.0)
			break;
	}
	// Constants, empirically found.
	const double k_vertical_thrust = 68.5;  // With this thrust, the drone lifts.
	const double k_vertical_offset = 0.6;   // Vertical offset where the robot actually targets to stabilize itself.
	const double k_vertical_p = 3.0;        // P constant of the vertical PID.
	const double k_roll_p = 50.0;           // P constant of the roll PID.
	const double k_pitch_p = 50.0;          // P constant of the pitch PID.
	double target_altitude = 1.5;  // The target altitude.
	
	while (wb_robot_step(timestep) != -1) { // Main loop

    	       const double time = wb_robot_get_time();  // in seconds.

	       // Retrieve robot position using the sensors.
	       const double roll = wb_inertial_unit_get_roll_pitch_yaw(imu)[0];
	       const double pitch = wb_inertial_unit_get_roll_pitch_yaw(imu)[1];
	       const double yaw = wb_inertial_unit_get_roll_pitch_yaw(imu)[2];
	       const double X = wb_gps_get_values(gps)[0];
	       const double Y = wb_gps_get_values(gps)[1];
	       const double altitude = wb_gps_get_values(gps)[2];
	       const double roll_velocity = wb_gyro_get_values(gyro)[0];
	       const double pitch_velocity = wb_gyro_get_values(gyro)[1];
	       const double yaw_velocity = wb_gyro_get_values(gyro)[2];
	       // Transform the keyboard input to disturbances on the stabilization algorithm.
	       double roll_disturbance = 0.0;
	       double pitch_disturbance = 0.0;
	       double yaw_disturbance = 0.0;
	       if (time > 5) {
		calcularDiferencia(X, Y, yaw, arrayDeCoordenadas[point].x, arrayDeCoordenadas[point].y, &pitch_disturbance, &roll_disturbance, &yaw_disturbance, &rotating, &yaw_velocity, &error);
		printf("x:%f ", X);
		printf("y:%f ", Y);
		printf("z:%f ",altitude);
		printf("yaw:%f ", yaw);
		printf("# Coordinate:%d\n", point);
		if ((pitch_disturbance > -0.15 && pitch_disturbance < 0.15) &&
		    (roll_disturbance > -0.15 && roll_disturbance < 0.15) &&
		     rotating == 0) {
		double timeReal = time;
		errorCount = 0;
		cPoints = 0;
		rotating = 1;
		if (point < 50) {
		    point += 1;
		    while (wb_robot_step(timestep) != -1) {
			if (wb_robot_get_time() - timeReal > 2.0)
			break;
			}
		    }
		else {
		    while (wb_robot_step(timestep) != -1) {
			if (wb_robot_get_time() - timeReal > 5.0)
			break;
			}		
		    }

		}
	       }
	       // Compute the roll, pitch, yaw and vertical inputs.
	       const double roll_input = k_roll_p * CLAMP(roll, -1.0, 1.0) + roll_velocity + roll_disturbance;
	       const double pitch_input = k_pitch_p * CLAMP(pitch, -1.0, 1.0) + pitch_velocity + pitch_disturbance;
	       const double yaw_input = yaw_disturbance;
	       const double clamped_difference_altitude = CLAMP(target_altitude - altitude + k_vertical_offset, -1.0, 1.0);
	       const double vertical_input = k_vertical_p * pow(clamped_difference_altitude, 3.0);
                   // Actuate the motors taking into consideration all the computed inputs.
	       const double front_left_motor_input = k_vertical_thrust + vertical_input - roll_input + pitch_input - yaw_input;
	       const double front_right_motor_input = k_vertical_thrust + vertical_input + roll_input + pitch_input + yaw_input;
	       const double rear_left_motor_input = k_vertical_thrust + vertical_input - roll_input - pitch_input + yaw_input;
	       const double rear_right_motor_input = k_vertical_thrust + vertical_input + roll_input - pitch_input - yaw_input;
	       //Set velocities for motors
	       wb_motor_set_velocity(front_left_motor, front_left_motor_input);
	       printf("front_left_motor_input:%f ", front_left_motor_input);
	       wb_motor_set_velocity(front_right_motor, -front_right_motor_input);
	       printf("front_right_motor_input:%f ", -front_right_motor_input);
	       wb_motor_set_velocity(rear_left_motor, -rear_left_motor_input);
	       printf("rear_left_motor_input:%f ", -rear_left_motor_input);
                  wb_motor_set_velocity(rear_right_motor, rear_right_motor_input);
	       printf("rear_right_motor_input:%f ", rear_right_motor_input);
	       //Landing the drone.
	       if (point == 50) {
	       double target_altitude = 0.0;
	       const double roll_input = k_roll_p * CLAMP(roll, -1.0, 1.0) + roll_velocity + roll_disturbance;
	       const double pitch_input = k_pitch_p * CLAMP(pitch, -1.0, 1.0) + pitch_velocity + pitch_disturbance;
	       const double yaw_input = yaw_disturbance;
	       const double clamped_difference_altitude = CLAMP(target_altitude - altitude + k_vertical_offset, -1.0, 1.0);
	       const double vertical_input = k_vertical_p * pow(clamped_difference_altitude, 3.0);
	       const double front_left_motor_input = k_vertical_thrust + vertical_input - roll_input + pitch_input - yaw_input;
	       const double front_right_motor_input = k_vertical_thrust + vertical_input + roll_input + pitch_input + yaw_input;
	       const double rear_left_motor_input = k_vertical_thrust + vertical_input - roll_input - pitch_input + yaw_input;
	       const double rear_right_motor_input = k_vertical_thrust + vertical_input + roll_input - pitch_input - yaw_input;
	       wb_motor_set_velocity(front_left_motor, front_left_motor_input);
	       wb_motor_set_velocity(front_right_motor, -front_right_motor_input);
	       wb_motor_set_velocity(rear_left_motor, -rear_left_motor_input);
                  wb_motor_set_velocity(rear_right_motor, rear_right_motor_input);
            	if (altitude < 0.1){
	               wb_motor_set_velocity(front_left_motor, 0.0);
	               wb_motor_set_velocity(front_right_motor, 0.0);
                          wb_motor_set_velocity(rear_left_motor, 0.0);
	               wb_motor_set_velocity(rear_right_motor, 0.0);
              	    while (wb_robot_step(timestep) != -1) { // Wait one second.
		           if (wb_robot_get_time() > 1.0)
			   break;
                           }
            	    //point = 0;
            	}
	       }
	};
	wb_robot_cleanup();
	return EXIT_SUCCESS;
}
