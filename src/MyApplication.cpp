#include "Utilities.h"

int main()
{
    MyApplication();
    return 0;
}

Point2f TOP_LEFT = Point2f(337, 35);
Point2f BOTTOM_LEFT = Point2f(38, 472);
Point2f TOP_RIGHT = Point2f(1570, 21);
Point2f BOTTOM_RIGHT = Point2f(1888, 451);
int TABLE_WIDTH = 1434; 
int TABLE_HEIGHT = 683;

void preProcess(Mat &src, Mat &dst)
/**
 * Preprocess the image before we perform analysis on it.
 * @param src The source image
 * @param dst The destination image after we perform preprocessing
 */
{
    // convert to grayscale
    // cvtColor(dst, dst, COLOR_BGR2GRAY);
    // perspective is skewed, but we have coordinates of corners
    // use this information and size of table to perform perspective transformation
    Mat dst_a;
    Point2f src_points[] = {TOP_LEFT, BOTTOM_LEFT, TOP_RIGHT, BOTTOM_RIGHT};
    Point2f dst_points[] = {Point2f(0, 0), Point2f(0, TABLE_HEIGHT), Point2f(TABLE_WIDTH, 0), Point2f(TABLE_WIDTH, TABLE_HEIGHT)};
    Mat perspective_matrix = getPerspectiveTransform(src_points, dst_points);
    warpPerspective(src, dst_a, perspective_matrix, Size(TABLE_WIDTH, TABLE_HEIGHT));
    /*
    int spatial = 20;
    int color = 20;
    pyrMeanShiftFiltering(dst_a, dst, spatial, color);
    */
    // canny edge detection
    Canny(dst_a, dst, 100, 200);
}

void MyApplication()
/**
 * My Application (the assignment)
 */
{
    // the coordinates of the corners
    // this information is in the assignment description

    std::cout << "Ritvik Kumar" << "\n";
    char *file_location = "pool-images/";
    char *pool_files[] = {
        "AllBalls.jpeg",
        "Table1.jpeg",
        "Table2.jpeg",
        "Table3.jpeg",
        "Table4.jpeg",
        "Table5.jpeg",
        "Table6.jpeg"};
    int number_of_images = sizeof(pool_files) / sizeof(pool_files[0]);

    // place to store our images
    Mat *pool_image = new Mat[number_of_images];
    Mat *processed_image = new Mat[number_of_images];

    // read images from pool-images folder, putting them in the Mat array
    for (int pool_file = 0; pool_file < number_of_images; pool_file++)
    {
        string filename(file_location);
        filename.append(pool_files[pool_file]);
        pool_image[pool_file] = imread(filename, -1);
        preProcess(pool_image[pool_file], processed_image[pool_file]);
    }

    // show images
    for (int proc_file = 0; proc_file < number_of_images; proc_file++)
    {
        string window_name(pool_files[proc_file]);
        imshow(window_name, processed_image[proc_file]);
        char pause = waitKey();
    }
}