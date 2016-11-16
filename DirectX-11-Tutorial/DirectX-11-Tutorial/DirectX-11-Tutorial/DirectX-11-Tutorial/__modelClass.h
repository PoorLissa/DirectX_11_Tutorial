#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

// The fstream library is now included to handle reading from the model text file.
#include <fstream>
#include <d3d11.h>
#include <d3dx10math.h>

#include "__textureClass.h"

using namespace std;


class ModelClass {
 private:
/*
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
*/
/*
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
*/
	 struct VertexType {
		 D3DXVECTOR3 position;
		 D3DXVECTOR2 texture;
		 D3DXVECTOR3 normal;
	 };

	 // The next change is the addition of a new structure to represent the model format.It is called ModelType.
	 // It contains position, texture, and normal vectors the same as our file format does.
	 struct ModelType {
		 float x, y, z;
		 float tu, tv;
		 float nx, ny, nz;
	 };

 public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device *);					// ��� ������� ��������� �� �����������
	bool Initialize(ID3D11Device *, WCHAR *);			// ��� ���������������
	bool Initialize(ID3D11Device *, char *, WCHAR *);	// ��� �������� ������ �� �����
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	// The ModelClass now lso has a GetTexture function so it can pass its own texture resource to shaders that will draw this model
	ID3D11ShaderResourceView* GetTexture();

 private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	// ModelClass has now a private LoadTexture() and ReleaseTexture() for loading and releasing the texture that will be used to render this model
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	//We also have two new functions to handle loading and unloading the model data from the text file.
	bool LoadModel(char*);
	void ReleaseModel();

 private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffer;

	int m_vertexCount;
	int m_indexCount;

	// The m_Texture variable is used for loading, releasing, and accessing the texture resource for this model.
	TextureClass* m_Texture;

	// The final change is a new private variable called m_model which is going to be an array of the new private structure ModelType.
	// This variable will be used to read in and hold the model data before it is placed in the vertex buffer.
	ModelType* m_model;
};

#endif
