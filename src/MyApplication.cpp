#include "Utilities.h"

int main()
{
    MyApplication();
    return 0;
}

void MyApplication()
{
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
    Mat *pool_image = new Mat[number_of_images];

    // read images from pool-images folder, putting them in the Mat array
    for (int pool_file = 0; pool_file < number_of_images; pool_file++)
    {
        string filename(file_location);
        filename.append(pool_files[pool_file]);
        pool_image[pool_file] = imread(filename, -1);
    }

    // show images
    for (int pool_file = 0; pool_file < number_of_images; pool_file++)
    {
        string window_name(pool_files[pool_file]);
        // namedWindow(window_name, WINDOW_NORMAL);
        imshow(window_name, pool_image[pool_file]);
        char pause = waitKey();
    }
}