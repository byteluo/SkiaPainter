#include <iostream>
#include "js_engine/engine.h"
#include "canvas/CanvasAdapter.h"

using namespace std;

string readFile(string path) {
	ifstream file;
	file.open(path, ios_base::in);

	if (!file.is_open()) {
		cout << "open file failed!" << endl;
		exit(-1);
	}
	string script;
	string tmp;
	while (getline(file, tmp)) {
		script = script + tmp + "\n";
	}
	file.close();
	return script;
}

void draw(string script) {
	using namespace FinePainter;
	auto engine = make_unique<JsEngine>();
	auto canvasClass = make_shared<JsClass>("Canvas", CanvasConstructor);
	
	registCanvasApi(canvasClass, save, "save");
	registCanvasApi1S2N(canvasClass, fillText, "fillText");
	registCanvasApi1S2N(canvasClass, strokeText, "strokeText");
	registCanvasApi1S(canvasClass, save2Image, "save2Image");
	registCanvasApi4N(canvasClass, strokeRect, "strokeRect");
	registCanvasApi4N(canvasClass, fillRect, "fillRect");
	registCanvasApi4N(canvasClass, clearRect, "clearRect");
	registCanvasApi1N(canvasClass, setLineWidth, "setLineWidth");
	registCanvasApi(canvasClass, stroke, "stroke");
	registCanvasApi(canvasClass, clip, "clip");
	registCanvasApi(canvasClass, fill, "fill");
	registCanvasApi(canvasClass, closePath, "closePath");
	registCanvasApi(canvasClass, beginPath, "beginPath");
	registCanvasApi2N(canvasClass, moveTo, "moveTo");
	registCanvasApi2N(canvasClass, lineTo, "lineTo");
	registCanvasApi4N(canvasClass, rect, "rect");
	registCanvasApi(canvasClass, restore, "restore");
	registCanvasApi1N(canvasClass, rotate, "rotate");
	registCanvasApi2N(canvasClass, scale, "scale");
	registCanvasApi2N(canvasClass, translate, "translate");
	registCanvasApi6N(canvasClass, setTransform, "setTransform");
	registCanvasApi6N(canvasClass, bezierCurveTo, "bezierCurveTo");
	registCanvasApi1S(canvasClass, setFillStyle, "setFillStyle");
	registCanvasApi1S(canvasClass, setStrokeStyle, "setStrokeStyle");

	canvasClass->addMethod("arc", Arc);
	engine->addFunction("Log", Log);
	engine->addJsClass(canvasClass);
	engine->execute(script.c_str());
}


int main() {
	cout << "Start Render" << endl;
	string script = readFile("d:/draw/echarts.js");
	draw(script);
	cout << "Render Finished" << endl;
}
