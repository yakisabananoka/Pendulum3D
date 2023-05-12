#include <DxLib.h>
#include "Image.h"

Image::Image(const std::filesystem::path& path) :
	Image(LoadGraph(path.string().c_str()))
{
}

Image::~Image()
{
	DeleteGraph(handle_);									//画像の削除
}

void Image::Draw(float x, float y, bool transFlg) const
{
	DrawGraph(static_cast<int>(x), static_cast<int>(y), handle_, transFlg);			//描画
}

Image::Image(int handle) :
	handle_(handle)
{
}
