#include "StringArtAnnealer.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int, char*[])
{
    cv::Mat img = cv::imread(
        "img.png",
        CV_LOAD_IMAGE_GRAYSCALE);

    assert(img.type() == CV_8U);
    field_t targetImage(img.rows, field_t::value_type(img.cols));
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            targetImage[i][j] = img.at<unsigned char>(i, j);
        }
    }

    StringArtAnnealer annealer(targetImage, 300, 20000);

    while (true) {
        auto const schedule = annealer.computeRunSchedule(10, 50, true);
        annealer.runAnnealing(schedule, 100);

        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                img.at<unsigned char>(i, j) = static_cast<unsigned char>(
                    annealer.bestState().field[i][j]);
            }
        }
        cv::imwrite(
            "img_out.png",
            img);
    }

    return 0;
}