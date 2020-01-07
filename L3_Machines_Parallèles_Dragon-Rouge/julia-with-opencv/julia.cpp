// julia_v1.cpp
//g++ -W -Wall -std=c++17 -O3 julia.cpp `pkg-config --cflags --libs opencv` -pthread

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

#include <complex>
#include <thread>

using namespace std;
using namespace cv;

#define H 700 
#define W 700

float N_ITER = 70.0;
constexpr float THRESHOLD = 1000.f;
constexpr std::complex<float> C(-0.8f, 0.156f);

Vec3b julia_pix(float x, float y) {
	int i;
	std::complex<float> z(x, y);
  for(i = 0; i < N_ITER; ++i) {
  	if(norm(z) > THRESHOLD) {
  	  break;
    } 
    z = z * z + C;
  }
	Vec3b color(5, 255* i / N_ITER, 45 * (i < N_ITER));
  return color;
}

void julia(Mat out, float zoom, int begin, int end) {
	for(int r = begin; r < end; ++r) {
	  float y = -(float(r) - out.rows / 2) * zoom / out.rows;
		//N_ITER+=0.001;
    for(int c = 0; c < W; ++c) {
	    float x = (float(c) - out.cols / 2) * zoom / out.cols;
      out.at<Vec3b>(r, c) = julia_pix(x, y);
    }
  }
	//N_ITER-=0.001;
}

int main() {
	Mat image(H, W, CV_8UC3);
	namedWindow("Dragon Rouge", WINDOW_AUTOSIZE);
	float zoom = 4.00;
 	int key;

	VideoWriter video("DragonRouge.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(W,H));

	while(1){
		if(zoom < 0)
			break;
  		
		imshow("Dragon Rouge", image);

		thread first(julia, image, zoom -=0.01, 0, 88);
		thread second(julia, image, zoom-=0.01, 88, 175);
		thread third(julia, image, zoom-=0.01, 175, 263);
		thread four(julia, image, zoom-=0.01, 263, 351);
		thread five(julia, image, zoom -=0.01, 351, 438);
		thread six(julia, image, zoom-=0.01, 438, 526);
		thread seven(julia, image, zoom-=0.01, 526, 613);
		thread eight(julia, image, zoom-=0.01, 613, H);
		
		first.join();
		second.join();
		third.join();
		four.join();
		five.join();
		six.join();
		seven.join();
		eight.join();
			
		key = waitKey(1);
		if(key == 27 || key == 113)
			break;
		video.write(image);
	}

	destroyAllWindows();
  return 0;
}
