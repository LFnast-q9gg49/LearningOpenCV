#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("D:\\infinity.jpg");
    if (img.empty()) {
        cout << "Error" << endl;
        return -1;
    }
    imshow("Lena", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}