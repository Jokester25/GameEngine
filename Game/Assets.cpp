#include "Assets.h"
using namespace nu;
using namespace std;

namespace Assets {

	Mesh playerMesh{ { Vector2{-2, -4}, Vector2{-2, 4}, Vector2{5, 0}, Vector2{-2,-4}, Vector2{-4, -2}, Vector2{-4, 2}, Vector2{-2, 4} }, Color{1.0f, 0.8f, 0.4f} };
	
	Model playerModel{ vector<Mesh>{playerMesh} };
}