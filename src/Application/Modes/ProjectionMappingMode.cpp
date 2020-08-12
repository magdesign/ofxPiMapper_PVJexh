#include "ProjectionMappingMode.h"

namespace ofx {
namespace piMapper {

ProjectionMappingMode::ProjectionMappingMode(){
	_surfaceScaleBeforeTransform = 1.0f;
	_bDrawLayerPanel = true;
}

ProjectionMappingMode * ProjectionMappingMode::_instance = 0;

ProjectionMappingMode * ProjectionMappingMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::ProjectionMappingMode();
	}
	return _instance;
}

void ProjectionMappingMode::setup(Application *app){
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getLayerPanelWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getProjectionEditorWidget().setSurfaceManager(app->getSurfaceManager());
}

void ProjectionMappingMode::update(Application * app){
	Gui::instance()->getProjectionEditorWidget().update();
	Gui::instance()->getScaleWidget().update();
}

void ProjectionMappingMode::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	Gui::instance()->getProjectionEditorWidget().draw();
	
	// Draw scale widget. The size of the widget is being set on surface select.
	BaseSurface * selectedSurface = app->getSurfaceManager()->getSelectedSurface();
	if(selectedSurface != 0){
		Gui::instance()->getScaleWidget().draw();
	}
	
	if(_bDrawLayerPanel){
		Gui::instance()->getLayerPanelWidget().draw();
	}
	
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

void ProjectionMappingMode::toggleLayerPanel(){
	_bDrawLayerPanel = !_bDrawLayerPanel;
}

void ProjectionMappingMode::onKeyPressed(Application * app, ofKeyEventArgs & args){
	switch(args.key){

	 case 't':
		 app->createSurface(SurfaceType::TRIANGLE_SURFACE);
		 break;

	 case 'q':
		 app->createSurface(SurfaceType::QUAD_SURFACE);
		 break;

	 case 'g':
		 app->createSurface(SurfaceType::GRID_WARP_SURFACE);
		 break;

	 //case 'x':
	//	 app->createSurface(SurfaceType::HEXAGON_SURFACE);
	//	 break;
			
	 case 'r':
		app->createSurface(SurfaceType::CIRCLE_SURFACE);
		break;

	 case 'd':
		 app->eraseSurface(app->getSurfaceManager()->getSelectedSurfaceIndex());
		 break;
	 
	 case 'p':
		 app->togglePerspective();
		 break;
	 
	 //case 'n':
	//	 app->addGridRow();
	//	 break;
	
	 case 'm':
		 app->removeGridRow();
		 break;
	 
	 //case 'v':
	//	 app->addGridColumn();
	//	 break;
			
	 //case 'b':
	//	 app->removeGridColumn();
	//	 break;
			
	 case '.':
		 app->selectNextSurface();
		 break;
			
	 case ',':
		 app->selectPrevSurface();
		 break;
			
	 case 'k':
		 app->selectNextVertex();
		 break;
	 
	 case 'l':
		 app->selectPrevVertex();
		 break;
	 
	 case '8':
		 app->moveSelection(Vec3(0.0f, -1.0f, 0.0f));
		 break;

	 case 'x':
            app->moveSelection(Vec3(0.0f, -10.0f, 0.0f));
		break;

	 case '9':
		 app->moveSelection(Vec3(0.0f, 1.0f, 0.0f));
		 break;

  	 case 'b':
           app->moveSelection(Vec3(0.0f, 10.0f, 0.0f));
            break;


	case '7':
           app->moveSelection(Vec3(-1.0f, 0.0f, 0.0f));
           break;

	 case 'v':
		app->moveSelection(Vec3(-10.0f, 0.0f, 0.0f));
		 break;

	 case '0':
                 app->moveSelection(Vec3(1.0f, 0.0f, 0.0f));
                 break;


	 case 'n':
		app->moveSelection(Vec3(10.0f, 0.0f, 0.0f));
		 break;

	 case 'w':
		 app->togglePause();
		 break;
			
	 case '5':
		 app->setNextSource();
		 break;
	
	 case 'a':
		 app->duplicateSurface();
		 break;
			
	 case 'h': // Move selected surface up the layer stack
		 app->moveLayerUp();
		 break;
		
	 case 'j': // Move selected surface down the layer stack
		 app->moveLayerDown();
		 break;
			
	 case 'o': // Scale surface up
		 app->scaleUp();
		 break;

	 case 'i': // Scale surface down
		 app->scaleDown();
		 break;

	 case 'y':
		 toggleLayerPanel();
		 break;

     case 'e':
         Gui::instance()->getProjectionEditorWidget().toggleEdgeBlendMode();
       break;

	/*
	 case 'n': // Set next preset
		 app->getSurfaceManager()->setNextPreset();
		 break;
	*/
			
	 default:
		 break;
	}
}

