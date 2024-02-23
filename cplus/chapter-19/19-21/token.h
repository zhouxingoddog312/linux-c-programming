#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include "Sales_data.h"
using std::string;
class Token
{
	friend std::ostream & operator<<(std::ostream &,const Token &);
	public:
		Token():tok(INT),ival(0) {}
		Token(const Token &t):tok(t.tok) {copyUnion(t);}
		Token(Token &&t):tok(std::move(t.tok)) {moveUnion(std::move(t));}
		~Token()
		{
			if(tok==STR)
				sval.~string();
			else if(tok==SAL)
				salval.~Sales_data();
		}
		Token & operator=(const Token &);
		Token & operator=(Token &&);
		Token & operator=(const std::string &);
		Token & operator=(const Sales_data &);
		Token & operator=(int);
		Token & operator=(char);
		Token & operator=(double);
	private:
		enum {INT,CHAR,DBL,STR,SAL} tok;
		union
		{
			int ival;
			char cval;
			double dval;
			std::string sval;
			Sales_data salval;
		};
		void copyUnion(const Token &);
		void moveUnion(Token &&);
		void free()
		{
			if(tok==STR)
				sval.~string();
			if(tok==SAL)
				salval.~Sales_data();
		}
};
std::ostream & operator<<(std::ostream &,const Token &);
#endif
