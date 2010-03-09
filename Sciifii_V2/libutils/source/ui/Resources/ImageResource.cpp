#include <ui/Resources/ImageResource.hpp>

#include <pngu.h>
#include <malloc.h>

using namespace UI::Resources;
using namespace std;

ImageResource::ImageResource(const string& imgPath, const u8 * defaultImage)
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

	if (!data) //use defaultImage data instead
	{
			width = 0;
			height = 0;
			if(defaultImage)
			{
					PNGUPROP imgProp;
					IMGCTX ctx = PNGU_SelectImageFromBuffer(defaultImage);

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
	}
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
