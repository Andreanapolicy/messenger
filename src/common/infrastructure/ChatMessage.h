#include <cstdlib>

namespace common::infrastructure
{
class ChatMessage
{
public:
	static const int HEADER_LENGTH = 4;
	static const int MAX_BODY_LENGTH = 1024;

	ChatMessage() = default;

	const char* GetData() const;

	char* GetData();

	std::size_t GetSize() const;

	const char* GetBody() const;

	char* GetBody();

	std::size_t GetBodySize() const;

	void SetBodySize(std::size_t new_length);

	bool DecodeHeader();

	void EncodeHeader();

private:
	char m_data[HEADER_LENGTH + MAX_BODY_LENGTH];
	std::size_t m_bodyLength = 0;
};
} // namespace common::infrastructure