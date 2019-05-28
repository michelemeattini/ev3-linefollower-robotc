#pragma config(Sensor, S2,     sensoreL,      sensorEV3_Color)
#pragma config(Sensor, S4,     sensoreR,      sensorEV3_Color)
#pragma config(Motor,  motorA,          motorL,       tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          motorR,       tmotorEV3_Large, PIDControl, driveRight, encoder)

int colorR, colorL; //variable to store the reflected light of the sensor
float error; 
float preverror;
float Proportional;
float Integral;
float Derivative;
float nVelocity = 20;
float kP = 1, kD = 1, kI = 1;

task main() {
	while(1){ 
		colorR = getColorReflected( sensoreR ); //get the reflected light from the right sensor
		colorL = getColorReflected( sensoreL ); //get the reflected light from the left sensor
		error = colorR - colorL; //calculate the error
		Proportional = error + kP; //calculate the proportional part
		Integral = Integral + ( kI * error ); //calculate the integral part
		Derivative = (error - preverror ) * kD; //calculate the derivative part
		setMotorSpeed( motorR, nVelocity + ( Proportional + Integral + Derivative ) ); //set the speed of the motor to the velocity base plus PID correction
		setMotorSpeed( motorL, nVelocity - ( Proportional + Integral + Derivative ) ); //set the speed of the motor to the velocity base minus PID correction
		preverror = error; 
	}
}
