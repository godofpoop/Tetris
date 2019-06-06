#include "MovementSystem.h"
#include "TetrisGame.h"
#include "HighScoreIO.h"

MovementSystem::MovementSystem()
{
	
}
void MovementSystem::init(SoundSystem& s,RenderSystem& rende)
{
	time = 0;
	speed = 1;
	animation_cycle = 0;
	fallSound = new Sound("sounds/fall.wav",false);
	clearSound = new Sound("sounds/clear.wav",false);
	rotateSound = new Sound("sounds/selection.wav", false);
	renderer = &rende;

	s.addSound(*clearSound);
	s.addSound(*fallSound);
	s.addSound(*rotateSound);
}
void MovementSystem::addEntity(Shape* e)
{
	shapes.push_back(e);
}
void MovementSystem::update(double delta,Shape* active)
{
	time += delta;
	if (time > 1.0 / speed && refresh) {
		if (active->touch) return;
		if (!translate(active, vector2(0, -20),shapes)) {
			active->touch = true;
			fallSound->play();
			remove();
			if (active->position.y > 400) {
				for (int i = 0; i < shapes.size(); i++) {
					renderer->remove(*shapes[i]);
					delete shapes[i];
						
					shapes[i] = nullptr;
				}
				shapes.clear();
				std::cout << "Its over\n";
				HighScoreIO::write(TetrisGame::score, TetrisGame::scores);
				TetrisGame::score = 0;
				TetrisGame::level = 1;
			}
			
		}
		//fall();
		time = 0;
	}
	animation();
	

}
void MovementSystem::animation()
{
	//if ((int)(time * 1000) % 5 != 0) return;
	if (markedtodie.size() == 0) {
		refresh = true;
		fall();
		remove();
		return;
	}
	refresh = false;
	renderer->remove(markedtodie[markedtodie.size() - 1]);
	delete markedtodie[markedtodie.size() - 1];
	markedtodie[markedtodie.size() - 1] = nullptr;
	markedtodie.pop_back();
}
void MovementSystem::fall()
{
	vector<Shape*> s;
	vector<Entity*> temp;
	for (int i = 0; i < shapes.size(); i++) {
		if (!shapes[i]->touch) continue;
		for (int j = 0; j < shapes[i]->entities.size(); j++) {
			if (contains(shapes[i]->entities[j], temp)) continue;
			temp.clear();
			flood(shapes[i]->entities[j], temp);
			s.push_back(new Shape());
			
			s[s.size() - 1]->entities = temp;
		}
	}
	for (int i = 0; i < s.size(); i++) {
		translate(s[i], vector2(0, -20),s);
		s[i]->entities.clear();
		delete s[i];

		s[i] = nullptr;
	}
}
void MovementSystem::flood(Entity* e,vector<Entity*> &temp)
{
	if (contains(e, temp)) return;
	temp.push_back(e);
	for (int i = 0; i < shapes.size(); i++) {
		for (int j = 0; j < shapes[i]->entities.size(); j++) {
			if (e == shapes[i]->entities[j]) continue;
			if (e->position.y == shapes[i]->entities[j]->position.y
				&& e->position.x == shapes[i]->entities[j]->position.x + 20) {
				flood(shapes[i]->entities[j],temp);
			}
			if (e->position.y == shapes[i]->entities[j]->position.y
				&& e->position.x == shapes[i]->entities[j]->position.x - 20) {
				flood(shapes[i]->entities[j],temp);
			}
			if (e->position.x == shapes[i]->entities[j]->position.x
				&& e->position.y == shapes[i]->entities[j]->position.y + 20) {
				flood(shapes[i]->entities[j],temp);
			}
			if (e->position.x == shapes[i]->entities[j]->position.x
				&& e->position.y == shapes[i]->entities[j]->position.y - 20) {
				flood(shapes[i]->entities[j],temp);
			}
		}
	}
}
bool MovementSystem::contains(Shape* s, vector<Shape*> shapes)
{
	bool b = false;
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i] == s) b = true;
	}
	return b;
}
bool MovementSystem::contains(Entity* s, vector<Entity*> shapes)
{
	bool b = false;
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i] == s) b = true;
	}
	return b;
}

