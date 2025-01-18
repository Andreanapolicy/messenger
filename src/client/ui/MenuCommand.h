#pragma once

namespace client::ui
{
enum class MenuCommand
{
	ShowChats, // show all available chats
	OpenChat, // open selected chat
	Exit, // exit from app
	Message, // message
	Unknown, // unknown command
};
}