#pragma once
#include <opencv2/opencv.hpp>

//Sending Signals
#define ASK_FOR_NEW_CARRIERID_SIGNAL			QByteArray::fromHex("FFFFFFFF20FFFF20")
#define PARDON_SIGNAL						QByteArray::fromHex("FFFFFFFF21FFFF21")

//Received Signals
#define CARRIERID_TO_CHECK_SIGNAL			QByteArray::fromHex("FFFFFFFF40FFFF40")

#define signalNumByte		8


//Color of drawn error contours
#define EXTRA_COATING_ERROR_COLOR_AUTO		cv::Scalar(	0,	0,	255) //BGR
#define MISS_COATING_ERROR_COLOR_AUTO		cv::Scalar(	14,	252,	245)
#define EXTRA_COATING_ERROR_COLOR			cv::Scalar(	19,	117,	235)
#define MISS_COATING_ERROR_COLOR			cv::Scalar(	135,	89,	249)


//
enum REGION_IN_CARRIER
{
	VIEW_11,
	VIEW_12,
	VIEW_21,
	VIEW_22,
	VIEW_31,
	VIEW_32,
	VIEW_41,
	VIEW_42
};

//the 
class onePCBResInfo
{
public:
	onePCBResInfo();
	~onePCBResInfo();

	std::string getPCBID();
	void getImgRes(cv::Mat& imgResF, cv::Mat& imgResB);
	cv::Mat getImgResFSide();
	cv::Mat getImgResBSide();
	int getErrorNumExtra();
	int getErrorNumMiss();
	std::vector<std::vector<cv::Point>> getErrorContoursExtraF();
	std::vector<std::vector<cv::Point>> getErrorContoursMissF();
	std::vector<std::vector<cv::Point>> getErrorContoursExtraB();
	std::vector<std::vector<cv::Point>> getErrorContoursMissB();
	bool isResModified() const;

	void setErrorNumExtra(int numberErr);
	void setErrorNumMiss(int numberErr);
	void setErrorContoursExtraF(std::vector<std::vector<cv::Point>> contoursErr);
	void setErrorContoursMissF(std::vector<std::vector<cv::Point>> contoursErr);
	void setErrorContoursExtraB(std::vector<std::vector<cv::Point>> contoursErr);
	void setErrorContoursMissB(std::vector<std::vector<cv::Point>> contoursErr);
	void beenModified();

private:
	std::string pcbID;
	cv::Mat imgResFSide;
	cv::Mat imgResBSide;
	int extraErrorNum;
	int missErrorNum;
	std::vector<std::vector<cv::Point>> contourExtraF;
	std::vector<std::vector<cv::Point>> contourMissF;
	std::vector<std::vector<cv::Point>> contourExtraB;
	std::vector<std::vector<cv::Point>> contourMissB;
	bool isModified;
};

//human recheck process checking one carrier's result at one time  //todo:
class CarrierResInfo
{
	CarrierResInfo();
	~CarrierResInfo();

	void getErrContours(std::string filePathXML);
private:
	int viewNum;
	std::string curCarrierID;
	std::map<REGION_IN_CARRIER, onePCBResInfo> carrierResInfoAuto;
	std::map<REGION_IN_CARRIER, onePCBResInfo> carrierResInfoManu;
};