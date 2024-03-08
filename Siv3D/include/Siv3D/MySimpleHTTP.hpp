//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "HashTable.hpp"
# include "URLView.hpp"
# include "HTTPResponse.hpp"
# include "AsyncHTTPTask.hpp"

namespace s3d
{
	class MemoryWriter;
	class IWriter;

	namespace MySimpleHTTP
	{

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ（バイト）
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, String name, const void* src, size_t size, FilePathView filePath);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ（バイト）
		/// @param writer ダウンロードしたデータの格納先
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, String name, const void* src, size_t size, MemoryWriter& writer);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ（バイト）
		/// @param writer ダウンロードしたデータの格納先の IWriter インタフェース
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, String name, const void* src, size_t size, IWriter& writer);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ（バイト）
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @return 非同期ダウンロードを管理するオブジェクト
		[[nodiscard]]
		AsyncHTTPTask PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, FilePathView filePath);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ（バイト）
		/// @return 非同期ダウンロードを管理するオブジェクト
		/// @remark ダウンロード内容はメモリに保存されます。ダウンロード完了後、`AsyncHTTPTask::getBlob()` または `AsyncHTTPTask::getBlobReader()` で取得します。
		[[nodiscard]]
		AsyncHTTPTask PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size);
	}
}
