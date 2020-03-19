//
// CircleSurface.h
// Copyright (c) 2017 Cristobal Mendoza
// With modifications by Krisjanis Rijnieks (c) 2017
// http://cuppetellimendoza.com

#ifndef OFXPIMAPPER_CIRCLESURFACE_H
#define OFXPIMAPPER_CIRCLESURFACE_H

#include "QuadSurface.h"
#include "Vec2.h"
#include "Vec3.h"

#define CIRCLE_SURFACE_STRINGIFY(A) #A

namespace ofx {
namespace piMapper {

class CircleSurface : public QuadSurface {
	public:
		CircleSurface();
		CircleSurface(QuadSurface &surface);
		int getType() override;
		void draw() override;
		void setup() override;

		// TODO: Feathering
		void setFeathering(float f);

	protected:
		void setupTextures();
		void drawMaskForSource(ofTexture &sourceTexture);
		ofFbo maskFbo;
//		ofFbo scaledSourceFbo;
		ofFbo outputFbo;
//		ofShader maskShader;
		float feathering = 0.0f;
		bool updateMask;
		bool maskIsReady;

//		std::string glESFragmentShader;
//		std::string glESVertexShader;
//
//		std::string gl2FragmentShader;
//		std::string gl2VertexShader;

		ofMesh maskMesh;

		// TODO: gl3 Shaders
//		std::string          gl3VertexShader;
//		std::string          gl3FragmentShader;

	private:
		std::vector<Vec2> defaultTexCoords;
		// We will use this pointer to determine if the source has changed.
		// This is a total kludge, but it keeps me from messing with the
		// upstream source.
		BaseSource* currentSource = 0;
		unsigned int lastSourceTextureId;
};

}
}


#endif //OFXPIMAPPER_CIRCLESURFACE_H
