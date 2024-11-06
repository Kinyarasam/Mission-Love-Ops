#include <stdio.h>
#include <SDL2/SDL.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/**
 * main - Entry point.
 *
 * Return: Always 0
 *          otherwise 1.
 */
int main(void)
{
	if (SDL_Init((SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0))
	{
		fprintf(stderr, "SDL Initialization error: %s\n", SDL_GetError());
		return (1);
	}

	SDL_Window * window = SDL_CreateWindow("Mission: Love Ops",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "SDL Window Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "SDL Renderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Event e;
	int quit = 0;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, "scripts/test_script.lua") != LUA_OK) {
		printf("Lua Error: %s\n", lua_tostring(L, -1));
		lua_close(L);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}

	lua_close(L);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}
