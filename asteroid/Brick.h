#pragma once
#include"libs.h"
#include"Shader.h"
#include"ball.h"

class Brick;

struct Node {
	glm::vec2 position;
	struct Node* next;
	bool solid;
};
class posLinkList {
	struct Node* head;
	struct Node* curNode;
	int count = 0;
public:
	posLinkList() {
		head = NULL;
		curNode = head;
	}
	void addNode(glm::vec2 pos1) {
		count++;
		if (head == NULL) {
			struct Node* tempNode = new Node({ pos1,NULL ,true});
			head = tempNode;
			head->next = NULL;
			curNode = head;
			return;
		}
		struct Node* tempNode = new Node({ pos1,NULL,true });
		tempNode->next = NULL;
		curNode->next = tempNode;
		curNode = tempNode;
	}
	bool checkOverlap(glm::vec2 vector1, glm::vec2 vector2, float brick_width, float brick_height) {
		if (abs(vector1.x - vector2.x) < brick_width/2 && (abs(vector1.y - vector2.y) < brick_height/2)) {
			return true;
		}
		return false;
	}
	bool checkColision(glm::vec2 pos1,float brick_width, float brick_height) {
		struct Node* temp = this->getHead();
		int incr = 0;
		bool flag = false;
		struct Node* prev = NULL;
		struct Node* deleteNode = NULL;
		for (temp; temp != NULL; temp = temp->next) {
			if (deleteNode != NULL) {
				if (deleteNode->solid) {
					flag = true;
				}
				count--;
				delete deleteNode;
				deleteNode = NULL;
			}
			incr++;
			if (checkOverlap(temp->position, glm::vec2(pos1.x, pos1.y), brick_width, brick_height)) {
				if (prev == NULL) {
					struct Node* tempNode = temp->next;
					//delete head;
					deleteNode = head;
					head = tempNode;
					continue;
				}
				prev->next = temp->next;
				//delete temp;
				deleteNode = temp;
				prev = temp;
				continue;
			}
			prev = temp;
			
		}
		if (deleteNode) {
			if (deleteNode->solid) {
				flag = true;
			}
			count--;
			delete deleteNode;
			
		}
		return flag;
	}
	inline struct Node* getHead() {
		return head;
	}
	inline int getcount() {
		return count;
	}
	~posLinkList() {
		struct Node* posl=NULL;
		for (head; head != NULL; head = head->next) {
			if (posl != NULL) {
				delete posl;
				posl = NULL;
			}
			posl = head;
		}
	}

};

class RectData {
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	RectData() {
	}
	void initRectData(float width,float height){
		float offset = 0.06f;
		float farWid = 2 * (width - offset);
		float vertices_box[16]{
			0.f,2*( height - offset),0.f,1.f,
			0.f,0.f,0.f,0.f,
			2*( width - offset),0.f,1.f,0.f,
			2*( width - offset),2*( height - offset),1.f,1.f
		};
		unsigned int noOfVertices = sizeof(vertices_box) / (4 * sizeof(float));
		GLuint indVert[] = {
			2,1,0,
			3,2,0
		};
		glBindVertexArray(0);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, noOfVertices * 4 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
	}
	~RectData() {
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);

	}
};

class Brick {
	//static std::vector<glm::vec2> position;
	static posLinkList position;
public:
	static RectData somData;
	static Texture* texture;
	static unsigned int posbo;
	static float brick_width;
	static float brick_height;
	Brick(int x,int y,int row,int col) {
		float unitStepX = row / (float)2;
		float normIndexX = (x - unitStepX) / (float)unitStepX;
		float unitStepY = col / (float)2;
		float normIndexY = (y - unitStepY) / (float)unitStepY;
		glm::vec2 posFin = glm::vec2(normIndexX, normIndexY);
		position.addNode(posFin);
	}
	static void initTex() {
		texture = new Texture("objfile/floor.png", GL_TEXTURE_2D, 0);
		somData.initRectData(brick_width, brick_height);
	}
	static void initData(Shader* shady) {
		
		struct Node* head = position.getHead();
		int incr = 0;
		for (head; head != NULL; head = head->next) {
			std::string temp = "offsets[" + std::to_string(incr) + "]";
			shady->setUniform2f(temp.c_str(), head->position);
			incr++;
		}

		/*for (int i = 0; i < position.size(); i++) {
			std::string temp = "offsets[" + std::to_string(i) + "]";
			shady->setUniform2f(temp.c_str(), position[i]);
		}*/
		
		/*glBindVertexArray(somData.vao);
		glGenBuffers(1, &posbo);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(glm::vec2), position.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(1, 1);*/
	}
	static void Draw(Shader* shady) {
		texture->bind();
		shady->setUniform1i("texture0", texture->getTextureUnit());
		shady->Use();
		glBindVertexArray(somData.vao);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, position.getcount());
	}
	static bool checkOverlap(glm::vec2 vector1, glm::vec2 vector2) {
		if (abs(vector1.x - vector2.x) < 2 * brick_width && (abs(vector1.y - vector2.y) < 2 * brick_height)) {
			return true;
		}
		return false;
	}
	static void detectCollision(Ball* ball) {
		if (position.checkColision(ball->position, brick_width, brick_height)) {
			ball->changeVelY();
		}
		/*struct Node* head = position.getHead();
		int incr = 0;
		struct Node* prev = NULL;
		for (head; head != NULL; head = head->next) {
			if (checkOverlap(head->position, glm::vec2(ball->position.x, ball->position.y))) {
				itArr.push_back(it);
			}
			std::string temp = "offsets[" + std::to_string(incr) + "]";
			shady->setUniform2f(temp.c_str(), head->position);
			incr++;
		}

		std::vector<std::vector<glm::vec2>::iterator> itArr;
		for (auto it = position.begin(); it!= position.end(); it++) {
			if (checkOverlap(*it, glm::vec2(ball->position.x, ball->position.y))) {
				itArr.push_back(it);
			}
		}
		for (int i = 0; i < 1; i++) {
			position.erase(itArr[i]);
		}*/
	}
	static void clearData() {
		delete texture;
		position.~posLinkList();
	}
	~Brick() {
		//glDeleteBuffers(1, &posbo);
	}
};

