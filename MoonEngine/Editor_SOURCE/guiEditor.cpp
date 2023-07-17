#include "guiEditor.h"
#include "../Engine_SOURCE/MnMesh.h"
#include "../Engine_SOURCE/MnResources.h"
#include "../Engine_SOURCE/MnTransform.h"
#include "../Engine_SOURCE/MnMeshRenderer.h"
#include "../Engine_SOURCE/MnMaterial.h"
#include "../Engine_SOURCE/MnRenderer.h"

#include "MnGridScript.h"

namespace gui
{
	using namespace Mn::enums;
	std::vector<Widget*> Editor::_Widgets = {};
	std::vector<EditorObject*> Editor::_EditorObjects = {};
	std::vector<DebugObject*> Editor::_DebugOjbects = {};

	void Editor::Initialize()
	{
		_DebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mn::Mesh> mesh
			= Mn::Resources::Find<Mn::Mesh>(L"DebugRect");
		std::shared_ptr<Mn::Material> material
			= Mn::Resources::Find<Mn::Material>(L"DebugMaterial");

		_DebugOjbects[(UINT)eColliderType::Rect] = new DebugObject();
		_DebugOjbects[(UINT)eColliderType::Rect]->AddComponent<Mn::Transform>();
		Mn::MeshRenderer* mr
			= _DebugOjbects[(UINT)eColliderType::Rect]->AddComponent<Mn::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		mesh = Mn::Resources::Find<Mn::Mesh>(L"DebugCircle");

		_DebugOjbects[(UINT)eColliderType::Circle] = new DebugObject();
		_DebugOjbects[(UINT)eColliderType::Circle]->AddComponent<Mn::Transform>();
		mr	= _DebugOjbects[(UINT)eColliderType::Circle]->AddComponent<Mn::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		//EditorObject* grid = new EditorObject();
		//grid->SetName(L"Grid");

		//mr = grid->AddComponent<Mn::MeshRenderer>();
		//mr->SetMesh(Mn::Resources::Find<Mn::Mesh>(L"RectMesh"));
		//mr->SetMaterial(Mn::Resources::Find<Mn::Material>(L"GridMaterial"));
		//Mn::GridScript* gridSc = grid->AddComponent<Mn::GridScript>();
		//gridSc->SetCamera(renderer::cameras[0]);

		//_EditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{
		for (EditorObject* obj : _EditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : _EditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)Mn::graphics::eDSType::Less];
		//Mn::graphics::GetDevice()->BindDepthStencilState(ds.Get());


		for (EditorObject* obj : _EditorObjects)
		{
			obj->Render();
		}

		for (const Mn::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshs.clear();
	}
	void Editor::Release()
	{
		for (auto widget : _Widgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : _EditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : _DebugOjbects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}
	void Editor::DebugRender(const Mn::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = _DebugOjbects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		Mn::Transform* tr = debugObj->GetComponent<Mn::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->Position(pos);
		tr->Scale(mesh.scale);
		tr->Rotation(mesh.rotation);

		tr->LateUpdate();

		Mn::Camera* mainCamara = renderer::mainCamera;

		Mn::Camera::SetGpuViewMatrix(mainCamara->GetGpuViewMatrix());
		Mn::Camera::SetGpuProjectionMatrix(mainCamara->GetGpuProjectionMatrix());

		debugObj->Render();
	}
}