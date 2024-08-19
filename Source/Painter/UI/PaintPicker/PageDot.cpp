#include "Painter/UI/PaintPicker/PageDot.h"

void UPageDot::SetActive(bool Active)
{
	DotImage->SetOpacity(Active ? 1.0 : 0.25);
}
