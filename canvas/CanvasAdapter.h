#ifndef   _CANVAS_ADAPTER_
#define   _CANVAS_ADAPTER_   

#include "ICanvas.h"
#include "SkiaCanvas.h"
#include "js_engine/engine.h"

using namespace v8;

double getNumberArg(const FunctionCallbackInfo<Value>& args, int index) {
	return args[index]->NumberValue(args.GetIsolate()->GetCurrentContext()).ToChecked();
}

const char* getStringArg(const FunctionCallbackInfo<Value>& args, int index) {
	v8::String::Utf8Value value(args.GetIsolate(), args[index]);
	return *value ? *value : "<string conversion failed>";
}

void Hook(const char* name, const FunctionCallbackInfo <Value>& args) {
	cout << name;
	for (int i = 0; i < args.Length(); i++) {
		cout << "  " << getStringArg(args, i);
	}
	cout << endl;
}

#define setHook(name, args)\
	Hook(name, args)\
	
/*
* #define setHook(name, args)\
* ;
*/

// 使用宏定义替代反射，但又想保留性能，只能暂时这么写了，希望可以找到一个更好的方法
#define registCanvasApi(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method();\
	});\

#define registCanvasApi1S(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getStringArg(args, 0));\
	});\

#define registCanvasApi1N(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getNumberArg(args, 0));\
	});\

#define registCanvasApi1S2N(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getStringArg(args, 0), getNumberArg(args, 1), getNumberArg(args, 2));\
	});\

#define registCanvasApi2N(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getNumberArg(args, 0), getNumberArg(args, 1));\
	});\

#define registCanvasApi4N(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getNumberArg(args, 0), getNumberArg(args, 1), getNumberArg(args, 2), getNumberArg(args, 3));\
	});\

#define registCanvasApi6N(clz, method, name) \
	clz->addMethod(name, [](const FunctionCallbackInfo <Value>& args) {  \
		Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);\
		setHook(name, args);\
		canvas->method(getNumberArg(args, 0), getNumberArg(args, 1), getNumberArg(args, 2), getNumberArg(args, 3), getNumberArg(args, 4), getNumberArg(args, 5));\
	});\


void CanvasConstructor(const FunctionCallbackInfo <Value>& args) {
	Isolate* isolate = args.GetIsolate();
	Local<Context> context = isolate->GetCurrentContext();
	// 这个 Canvas 可能有内存泄露的风险
	Canvas* obj = new SkiaCanvas<double>(getNumberArg(args, 0), getNumberArg(args, 1));
	args.This()->SetAlignedPointerInInternalField(0, obj);
}

void Arc(const FunctionCallbackInfo<Value>& args) {
	Canvas* canvas = (Canvas*)args.This()->GetAlignedPointerFromInternalField(0);
	setHook("arc", args); \
	canvas->arc(getNumberArg(args, 0), getNumberArg(args, 1), getNumberArg(args, 2), getNumberArg(args, 3), getNumberArg(args, 4), getNumberArg(args, 5));
}


void Log(const FunctionCallbackInfo<Value>& args) {
	cout << getStringArg(args, 0) << endl;
}

#endif   