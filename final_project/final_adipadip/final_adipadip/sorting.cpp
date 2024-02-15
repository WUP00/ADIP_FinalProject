#include "final.h"


class Ve
{
public:
	vector<string> ReadImage(cv::String pattern);
};

vector<string> Ve::ReadImage(cv::String pattern)
{
	vector<string> temp;
	vector<cv::String> fn;
	glob(pattern, fn, false);
	size_t count = fn.size(); //number of png files in images folder
	for (size_t i = 0; i < count; i++)
	{
		temp.push_back(fn[i]);
	}
	return temp;
}

void image_processing(Mat& img) {
	cvtColor(img, img, CV_BGR2GRAY);
	adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 9, 2);
}
int sorting()
{
	String pattern = "./random/*.png";
	Ve ve;
	vector<string> img_path = ve.ReadImage(pattern);

	long long* array;
	array = new long long[img_path.size()];
	Mat hashA;
	for (int i = 0; i < img_path.size(); i++)
	{
		Mat process = imread(img_path[i]);
		image_processing(process);

		//cout << img_path[i] << endl;
		//imshow("img", process);
		//waitKey(10);

	/*	Ptr<MarrHildrethHash> create(float alpha = 2.0f, float scale = 1.0f);
		Ptr<MarrHildrethHash> func = MarrHildrethHash::create;*/
		//func->compute(process, hashA);
		//array[i] = (long long)hashA.data;
	}
	
	

	return 0;
}