#include <cstdlib>
#include <opencv2/opencv.hpp>

cv::Mat Read_file(const char* src);
void Show_image(const cv::Mat& img, const char* name);

// color style
// applyColorMap(src, dst, COLORMAP)
void Color_style(const cv::Mat& img);

// logic operation
void bit_wise(const cv::Mat& img);

// channel split and merge
// each RGB channel can turn to a grey image
void channel_operate(const cv::Mat& img);

int main(int argc, char **argv){
    cv::Mat image = Read_file(argv[1]);
    char name[] = "out";
    Show_image(image, name);
    // Color_style(image);
    // bit_wise(image);
    channel_operate(image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    exit(0);
}


cv::Mat Read_file(const char* src){
    cv::Mat temp_image = cv::imread(src);
    if (temp_image.empty()){
        fprintf(stdout, "can't find the image %s\n", src);
        exit(1);
    }
    return temp_image;
}

void Show_image(const cv::Mat&img, const char* name){
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, img);
}

void Color_style(const cv::Mat& img){
    int i = 0;
    while (true){
        cv::Mat temp;
        int c = cv::waitKey(2000);
        if (i == 22){
            break;
        }
        cv::applyColorMap(img, temp,i);
        i++;
        cv::imshow("color_style", temp);
    }
}

void bit_wise(const cv::Mat& img){
    cv::Mat temp_img = cv::Mat::zeros(img.size(), img.type());
    cv::Mat temp_img_2 = cv::Mat::zeros(cv::Size(256,256), CV_8UC3);
    cv::Mat temp_img_3 = temp_img_2.clone();
    cv::rectangle(temp_img_2, cv::Rect(100,100,80,80), cv::Scalar(255,255,0), -1, cv::LINE_8, 0);
    cv::rectangle(temp_img_3, cv::Rect(140,140,90,90), cv::Scalar(0,255,255), -1, cv::LINE_8, 0);
    // thickness >0 is a frame  <0 is filled
    cv::Mat dst;
    cv::bitwise_and(temp_img_2, temp_img_3,dst);
    cv::imshow("bit_wise_temp2", dst);
    // the area intersection, and color is (0, 255, 0)

    dst = ~(~temp_img_2|temp_img_3);
    cv::imshow("bit_wise_test", dst);
    // bitwise_not == ~

}

void channel_operate(const cv::Mat& image){
    std::vector<cv::Mat> channel;
    cv::split(image, channel);
    cv::Mat dst;

    channel[0] = 0;
    channel[2] = 0;
    cv::merge(channel, dst);
    cv::imshow("green", dst);

    // error
    /*
    cv::Mat dst2;
    int form[] = {0,2,1,1,2,0};
    cv::mixChannels(&image,1, &dst2,1, form, 3);
    cv::imshow("mix", dst2);
     */
}

// brush up
/*
cv::Mat img_convert(const cv::Mat& img);

int main() {
    cv::Mat image = cv::imread("D:\\Opencv_Examples\\sample_1.jpg");
    if (image.empty()){
        fprintf(stdout, "can't find the file");
        exit(1);
    }
    cv::namedWindow("output", cv::WINDOW_FREERATIO);
    cv::imshow("output", image);

    cv::imshow("anothor_show", img_convert(image));
    cv::waitKey(0);
    exit(0);
}

cv::Mat img_convert(const cv::Mat& img){
    cv::Mat temp_img = cv::Mat::zeros(img.size(), img.type());
    cv::cvtColor(img, temp_img, cv::COLOR_BGR2GRAY);
    return temp_img;
}
*/