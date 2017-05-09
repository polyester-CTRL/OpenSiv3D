﻿# include <Siv3D.hpp>

void Main()
{
	// 空のテクスチャ
	Texture texture;

	double t = 0.0;

	while (System::Update())
	{
		if (KeyF.down())
		{
			Graphics::SetFullScreen(true, Size(1920, 1080), 1);
		}

		if (KeyW.down())
		{
			Graphics::SetFullScreen(false, Size(1280, 720));
		}

		// 何かがドロップされた
		if (DragDrop::HasNewFilePaths())
		{
			const auto items = DragDrop::GetDroppedFilePaths();

			// テクスチャとしてロードに成功したら
			if (const Texture tmp{ items[0].path })
			{
				// テクスチャを置き換える
				texture = tmp;

				Log << texture.size();

				// ウィンドウをテクスチャと同じサイズにする
				Window::Resize(texture.size(), false);
			}
		}

		if (texture)
		{
			texture.draw();
		}

		t += System::DeltaTime();

		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t * 30_deg;

			const Vec2 pos = Circular(200, angle) + Window::Center();

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
	}
}