bool MovementSystem::translate(Shape *s,vector2 v)
{
	if (s->touch) return false;
	bool b = true;
	for (int j = 0; j < s->entities.size(); j++) {
		vector2 temp = s->entities[j]->position;
		temp.x += v.x;
		temp.y += v.y;
		if (temp.x < 100) b = false;
		if (temp.x > 300) b = false;
		if (temp.y < 190) b = false;
		
		for (int n = 0; n < shapes.size(); n++) {
			if (s == shapes[n]) continue;
			if (!shapes[n]->touch) continue;
			for (int m = 0; m < shapes[n]->entities.size(); m++) {
				if (shapes[n]->entities[m]->position.x == temp.x && shapes[n]->entities[m]->position.y == temp.y) {
					b = false;
				}
			}
		}
	}
	if (b) {
		s->position.x += v.x;
		s->position.y += v.y;
		for (int j = 0; j < s->entities.size(); j++) {
			s->entities[j]->position.x += v.x;
			s->entities[j]->position.y += v.y;
		}
	}
	return b;
}
bool MovementSystem::translate(Shape* s, vector2 v, vector<Shape*> others)
{
	bool b = true;
	for (int j = 0; j < s->entities.size(); j++) {
		vector2 temp = s->entities[j]->position;
		temp.x += v.x;
		temp.y += v.y;
		if (temp.x < 100) b = false;
		if (temp.x > 300) b = false;
		if (temp.y < 190) b = false;

		for (int n = 0; n < others.size(); n++) {
			if (s == others[n]) continue;
			if (others[n] == nullptr) continue;
			for (int m = 0; m < others[n]->entities.size(); m++) {
				if (others[n]->entities[m]->position.x == temp.x && others[n]->entities[m]->position.y == temp.y) {
					b = false;
				}
			}
		}
	}
	if (b) {
		s->position.x += v.x;
		s->position.y += v.y;
		for (int j = 0; j < s->entities.size(); j++) {
			s->entities[j]->position.x += v.x;
			s->entities[j]->position.y += v.y;
		}
	}
	return b;
}

void MovementSystem::remove()
{
	int removed_lines = 0;
	float highest = 0;
	for (int k = 190; k < 800; k += 20) {
		int columns = 0;
		for (int i = 0; i < shapes.size(); i++) {
			if (!shapes[i]->touch) continue;
			for (int j = 0; j < shapes[i]->entities.size(); j++) {
				if (shapes[i]->entities[j]->position.y == k) {
					columns++;
				}
			}
		}
		if (columns > 9) {
			clearSound->play();
			if(!highest) highest = k;
			removed_lines++;
			std::cout << "tetris";
			for (int i = 0; i < shapes.size(); i++) {
				if (!shapes[i]->touch) continue;
				for (int j = 0; j < shapes[i]->entities.size(); j++) {
					if (shapes[i]->entities[j]->position.y == k) {
						shapes[i]->entities[j]->color = vector4(1.0);
						markedtodie.push_back(shapes[i]->entities[j]);
					}
					//shapes[i]->entities[j]->position.y -= 20*removed_lines;
				}
			}
		}
	}
	for (int i = 0; i < markedtodie.size(); i++) {
		int p = 0;
		for (int k = 0; k < shapes.size(); k++) {
			for (int j = 0; j < shapes[k]->entities.size(); j++) {
				if (markedtodie[i] == shapes[k]->entities[j]) {
					
					shapes[k]->entities.erase(shapes[k]->entities.begin() + j-p);
					p++;
					//fall();
				}
			}
		}
		/*renderer->remove(markedtodie[i]);
		delete markedtodie[i];

		markedtodie[i] = nullptr;*/
	}
	//markedtodie.clear();
	if (!removed_lines) return;
	std::cout << removed_lines << std::endl;
	TetrisGame::score += pow(2,removed_lines)*100;
	if (TetrisGame::score >= pow(2, TetrisGame::level) * 500) {
		TetrisGame::level++;
	}
	/*for (int i = 0; i < shapes.size(); i++) {
		for (int j = 0; j < shapes[i]->entities.size(); j++) {
			if (shapes[i]->entities[j]->position.y > highest) {
				shapes[i]->entities[j]->position.y -= removed_lines * 20;
			}
		}
	}*/
	
}
void MovementSystem::rotate(Shape *s)
{
	if (s->touch) return;
	rotateSound->play();
	bool b = true;
	for (int i = 0; i < s->entities.size(); i++) {
		vector2 temp = s->entities[i]->position - s->position;
		float t = -temp.x;
		temp.x = temp.y;
		temp.y = t;
		temp.x += s->position.x;
		temp.y += s->position.y;

		if (temp.x < 100) translate(s, vector2(20, 0));
		if (temp.x > 280) translate(s, vector2(-20, 0));
		if (temp.y < 190) b = false;
		for (int j = 0; j < shapes.size(); j++) {
			if (s == shapes[j]) continue;
			for (int k = 0; k < shapes[j]->entities.size(); k++) {
				if (shapes[j]->entities[k]->position.x == temp.x && shapes[j]->entities[k]->position.y == temp.y) {
					b = false;
				}
			}
		}
	}
	if (b) {
		s->rotation++;
		if (s->rotation > 3) s->rotation = 0;
		for (int i = 0; i < s->entities.size(); i++) {
			s->entities[i]->position.x -= s->position.x;
			s->entities[i]->position.y -= s->position.y;
			float t = -s->entities[i]->position.x;
			s->entities[i]->position.x = s->entities[i]->position.y;
			s->entities[i]->position.y = t;
			s->entities[i]->position.x += s->position.x;
			s->entities[i]->position.y += s->position.y;
		}
	}
}
MovementSystem::~MovementSystem()
{
}
