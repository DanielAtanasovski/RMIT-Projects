#include "Player.h"
#include "../manager/Input.h"
#include "../math/Math.h"
#include "Bullet.h"
#include <iostream>

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

Player::Player(Game& game, Vector3 position, float rotation) : game(game), CollidableEntity(position, rotation)
{
	if (!loadModel()) {
		if (!err.empty()) {
			std::cerr << err << std::endl;
		}
		exit(1);
	}
}

void Player::setBodyMaterial() {
	GLfloat spec[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat shininess[] = { 128.0 };
	GLfloat emission[] = { 0, 0, 0, 0.0 };
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
}

void Player::setWindowMaterial() {
	GLfloat spec[] = { 0,0,0,0 };
	GLfloat diffuse[] = { 0.1, 0.1, 0.1, 0.1 };
	GLfloat shininess[] = { 50.0 };
	GLfloat emission[] = { 0, 0, 0, 0.0 };
	GLfloat ambient[] = { 0, 0, 0, 0.6 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
}

void Player::draw()
{
	if (dead)
		return;
	
	glPushMatrix();
	
	// Translate Model
	glTranslatef(position.x, position.y, position.z);


	glRotatef(-game.getCamera().getYaw() - 90, 0, 1, 0);
	glRotatef(game.getCamera().getPitch(), 1, 0, 0);

	
	// Ship Model
	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Rotate it up
	glRotatef(0, 0, 0, 1); // Rotate to face forward

	// Rotation
	drawShip();
	
	//glutSolidSphere(1.0, 20, 16);
	glPopMatrix();

	// Draw Bounding Circle
	//CollidableEntity::drawDebugCollisionCircle();

	glPopMatrix();

	bulletsDraw();
}

void Player::bulletsDraw()
{
	for (Bullet* bullet : bullets) {
		bullet->draw();
	}
}

void Player::bulletsUpdate(float deltaTime)
{
	for (Bullet* bullet : bullets) {
		bullet->update(deltaTime);
		if (bullet->getDead())
			std::cout << "Dead!" << std::endl;
	}
}

void Player::drawShip() {
	// Ship
	glPushMatrix();

	// Based on example provided https://github.com/tinyobjloader/tinyobjloader#example-code-deprecated-api
	for (size_t s = 0; s < shapes.size(); s++) { // loop shapes
		size_t index_offset = 0;
		//std::vector<Vector3> faceVertexPoints = std::vector<Vector3>();
		//std::vector<Vector3> faceNormalPoints = std::vector<Vector3>();
		//std::vector<Vector2> faceTexPoints = std::vector<Vector2>();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, game.getShipTexture());
		glBegin(GL_TRIANGLES);
		// Loop faces within shape
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
			//faceVertexPoints.clear();
			//faceNormalPoints.clear();
			//std::cout << shapes[s].name << std::endl;

			// Set Material for current shape
			if (shapes[s].name == SHAPE_WINDOW_NAME) {
				setWindowMaterial();
				//std::cout << "Apply Window" << std::endl;
			}
			else {
				setBodyMaterial();
			}

			// loop over vertexs within face

			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				// Normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
					glNormal3f(nx, ny, nz);
				}

				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					glTexCoord2f(tx, ty);
				}

				// Vertex point
				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
				glVertex3f(vx, vy, vz);
				
				//faceVertexPoints.push_back(Vector3(vx, vy, vz));
				//faceNormalPoints.push_back(Vector3(nx, ny, nz));
				//faceTexPoints.push_back(Vector2(tx, ty));
			}

			//glEnable(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, game.getShipTexture());
			//glBegin(GL_TRIANGLES);
			//for (size_t i = 0; i < faceVertexPoints.size(); i++)
			//{
			//	// Draw Triangle
			//	//glColor3f(1.0f, 1.0f, 1.0f);
			//	glNormal3f(faceNormalPoints[i].x, faceNormalPoints[i].y, faceNormalPoints[i].z);
			//	glTexCoord2f(faceTexPoints[i].x, faceTexPoints[i].y);
			//	glVertex3f(faceVertexPoints[i].x, faceVertexPoints[i].y, faceVertexPoints[i].z);
			//}
			//glEnd();
			//glDisable(GL_TEXTURE_2D);

			index_offset += fv;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	glPopMatrix();
}

void Player::update(float deltaTime) {

	if (dead)
		return;

	if (Input::onPressed('z')) {
		distFromCamera += DISTANCE_FROM_CAMERA_STEP * deltaTime;
	}
	else if (Input::onPressed('x')) {
		distFromCamera -= DISTANCE_FROM_CAMERA_STEP * deltaTime;
	}
	distFromCamera = Math::clamp(distFromCamera, MIN_DISTANCE_FROM_CAMERA, MAX_DISTANCE_FROM_CAMERA);

	// Update Position
	position = game.getCamera().getPosition() + (game.getCamera().getForward() * distFromCamera) + (game.getCamera().getUp() * -3);

	if (Input::onMouseLeftDown())
		shoot(deltaTime);

	bulletsUpdate(deltaTime);
	bulletsCheck(deltaTime);
}

void Player::shoot(float deltaTime)
{
	if (canShoot) {
		bullets.push_back(new Bullet(game, position, game.getCamera().getForward()));
		canShoot = false;
	}
	else {
		currentFireRate += deltaTime;
		if (currentFireRate >= FIRE_RATE) {
			currentFireRate = 0;
			canShoot = true;
		}
	}
		
}

void Player::bulletsCheck(float deltaTime)
{
	auto i = bullets.begin();

	while (i != bullets.end()) {
		if ((*i)->getDead()) {
			i = bullets.erase(i);
		}
		else {
			++i;
		}
	}

	//for (size_t i = 0; i < bullets.size(); i++)
	//{
	//	if (bullets[i]->getDead()) {
	//		std::cout << "WOAH DEAD" << std::endl;
	//	}
	//	else {
	//		std::cout << "Not dead?" << std::endl;
	//	}
	//}
}

bool Player::loadModel() {
	// Based on example provided https://github.com/tinyobjloader/tinyobjloader#example-code-deprecated-api
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, SHIP_MODEL_PATH.c_str())) 
		return false;
	return true;
}