void ProjectionMappingMode::onMousePressed(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMousePressed(args);
	
	CircleJoint * hitJoint = 0;
    EdgeBlendJoint * hitEdgeBlendJoint = 0;
	int hitJointIndex = -1;
	BaseSurface * hitSurface = 0;

	hitJoint = Gui::instance()->getProjectionEditorWidget().hitTestJoints(Vec2(args.x, args.y));
    hitEdgeBlendJoint = Gui::instance()->getProjectionEditorWidget().hitTestEdgeBlendJoints(Vec2(args.x, args.y));
	
    if(hitJoint){
		for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
			if((*Gui::instance()->getProjectionEditorWidget().getJoints())[i] == hitJoint){
				hitJointIndex = i;
				break;
			}
		}
    }else if(hitEdgeBlendJoint) {
        for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
            if((*Gui::instance()->getProjectionEditorWidget().getEdgeBlendJoints())[i] == hitEdgeBlendJoint){
                hitJointIndex = i;
                break;
            }
        }
    }else{
		for(int i = app->getSurfaceManager()->size() - 1; i >= 0; --i){
			if(app->getSurfaceManager()->getSurface(i)->hitTest(Vec2(args.x, args.y))){
				hitSurface = app->getSurfaceManager()->getSurface(i);
				break;
			}
		}
	}
	
	if(Gui::instance()->getScaleWidget().inside(args.x, args.y)){
		//
	}else if(hitJoint){
		hitJoint->select();
		hitJoint->startDrag();
		Gui::instance()->notifyJointPressed(args, hitJointIndex);
    }else if(hitEdgeBlendJoint){
        hitEdgeBlendJoint->select();
        hitEdgeBlendJoint->startDrag();
        Gui::instance()->notifyEdgeBlendJointPressed(args, hitJointIndex);
	}else if(hitSurface){
		_clickPosition = Vec2(args.x, args.y); // TODO: redesign this so we can use a kind of
												  //       display stack.
		_bSurfaceDrag = true; // TODO: Should be something like `hitSurface->startDrag()`
		Gui::instance()->notifySurfacePressed(args, hitSurface);
	}else{
		Gui::instance()->notifyBackgroundPressed(args);
	}
}

void ProjectionMappingMode::onMouseReleased(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMouseReleased(args);
	_bSurfaceDrag = false; // TODO: handle this locally
	Gui::instance()->getProjectionEditorWidget().stopDragJoints();
}

void ProjectionMappingMode::onMouseDragged(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMouseDragged(args);
	Gui::instance()->getProjectionEditorWidget().mouseDragged(args);
	
	// TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
	if(_bSurfaceDrag){
		Vec2 mousePosition = Vec2(args.x, args.y);
		Vec2 distance = mousePosition - _clickPosition;
		Gui::instance()->getProjectionEditorWidget().moveSelectedSurface(Vec3(
			distance.x,
			distance.y,
			0.0f));
		_clickPosition = mousePosition;
	}
}

void ProjectionMappingMode::onJointPressed(Application * app, GuiJointEvent & e){
	app->getCmdManager()->exec(new SelVertexCmd(app->getSurfaceManager(), e.jointIndex));
	app->getCmdManager()->exec(new MvSurfaceVertCmd(
		e.jointIndex,
		app->getSurfaceManager()->getSelectedSurface()));
}

void ProjectionMappingMode::onEdgeBlendJointPressed(Application * app, GuiJointEvent & e){
    //app->getCmdManager()->exec(new SelEdgeBlendJointCmd(&(Gui::instance()->getProjectionEditorWidget()), e.jointIndex));
    //cout << " selected joint: " <<  Gui::instance()->getProjectionEditorWidget().getSelectedEdgeBlendJoint() << endl;
    app->getCmdManager()->exec(new MvSurfaceEdgeBlendJointCmd(
        e.jointIndex,
        &(Gui::instance()->getProjectionEditorWidget()) ));
}

void ProjectionMappingMode::onSurfacePressed(Application * app, GuiSurfaceEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != e.surface){
		app->getCmdManager()->exec(new SelSurfaceCmd(app->getSurfaceManager(), e.surface ));
	}
	
	app->getCmdManager()->exec(new StartDragSurfaceCmd(e.surface));
}

void ProjectionMappingMode::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != 0){
		app->getCmdManager()->exec(new DeselectSurfaceCmd(app->getSurfaceManager()));
	}
}

void ProjectionMappingMode::onGuiEvent(Application * app, GuiEvent & e){
	
	// Scale widget now. More widgets later.
	if(e.widget == &Gui::instance()->getScaleWidget()){
		if(e.args.type == e.args.Pressed){
			if(app->getSurfaceManager()->getSelectedSurface() == 0){
				return;
			}
			
			_surfaceScaleBeforeTransform =
				app->getSurfaceManager()->getSelectedSurface()->getScale();
		}else if(e.args.type == e.args.Released){
			if(app->getSurfaceManager()->getSelectedSurface() == 0){
				return;
			}
			
			if(_surfaceScaleBeforeTransform !=
				app->getSurfaceManager()->getSelectedSurface()->getScale()){
				
				app->getCmdManager()->exec(new ScaleSurfaceFromToCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					_surfaceScaleBeforeTransform,
					app->getSurfaceManager()->getSelectedSurface()->getScale()));
			}
		}else if(e.args.type == e.args.Dragged){
			app->getSurfaceManager()->getSelectedSurface()->scaleTo(e.widget->getScale());
		}
	}
}

} // namespace piMapper
} // namespace ofx
