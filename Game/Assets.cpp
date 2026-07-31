#include "Assets.h"
using namespace nu;
using namespace std;

namespace assets {

	Mesh playerMesh{ { Vector2{-2, -4}, Vector2{-2, 4}, Vector2{5, 0}, Vector2{-2,-4}, Vector2{-4, -2}, Vector2{-4, 2}, Vector2{-2, 4} }, Color{1.0f, 0.8f, 0.4f} };
	Model playerModel{ vector<Mesh>{playerMesh} };

	Mesh bulletMesh{{Vector2{ -1, -1 },Vector2{ 1, 0 }, Vector2{ -1, 1 }, Vector2{ -1, -1 } },Color{ 0.5f, 0.3f, 0.4f }};
	Model bulletModel(vector<Mesh>{bulletMesh});

	Mesh enemyMesh{ { Vector2{ 3, 0 }, Vector2{ -1, -3 }, Vector2{ 0, 0 }, Vector2{ -1, 3 }, Vector2{ 3, 0 }}, Color{1.0f, 0.0f, 0.0f} };
	Model enemyModel(vector<Mesh>{enemyMesh});

	Mesh astroidMesh{ { Vector2{ 3, 0 }, Vector2{ 0, -3 }, Vector2{ -2, -1 }, Vector2{ 0, 0 }, Vector2{ -2, 1 }, Vector2{ 0, 3 }, Vector2{ 3, 0 }}, Color{1.0f, 0.0f, 0.0f} };
	Model astroidModel(vector<Mesh>{astroidMesh});

	Mesh medPackMesh{ {Vector2{ -1, -3 }, Vector2{ 1, -3 }, Vector2{ 1, -1 }, Vector2{ 3, -1 }, Vector2{ 3, 1 }, Vector2{ 1, 1 }, Vector2{ 1, 3 }, Vector2{ -1, 3 }, Vector2{ -1, 1 }, Vector2{ -3, 1 }, Vector2{ -3, -1 }, Vector2{ -1, -1 }, Vector2{ -1, -3 } }, Color{ 0.0f, 1.0f, 0.0f } };
	Model medPackModel(vector<Mesh>{medPackMesh});


	}