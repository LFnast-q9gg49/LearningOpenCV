#include <cstdlib>
#include <opencv2/opencv.hpp>

cv::Mat Read_Image(const char* src);
void Show_Image(const char* wnd_name, const cv::Mat& img);

// resize
void Resize_Image(const cv::Mat& img);
// mirror
void Mirror_Image(const cv::Mat& img);
// warp affine
// src,dst,dsize, M(2*3), flag(INTER_?), borderMode
void Rotate_Image(const cv::Mat& img);
// video
void Video_Operate();

// brush up
/*
void Normalization(const cv::Mat& img);
void Draw_Rect(const cv::Mat& img);
static void on_mouse(int event, int x, int y, int flags, void* userdata);

struct user_data_paradigm{
    cv::Point  ini_cursor;
    cv::Point  end_cursor;
    cv::Mat    usr_image;
    cv::Mat    temp_image;
};
*/
int main(int argc, char** argv) {
    // only for a single image
    if (argc < 2){
        fprintf(stdout, "Usage: ./xxx.exe <Image_Source>\n");
        exit(1);
    }
    cv::Mat image = Read_Image(argv[1]);
    Show_Image("raw image", image);
    // Normalization(image);
    // Draw_Rect(image);
    // Mirror_Image(image);
    // Rotate_Image(image);
    Video_Operate();

    cv::waitKey(0);
    cv::destroyAllWindows();
    exit(0);
}

cv::Mat Read_Image(const char* src){
    cv::Mat temp_image = cv::imread(src, cv::IMREAD_ANYCOLOR);
    if (temp_image.empty()){
        fprintf(stdout, "can't find the image from : %s", src);
        exit(1);
    }
    return temp_image;
}

void Show_Image(const char* wnd_name, const cv::Mat& img){
    cv::namedWindow(wnd_name, cv::WINDOW_FREERATIO);
    cv::imshow(wnd_name, img);
}

void Resize_Image(const cv::Mat& img){
    // zoomin, zoomout
    cv::Mat zoom_in, zoom_out;
    cv::resize(img, zoom_in, cv::Size(img.cols/2, img.rows/2), 0, 0, cv::INTER_LINEAR);
    Show_Image("zoomin", zoom_in);
}

void Mirror_Image(const cv::Mat& img){
    cv::Mat dst;

    // up and down
    cv::flip(img, dst, 0);
    Show_Image("0", dst);

    // right and left
    cv::flip(img, dst, 1);
    Show_Image("1", dst);

    // both, same as rotate 180 degree
    cv::flip(img, dst, -1);
    Show_Image("-1", dst);
}

void Rotate_Image(const cv::Mat& img){
    cv::Mat dst, M;
    M = cv::getRotationMatrix2D(cv::Point( img.cols/2, img.rows/2), 45, 1);
    double cos = abs(M.at<double>(0, 0));
    double sin = abs(M.at<double>(0, 1));

    M.at<double>(0, 2) = M.at<double>(0, 2) + (cos*img.cols + sin*img.rows - img.cols)/2;
    M.at<double>(1, 2) = M.at<double>(1, 2) + (sin*img.cols + cos*img.rows - img.rows)/2;

    cv::warpAffine(img, dst, M,cv::Size(cos*img.cols+sin*img.rows, cos*img.rows+sin*img.cols), cv::INTER_LANCZOS4, 0, cv::Scalar(255, 0, 0));
    Show_Image("rotate", dst);
}

void Video_Operate(){
    cv::VideoCapture capture(0);
    cv::Mat frame;
    while(true){
        capture.read(frame);
        if (frame.empty()){
            break;
        }
        cv::flip(frame,frame,1);
        cv::imshow("frame", frame);
        int c = cv::waitKey(10);
        if (c==27){
            break;
        }
    }
    capture.release();
}

/*
// brush up

void Normalization(const cv::Mat& img){
    cv::Mat img_clone = img.clone();
    cv::Mat dst = cv::Mat::zeros(img.size(), img.type());
    cv::Mat normed_dst = cv::Mat::zeros(img.size(), img.type());
    img_clone.convertTo(dst, CV_32F);
    cv::normalize(dst, normed_dst, 1, 0, cv::NORM_MINMAX);
    Show_Image("normed_img", normed_dst);
}

static void on_mouse(int event, int x, int y, int flags, void* userdata){
    auto user_data = &(*(user_data_paradigm*)userdata);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN: {
            user_data->ini_cursor = cv::Point (x, y);
            break;
        }
        case cv::EVENT_MOUSEMOVE:{
            if (user_data->ini_cursor.x > 0 && user_data->ini_cursor.y > 0){
                user_data->end_cursor = cv::Point (x, y);
                cv::Rect box(user_data->ini_cursor.x,
                             user_data->ini_cursor.y,
                             user_data->end_cursor.x - user_data->ini_cursor.x,
                             user_data->end_cursor.y - user_data->ini_cursor.y);
                user_data->temp_image.copyTo(user_data->usr_image);
                cv::rectangle(user_data->usr_image, box, cv::Scalar(0, 0, 255), 4);
                Show_Image("mouse", user_data->usr_image);
            }
            break;
        }
        case cv::EVENT_LBUTTONUP:{
            user_data->end_cursor = cv::Point (x,y);
            cv::Rect box(user_data->ini_cursor.x,
                         user_data->ini_cursor.y,
                         user_data->end_cursor.x - user_data->ini_cursor.x,
                         user_data->end_cursor.y - user_data->ini_cursor.y);
            cv::rectangle(user_data->usr_image, box, cv::Scalar(0, 0, 255), 4);
            Show_Image("mouse", user_data->usr_image);
            user_data->ini_cursor = cv::Point (-1, -1);
            break;
        }
        default:{
            break;
        }
    }
}

void Draw_Rect(const cv::Mat& img){
    cv::namedWindow("mouse", cv::WINDOW_FREERATIO);
    auto* user_data = new user_data_paradigm;
    user_data->usr_image = img.clone();
    user_data->temp_image = img.clone();
    user_data->ini_cursor = cv::Point (-1, -1);
    user_data->end_cursor = cv::Point (-1, -1);

    cv::setMouseCallback("mouse", on_mouse, (void*)user_data);
    Show_Image("mouse", user_data->usr_image);
}

 */