
#include <iostream>
//#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace std;
//using namespace cv;

#define G 9.81

int main(void) {

	vector<string> type_vec = { "KVH1750", "IMU910" };
	vector<double> acc_vec = { 0.05, 0.5};
	vector<double> gyro_vec = { 0.01 * G * 0.001, 0.05 * G * 0.001 };


	for (int i = 0; i < type_vec.size(); ++i) {

		double time = 200;
		double acc_drift = acc_vec[i];
		double gyro_drift = gyro_vec[i];

		double acc = acc_drift * time / 3600;
		double gyro = gyro_drift * time / 3600;
		double g_err = 0.5f * gyro * time * time;
		//double g_vec[3] = { g_err, g_err, g_err };
		double ang = acc * 3.1415926 / 180;

		double cos_ = cos(ang), sin_ = sin(ang);
		double mat[9] = { cos_ * cos_ + sin_ * sin_ * sin_, -cos_ * sin_ + sin_ * cos_ * sin_, -sin_ * cos_,
						sin_ * cos_, cos_ * cos_, sin_,
						sin_ * cos_ - cos_ * sin_ * sin_, -sin_ * sin_ - cos_ * cos_ * sin_, cos_ * cos_ };

		double err[3];
		err[0] = (mat[0] + mat[1] + mat[2]) * g_err;
		err[1] = (mat[3] + mat[4] + mat[5]) * g_err;
		err[2] = (mat[6] + mat[7] + mat[8]) * g_err;

		double error = sqrt(err[0] * err[0] + err[1] * err[1] + err[2] * err[2]);
		cout << "Type: " << type_vec[i] << " Error: " << error << "m." << endl;
		//Time: " << (to_string((int)time)) << "s, Error: " << error << "m." << endl;
	}

	system("pause");
	return 0;
}

