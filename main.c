#include <stdio.h>
#include <stdlib.h>

#define EP 0.00001
#define NUM 2

struct Neuron {
	double value;
	struct Neuron* prev;
};

double Lerr(double target, double value) {
	return (target - value) * (target - value);
}

int main() {
	time_t ti;
	srand((unsigned) time(&ti));
	double I[NUM] = {5.0, 7.0};
	double WL[NUM][NUM] = {{3.0, 2.0},{2.0, 3.0}};
	double L[NUM] = {I[0]*WL[0][0] + I[1]*WL[0][1], I[0]*WL[1][0]+I[1]*WL[1][1]};
	double WO[NUM] = {3.0, 2.0};
	double o = L[0]*WO[0] + L[1]*WO[1];
	double t = 5;
	double e = Lerr(t, o);
	double dEdo[1] = {-2*(t-o)};
	double dodwo[NUM] = {L[0], L[1]};
	double dodl[NUM] = {WO[0], WO[1]};
	double dldwl[NUM][NUM] = {{I[0], I[1]},{I[0], I[1]}};
	double dEdwo[NUM] = {-dEdo[0]*dodwo[0], -dEdo[0]*dodwo[1]};
	double dEdwl[NUM][NUM] = {{-dEdo[0]*dodl[0]*dldwl[0][0], -dEdo[0]*dodl[0]*dldwl[0][1]},{-dEdo[0]*dodl[1]*dldwl[0][1], -dEdo[0]*dodl[1]*dldwl[1][1]}};
	printf("%f %f\n", o, e);
	for(int i = 0; i < 3000000; i++) {
		I[0] = rand()%21;
		I[1] = rand()%19;
		// Layer 1
		for(int j = 0; j < NUM; j++) {
			L[j] = 0;
			for(int k = 0; k < NUM; k++) {
				L[j] += I[k] * WL[j][k];
			}
		}
		// Output Layer
		o = 0;
		for(int j = 0; j < NUM; j++) {
			o += L[j]*WO[j];
		}
		// Error Calculation
		t = I[0]-I[1];
		e = Lerr(t, o);
		// Back Propogation
		dEdo[0] = -2*(t-o);
		for(int j = 0; j < NUM; j++) {
			dodwo[j] = L[j];
			dodl[j] = WO[j];
			dEdwo[j] = -dEdo[0]*dodwo[j];
			WO[j] += EP*dEdwo[j];
			for(int k = 0; k < NUM; k++) {
				dldwl[j][k] = I[j];
				dEdwl[j][k] = -dEdo[j]*dodl[j]*dldwl[j][k];
				WL[j][k] += EP*dEdwl[j][k];
			}
		}
	}
	printf("%f %f\n", o, e);
	printf("Inputs\n");
	printf("%0.3f\n", I[0]);
	printf("%0.3f\n", I[1]);
	I[0] = 1.325;
	I[1] = 100;
	// Layer 1
	for(int j = 0; j < NUM; j++) {
		L[j] = 0;
		for(int k = 0; k < NUM; k++) {
			L[j] += I[k] * WL[j][k];
		}
	}
	// Output Layer
	o = 0;
	for(int j = 0; j < NUM; j++) {
		o += L[j]*WO[j];
	}
	// Error Calculation
	t = I[0]-I[1];
	e = Lerr(t, o);
	printf("%f %f\n", o, e);
	printf("Inputs\n");
	printf("%0.3f\n", I[0]);
	printf("%0.3f\n", I[1]);
	printf("Weights\n");
	printf("%0.3f %0.3f  %0.3f\n", WL[0][0], WL[0][1], WO[0]);
	printf("%0.3f %0.3f  %0.3f\n", WL[1][0], WL[1][1], WO[1]);
	return 0;
}

