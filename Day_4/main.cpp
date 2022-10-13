#include <cstdlib>
#include <opencv2/opencv.hpp>

cv::Mat Read_Image(const char* src);
void Show_Image(const cv::Mat& img, const char* name);

void Polygon(const char* name);

void Mouse_Operate(const cv::Mat& img);
static void on_draw(int event, int x, int y, int flags, void* userdata);

// normalize
// NORM_MINMAX  NORM_INF   NORM_L1  NORM_2
// INF:
//  2  8  10   ------   0.2  0.8  1.0
// MINMAX:
//  2  8  10   ------   delta = 10-2 =8   2-2/10-2  8-2/10-2  10-2/10-2
// L1:
//  2  8  10   ------  2+8+10 = 20  0.1  0.4  0.5
// L2:
//  2  8  10   ------  (4+64+100)^0.5 = 13  0.15  0.42  0.77
void Normalize(const cv::Mat& img);

// brush up
/*
void Change_Background(const cv::Mat&img, const char* name);
void Random_Drawing(const char* name);
*/

int main(__attribute__((unused)) int argv, char** argc){
    cv::Mat image = Read_Image(argc[1]);
    char window_name[] = {'s','a','m','p','l','e','_','1','\0'};
    Show_Image(image, window_name);
    // Polygon("polygon");
    // Mouse_Operate(image);
    Normalize(image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    exit(0);
}

cv::Mat Read_Image(const char* src){
    cv::Mat temp_image = cv::imread(src, cv::IMREAD_ANYCOLOR);
    if (temp_image.empty()){
        fprintf(stdout, "can't find the image : %s", src);
        exit(1);
    }
    return temp_image;
}

void Show_Image(const cv::Mat& img, const char* name){
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, img);
}

void Normalize(const cv::Mat& img){
    cv::Mat dst_1, dst_2;
    img.convertTo(dst_1, CV_32F);
    cv::normalize(dst_1, dst_2, 1.0, 0, cv::NORM_MINMAX);
    Show_Image(dst_1, "float"); // error, float must between 0 to 1
    Show_Image(dst_2, "norm");
}

void Polygon(const char* name){
    cv::Mat canvas = cv::Mat::zeros(cv::Size(512,512), CV_8UC3);
    cv::Point point_1(100,100);
    cv::Point point_2(350,100);
    cv::Point point_3(450,280);
    cv::Point point_4(320,450);
    cv::Point point_5(80 ,400);
    std::vector<cv::Point> points;
    points.push_back(point_1);
    points.push_back(point_2);
    points.push_back(point_3);
    points.push_back(point_4);
    points.push_back(point_5); // azhe

    // this function only can draw lines;
    cv::polylines(canvas, points, true, cv::Scalar(0, 0, 255), 1, cv::LINE_AA, 0);

    // paint
    cv::fillPoly(canvas, points, cv::Scalar(255, 255, 0), cv::LINE_AA, 0);

    // draw contours

    Show_Image(canvas, name);
}

cv::Point sp(-1,-1);
cv::Point ep(-1,-1);
cv::Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata){

    cv::Mat image = *(cv::Mat*)userdata;
    switch (event) {
        case cv::EVENT_LBUTTONDOWN: {
            sp.x = x;
            sp.y = y;
            break;
        }
        case cv::EVENT_MOUSEMOVE:{
            if (sp.x > 0 && sp.y > 0){
                ep.x = x;
                ep.y = y;
                cv::Rect box(sp.x, sp.y, ep.x-sp.x, ep.y-sp.y);
                temp.copyTo(image);
                cv::rectangle(image, box, cv::Scalar(0,0,255), 1, cv::LINE_AA, 0);
                Show_Image(image, "mouse");

            }
            break;
        }
        case cv::EVENT_LBUTTONUP: {
            ep.x = x;
            ep.y = y;
            cv::Rect box(sp.x, sp.y, ep.x - sp.x, ep.y - sp.y);
            cv::rectangle(image, box, cv::Scalar(0, 0, 255), 1, cv::LINE_AA, 0);
            Show_Image(image, "mouse");
            Show_Image(image(box), "roi");
            sp.x = -1;
            sp.y = -1;
            break;
        }
        default: {
            break;
        }
    }
}

void Mouse_Operate(const cv::Mat& img){
    cv::namedWindow("mouse", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("mouse", on_draw, (void*)&img);
    Show_Image(img, "mouse");
    temp = img.clone();
}

// brush up
/*
void Change_Background(const cv::Mat& img, const char* name){
    cv::Mat hsv_img = cv::Mat::zeros(img.size(), img.type());
    cv::Mat background = hsv_img.clone();
    cv::Mat img_mask = hsv_img.clone();

    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV, img.channels());
    cv::inRange(hsv_img, cv::Scalar(35,43,46), cv::Scalar(77,255,255), img_mask);
    img_mask = ~img_mask;
    background = cv::Scalar(30, 30, 200);
    img.copyTo(background, img_mask);
    Show_Image(background, name);
}

void Random_Drawing(const char* name){
    cv::Mat canvas = cv::Mat::zeros(cv::Size(512,512), CV_8UC3);
    cv::RNG rng(123);
    while(true){
        int c = cv::waitKey(10);
        if (c == 27){
            break;
        }
        cv::line(canvas,
                 cv::Point(rng.uniform(0, canvas.cols), rng.uniform(0, canvas.rows)),
                 cv::Point(rng.uniform(0, canvas.cols), rng.uniform(0, canvas.rows)),
                 cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, cv::LINE_AA, 0);
        Show_Image(canvas, name);
    }
}

 */