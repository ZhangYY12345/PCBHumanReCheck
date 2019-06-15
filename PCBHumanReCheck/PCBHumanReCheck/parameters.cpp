#include "parameters.h"
#include "methods.h"


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

std::map<std::string, REGION_IN_CARRIER> g_viewName_Reverse = {
{ "VIEW_11", VIEW_11 },
{ "VIEW_12", VIEW_12 },
{ "VIEW_21", VIEW_21 },
{ "VIEW_22", VIEW_22 },
{ "VIEW_31", VIEW_31 },
{ "VIEW_32", VIEW_32 },
{ "VIEW_41", VIEW_41 },
{ "VIEW_42", VIEW_42 }
};

//------------------------------------------------
//------------------onePCBResInfo-----------------
//------------------------------------------------
onePCBResInfo::onePCBResInfo()
{
	pcbID = "";
	imgResFSide = cv::Mat();
	imgResBSide = cv::Mat();
	extraErrorNum = 0;
	missErrorNum = 0;
	isModified = false;
}

onePCBResInfo::~onePCBResInfo()
{
	if(!contourExtraF.empty())
	{
		contourExtraF.clear();
	}

	if (!contourMissF.empty())
	{
		contourMissF.clear();
	}

	if (!contourExtraB.empty())
	{
		contourExtraB.clear();
	}

	if (!contourMissB.empty())
	{
		contourMissB.clear();
	}
}

void onePCBResInfo::resetOneSideRes(int sideInfo, onePCBResInfo obj)
{
	if (pcbID == obj.pcbID)
	{
		if (sideInfo == 0)		//front side
		{
			isModified = obj.isModified;
			contourExtraF.assign(obj.contourExtraF.begin(), obj.contourExtraF.end());
			contourMissF.assign(obj.contourMissF.begin(), obj.contourMissF.end());

			extraErrorNum = contourExtraF.size() + contourExtraB.size();
			missErrorNum = contourMissF.size() + contourMissB.size();
		}
		else if (sideInfo == 1)	//back side
		{
			isModified = obj.isModified;
			contourExtraB.assign(obj.contourExtraB.begin(), obj.contourExtraB.end());
			contourMissB.assign(obj.contourMissB.begin(), obj.contourMissB.end());

			extraErrorNum = contourExtraF.size() + contourExtraB.size();
			missErrorNum = contourMissF.size() + contourMissB.size();
		}
	}
}

bool onePCBResInfo::empty()
{
	return !(pcbID != "" && !imgResFSide.empty() && !imgResBSide.empty());
}

void onePCBResInfo::clearInfo()
{
	pcbID = "";
	imgResFSide = cv::Mat();
	imgResBSide = cv::Mat();
	extraErrorNum = 0;
	missErrorNum = 0;
	isModified = false;

	if (!contourExtraF.empty())
	{
		contourExtraF.clear();
	}

	if (!contourMissF.empty())
	{
		contourMissF.clear();
	}

	if (!contourExtraB.empty())
	{
		contourExtraB.clear();
	}

	if (!contourMissB.empty())
	{
		contourMissB.clear();
	}

}

void onePCBResInfo::erase(int sideInfo, ERR_CONTOUR_NAME errNameInfo, std::vector<cv::Point> pts)
{
	if(sideInfo == 0)
	{
		if(errNameInfo == EXTRA_ERR)
		{
			eraseOneContour(contourExtraF, pts);
			extraErrorNum--;
			isModified = true;
		}
		else if(errNameInfo == MISS_ERR)
		{
			eraseOneContour(contourMissF, pts);
			missErrorNum--;
			isModified = true;
		}
	}
	else if(sideInfo == 1)
	{
		if (errNameInfo == EXTRA_ERR)
		{
			eraseOneContour(contourExtraB, pts);
			extraErrorNum--;
			isModified = true;
		}
		else if (errNameInfo == MISS_ERR)
		{
			eraseOneContour(contourMissB, pts);
			missErrorNum--;
			isModified = true;
		}
	}
}

