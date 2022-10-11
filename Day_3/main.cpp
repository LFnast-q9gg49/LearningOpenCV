#include <cstdio>
#include <opencv2/opencv.hpp>

cv::Mat Read_Image(const char* src);
void Show_Image(const cv::Mat& img);
// void Split_Channels(const cv::Mat& img);
void In_range(const cv::Mat& img);
// pixel calculate
void Pixel_Statistic(const cv::Mat& img);
// draw
void Drawing(const cv::Mat& img);
// random number and color
void Random(const cv::Mat& img);

int main(__attribute__((unused)) int argv, char** argc){

    cv::Mat image = Read_Image(argc[1]);
    // Split_Channels(image);
    Show_Image(image);
    // In_range(image);
    // Drawing(image);
    Random(image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    exit(0);
}

cv::Mat Read_Image(const char* src){
    cv::Mat temp_image = cv::imread(src, cv::IMREAD_ANYCOLOR);
    if(temp_image.empty()){
        fprintf(stdout, "can't find the image :%s", src);
        exit(1);
    }
    return temp_image;
}

void Show_Image(const cv::Mat& img){
    cv::namedWindow("show_image", cv::WINDOW_AUTOSIZE);
    cv::imshow("show_image", img);
}

void In_range(const cv::Mat& img){
    cv::Mat temp_image = cv::Mat::zeros(img.size(), img.type());
    cv::cvtColor(img, temp_image,cv::COLOR_BGR2HSV);

    cv::Mat image_mask;
    cv::inRange(temp_image, cv::Scalar(35,43,46), cv::Scalar(77,255,255),image_mask);
    cv::namedWindow("range", cv::WINDOW_AUTOSIZE);
    cv::imshow("range", image_mask);

    cv::Mat red_back = cv::Mat::zeros(img.size(), img.type());
    red_back = cv::Scalar(30,30,200);
    image_mask = ~image_mask;
    img.copyTo(red_back, image_mask);
    cv::imshow("red_back", red_back);
}

void Pixel_Statistic(const cv::Mat& img){
    int min_value, max_value;
    cv::Point min_location, max_location;
    // only used for single channel
    // cv::minMaxLoc(img, &min_value, &max_value, &min_location, &max_location,cv::Mat());
    // cv::meanStdDev(image, stddev)
}

void Drawing(const cv::Mat& img){
    cv::Rect rect;
    rect.x = 100;
    rect.y = 50;
    rect.height = 600;
    rect.width = 200;
    cv::rectangle(img, rect, cv::Scalar(155, 0, 30), -1, cv::LINE_AA, 0);
    cv::circle(img, cv::Point(350, 400), 15, cv::Scalar(10, 25, 30), 5, cv::LINE_8, 0);
    cv::imshow("rect", img);
}

void Random(const cv::Mat& img){
    cv::Mat canvas = cv::Mat::zeros(cv::Size(512,512), CV_8UC3);
    cv::RNG rng(12345);
    while(true){
        int c = cv::waitKey(100);
        if (c == 27){
            break;
        }
        line(canvas,
             cv::Point(rng.uniform(0,canvas.cols),rng.uniform(0,canvas.rows)),
             cv::Point(rng.uniform(0,canvas.cols),rng.uniform(0,canvas.rows)),
             cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),1,cv::LINE_AA, 0);
        cv::imshow("line", canvas);
    }
}

// so we conclude that the channel split will make the 8U3C to three 8U1C
// That is why the three channel are all grey pictures.
/*

void Split_Channels(const cv::Mat& img){
    std::vector<cv::Mat> split_channels;

    cv::Mat Test_Image = cv::Mat::zeros(cv::Size(16,16), CV_8UC3);
    Test_Image = cv::Scalar(30, 0, 255);
    cv::imshow("test", Test_Image);
    // std::cout<<Test_Image<<std::endl;

    cv::split(Test_Image, split_channels);
    cv::imshow("test_1", split_channels[0]);
    std::cout<<split_channels[0]<<std::endl;
}

*/