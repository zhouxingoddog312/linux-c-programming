#ifndef _QUOTE_H
#define _QUOTE_H
#include <iostream>
#include <string>
class Quote
{
	public:
		Quote()=default;
		Quote(const std::string &book,double sales_price):price(sales_price),bookNo(book) {}
		std::string isbn() const {return bookNo;}
		virtual double net_price(std::size_t n) const {return n*price;}
		virtual std::string debug() const {return "bookNo="+bookNo+"\n"+"price="+std::to_string(price);}
		virtual ~Quote()=default;
	protected:
		double price=0.0;
	private:
		std::string bookNo;
};
class Disc_quote:public Quote
{
	public:
		Disc_quote()=default;
		Disc_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),quantity(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const=0;
		virtual std::string debug() const override
		{
			return Quote::debug()+"\n"+"quantity="+std::to_string(quantity)+"\n"+"discount="+std::to_string(discount);
		}
	protected:
		std::size_t quantity=0;
		double discount=0.0;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n);
class Bulk_quote:public Disc_quote
{
	public:
		Bulk_quote()=default;
		using Disc_quote::Disc::quote;
		virtual double net_price(std::size_t n) const override
		{
			if(n>=quantity)
				return n*(1-discount)*price;
			else
				return n*price;
		}
};
class Limit_quote:public Disc_quote
{
	public:
		Limit_quote()=default;
		using Disc_quote::Disc::quote;
		virtual double net_price(std::size_t n) const override
		{
			if(n<=quantity)
				return n*(1-discount)*price;
			else
				return quantity*(1-discount)*price+(n-quantity)*price;
		}
};
#endif