onePCBResInfo& onePCBResInfo::operator=(onePCBResInfo& obj)
{
	pcbID = obj.pcbID;
	imgResFSide = obj.imgResFSide.clone();
	imgResBSide = obj.imgResBSide.clone();
	extraErrorNum = obj.extraErrorNum;
	missErrorNum = obj.missErrorNum;
	isModified = obj.isModified;

	contourExtraF.assign(obj.contourExtraF.begin(), obj.contourExtraF.end());
	contourMissF.assign(obj.contourMissF.begin(), obj.contourMissF.end());
	contourExtraB.assign(obj.contourExtraB.begin(), obj.contourExtraB.end());
	contourMissB.assign(obj.contourMissB.begin(), obj.contourMissB.end());

	return *this;
}

bool onePCBResInfo::operator==(onePCBResInfo& obj)
{
	return pcbID == obj.pcbID
		&& extraErrorNum == obj.extraErrorNum
		&& missErrorNum == obj.missErrorNum
		&& isModified == obj.isModified
		&& isSameDVecPt(contourExtraF, obj.contourExtraF)
		&& isSameDVecPt(contourMissF, obj.contourMissF)
		&& isSameDVecPt(contourExtraB, obj.contourExtraB)
		&& isSameDVecPt(contourMissB, obj.contourMissB);
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

void CarrierResInfo::clearAllInfo()
{
	viewNum = 0;
	curCarrierID = "";
	carrierResInfoAuto.clear();
	carrierResInfoManu.clear();
}

bool CarrierResInfo::isInCarrierReChecking()
{
	return !carrierResInfoManu.empty();
}

void CarrierResInfo::setViewNum(int numView)
{
	viewNum = numView;
}

void CarrierResInfo::setErrContoursAuto(std::string filePathXML)
{
	std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };

	cv::FileStorage fs(filePathXML, cv::FileStorage::READ);
	if (fs.isOpened())
	{
		fs["CarrierID"] >> curCarrierID;
		fs["CarrierViewNum"] >> viewNum;

		for (int i = 0; i < viewNum; i++)
		{
			std::string upperLabel = g_viewName[g_Views[i]];
			cv::FileNode fn = fs[upperLabel];

			fn[labels[0]] >> carrierResInfoAuto[g_Views[i]].contourExtraF;
			fn[labels[1]] >> carrierResInfoAuto[g_Views[i]].contourMissF;
			fn[labels[2]] >> carrierResInfoAuto[g_Views[i]].contourExtraB;
			fn[labels[3]] >> carrierResInfoAuto[g_Views[i]].contourMissB;

			carrierResInfoAuto[g_Views[i]].extraErrorNum = carrierResInfoAuto[g_Views[i]].contourExtraF.size() + carrierResInfoAuto[g_Views[i]].contourExtraB.size();
			carrierResInfoAuto[g_Views[i]].missErrorNum = carrierResInfoAuto[g_Views[i]].contourMissF.size() + carrierResInfoAuto[g_Views[i]].contourMissB.size();
		}
	}
	fs.release();
}

void CarrierResInfo::setOnePCBResAuto(REGION_IN_CARRIER viewID, onePCBResInfo oneRes)
{
	carrierResInfoAuto[viewID] = oneRes;
}

void CarrierResInfo::getOnePCBResAuto(REGION_IN_CARRIER viewID, onePCBResInfo& oneRes)
{
	oneRes = carrierResInfoAuto[viewID];
}

onePCBResInfo CarrierResInfo::getOnePCBResAuto(REGION_IN_CARRIER viewID)
{
	return carrierResInfoAuto[viewID];
}

void CarrierResInfo::getCarrierResAuto(std::map<REGION_IN_CARRIER, onePCBResInfo>& allRes)
{
	allRes = carrierResInfoAuto;
}

std::map<REGION_IN_CARRIER, onePCBResInfo> CarrierResInfo::getCarrierResAuto()
{
	return carrierResInfoAuto;
}

