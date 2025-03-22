#include <iostream>
#include <iomanip>

struct Capacitor {
	double *time;
	double *voltage;
	double *current;
	double C;
};

void simulateConstCurrent(Capacitor &cap,int Timesteps, double dt, double I0){
int i;
for(i = 1; i < Timesteps; ++i){
		cap.time[i] = cap.time[i - 1] + dt;
		cap.voltage[i] = cap.voltage[i-1] + (cap.current[i-1] * dt)/ cap.C;
		cap.current[i] = I0;

		if(i % 200 == 0){
				std::cout<< "time: " << cap.time[i] << "s, Voltage: "
				<< cap.voltage[i] << "V, Current: " 
				<< cap.current[i] << "A\n";
			}
	}
}




void simulateConstVoltage(Capacitor &cap,int Timesteps, double dt, double V0, double R){
cap.current [0] = V0/R;
int i;
for(i = 1; i < Timesteps; ++i){
	cap.time[i] = cap.time[i-1] + dt;
	cap.current[i] = cap.current[i-1] -(cap.current[i-1] * dt)/(cap.C * R);
	cap.voltage[i] = V0 - (cap.current[i] * R);

	if(i % 200 == 0){
		std::cout<<"time: " << cap.time[i] << "s, Voltage: "
		<< cap.voltage[i] << "V, Current: " 
		<< cap.current[i] << "A\n";
		}
	}
}
int main()
{
const double dt = 1e-10;
const double timeFinal = 5e-6;
const int Timesteps = 50000;
const double R = 1000;
const double C = 100e-12;
const double I0 = 1e-2;
const double V0 = 10;


Capacitor cap;
cap.C = C;
cap.time = new double[Timesteps];
cap.voltage = new double[Timesteps];
cap.current = new double[Timesteps]; 

cap.time[0] = 0;
cap.voltage[0] = 0;


std::cout << "Simulating Constant Current...\n";
simulateConstCurrent(cap,Timesteps,dt,I0);

std::cout << "Simulating Constant Voltage...\n";
simulateConstVoltage(cap,Timesteps,dt,V0,R);

delete[] cap.time;
delete[] cap.voltage;
delete[] cap.current;

return 0;
}
