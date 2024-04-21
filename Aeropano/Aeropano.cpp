#include <opencv2/opencv.hpp>
#include <iostream>


int main()
{
    cv::Mat imgs[] = { cv::imread("imgs/t5.jpeg"), cv::imread("imgs/t6.jpeg") };
    cv::Ptr<cv::ORB> orb = cv::ORB::create(); //Construtor do ORB retorna ptr da instancia (?)

    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;

    orb->detectAndCompute(imgs[0], cv::noArray(), kp1, des1); //Processamento da imagem para reconhecer feature points e retornar seus kps
    orb->detectAndCompute(imgs[1], cv::noArray(), kp2, des2); //-e descriptors

    cv::Ptr<cv::BFMatcher> bfmatcher = cv::BFMatcher::create(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches;

    bfmatcher->match(des1, des2, matches);

    //Executa algoritmo organizacional por distancia em "matches"
    std::sort(matches.begin(), matches.end(), [](const cv::DMatch& a, const cv::DMatch& b) {
        return a.distance < b.distance;
        });

    cv::Mat imgMatches;
    cv::drawMatches(imgs[0], kp1, imgs[1], kp2, matches, imgMatches);
    cv::imshow("Feature Matches:", imgMatches);
    cv::waitKey(0);

    return 0;
}