void CarrierResInfo::setErrContoursManu(std::vector<REGION_IN_CARRIER> viewId, std::string filePathXML)
{
	if (!viewId.empty())
	{
		std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };

		cv::FileStorage fs(filePathXML, cv::FileStorage::READ);
		if (fs.isOpened())
		{
			for (std::vector<REGION_IN_CARRIER>::iterator itor = viewId.begin(); 
				itor != viewId.end(); itor ++)
			{
				std::string upperLabel = g_viewName[*itor];
				cv::FileNode fn = fs[upperLabel];

				fn[labels[0]] >> carrierResInfoAuto[*itor].contourExtraF;
				fn[labels[1]] >> carrierResInfoAuto[*itor].contourMissF;
				fn[labels[2]] >> carrierResInfoAuto[*itor].contourExtraB;
				fn[labels[3]] >> carrierResInfoAuto[*itor].contourMissB;

				carrierResInfoAuto[*itor].extraErrorNum = 
					carrierResInfoAuto[*itor].contourExtraF.size() 
					+ carrierResInfoAuto[*itor].contourExtraB.size();
				carrierResInfoAuto[*itor].missErrorNum = 
					carrierResInfoAuto[*itor].contourMissF.size() 
					+ carrierResInfoAuto[*itor].contourMissB.size();
			}
		}
		fs.release();
	}
}

void CarrierResInfo::saveManuErrContr(std::string filePath)
{
	std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };
	cv::FileStorage fs(filePath, cv::FileStorage::WRITE);

	if (fs.isOpened())
	{
		fs << "CarrierID" << curCarrierID;
		for (std::map<REGION_IN_CARRIER, onePCBResInfo>::iterator itor = carrierResInfoManu.begin();
			itor != carrierResInfoManu.end(); itor++)
		{
			std::string upperLabel = g_viewName[itor->first];
			fs << upperLabel << "{";
			fs << labels[0] << carrierResInfoManu[itor->first].contourExtraF;
			fs << labels[1] << carrierResInfoManu[itor->first].contourMissF;
			fs << labels[2] << carrierResInfoManu[itor->first].contourExtraB;
			fs << labels[3] << carrierResInfoManu[itor->first].contourMissB;
			fs << "}";
		}

	}
	fs.release();
}

void CarrierResInfo::setOnePCBResManu(REGION_IN_CARRIER viewID, onePCBResInfo oneRes)
{
	carrierResInfoManu[viewID] = oneRes;
}

void CarrierResInfo::getOnePCBResManu(REGION_IN_CARRIER viewID, onePCBResInfo& oneRes)
{
	oneRes = carrierResInfoManu[viewID];
}

onePCBResInfo CarrierResInfo::getOnePCBResManu(REGION_IN_CARRIER viewID)
{
	return carrierResInfoManu[viewID];
}

void CarrierResInfo::setCarrierResManu(std::map<REGION_IN_CARRIER, onePCBResInfo> carrierRes)
{
	std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier_this = this->carrierResInfoManu.begin();
	for (std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier = carrierRes.begin(); itor_carrier != carrierRes.end(); ++itor_carrier)
	{
		(*itor_carrier_this).second = (*itor_carrier).second;

		itor_carrier_this++;
	}
}

void CarrierResInfo::getCarrierResManu(std::map<REGION_IN_CARRIER, onePCBResInfo>& allRes)
{
	allRes = carrierResInfoManu;
}

std::map<REGION_IN_CARRIER, onePCBResInfo> CarrierResInfo::getCarrierResManu()
{
	return carrierResInfoManu;
}

bool CarrierResInfo::isRechecked(REGION_IN_CARRIER viewID)
{
	return carrierResInfoManu.find(viewID) != carrierResInfoManu.end();
}

void CarrierResInfo::revokeManuChanged(REGION_IN_CARRIER viewID)
{
	if (isRechecked(viewID))
	{
		carrierResInfoManu.erase(viewID);
	}
}

CarrierResInfo& CarrierResInfo::operator=(CarrierResInfo& obj)
{
	if (this != &obj)
	{
		this->viewNum = obj.viewNum;
		this->curCarrierID = obj.curCarrierID;
		std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier_this = this->carrierResInfoAuto.begin();
		for (std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier = obj.carrierResInfoAuto.begin(); itor_carrier != obj.carrierResInfoAuto.end(); ++itor_carrier)
		{
			(*itor_carrier_this).second = (*itor_carrier).second;

			itor_carrier_this++;
		}

		std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier_this_manu = this->carrierResInfoManu.begin();
		for (std::map<REGION_IN_CARRIER, onePCBResInfo >::iterator itor_carrier = obj.carrierResInfoManu.begin(); itor_carrier != obj.carrierResInfoManu.end(); ++itor_carrier)
		{
			(*itor_carrier_this_manu).second = (*itor_carrier).second;

			itor_carrier_this_manu++;
		}
	}

	return *this;
}
