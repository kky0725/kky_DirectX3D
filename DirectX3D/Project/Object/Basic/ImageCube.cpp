#include "Framework.h"
#include "ImageCube.h"

ImageCube::ImageCube()
{
	_size = { 1.0f, 1.0f };
	CreateFaces();
}

ImageCube::~ImageCube()
{
}

void ImageCube::Render()
{
	for (Quad* face : _faces)
		face->Render();
}

void ImageCube::CreateFaces()
{
	//Foward


	//Backward


	//Left


	//Right


	//Top


	//Bottom


}

void ImageCube::CreateFace(Vector3 roation)
{
	Quad* quad = new Quad(_size);
	quad->SetParent(this);


}
