#include "ChatMessage.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace common::infrastructure
{

const char* ChatMessage::GetData() const
{
	return m_data;
}

char* ChatMessage::GetData()
{
	return m_data;
}

std::size_t ChatMessage::GetSize() const
{
	return HEADER_LENGTH + m_bodyLength;
}

const char* ChatMessage::GetBody() const
{
	return m_data + HEADER_LENGTH;
}

char* ChatMessage::GetBody()
{
	return m_data + HEADER_LENGTH;
}

std::size_t ChatMessage::GetBodySize() const
{
	return m_bodyLength;
}

void ChatMessage::SetBodySize(std::size_t new_length)
{
	m_bodyLength = new_length;
	if (m_bodyLength > MAX_BODY_LENGTH)
	{
		m_bodyLength = MAX_BODY_LENGTH;
	}
}

bool ChatMessage::DecodeHeader()
{
	char header[HEADER_LENGTH + 1] = "";
	std::strncat(header, m_data, HEADER_LENGTH);
	m_bodyLength = std::atoi(header);
	if (m_bodyLength > MAX_BODY_LENGTH)
	{
		m_bodyLength = 0;
		return false;
	}
	return true;
}

void ChatMessage::EncodeHeader()
{
	char header[HEADER_LENGTH + 1] = "";
	std::sprintf(header, "%4d", static_cast<int>(m_bodyLength));
	std::memcpy(m_data, header, HEADER_LENGTH);
}
} // namespace common::infrastructure