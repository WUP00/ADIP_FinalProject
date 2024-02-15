#define _CRT_SECURE_NO_DEPRECATE
#include "final.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

template <typename T>
inline void test_one(const std::string& title, const Mat& a, const Mat& b)
{
	
	Mat hashA, hashB;
	Ptr<ImgHashBase> func;
	func = T::create();
	func->compute(a, hashA);
	func->compute(b, hashB);
	cout << "compare: " << func->compare(hashA, hashB) << endl << endl;
}
void histogram_calculation(const Mat& Image, Mat& histoImage)
{
	// Create the histogram for 256 bins
	// The number of possibles values
	int histSize = 255;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	vector<Mat>  bgr_planes;
	split(Image, bgr_planes);

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize,
		&histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize,
		&histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize,
		&histRange, uniform, accumulate);

	// Draw the histogram
	// We go to draw lines for each channel
	int hist_w = 512;
	int hist_h = 400;

	int bin_w = cvRound((float)hist_w / (float)histSize);

	// Create image with gray base
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	// Normalize the histograms to height of image
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) {
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0
		);
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0
		);
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0
		);
	}

	//   imshow("Histogram", histImage);
	histoImage = histImage;

}


int PUBG()
{
	Mat first_frame = imread("C:/Users/wup4416/Desktop/ADIP/final_project/final_adipadip/random/001.png");
	//imshow("first_frame_origin", first_frame);
	//waitKey(0);

	Mat blurout, medianout, gaussainout, bilaterout;
	blur(first_frame, blurout, Size(5, 5), Point(-1, -1));
	//imshow("first_frame_meanfilter", blurout);
	//waitKey(0);

	//medianBlur(first_frame, medianout, 7);
	//imshow("first_frame_mediafilter", medianout);
	//waitKey(0);

	

	bilateralFilter(blurout, bilaterout, 50, 150, 3);
	//imshow("first_frame_bilateralFilter", bilaterout);
	waitKey(0);

	
	Mat sharp;
	Mat sharpening_kernel = (Mat_<double>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	filter2D(bilaterout, sharp, -10, sharpening_kernel);
	//imshow("sharpening", sharp);
	//waitKey(0);

	Mat new_image = Mat::zeros(first_frame.size(), first_frame.type());
	double alpha = 0.9;
	for (int y = 0; y < first_frame.rows; y++) {
		for (int x = 0; x < first_frame.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * (sharp.at<Vec3b>(y, x)[c]));
			}
		}
	}

	//imshow("contrast", new_image);
	//waitKey(0);

	Mat src, ycrcb, imageq;
	Mat histImage;

	//get src image

	resize(new_image, src, Size(), 1, 1);
	imshow("Source image", src);
	//calculate src channel equalize
	histogram_calculation(src, histImage);
	/*imshow("Color Image Histogram", histImage);*/
	vector<Mat> yuv;
	cvtColor(src, ycrcb, COLOR_BGR2YCrCb);
	split(ycrcb, yuv);

	//equalize Y
	equalizeHist(yuv[0], yuv[0]);

	//merge channels
	merge(yuv, imageq);
	cvtColor(imageq, imageq, COLOR_YCrCb2BGR);
	/*imshow("Equalized image", imageq);
	imwrite("Equalized_image.png", imageq);*/
	//calculate every channel histogram
	histogram_calculation(imageq, histImage);



	//imshow("Equalized color image histogram", histImage);
	//imwrite("Equalized_color_image_histogram.png", histImage);

	waitKey(0);

	GaussianBlur(imageq, gaussainout, Size(7, 7), 11, 11);



	imshow("first_frame_Gaussianfilter", gaussainout);
	imwrite("001.png", gaussainout);
	waitKey(0);

	/*Mat fastcolor;
	fastNlMeansDenoisingColored(sharp, fastcolor);
	imshow("fastcolorr", fastcolor);
	imwrite("fastcolorr.png", fastcolor);
	waitKey(0);*/

	//Mat fmdcout;
	//fastNlMeansDenoisingColored(blurout, fmdcout, 10 , 10, 7, 21);
	//imshow("fmdc", fmdcout);
	//waitKey(0);

	//Mat sharp_again;
	//filter2D(fmdcout, sharp_again, -10, sharpening_kernel); 
	//imshow("sharpen_again", sharp_again);
	//waitKey(0);

	//Mat grayscale;
	//
	//cvtColor(blurout, grayscale, CV_BGR2GRAY);
	//Mat mat_raw(720, 1280, CV_8U, grayscale.data);
	//Mat DFT = fft(mat_raw);

	//Mat HPF(720, 1280, CV_32FC2);
	//butterworthLPF(DFT, HPF, 50, 3, 720, 1280);
	//Mat IDFT = ifft(HPF);
	//imshow("hpf", plot_fft(HPF));
	//imshow("idft", IDFT);
	//waitKey(0);

	//test_one<MarrHildrethHash>("MarrHildrethHash", imageq, sharp);
	//system("pause"); 
	destroyAllWindows();
	return 0;

}