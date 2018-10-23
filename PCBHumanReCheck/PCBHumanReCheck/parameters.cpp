#include "parameters.h"


REGION_IN_CARRIER g_Views[8] = { VIEW_11, VIEW_12, VIEW_21, VIEW_22, VIEW_31, VIEW_32, VIEW_41, VIEW_42 };
std::map<REGION_IN_CARRIER, std::string> g_viewName = {
{ VIEW_11, "VIEW_11" },
{ VIEW_12, "VIEW_12" },
{ VIEW_21, "VIEW_21" },
{ VIEW_22, "VIEW_22" },
{ VIEW_31, "VIEW_31" },
{ VIEW_32, "VIEW_32" },
{ VIEW_41, "VIEW_41" },
{ VIEW_42, "VIEW_42" }
};

//--------------------------------------------------
//------------------onePCBResInfo-------------------
//--------------------------------------------------
onePCBResInfo::onePCBResInfo()
{
	pcbID = "";
	imgResFSide = cv::Mat();
	imgResBSide = cv::Mat();
	extraErrorNum = 0;
	missErrorNum = 0;

	if(!contourExtra.empty())
	{
		contourExtra.clear();
	}

	if(!contourMiss.empty())
	{
		contourMiss.clear();
	}

	isModified = false;
}

onePCBResInfo::~onePCBResInfo()
{
}

std::string onePCBResInfo::getPCBID()
{
	return pcbID;
}

void onePCBResInfo::getImgRes(cv::Mat& imgResF, cv::Mat& imgResB)
{
	imgResF = imgResFSide.clone();
	imgResB = imgResBSide.clone();
}

cv::Mat onePCBResInfo::getImgResFSide()
{
	return imgResFSide.clone();
}

cv::Mat onePCBResInfo::getImgResBSide()
{
	return imgResBSide.clone();
}

int onePCBResInfo::getErrorNumExtra()
{
	return extraErrorNum;
}

int onePCBResInfo::getErrorNumMiss()
{
	return missErrorNum;
}

std::vector<std::vector<cv::Point>> onePCBResInfo::getErrorContoursExtraF()
{
	return contourExtraF;
}

std::vector<std::vector<cv::Point>> onePCBResInfo::getErrorContoursMissF()
{
	return contourMissF;
}

std::vector<std::vector<cv::Point>> onePCBResInfo::getErrorContoursExtraB()
{
	return contourExtraB;
}

std::vector<std::vector<cv::Point>> onePCBResInfo::getErrorContoursMissB()
{
	return contourMissB;
}

bool onePCBResInfo::isResModified() const
{
	return isModified;
}

void onePCBResInfo::setErrorNumExtra(int numberErr)
{
	extraErrorNum = numberErr;
}

void onePCBResInfo::setErrorNumMiss(int numberErr)
{
	missErrorNum = numberErr;
}

void onePCBResInfo::setErrorContoursExtraF(std::vector<std::vector<cv::Point>> contoursErr)
{
	contourExtraF = contoursErr;
}

void onePCBResInfo::setErrorContoursMissF(std::vector<std::vector<cv::Point>> contoursErr)
{
	contourMissF = contoursErr;
}

void onePCBResInfo::setErrorContoursExtraB(std::vector<std::vector<cv::Point>> contoursErr)
{
	contourExtraB = contoursErr;
}

void onePCBResInfo::setErrorContoursMissB(std::vector<std::vector<cv::Point>> contoursErr)
{
	contourMissB = contoursErr;
}

void onePCBResInfo::beenModified()
{
	isModified = true;
}


//------------------------------------------------
//------------------CarrierResInfo----------------
//------------------------------------------------
CarrierResInfo::CarrierResInfo()
{
	viewNum = 0;
	curCarrierID = "";
}

CarrierResInfo::~CarrierResInfo()
{
}

void CarrierResInfo::getErrContours(std::string filePathXML)
{
	std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };

	cv::FileStorage fs(filePathXML, cv::FileStorage::READ);
	fs["CarrierID"] >> curCarrierID;

	switch (viewNum)
	{
	case 1:
		{
		std::string upperLabel = g_viewName[VIEW_11];
		cv::FileNode fn = fs[upperLabel];
		
		fn[labels[0]] >> carrierResInfoAuto[VIEW_11].
		
	}
	case 4:
		{
			
		}
	case 6:
		{
			
		}
	case 8:
		{
			
		}
	}

	fs.release();
}
