/*The program is designed to extract the red stamp part of the seal. which is constructed by opencv3.*/

/*build by opencv3.4-------------------with console*/
/*The same method can be used to extract the red part of the seal.*/
/*If there is a better effect, please inform the author of the method. Thank you.*/
#include<iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<vector>
using namespace std;
using namespace cv;
void filteredRed(const Mat &inputImage, Mat &resultGray, Mat &resultColor) {
	Mat hsvImage;
	cvtColor(inputImage, hsvImage, CV_BGR2HSV);
	
	resultGray = Mat(hsvImage.rows, hsvImage.cols, CV_8U, cv::Scalar(255));
	resultColor = Mat(hsvImage.rows, hsvImage.cols, CV_8UC3, cv::Scalar(255, 255, 255));
	double H = 0.0, S = 0.0, V = 0.0;
	//Filter out black
	for (int i = 0; i<hsvImage.rows; i++)
	{
		for (int j = 0; j<hsvImage.cols; j++)
		{
			H = hsvImage.at<Vec3b>(i, j)[0];
			S = hsvImage.at<Vec3b>(i, j)[1];
			V = hsvImage.at<Vec3b>(i, j)[2];

		
				if ((H >=156&&H<=180) && (V > 46)&&(S>=43))
				{
					resultGray.at<uchar>(i, j) = 0;
					resultColor.at<Vec3b>(i, j)[0] = inputImage.at<Vec3b>(i, j)[0];
					resultColor.at<Vec3b>(i, j)[1] = inputImage.at<Vec3b>(i, j)[1];
					resultColor.at<Vec3b>(i, j)[2] = inputImage.at<Vec3b>(i, j)[2];
				}

			
		}
	}
	//Extract red
	for (int i = 0; i<resultColor.rows; i++)
	{
		for (int j = 0; j<resultColor.cols; j++)
		{
			H = resultColor.at<Vec3b>(i, j)[0];
			S = resultColor.at<Vec3b>(i, j)[1];
			V = resultColor.at<Vec3b>(i, j)[2];

			if (S >=43)
			{
				if (((H >=156 && H < 180) || (H >= 0 && H < 10))&&(V>=46))
				{
					resultGray.at<uchar>(i, j) = 0;
					resultColor.at<Vec3b>(i, j)[0] = inputImage.at<Vec3b>(i, j)[0];
					resultColor.at<Vec3b>(i, j)[1] = inputImage.at<Vec3b>(i, j)[1];
					resultColor.at<Vec3b>(i, j)[2] = inputImage.at<Vec3b>(i, j)[2];
				}

			}
		}
	}
}
Mat createAlpha(cv::Mat& src)
{
	cv::Mat alpha = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
	cv::Mat gray = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
	cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			alpha.at<uchar>(i, j) = 255 - gray.at<uchar>(i, j);
		}
	}
	return alpha;
}
int addAlpha(cv::Mat& src, cv::Mat& dst, cv::Mat& alpha)
{
	if (src.channels() == 4)
	{
		return -1;
	}
	else if (src.channels() == 1)
	{
		cv::cvtColor(src, src, cv::COLOR_GRAY2RGB);
	}
	dst = Mat(src.rows, src.cols, CV_8UC4);
	std::vector<cv::Mat> srcChannels;
	std::vector<cv::Mat> dstChannels;
	//Separation channel
	cv::split(src, srcChannels);
	dstChannels.push_back(srcChannels[0]);
	dstChannels.push_back(srcChannels[1]);
	dstChannels.push_back(srcChannels[2]);
	//Adding Transparency Channel
	dstChannels.push_back(alpha);
	//Merge channel
	cv::merge(dstChannels, dst);
	return 0;
}
int main()
{
	Mat img= imread("test.png");
	Mat resultGray, resultColor;
	filteredRed(img, resultGray, resultColor);
	imshow("Extracted Red Picture", resultColor);
	waitKey(2000);
	//Make the extracted image transparent and save
	Mat dst;
	Mat alpha = createAlpha(resultColor);
	addAlpha(resultColor, dst, alpha);
	imwrite("Í¸Ã÷±³¾°.png", dst);
	namedWindow("Í¸Ã÷±³¾°", WINDOW_NORMAL);
	imshow("Í¸Ã÷±³¾°", alpha);
	waitKey(0);
	return 0;
}
