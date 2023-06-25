#ifndef _MESSAGE_H
#define _MESSAGE_H
#include <string>
#include <set>
class Folder;
class Message
{
	friend class Folder;
	friend void swap(Message &,Message &);
	public:
		explicit Message(const std::string &str=""):contents(str) {}
		Message(const Message &);
		Message(Message &&m):contents(std::move(m.contents)) {move_Folders(&m);}
		Message & operator=(const Message &);
		Message & operator=(Message &&);
		~Message();
		void save(Folder &);
		void remove(Folder &);
	private:
		std::string contents;
		std::set<Folder *> folders;
		void add_to_Folders(const Message &);
		void remove_from_Folders();
		void addfolder(Folder *f) {folders.insert(f);}
		void remfolder(Folder *f) {folders.erase(f);}
		void move_Folders(Message *m);
};
class Folder
{
	friend void swap(Message &,Message &);
	friend class Message;
	public:
		Folder()=default;
		Folder(const Folder &f):messages(f.messages) {add_to_Messages(f);}
		Folder(Folder &&f) {move_Messages(&f);}
		Folder & operator=(const Folder &);
		Folder & operator=(Folder &&);
		~Folder();
		void save(Message &);
		void remove(Message &);
	private:
		std::set<Message *> messages;
		void addMsg(Message *m) {messages.insert(m);}
		void remMsg(Message *m) {messages.erase(m);}
		void add_to_Messages(const Folder &);
		void remove_from_Messages();
		void move_Messages(Folder *);
};
#endif
