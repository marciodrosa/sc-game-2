#pragma once

#include <SDL.h>

namespace sc
{
	/** Base class for elements that can be rendered. */
	class RenderElement
	{
	public:
		RenderElement();
		virtual ~RenderElement();

		/** The X coordinate of the pivot, defaults to 0 (left). */
		int PivotX;

		/** The Y coordinate of the pivot, defaults to 0 (top). */
		int PivotY;

		/** The width of the element. */
		int Width;

		/** The height of the element. */
		int Height;

		/** Aligns the pivot (X and Y) to the center of the element. */
		void CenterPivot();

		/** Aligns the X coordinate of the pivot to the left edge. */
		void LeftPivot();

		/** Aligns the X coordinate of the pivot to the right edge. */
		void RightPivot();

		/** Aligns the Y coordinate of the pivot to the top edge. */
		void TopPivot();

		/** Aligns the Y coordinate of the pivot to the bottom edge. */
		void BottomPivot();

		/** Creates and returns the rect to draw this element. */
		SDL_Rect GetRect(int x, int y);

		/** Renders this element at position x and y. */
		void RenderAt(SDL_Renderer* renderer, int x, int y);

		/** Function that must be implemented to render this element in the given rederer. */
		virtual void Render(SDL_Renderer* renderer, SDL_Rect& rect) = 0;
	};
}
