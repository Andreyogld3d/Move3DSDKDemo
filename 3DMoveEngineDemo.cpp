
#include "IUserCallback.h"
#include "IEngine.h"
#include "IScene.h"
#include "IDisplayedObject.h"
#include "IMaterial.h"
#include <vector>

#ifdef _DEBUG
#pragma comment(lib, "3DMoveEngined.lib")
#else
#pragma comment(lib, "3DMoveEngine.lib")
#endif

struct SomeUserCallback : public IUserCallback {
	float* test;
	IScene* sc;

	virtual void Update(float dt)
	{
		IDisplayedObject* obj = sc->GetObjectByName("Storojka");
		IMaterial* mat = obj->GetObjectMaterial();
		float offset = 500.0f * dt;
		float v[] = { 0.0f, 250.0f * dt, 0.0f };
		mat->SetShaderConstantValue("test", v, 3);
	}
	virtual void Setup(IScene* scene)
	{
		sc = scene;
		std::vector<IDisplayedObject *> objects;
		scene->GetObjects(objects);
		IDisplayedObject* obj = scene->GetObjectByName("Storojka");
		IMaterial* mat = obj->GetObjectMaterial();
		float v[] = { 10.0f, 30.0f, 40.0f };
		mat->SetShaderConstantValue("test", v, 3);
	}
	SomeUserCallback() : test(NULL), sc(NULL)
	{
	}
};

int __stdcall WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInstance, char* lpCmdLine, int nWinMode)
{
	IEngine* engine = IEngine::GetEngine();

	SomeUserCallback someUserCallback;

	engine->Run(0, 0, 0, false, &someUserCallback);
}