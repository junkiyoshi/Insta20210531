#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> location_list = { glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.25), glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.75) };
	vector<int> loop_count_list = { 1, 5 };

	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

		ofSetColor(39);
		ofSetLineWidth(3);

		ofBeginShape();
		for (int x = 0; x <= 340; x += 1) {

			auto y = ofMap(ofNoise(noise_seed.x, (x * 0.5 + ofGetFrameNum()) * 0.008), 0, 1, -100, 100);

			ofVertex(x, y);

			if (x == 0) {

				ofDrawCircle(x, y, 5);
			}
		}
		ofEndShape();

		ofDrawLine(glm::vec2(0, -100), glm::vec2(0, 100));
		ofDrawLine(glm::vec2(340, -100), glm::vec2(340, 100));

		ofDrawLine(glm::vec2(-10, -50), glm::vec2(10, -50));
		ofDrawLine(glm::vec2(-10, 0), glm::vec2(10, 0));

		ofDrawLine(glm::vec2(-10, 20), glm::vec2(10, 20));
		ofDrawLine(glm::vec2(-10, 70), glm::vec2(10, 70));

		ofTranslate(-180, 0);
		ofNoFill();
		ofSetColor(39);
		ofSetLineWidth(1.5);

		for (int k = 0; k < loop_count_list[i]; k++) {

			if (k > 0) {

				ofSetColor(39);
				ofDrawLine(glm::vec2(180 + k * 6, -100), glm::vec2(180 + k * 6, 100));
			}

			ofPushMatrix();

			auto noise_value = ofNoise(noise_seed.x, (ofGetFrameNum() + k * 6) * 0.008);
			if (noise_value > 0.25 && noise_value < 0.5) { ofRotateX(ofMap(noise_value, 0.25, 0.5, -180, 180)); }
			if (noise_value > 0.6 && noise_value < 0.85) { ofRotateY(ofMap(noise_value, 0.6, 0.85, -180, 180)); }

			ofMesh face, line;
			line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

			this->setRingToMesh(face, line, glm::vec3(), ofMap(k, 0, loop_count_list[i], 120, 50), 20, 10);

			ofSetColor(39);
			face.draw();

			ofSetColor(239);
			line.draw();

			ofPopMatrix();
		}

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& line_target, glm::vec3 location, float radius, float width, float height) {

	int deg_span = 90;
	for (int deg = 45; deg < 400; deg += deg_span) {

		auto face_index = face_target.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		face_target.addVertices(vertices);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2);

		auto line_index = line_target.getNumVertices();

		line_target.addVertices(vertices);

		line_target.addIndex(line_index + 0); line_target.addIndex(line_index + 1);
		line_target.addIndex(line_index + 2); line_target.addIndex(line_index + 3);
		line_target.addIndex(line_index + 4); line_target.addIndex(line_index + 5);
		line_target.addIndex(line_index + 6); line_target.addIndex(line_index + 7);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}