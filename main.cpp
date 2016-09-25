#include "StringArtAnnealer.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int, char*[])
{
    cv::Mat img = cv::imread(
        "C:/Users/1/PycharmProjects/playing_with_opencv/yoda_monochrome_by_timdallinger-d4yya3v.png",
        CV_LOAD_IMAGE_GRAYSCALE);

    assert(img.type() == CV_8U);
    field_t targetImage(img.rows, field_t::value_type(img.cols));
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            targetImage[i][j] = img.at<unsigned char>(i, j);
        }
    }

    StringArtAnnealer annealer(targetImage, 100, 20000);

    auto const schedule = annealer.computeRunSchedule(10, 100, true);

    while (true) {
        annealer.runAnnealing(schedule, 10);

        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                img.at<unsigned char>(i, j) = static_cast<unsigned char>(
                    annealer.bestState().field[i][j]);
            }
        }
        cv::imwrite(
            "C:/Users/1/PycharmProjects/playing_with_opencv/yoda_monochrome_by_timdallinger-d4yya3v_out.png",
            img);
    }

    return 0;
}