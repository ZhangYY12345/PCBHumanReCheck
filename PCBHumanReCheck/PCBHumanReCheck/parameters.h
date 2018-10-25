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
#define EXTRA_COATING_ERROR_QCOLOR_AUTO		QColor(	255,	0,	0) //RGB
#define MISS_COATING_ERROR_QCOLOR_AUTO		QColor(	245,	252,	14)
#define EXTRA_COATING_ERROR_QCOLOR			QColor(	235,	117,	19)
#define MISS_COATING_ERROR_QCOLOR			QColor(	249,	89,	135)

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


enum ERR_CONTOUR_NAME
{
	EXTRA_ERR,
	MISS_ERR,
	NULL_ERR
};

//the 
class onePCBResInfo
{
public:
	onePCBResInfo();
	~onePCBResInfo();

	bool empty();
	void clearInfo();
	void erase(int sideInfo, ERR_CONTOUR_NAME errNameInfo, std::vector<cv::Point> pts);
	onePCBResInfo& operator = (onePCBResInfo& obj);

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
public:
	CarrierResInfo();
	~CarrierResInfo();

	void clearAllInfo();
	bool isInCarrierReChecking();

	void setViewNum(int numView);

	//resAuto
	void setErrContoursAuto(std::string filePathXML);

	void setOnePCBResAuto(REGION_IN_CARRIER viewID, onePCBResInfo oneRes);
	void getOnePCBResAuto(REGION_IN_CARRIER viewID, onePCBResInfo& oneRes);
	onePCBResInfo getOnePCBResAuto(REGION_IN_CARRIER viewID);
	void getCarrierResAuto(std::map<REGION_IN_CARRIER, onePCBResInfo>& allRes);
	std::map<REGION_IN_CARRIER, onePCBResInfo> getCarrierResAuto();


	//resManu
	void setOnePCBResManu(REGION_IN_CARRIER viewID, onePCBResInfo oneRes);
	void getOnePCBResManu(REGION_IN_CARRIER viewID, onePCBResInfo& oneRes);
	onePCBResInfo getOnePCBResManu(REGION_IN_CARRIER viewID);

	void setCarrierResManu(std::map<REGION_IN_CARRIER, onePCBResInfo> carrierRes);
	void getCarrierResManu(std::map<REGION_IN_CARRIER, onePCBResInfo>& allRes);
	std::map<REGION_IN_CARRIER, onePCBResInfo> getCarrierResManu();

	CarrierResInfo& operator = (CarrierResInfo& obj);
private:
	int viewNum;
	std::string curCarrierID;
	std::map<REGION_IN_CARRIER, onePCBResInfo> carrierResInfoAuto;
	std::map<REGION_IN_CARRIER, onePCBResInfo> carrierResInfoManu;
};