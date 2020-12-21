/*
 *  Copyright: D-SenS Consortium, 2013
 *   
 *  Created: June 7, 2013
 *  
 *  Author: Daniel Moldovan, AIT Austrian Institute of Technology
 */
#ifndef DSENS_intrusiondetection_CVolumes_H
#define DSENS_intrusiondetection_CVolumes_H

// include standard libraries
//
#include <vector>
#include <string>

// include dependencies
//
#include <S3E.h>
#include <ESVS_errors.h>
#include <PfeDx.h>
#include <PfeCCLabeling_16u_C1IR.h>
#include <PfeStopWatch.h>
#include <PfeHeapMan.h>
#include <PfeDraw.h>
#include <OpenNI.h>

// include other source files
//
#include <dsens/intrusiondetection/Volume_Demo.h>
#include <dsens/core/core.h>
#include <dsens/linalg/LinAlg.h>

namespace dsens {
namespace intrusiondetection {

using namespace dsens::linalg;
using namespace std;
/**
Class used in filtering the data surrounding the 3D volume
*/
class DSENS_EXPORT CVolume
{
private:
	std::string sType;

public:
	EsvStatus SetType(std::string _sType);
	Pfe64f Esv3dDistance(EsvPoint3d *p1, EsvPoint3d *p2);
	virtual EsvStatus Esv3dVolumeFilterFromDepth(PfePixImgStruct *pSrc,	PfePixImgStruct *pDst, PfePixImgStruct *pImg3D, EsvInitStruct *pEsvInit){return esvOK;};
	virtual EsvStatus Esv3dVolumeFilterFromPrimesenseDepth(Sensor &globalComm, PfePixImgStruct *pSrc,	PfePixImgStruct *pDst, openni::VideoFrameRef	*vfDepthFrame){return esvOK;}; 
	virtual EsvStatus Esv3dFilterWithLabels(PfePixImgStruct *pImgDepth,
																					PfePixImgStruct *pImgLables,
																					PfePixImgStruct *pImg3D, 
																					EsvInitStruct *pEsvInit, 
																					PfeCCLabelingStruct *pLabeling, 
																					std::vector<PfeLabelSmallStruct>* pVecAlarmObjects){return esvOK;};
	virtual EsvStatus Esv3dFilterWithLabels_Primesense(Sensor &globalComm, PfePixImgStruct *pImgDepth,
																					PfePixImgStruct *pImgLables,
																					openni::VideoFrameRef	*vfDepthFrame, 
																					EsvInitStruct *pEsvInit, 
																					PfeCCLabelingStruct *pLabeling, 
																					std::vector<PfeLabelSmallStruct>* pVecAlarmObjects){return esvOK;};
};

/**
Class used in filtering the data surrounding a Spherical Volume.
*/
class DSENS_EXPORT CVolume_Ball : public CVolume
{
private:
	EsvPoint3d	esv3dCenter;
	Pfe32f			f32Radius;
	Pfe32f			f32OuterRadius;

public:
	CVolume_Ball(std::string _sType);
	CVolume_Ball(std::string _sType, Pfe32f _cx, Pfe32f _cy, Pfe32f _cz, Pfe32f _radius, Pfe32f _minObjectSize);
	EsvStatus SetVolumeValues(Pfe32f _cx, Pfe32f _cy, Pfe32f _cz, Pfe32f _radius, Pfe32f _minObjectSize);
	EsvStatus Esv3dVolumeFilterFromDepth(PfePixImgStruct *pSrc,	PfePixImgStruct *pDst, PfePixImgStruct *pImg3D, EsvInitStruct *pEsvInit);
	EsvStatus Esv3dVolumeFilterFromPrimesenseDepth(Sensor &globalComm, PfePixImgStruct *pSrc,	PfePixImgStruct *pDst, openni::VideoFrameRef	*vfDepthFrame);//openni::VideoStream	&g_vsDepthStream, 
	EsvStatus CVolume_Ball::Esv3dFilterWithLabels(PfePixImgStruct *pImgDepth,
																							PfePixImgStruct *pImgLables,
																							PfePixImgStruct *pImg3D, 
																							EsvInitStruct *pEsvInit, 
																							PfeCCLabelingStruct *pLabeling, 
																							std::vector<PfeLabelSmallStruct>* pVecAlarmObjects);
	EsvStatus Esv3dFilterWithLabels_Primesense(Sensor &globalComm, PfePixImgStruct *pImgDepth,
																					PfePixImgStruct *pImgLables,
																					openni::VideoFrameRef	*vfDepthFrame, 
																					EsvInitStruct *pEsvInit, 
																					PfeCCLabelingStruct *pLabeling, 
																					std::vector<PfeLabelSmallStruct>* pVecAlarmObjects);//openni::VideoStream	&g_vsDepthStream, 
};

/**
Class used for defining the parameters of the Virtual Fence.
*/
class DSENS_EXPORT virtualFence{
	public:
		 vector<CVolume*>	vecVolumes;
		 Vec							axis;
		 Vec							centroid_Vec;
		 float						angle;
		 int							scaleFactor;
		 int							CtrAlarm;
		 CVolume_Ball			*pTempBall;
		 float						SphRad[10];
		 Pfe32f						f32MinObjectSize;
		 PfeCCLabelingStruct *pLabeling;
};
/**
Depth Acquisition that will generate the 3D structure of the scene needed for setting up the Virtual Fence.
*/
DSENS_EXPORT int DepthAcquisition(Sensor &globalComm, pointCloud &scene);
/**
Continuous Depth Acquistion with the Intrusion Detection activated.
*/
DSENS_EXPORT int Update3Ddata(Sensor &globalComm, virtualFence &fence);
/**
Selection of the type of 3D sensor used for the intrusion detection.
*/
DSENS_EXPORT void selectInputSensor(Sensor &globalComm, virtualFence &fence);
/**
Creation of the Labeling structure
*/
DSENS_EXPORT EsvStatus CreateCCLabelingStruct(EsvInitStruct *pEsvInit, virtualFence &fence, PfePixImgStruct *pImgLabeling);
/**
Detection of the intruding objects for the stereo vision sensor.
*/
DSENS_EXPORT void objectDetection_Stereo(Sensor &globalComm, virtualFence &fence, PfePixImgStruct &pfeImgFilteredDepth, PfePixImgStruct &pfeImgLabels, PfePixImgStruct &pfeImgDepth, PfePixImgStruct &img3D, EsvInitStruct *pEsvInit, std::vector<PfeLabelSmallStruct> &vecAlarmObjects);
/**
Detection of the intruding objects for the ToF sensor.
*/
DSENS_EXPORT void objectDetection_Primesense(Sensor &globalComm, virtualFence &fence, openni::VideoFrameRef	&vfDepthFrame, PfePixImgStruct &pfeImgFilteredDepth, PfePixImgStruct &pfeImgLabels, PfePixImgStruct &pfeImgPrimesense, PfePixImgStruct &pfeImgPrimesenseBgModel, std::vector<PfeLabelSmallStruct> &vecAlarmObjects);
}
}
#endif