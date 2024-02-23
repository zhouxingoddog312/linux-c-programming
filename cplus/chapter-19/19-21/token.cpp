#include "token.h"
void Token::copyUnion(const Token &t)
{
	switch(tok)
	{
		case Token::INT:
			ival=t.ival;
			break;
		case Token::CHAR:
			cval=t.cval;
			break;
		case Token::DBL:
			dval=t.dval;
			break;
		case Token::STR:
			new (&sval) std::string(t.sval);
			break;
		case Token::SAL:
			new (&salval) Sales_data(t.salval);
			break;
	}
}
void Token::moveUnion(Token &&t)
{
	switch(tok)
	{
		case Token::INT:
			ival=t.ival;
			break;
		case Token::CHAR:
			cval=t.cval;
			break;
		case Token::DBL:
			dval=t.dval;
			break;
		case Token::STR:
			new (&sval) std::string(std::move(t.sval));
			break;
		case Token::SAL:
			new (&salval) Sales_data(std::move(t.salval));
			break;
	}
}
Token & Token::operator=(int i)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=INT;
	ival=i;
	return *this;
}
Token & Token::operator=(char ch)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=CHAR;
	cval=ch;
	return *this;
}
Token & Token::operator=(double d)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=DBL;
	dval=d;
	return *this;
}
Token & Token::operator=(const std::string &str)
{
	if(tok==STR)
		sval=str;
	else if(tok==SAL)
	{
		salval.~Sales_data();
		tok=STR;
		new (&sval) std::string(str);
	}
	else
	{
		tok=STR;
		new (&sval) std::string(str);
	}
	return *this;
}
Token & Token::operator=(const Sales_data &sales)
{
	if(tok==SAL)
		salval=sales;
	else if(tok==STR)
	{
		sval.~string();
		tok=SAL;
		new (&salval) Sales_data(sales);
	}
	else
	{
		tok=SAL;
		new (&salval) Sales_data(sales);
	}
	return *this;
}
Token & Token::operator=(const Token &t)
{
	switch(tok)
	{
		case Token::STR:
			if(t.tok==STR)
				sval=t.sval;
			else
			{
				sval.~string();
				tok=t.tok;
				copyUnion(t);
			}	
			break;
		case Token::SAL:
			if(t.tok==SAL)
				salval=t.salval;
			else
			{
				salval.~Sales_data();
				tok=t.tok;
				copyUnion(t);
			}
			break;
		default:
			tok=t.tok;
			copyUnion(t);
	}
	return *this;
}
Token & Token::operator=(Token &&t)
{
	if(this!=&t)
	{
		free();
		tok=std::move(t.tok);
		moveUnion(std::move(t));
	}
	return *this;
}
std::ostream & operator<<(std::ostream &os,const Token &t)
{
	switch(t.tok)
	{
		case Token::INT:
			std::cout<<t.ival;
			break;
		case Token::CHAR:
			std::cout<<t.cval;
			break;
		case Token::DBL:
			std::cout<<t.dval;
			break;
		case Token::STR:
			std::cout<<t.sval;
			break;
		case Token::SAL:
			std::cout<<t.salval;
			break;
	}
	return os;
}
