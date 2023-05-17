#ifndef   _SKIA_PAINTER_V8_
#define   _SKIA_PAINTER_V8_

#include "libplatform/libplatform.h"
#include "v8-context.h"
#include "v8-initialization.h"
#include "v8-isolate.h"
#include "v8-local-handle.h"
#include "v8-primitive.h"
#include "v8-script.h"
#include "v8-template.h"
#include "v8-exception.h"
#include "v8-external.h"
#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "WINMM.lib")
#pragma comment( lib, "psapi.lib" )
#pragma comment( lib, "v8_monolith.lib" )
#pragma comment( lib, "dbghelp.lib" )

#include <vector>
#include <functional>

namespace FinePainter{

	using namespace v8;
	using namespace std;

	struct JsMethod {
		const char* name;
		FunctionCallback method;
		JsMethod(const char* name, const FunctionCallback& method) {
			this->name = name;
			this->method = method;
		}
	};
	
	class JsClass {
	private:
		const char* className;
		FunctionCallback constructor;
		vector<shared_ptr<JsMethod>> methods;
	public:
		
		JsClass(const char* className, const FunctionCallback& callback) {
			this->className = className;
			constructor = callback;
		}

		void addMethod(const char* name, const FunctionCallback& method) {
			auto m = make_shared<JsMethod>(name, method);
			methods.push_back(m);
		}

		const char* getClassName() {
			return className;
		}

		FunctionCallback& getConstructor() {
			return constructor;
		}

		vector<shared_ptr<JsMethod>>& getMethods() {
			return methods;
		}
	};

	class JsEngine {
	private:
		Isolate* isolate;
		unique_ptr<Platform> platform = platform::NewDefaultPlatform();
		vector<shared_ptr<JsClass>> class_vector;
		Isolate::CreateParams create_params;
		vector<shared_ptr<JsMethod>> methods;
	public:
		Isolate* getIsolate() {
			return isolate;
		}
		JsEngine() {
			V8::InitializeICUDefaultLocation("main");
			V8::InitializeExternalStartupData("main");
			V8::InitializePlatform(platform.get());
			V8::Initialize();
			create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
			isolate = Isolate::New(create_params);
		}
		void execute(const char* script) {
			Isolate::Scope isolate_scope(isolate);
			HandleScope handle_scope(isolate);
			v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
		
			for (int i = 0; i < class_vector.size(); i++) {
				shared_ptr<JsClass> clz = class_vector.at(i);
				Local<FunctionTemplate> constructor = FunctionTemplate::New(isolate, clz->getConstructor());
				
				Handle<ObjectTemplate> proto = constructor->PrototypeTemplate();
				vector<shared_ptr<JsMethod>> methods = clz->getMethods();
				
				for (int i = 0; i < methods.size(); i++) {
					shared_ptr<JsMethod> method = methods.at(i);
					proto->Set(isolate, method->name, FunctionTemplate::New(isolate, method->method));
				}

				global->Set(isolate, clz->getClassName(), constructor);
				Handle<ObjectTemplate> instance = constructor->InstanceTemplate();
				instance->SetInternalFieldCount(1);
			}

			for (int i = 0; i < methods.size(); i++) {
				shared_ptr<JsMethod> method = methods.at(i);
				global->Set(isolate, method->name, FunctionTemplate::New(isolate, method->method));
			}
	
			Local<Context> context = Context::New(isolate, NULL, global);
			Local<String> source = String::NewFromUtf8(isolate, script).ToLocalChecked();
			auto v = Script::Compile(context, source).ToLocalChecked()->Run(context);
			if (v.IsEmpty()) {
				std::cout << "V8 Runtime Error!" << endl;
			}
		}

		void addJsClass(shared_ptr<JsClass> v8Class) {
			class_vector.push_back(v8Class);
		}
		void addFunction(const char* name, const FunctionCallback& method) {
			auto m = make_shared<JsMethod>(name, method);
			methods.push_back(m);
		}
		~JsEngine() {
			isolate->Dispose();
			V8::Dispose();
			delete create_params.array_buffer_allocator;
		}
	};
}

#endif