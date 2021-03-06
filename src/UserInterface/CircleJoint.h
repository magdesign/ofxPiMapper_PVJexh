#pragma once

#include "ofMain.h"
#include "BaseJoint.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {
class CircleJoint : public BaseJoint {

	public:
		CircleJoint();

		void update();
		void draw();
		bool hitTest(Vec2 position);

    protected:
		float radius;
        ofImage circle;
        ofImage circle_filled;
		void setDefaultProperties();

};

} // namespace piMapper
} // namespace ofx
