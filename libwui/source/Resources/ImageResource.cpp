#include <ui/Resources/ImageResource.hpp>
#include <exception/Exception.h>

#include <pngu.h>
#include <malloc.h>

using namespace UI::Resources;
using namespace std;
using namespace Libwiisys;


ImageResource::ImageResource(const string& imgPath)
{
	data = NULL;
	width = 0;
	height = 0;

	if(imgPath.length() > 0)
	{
			PNGUPROP imgProp;
			IMGCTX ctx = PNGU_SelectImageFromDevice(imgPath.c_str());

			if(ctx)
			{
					int res = PNGU_GetImageProperties(ctx, &imgProp);

					if(res == PNGU_OK)
					{
							int len = imgProp.imgWidth * imgProp.imgHeight * 4;
							if(len%32) len += (32-len%32);
							data = (u8 *)memalign (32, len);

							if(data)
							{
									res = PNGU_DecodeTo4x4RGBA8 (ctx, imgProp.imgWidth, imgProp.imgHeight, data, 255);

									if(res == PNGU_OK)
									{
											width = imgProp.imgWidth;
											height = imgProp.imgHeight;
											DCFlushRange(data, len);
									}
									else
									{
											free(data);
											data = NULL;
									}
							}
					}
					PNGU_ReleaseImageContext (ctx);
			}
	}

	if (!data)
		throw Exception("Error creating image from data.", -1);
}

ImageResource::ImageResource(const u8 * buffer)
{
	width = 0;
	height = 0;
	if(buffer)
	{
			PNGUPROP imgProp;
			IMGCTX ctx = PNGU_SelectImageFromBuffer(buffer);

			if(!ctx)
					return;

			int res = PNGU_GetImageProperties(ctx, &imgProp);

			if(res == PNGU_OK)
			{
					int len = imgProp.imgWidth * imgProp.imgHeight * 4;
					if(len%32) len += (32-len%32);
					data = (u8 *)memalign (32, len);

					if(data)
					{
							res = PNGU_DecodeTo4x4RGBA8 (ctx, imgProp.imgWidth, imgProp.imgHeight, data, 255);

							if(res == PNGU_OK)
							{
									width = imgProp.imgWidth;
									height = imgProp.imgHeight;
									DCFlushRange(data, len);
							}
							else
							{
									free(data);
									data = NULL;
							}
					}
			}
			PNGU_ReleaseImageContext (ctx);
	}
	
	if (!data)
		throw Exception("Error creating image from data.", -1);
}

ImageResource::~ImageResource()
{
	if(data)
	{
		free(data);
		data = NULL;
	}
}

u8* ImageResource::Image()
{
	return data;
}

int ImageResource::Width()
{
	return width;
}

int ImageResource::Height()
{
	return height;
}
