#pragma once
//#include <SDL.h>
#include <string>
#include <map>
#include "FWApplication.h"

class Texture {
public:
	static Texture& instance() {
		static Texture inst;
		return inst;
	}

	SDL_Texture* get(const std::string& name) {
		if (textures.count(name) == 0) {
			auto app = FWApplication::GetInstance();
			auto tex = app->LoadTexture(name);
			textures.insert_or_assign(name, tex);

			return tex;
		}
		else {
			return textures.at(name);
		}
	}

private:
	std::map<std::string, SDL_Texture*> textures;
};

#define tex Texture::instance().get