#include <math.h>
#include <cstdio>
#include <cstdlib>
#include "monadWindow.h"

void circle(MonadWindow reference,int points){
	float tangle = (float)((points - 2) * 180);
	float angle = tangle/points;
	MonadWindow mon = mkMonadWindow(reference);

	for(int i = 0; i< points;i++)
		monadTriangle(mon,angle);

	unmkMonadWindow(mon);
}

float lin( float dh, float h){
	return (h - dh)/h;
}

float cuple( float dh, float h ){
	return sqrt( (h*h  - dh*dh) )/h;
}

void sphere(MonadWindow reference, float radius, int slices, int stacks) {
	MonadWindow nw = mkMonadWindow(reference);
    monadScale(nw, radius, radius, radius);
	stacker(nw,slices,stacks,1, cuple);
	monadRotate(nw,180,1.0,0.0,0.0);
	stacker(nw, slices,stacks,1, cuple);
	unmkMonadWindow(nw);
}

void cone(MonadWindow reference, float radius, float height, int slices, int stacks) {
    float normalizeHeight = height/radius;
    MonadWindow nw = mkMonadWindow(reference);
    monadScale(nw, radius, radius, radius);
    stacker(nw, slices, stacks, normalizeHeight, lin);
    unmkMonadWindow(nw);
}

int main(int argc, char **argv) {
	MonadWindow reference = mkMonadWindow();
    cone(reference, 2, 4, 10, 1);
	print_trace(reference,"figure.xml","figure");

	unmkMonadWindow(reference);
	return 1;
}
