#include <stdio.h>
#include <locale.h>

#define PRECISION 0.001
#define PI 3.1415926

float pow(float x, int n) { 
	float res = 1;

	for (int i = 0; i < n; i++) {
		res *= x;
	}

	return res;
}
int fact(int x) { 
	int res = 1;

	for (int i = 1; i < (x + 1); i++) {
		res *= i;
	}

	return res;
}
float my_binom(int n, int k) {
	return 1.0 * fact(n) / fact(k) / fact(n - k);
}
float my_bernulli(int n) {

	float s = 0; 

	if (n <= 0) { return 1; } 
	if (n == 1) { return -0.5; } 
	if (n % 2 == 1) { return 0; } 

	for (int i = 1; i < n + 1; i++) {

		s += my_binom(n + 1, i + 1) * my_bernulli(n - i);

	}
	return -1.0 / (n + 1) * s;
}
float my_abs(float x) { 
	if (x >= 0) {
		return x;
	}
	return -x;
}


float tan(float x, float precision)
{
	int n = 1; 

	float res = x; 
	float prev = 0; 

	float delta = my_abs(res - prev); 

	
	float a = x;
	float b = -1; 
	float c = 4; 
	float d = 2; 

	while (delta > precision) {

		n += 1; 
		a *= pow(x, 2); 

		
		float n2 = 2 * n; 

		d *= n2 * (n2 - 1);
		c *= 4;
		b *= -1;

		float B = my_bernulli(n2); 

		prev = res; 

		
		res += a * B * b * c * (1 - c) / d;

		delta = my_abs(res - prev); 
	}

	return res;
}

int main() {

	setlocale(LC_ALL, "rus");

	
	float tests_array_argx[6];
	tests_array_argx[0] = PI / 3;
	tests_array_argx[1] = PI / 4;
	tests_array_argx[2] = PI / 6;
	tests_array_argx[3] = -PI / 3;
	tests_array_argx[4] = -PI / 4;
	tests_array_argx[5] = -PI / 6;
	
	float tests_array_calc_res[6];
	tests_array_calc_res[0] = (float)1.71308410;
	tests_array_calc_res[1] = (float)0.999494731;
	tests_array_calc_res[2] = (float)0.577277601;
	tests_array_calc_res[3] = (float)-1.71308410;
	tests_array_calc_res[4] = (float)-0.999494731;
	tests_array_calc_res[5] = (float)-0.577277601;

	for (int i = 0; i < 6; i++)

		if (tan(tests_array_argx[i], PRECISION) == tests_array_calc_res[i]) {
			printf("Тест №%i\t - \tуспех\n", (i + 1)); 
		}
		else {
			printf("%f - %f\n", tan(tests_array_argx[i], PRECISION), tests_array_calc_res[i]);
			printf("Тест №%i\t - \tпровал\n", (i + 1));
		}
	return 0;

}
