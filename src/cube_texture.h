#ifndef cube_texture_h_
#define cube_texture_h_

#include "texture.h"

class CubeTexture : public Texture {
public:
	CubeTexture();
	CubeTexture *load(const char *const *filenames);
};

#endif
