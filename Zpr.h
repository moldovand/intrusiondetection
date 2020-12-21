/*
 *  Copyright: D-SenS Consortium, 2013
 *   
 *  Created: June 7, 2013
 *
 *  Purpose: Zoom-pan-rotate mouse manipulation module for GLUT (Project: D-SenS)
 *  
 *  Author: Daniel Moldovan, AIT Austrian Institute of Technology
 */
#ifndef DSENS_intrusiondetection_ZPR_H
#define DSENS_intrusiondetection_ZPR_H

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glut.h>

#include <dsens/core/core.h>
#include <dsens/linalg/LinAlg.h>

#ifdef __cplusplus
extern "C"
{
#endif

namespace dsens {
namespace intrusiondetection {

using namespace std;
using namespace dsens::linalg;

/** 
Initialization of the @param SelectionPoint object
*/
DSENS_EXPORT void zprInit();

/** 
Used for generating the parameters of the spherical virtual fence. It manipulates 3D points from the scene and 2D coordinates of the cursor.
@param selectedControlPoint index for the selected 3D point 
@param mouseX X coordinate of the cursor
@param mouseY Y coordinate of the cursor
@param ControlKey keyboard control for switching between scene manipulation (rotation, panning, zooming) and 
									definition of the sphere (selection of center, radius generation, positioning of the sphere in 3D volume)
@param ControlPoint center of the spherical fence
*/
class DSENS_EXPORT SelectionPoint{
	public:
		 static int selectedControlPoint;
		 static int mouseX;
		 static int mouseY;
		 static int ControlKey;
		 static vector< Vec > ControlPoint;
};

}
}
#ifdef __cplusplus
}
#endif

#endif
