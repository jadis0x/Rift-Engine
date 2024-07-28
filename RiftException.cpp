#include "RiftException.h"
#include <sstream>

RiftException::RiftException(int line, const char* file) noexcept
{
	this->line = line;
	this->file = file;
}

const char* RiftException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* RiftException::GetType() const noexcept
{
	return "Rift Exception";
}

int RiftException::GetLine() const noexcept
{
	return line;
}

const std::string& RiftException::GetFile() const noexcept
{
	return file;
}

std::string RiftException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[FILE] " << file << std::endl << "[LINE] " << line;

	return oss.str();
}
