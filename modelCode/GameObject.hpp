#ifndef GameObject_hpp
#define GameObject_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class GameObject {

public:
	GameObject();
	~GameObject();

	SDL_Rect getSrc() const { return srcRect; }
	SDL_Rect getDest() const { return destRect; }
	SDL_Rect getHitbox() { return hitbox; }
	SDL_Texture* getTexture() const { return texture; }
	
	void setHitbox(int x, int y, int w, int h);
	void setSrc(int x, int y, int w, int h);
	void setDest(int x, int y, int scale);
	void setTexture(const char* texture_file, SDL_Renderer* ren);
	void setPos(int x, int y);
	void render(SDL_Renderer* ren, bool flip);

	int xpos, ypos, xvel, yvel;

	bool isSolid = false;
	bool isTrap = false;

private:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect, hitbox;
};

#endif // !GameObject
