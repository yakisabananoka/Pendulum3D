#pragma once
#include <filesystem>

/// @brief 画像
class Image
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	Image(const std::filesystem::path& path);
	virtual ~Image();

	/// @brief 通常の描画
	/// @param x X座標
	/// @param y Y座標
	/// @param transFlg 透過するか
	void Draw(float x, float y, bool transFlg) const;

	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

	Image(Image&&) = default;
	Image& operator=(Image&&) = default;

protected:
	/// @brief コンストラクタ
	/// @param handle ハンドル
	Image(int handle);

	int handle_;		//ハンドル
};

