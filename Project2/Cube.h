#include "GameAsset.h"
#include "IInterpolator.h"
#include "TriangularPyramidAsset.h"


#ifndef CUBE_H_
#define CUBE_H_

class Cube : public GameAsset {
public:
	Cube();
	Cube(float x, float y, float z, string shader);
	~Cube();

	virtual void update();
	virtual void draw();
	void setInterpolator(shared_ptr<IInterpolator> li);
private:
	shared_ptr<IInterpolator> li;
	shared_ptr<Vector3>		vecPos;
	shared_ptr<Point3>        pos;
};

#endif // CUBE_H_