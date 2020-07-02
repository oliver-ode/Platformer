#include "GameObject.hpp"

GameObject::GameObject() {}
GameObject::~GameObject() {}

void GameObject::setSrc(int x, int y, int w, int h) {
	srcRect.x = x;
	srcRect.y = y;
	srcRect.w = w;
	srcRect.h = h;
}

void GameObject::setDest(int x, int y, int scale) {
	xpos = x;
	ypos = y;
	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w*scale;
	destRect.h = srcRect.h*scale;
}

void GameObject::setTexture(const char* texture_file, SDL_Renderer* ren) {
	SDL_Surface* surf = IMG_Load(texture_file);
	texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
}

void GameObject::setHitbox(int x, int y, int w, int h) {
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = w;
	hitbox.h = h;
}

void GameObject::render(SDL_Renderer* ren, bool flip) {
	if (flip) SDL_RenderCopyEx(ren, texture, &srcRect, &destRect, NULL, nullptr, SDL_FLIP_HORIZONTAL);
	else SDL_RenderCopy(ren, texture, &srcRect, &destRect);
}

void GameObject::setPos(int x, int y) {
	xpos = x;
	ypos = y;
	destRect.x = x;
	destRect.y = y;
}

