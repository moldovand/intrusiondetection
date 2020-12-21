/*
 *  Copyright: D-SenS Consortium, 2013
 *   
 *  Created: June 7, 2013
 *  
 *  Author: Daniel Moldovan, AIT Austrian Institute of Technology
 */
#ifndef DSENS_intrusiondetection_BackgroundModel_H
#define DSENS_intrusiondetection_BackgroundModel_H
 
#include <S3E.h>
#include <ESVS_errors.h>
#include <string>
#include <vector>
#include <PfeDx.h>

#include <dsens/core/core.h>

namespace dsens {
namespace intrusiondetection {
/**
Background model integration from Depth Image
@param pAdd the source
@param pBg the output
*/
DSENS_EXPORT PfeStatus Esv3dIntegrateBackgroundFromDepth(PfePixImgStruct *pAdd,	PfePixImgStruct *pBg);
/**
Background model integration from Disparity Image
@param pAdd the source
@param pBg the output
*/
DSENS_EXPORT PfeStatus Esv3dIntegrateBackgroundFromDisparity(PfePixImgStruct *pAdd,	PfePixImgStruct *pBg);

/**
Background subtraction from Depth
*/
DSENS_EXPORT PfeStatus Esv3dSubtractBackgroundFromDepth(PfePixImgStruct *pSrc,	PfePixImgStruct *pBg, Pfe16u u16MinDiffToKeep);
/**
Background subtraction from Disparity
*/
DSENS_EXPORT PfeStatus Esv3dSubtractBackgroundFromDisparity(PfePixImgStruct *pSrc,	PfePixImgStruct *pBg, Pfe16u u16MinDiffToKeep);
/**
Background subtraction from Depth, single sided
*/
DSENS_EXPORT PfeStatus Esv3dSubtractBackgroundFromDepthSingleSided(PfePixImgStruct *pSrc,	PfePixImgStruct *pBg, Pfe16u u16MinDiffToKeep);
/**
Background subtraction from Disparity, single sided
*/
DSENS_EXPORT PfeStatus Esv3dSubtractBackgroundFromDisparitySingleSided(PfePixImgStruct *pSrc,	PfePixImgStruct *pBg, Pfe16u u16MinDiffToKeep);
/**
Background subtraction function called in the above functions
*/
DSENS_EXPORT PfeStatus Esv3dSubtractBackground(PfePixImgStruct *pSrc,	PfePixImgStruct *pBg, PfePixImgStruct *pDst, Pfe16u u16MinDiffToKeep, const Pfe16u u16InvalidVal, const PfeBool bRemoveAlwaysIfSrcLess, const PfeBool bRemoveAlwaysIfSrcMore, const PfeBool bReplaceWithBg);
}
}
#endif