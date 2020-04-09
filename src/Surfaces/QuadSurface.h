#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"
#include "Vec2.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class QuadSurface : public BaseSurface {
	public:
		QuadSurface();
		~QuadSurface();

		void setup();
		void setup(
			Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4,
			Vec2 t1, Vec2 t2, Vec2 t3, Vec2 t4,
			BaseSource * newSource);
		void draw();
		void setVertex(int index, Vec3 p);
		void setVertices(std::vector<Vec3> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(std::vector<Vec2> t);
		void moveBy(Vec3 v);

		int getType();
		bool hitTest(Vec2 p);
		Vec3 getVertex(int index);
		Vec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		std::vector<Vec3> getVertices();
		std::vector<Vec2> getTexCoords();
        void setEdges(ofVec4f _edges);
	
		void setPerspectiveWarping(bool b);
		bool getPerspectiveWarping();
        void setEdgeBlendMode(bool b);
	
		ofRectangle getMeshBoundingBox();
		BaseSurface * clone();

	private:
		void calculateHomography();
        void setupShaders();


		float _matrix[16];
		bool _perspectiveWarping;
        bool _edgeBlendingMode;
		ofMesh _meshCache;
        ofShader edgeBlendShader;
        string glESFragmentShader;
        string glESVertexShader;
        string gl2FragmentShader;
        string gl2VertexShader;
        ofVec4f edges;
};

} // namespace piMapper
} // namespace ofx
