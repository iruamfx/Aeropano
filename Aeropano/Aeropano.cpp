#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    const std::string path1 = "C:\\Workspace\\CPP\\Aeropano\\Aeropano\\imgs\\t5.jpeg";
    const std::string path2 = "C:\\Workspace\\CPP\\Aeropano\\Aeropano\\imgs\\t6.jpeg";
    std::vector<cv::Mat> imgs = {cv::imread(path1), cv::imread(path2)};
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA; //TODO: add argument handling
    bool crop;

#pragma region Argument Handling



	for (int i = 0; i < argc; i++)
	{
        std::string arg = argv[i];
        size_t imPos = arg.find("-im"); // Verifica se a substring "-im" está presente
        size_t cropPos = arg.find("crop"); // Verifica se a substring "-im" está presente

        if (imPos != std::string::npos) // std::string::npos é um valor especial para representar um retorno de size_t nulo.
        {
            arg.erase(imPos, 3); // 3 é o tamanho da substring "-im"
            imgs.push_back(cv::imread(arg));
        }

        if (cropPos != std::string::npos) // std::string::npos é um valor especial para representar um retorno de size_t nulo.
        {
            crop = true;
        }
	}

#pragma endregion

    cv::Mat pano;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
    cv::Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != cv::Stitcher::OK)
    {
        std::cout << "Can't stitch images, error code = " << status << std::endl;
        return EXIT_FAILURE;
    }

    cv::imshow("Pano", pano);
    cv::waitKey(0);
    return EXIT_SUCCESS;
}