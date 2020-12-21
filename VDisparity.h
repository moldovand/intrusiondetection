/*
 *  Copyright: D-SenS Consortium, 2013
 *   
 *  Created: June 7, 2013
 *  
 *  Author: Daniel Moldovan, AIT Austrian Institute of Technology
 */
#ifndef DSENS_intrusiondetection_VDisparity_H
#define DSENS_intrusiondetection_VDisparity_H

// include dependencies
//
#include <PfeDx.h>
#include <PfeHeapMan.h>
#include <S3E.h>
#include <ESVS_errors.h>

#include <dsens/core/core.h>

namespace dsens {
namespace intrusiondetection {

DSENS_EXPORT PfeStatus V_Disparity(const PfeSize &imageSize, PfePixImgStruct *pfeImgDisparity, Pfe16u **ImageDisp, Pfe16u **vDisp,  PfeSize &vDispSize, const PfeBool PixAccuracy);

}
}
#endif