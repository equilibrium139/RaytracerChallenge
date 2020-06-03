#include "Canvas.h"

#include <algorithm>

std::string CanvasToPPM(const Canvas& canvas)
{
	std::string fileContents;
	const int headerLength = 17;
	// canvas.width * canvas.height is the # of pixels, each pixel is represented by 12 chars max:
	// 100 100 100 (9 digits + 2 spaces between + whitespace after = 12)
	const int maxBodyLength = canvas.width * canvas.height * 12;
	fileContents.reserve(headerLength + maxBodyLength);
	fileContents.append("P3\n" + 
						std::to_string(canvas.width)  + " " + std::to_string(canvas.height) + "\n" +
						"255 ");
	const int maxLineLength = 69; // 70 - 1 for newline character
	int currentLineLength = 4; //255 + " "
	const auto& pixels = canvas.GetPixels();
	std::string colorInPPMFormat;
	for (const auto& color : canvas.GetPixels())
	{
		colorInPPMFormat = ColorToPPMFormat(color);
		int lineLength = currentLineLength + colorInPPMFormat.size() + 1;
		if (lineLength > maxLineLength)
		{
			fileContents += "\n" + colorInPPMFormat + " ";
			currentLineLength = colorInPPMFormat.size() + 1;
		}
		else if (lineLength == maxLineLength)
		{
			fileContents += colorInPPMFormat + "\n";
			currentLineLength = 0;
		}
		else
		{
			fileContents += colorInPPMFormat + " ";
			currentLineLength += colorInPPMFormat.size() + 1;
		}
	}
	fileContents.push_back('\n');
	return fileContents;
}

std::string ColorToPPMFormat(const Color& color)
{
	return std::to_string((int)(std::clamp(color.r, 0.0f, 1.0f) * 255)) + " " 
		 + std::to_string((int)(std::clamp(color.g, 0.0f, 1.0f) * 255)) + " "
		 + std::to_string((int)(std::clamp(color.b, 0.0f, 1.0f) * 255));
}
