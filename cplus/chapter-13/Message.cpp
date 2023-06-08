#include "Message.h"
void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}
void Message::add_to_Folders(const Message &m)
{
	for(auto f:m.folders)
		f->addMsg(this);
}
void Message::remove_from_Folders()
{
	for(auto f:folders)
		f->remMsg(this);
}
Message::Message(const Message &m):contents(m.contents),folders(m.folders)
{
	add_to_Folders(m);
}
Message & Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents=rhs.contents;
	folders=rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
Message::~Message()
{
	remove_from_Folders();
}
void swap(Message &lhs,Message &rhs)
{
	using std::swap;
	for(auto f:lhs.folders)
		f->remMsg(&lhs);
	for(auto f:rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.contents,rhs.contents);
	swap(lhs.folders,rhs.folders);
	for(auto f:lhs.folders)
		f->addMsg(&lhs);
	for(auto f:rhs.folders)
		f->addMsg(&rhs);
}



void Folder::add_to_Messages(const Folder &f)
{
	for(auto m:f.messages)
		m->addfolder(this);
}
void Folder::remove_from_Messages()
{
	for(auto m:messages)
		m->folders.erase(this);
}
void Folder::save(Message &m)
{
	messages.insert(&m);
	m.addfolder(this);
}
void Folder::remove(Message &m)
{
	messages.erase(&m);
	m.remfolder(this);
}
Folder & Folder::operator=(const Folder &rhs)
{
	remove_from_Messages();
	messages=rhs.messages;
	add_to_Messages(rhs);
	return *this;
}
Folder::~Folder()
{
	remove_from_Messages();
}
