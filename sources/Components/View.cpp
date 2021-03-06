#include "View.h"

using namespace Nodable;

View::View()
{
	setMember("__class__", "View");
	
	// set default colors
	colors[ColorType_Fill]             = {1.0f, 1.0f, 1.0f, 1.0f};
	colors[ColorType_Border]           = {0.2f, 0.2f, 0.2f, 1.0f};
	colors[ColorType_BorderHighlights] = {1.0f, 1.0f, 1.0f, 0.8f};
	colors[ColorType_Shadow]           = {0.0f, 0.0f, 0.0f, 0.2f};
}

void View::setColor(ColorType_ _type, ImColor _color)
{
	colors[_type] = _color;
}

ImColor View::getColor(ColorType_ _type)
{
	return colors[_type];
}

void View::DrawRectShadow (ImVec2 _topLeftCorner, ImVec2 _bottomRightCorner, float _borderRadius, int _shadowRadius, ImVec2 _shadowOffset, ImColor _shadowColor)
{
	ImVec2 itemRectMin(_topLeftCorner.x + _shadowOffset.x, _topLeftCorner.y + _shadowOffset.y);
	ImVec2 itemRectMax(_bottomRightCorner.x + _shadowOffset.x, _bottomRightCorner.y + _shadowOffset.y);
	ImVec4 color       = _shadowColor;
	color.w /= _shadowRadius;
	auto borderRadius  = _borderRadius;

	// draw N concentric rectangles.
	for(int i = 0; i < _shadowRadius; i++)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		draw_list->AddRectFilled(itemRectMin, itemRectMax, ImColor(color), borderRadius);

		itemRectMin.x -= 1.0f;
		itemRectMin.y -= 1.0f;

		itemRectMax.x += 1.0f;
		itemRectMax.y += 1.0f;

		borderRadius += 1.0f;
	}
}

void View::ShadowedText(ImVec2 _offset, ImColor _shadowColor, const char* _format, ...)
{
	// draw first the shadow
	auto p = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(p.x + _offset.x, p.y + _offset.y));	

	va_list args;
    va_start(args, _format);
    ImGui::TextColored(_shadowColor, _format, args);
	ImGui::SetCursorPos(p);
    ImGui::Text(_format, args);
    va_end(args);
}

void View::ColoredShadowedText(ImVec2 _offset, ImColor _textColor, ImColor _shadowColor, const char* _format, ...)
{
	// draw first the shadow
	auto p = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(p.x + _offset.x, p.y + _offset.y));	

	va_list args;
    va_start(args, _format);
    ImGui::TextColored(_shadowColor, _format, args);
	ImGui::SetCursorPos(p);
    ImGui::TextColored(_textColor, _format, args);
    va_end(args);
}