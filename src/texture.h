#ifndef texture_h_
#define texture_h_

class Texture
{
public:
	unsigned int id;
	int width, height, nch;
	void load(const char *filename);
	void bind(GLenum target);
};


#endif
