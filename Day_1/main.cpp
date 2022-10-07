#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

cv::Mat Read_Image(const std::string& src);
cv::Mat Color_To_Grey(const cv::Mat& img);
void What_Is_Mat(const cv::Mat& img);
void Pixel_operation(const cv::Mat& img);

int main(int argc, char** argv){
    // the second param is the mode
    std::string src = "D:\\Opencv_Examples\\sample_2.png";

    // imshow 8 bit  Blue Green Red (RGB little endian)    256*256*256*256(transparent)
    // HSV : H(0-180) S,V(0-255)
    cv::Mat image = Read_Image(src);

    What_Is_Mat(image);
    Pixel_operation(image);
    cv::namedWindow("wnd_1", cv::WINDOW_AUTOSIZE);
    cv::imshow("wnd_1", image);

    cv::Mat image_grey = Color_To_Grey(image);
    cv::imwrite("D:\\Opencv_Examples\\sample_2_grey.png", image_grey);
    cv::namedWindow("wnd_2", cv::WINDOW_AUTOSIZE);
    cv::imshow("wnd_2", image_grey);

    cv::waitKey(0);
    cv::destroyAllWindows();
    exit(0);
}

cv::Mat Read_Image(const std::string& src){
    cv::Mat img = cv::imread(src, cv::IMREAD_ANYCOLOR);
    if (img.empty()){
        fprintf(stdout, "can't find the image");
        exit(-1);
    }
    return img;
}

cv::Mat Color_To_Grey(const cv::Mat& img){
    cv::Mat img_grey;
    cv::cvtColor(img, img_grey, cv::COLOR_BGR2GRAY);
    if (img_grey.empty()){
        fprintf(stdout, "can't convert the image");
        exit(-1);
    }
    return img_grey;
}

void What_Is_Mat(const cv::Mat& img){
    // Matrix
    // head + Data Block
    // 1. clone  2. copyTo  3. =
    /*
    cv::Mat m1, m2;
    m1 = img.clone();
    img.copyTo(m2);
    */
    // create a blank image
    // Mat::zeros(src.size(), src.type());
    cv::Mat m3, m4;
    m3 = cv::Mat::zeros(img.size(), img.type());
    m4 = cv::Mat::zeros(cv::Size(8,8), CV_8UC1);// unsigned single channel
    std::cout << m4 << std::endl;
    fprintf(stdout, "width:%d height:%d channel:%d\n", m4.cols, m4.rows, m4.channels());

    cv::Mat m5 = cv::Mat::ones(cv::Size(512,512), CV_8UC3);
    m5 = cv::Scalar(0,0,0);
    cv::namedWindow("Mat_test", cv::WINDOW_FULLSCREEN);
    cv::imshow("Mat_test", m5);

}

void Pixel_operation(const cv::Mat& img){
    cv::Mat temp_image = img.clone();
    fprintf(stdout, "width:%d height:%d channel:%d\n", temp_image.cols, temp_image.rows, temp_image.channels());
    for (auto row = 0; row < temp_image.rows; ++row){
        for (auto col = 0; col < temp_image.cols; ++col){
            if (temp_image.channels() == 1){
                temp_image.at<uchar>(row, col) = 255 - temp_image.at<uchar>(row, col);
            } else if (temp_image.channels() == 3){
                cv::Vec3b bgr = temp_image.at<cv::Vec3b>(row, col);
                temp_image.at<cv::Vec3b>(row, col)[0] = 255-bgr[0];
                temp_image.at<cv::Vec3b>(row, col)[1] = 255-bgr[1];
                temp_image.at<cv::Vec3b>(row, col)[2] = 255-bgr[2];
            }
        }
    }
    cv::namedWindow("verseImage", cv::WINDOW_AUTOSIZE);
    cv::imshow("verseImage", temp_image);


    // + - * /
    cv::Mat ret = temp_image + cv::Scalar(50,50,50);
    cv::imshow("what_do_i_get", ret);
    // value changed

    // multiply
    cv::multiply(temp_image, cv::Scalar(2,2,2), ret);
    cv::imshow("multiply", ret);

    // below one is used to add to avoid over 255
    // cv::saturate_cast<uchar>();

    /*
    cv::add()
    cv::subtract()
    cv::divide()
    cv::multiply()
     */
}