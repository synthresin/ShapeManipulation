#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/svg/Svg.h"
#include "cinder/svg/SvgGl.h"
#include "cinder/cairo/Cairo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ShapeManipulationApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
    svg::DocRef     mDoc;
    Shape2d         mShape;
    
    Vec2i           mMousePos;
    float           mRot;
};

Shape2d getCenteredShape2dfromSVGDoc(svg::DocRef doc) {
    Shape2d s = doc->getShape();
    s.transform( MatrixAffine2f::makeTranslate( -doc->getSize()/2 ) );
    return s;
}

void ShapeManipulationApp::setup()
{
    mDoc = svg::Doc::create( loadResource("logoFrag1.svg") );
    mShape = getCenteredShape2dfromSVGDoc(mDoc);
}

void ShapeManipulationApp::mouseDown( MouseEvent event )
{
    
}

void ShapeManipulationApp::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void ShapeManipulationApp::update()
{
}

void ShapeManipulationApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    gl::color(0, 0, 0);
    Vec2f dirVec = mMousePos - getWindowCenter();
    float angle = toDegrees(atan2(dirVec.y, dirVec.x)) + 90;
    
    gl::pushMatrices();
        gl::translate(getWindowCenter());
        gl::rotate(angle);
        gl::drawSolid(mShape);
    gl::popMatrices();
}

CINDER_APP_BASIC( ShapeManipulationApp, RendererGl )
