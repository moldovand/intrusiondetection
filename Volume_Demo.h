#ifndef DSENS_intrusiondetection_volume_demo_H
#define DSENS_intrusiondetection_volume_demo_H

// include standard libraries
//
#include <vector>

// include dependencies
//
#include <PfeDx.h>
#include <S3E.h>
#include <OpenNI.h>

// include other source files
//
#include <dsens/core/core.h>
#include <dsens/pointcloudgenerator/PointCloudGenerator.h>
//#include <dsens/intrusiondetection/CVolumes.h>

namespace dsens {
namespace intrusiondetection {

	using namespace dsens::pointcloudgenerator;
	using namespace std;

/**
Class for manipulating data streams related to 2 types of Sensors: stereo vision and ToF.

@param pDepthArray depth frame of the ToF sensor
@param g_vsDepthStream depth stream of the ToF sensor
@param cli container of command line parameters
@param PrimesenseCam indicator of the presence of a ToF camera
@param vDisp v-disparity (vertical disparity) image
@param ImageDisp disparity image (provided by the stereo vision)
@param vDispSize size of the v-disparity image
@param imageSize size of the input image (only for the stereo vision case)
@param pEsvInit ESVS initialization stucture
*/
class DSENS_EXPORT Sensor{
	public:
		 openni::DepthPixel*		pDepthArray;
		 openni::VideoStream		g_vsDepthStream;
		 openni::VideoStream		g_vsColorStream;
		 CmdLineStruct					cli;
		 bool										PrimesenseCam;
		 Pfe16u									**vDisp;
		 Pfe16u									**ImageDisp;
		 PfeSize								vDispSize;
		 PfeSize								imageSize;
		 EsvInitStruct					*pEsvInit;

	~Sensor () {    
		if(!Sensor::PrimesenseCam) {
        for(size_t i=0; i<Sensor::imageSize.u32Height; i++)
            delete [] Sensor::vDisp[i];
        delete [] Sensor::vDisp;

        for(size_t i=0; i<Sensor::imageSize.u32Height; i++)
            delete [] Sensor::ImageDisp[i];
        delete [] Sensor::ImageDisp;
    }

		if(Sensor::PrimesenseCam){
			delete Sensor::pDepthArray;
		}

		}
	};

DSENS_EXPORT PfeStatus AllocAndCopy(PfePixImgStruct* pDst, PfePixImgStruct* pSrc);
DSENS_EXPORT PfeStatus AllocAndCopy_RGB(PfePixImgStruct* pDst, PfePixImgStruct* pSrc);
DSENS_EXPORT EsvStatus Prepare3DReconstruction(char * pszIniPath, EsvInitStruct *pEsvInit, PfePixImgStruct *img3DTemplate, PfePixImgStruct *img3D);
DSENS_EXPORT PfeStatus PfeDrawBox_16u(PfePixImgStruct *pImg, PfePoint p1, PfePoint p2, Pfe32u u32Size, Pfe16u u8Color);
DSENS_EXPORT PfeStatus PfeDrawBox_8u(PfePixImgStruct *pImg, PfePoint p1, PfePoint p2, Pfe32u u32Size, Pfe16u u16Color);
DSENS_EXPORT PfeStatus AllocImg(PfePixImgStruct* pfeImg, Pfe32u u32Width, Pfe32u u32Height, Pfe32u u16BitsPerPixel);
DSENS_EXPORT EsvStatus EsvDisparityToZ(PfePixImgStruct *pImgDisp, PfePixImgStruct *pImgZ, EsvInitStruct *pEsvInit);
DSENS_EXPORT Pfe64s GetTimeMS();
DSENS_EXPORT int readCommandLine(Sensor &globalComm, int argc, char** argv);
DSENS_EXPORT void intrusionInitialize(Sensor &globalComm, pointCloud &scene);

}

}

#endif